#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/pwm.h"
#include "ssd1306.h"

// Definição dos pinos utilizados
#define LED_R_PIN 13  // LED vermelho
#define LED_G_PIN 11  // LED verde
#define LED_B_PIN 12  // LED azul
#define BTN_A_PIN 5   // Botão de controle
#define BTN_EMG_PIN 6 // Botão de emergência
#define BUZZER1_PIN 10 // Buzzer 1
#define BUZZER2_PIN 9  // Buzzer 2

// Configuração da interface I2C para comunicação com o display OLED
#define I2C_PORT i2c1
#define I2C_SDA 15
#define I2C_SCL 14

ssd1306_t tela; // Estrutura do display OLED

// Função para inicializar o display OLED
void inicia_oled() {
    i2c_init(I2C_PORT, 400 * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);
    ssd1306_init(&tela, 128, 64, 0x3C, I2C_PORT);
}

// Função para exibir mensagens no display OLED com contagem regressiva
void exibir_mensagem(const char *linha1, int tempo) {
    for (int i = tempo; i >= 0; i--) {
        if (gpio_get(BTN_EMG_PIN) == 0) return; // Verifica se o botão de emergência foi pressionado
        ssd1306_clear(&tela);
        ssd1306_draw_string(&tela, 5, 20, 1, linha1);
        char buffer[16];
        sprintf(buffer, "Tempo: %d seg", i);
        ssd1306_draw_string(&tela, 5, 40, 1, buffer);
        ssd1306_show(&tela);
        sleep_ms(1000);
    }
}

// Funções para controle do semáforo
void SinalAberto() {
    gpio_put(LED_R_PIN, 0);
    gpio_put(LED_G_PIN, 1);
    gpio_put(LED_B_PIN, 0);
    exibir_mensagem("SINAL ABERTO", 7);
}

void SinalAtencao() {
    gpio_put(LED_R_PIN, 1);
    gpio_put(LED_G_PIN, 1);
    gpio_put(LED_B_PIN, 0);
    exibir_mensagem("SINAL DE ATENCAO", 3);
}

void SinalFechado() {
    gpio_put(LED_R_PIN, 1);
    gpio_put(LED_G_PIN, 0);
    gpio_put(LED_B_PIN, 0);
    exibir_mensagem("SINAL FECHADO", 7);
}

// Função para ativar a emergência
void Emergencia() {
    ssd1306_clear(&tela);
    ssd1306_draw_string(&tela, 10, 30, 1, "!!! EMERGENCIA !!!");
    ssd1306_show(&tela);
    
    while (gpio_get(BTN_EMG_PIN) == 0) {
        // Piscar LED azul e vermelho alternadamente
        for (int i = 0; i < 5; i++) {
            gpio_put(LED_R_PIN, 1);
            gpio_put(LED_G_PIN, 0);
            gpio_put(LED_B_PIN, 1);
            sleep_ms(100);
            gpio_put(LED_R_PIN, 0);
            gpio_put(LED_B_PIN, 1);
            sleep_ms(100);
        }
        
        // Ativar buzzer com PWM
        for (int i = 0; i < 3; i++) {
            pwm_set_gpio_level(BUZZER1_PIN, 1000);
            pwm_set_gpio_level(BUZZER2_PIN, 500);
            sleep_ms(150);
            pwm_set_gpio_level(BUZZER1_PIN, 500);
            pwm_set_gpio_level(BUZZER2_PIN, 1000);
            sleep_ms(150);
            pwm_set_gpio_level(BUZZER1_PIN, 0);
            pwm_set_gpio_level(BUZZER2_PIN, 0);
        }
    }
    ssd1306_clear(&tela);
    ssd1306_show(&tela);
}

int main() {
    stdio_init_all();
    
    // Inicialização dos pinos GPIO
    gpio_init(LED_R_PIN);
    gpio_set_dir(LED_R_PIN, GPIO_OUT);
    gpio_init(LED_G_PIN);
    gpio_set_dir(LED_G_PIN, GPIO_OUT);
    gpio_init(LED_B_PIN);
    gpio_set_dir(LED_B_PIN, GPIO_OUT);
    
    gpio_init(BTN_A_PIN);
    gpio_set_dir(BTN_A_PIN, GPIO_IN);
    gpio_pull_up(BTN_A_PIN);
    
    gpio_init(BTN_EMG_PIN);
    gpio_set_dir(BTN_EMG_PIN, GPIO_IN);
    gpio_pull_up(BTN_EMG_PIN);
    
    // Configuração dos buzzers como PWM
    gpio_set_function(BUZZER1_PIN, GPIO_FUNC_PWM);
    gpio_set_function(BUZZER2_PIN, GPIO_FUNC_PWM);
    uint slice1 = pwm_gpio_to_slice_num(BUZZER1_PIN);
    uint slice2 = pwm_gpio_to_slice_num(BUZZER2_PIN);
    pwm_set_enabled(slice1, true);
    pwm_set_enabled(slice2, true);
    
    inicia_oled(); // Inicializa o display OLED
    
    while (true) {
        if (gpio_get(BTN_EMG_PIN) == 0) {
            Emergencia();
        } else {
            SinalFechado();
            SinalAtencao();
            SinalAberto();
        }
    }
    return 0;
}
