# 🚦 Semáforo Inteligente com BitDogLab Pico W

## 📌 Descrição do Projeto
Este projeto implementa um **sistema de semáforo inteligente** utilizando a placa **BitDogLab Pico W**, controlando LEDs, buzzers e um display OLED via I2C. O sistema simula um ciclo semafórico tradicional e possui um **modo de emergência**, ativado por um botão, para alertas sonoros e visuais.

## 🛠️ Componentes Utilizados
- **BitDogLab Pico W**
- **LEDs:** Vermelho, Verde e Azul
- **Botões:** Controle (BTN_A) e Emergência (BTN_EMG)
- **Buzzers:** Dois buzzers para alerta sonoro
- **Display OLED SSD1306** (comunicação I2C)
- **Resistores e Jumpers** para conexão

## 🔌 Esquemático de Ligação

| Componente       | Pino Pico W |
|------------------|------------|
| LED Vermelho     | GP13       |
| LED Verde       | GP11       |
| LED Azul        | GP12       |
| Botão Controle  | GP5        |
| Botão Emergência | GP6        |
| Buzzer 1        | GP10       |
| Buzzer 2        | GP9        |
| OLED SDA        | GP15       |
| OLED SCL        | GP14       |

## 🚀 Instalação e Execução

### 1️⃣ Configuração do Ambiente
- Instale o **SDK do Raspberry Pi Pico**.
- Utilize um compilador compatível como **arm-none-eabi-gcc**.
- Configure o **CMake** para compilar o código.

### 2️⃣ Clonar o Repositório
```bash
git clone https://github.com/seuusuario/semaforo_pico.git
cd semaforo_pico
```

### 3️⃣ Compilar e Gravar no Pico W
```bash
mkdir build && cd build
cmake ..
make
cp semaforo.uf2 /media/$USER/RPI-RP2
```

## 🔄 Funcionamento do Projeto
1. O semáforo alterna automaticamente entre os estados:
   - **Aberto** (LED Verde aceso)
   - **Atenção** (LEDs Vermelho e Verde acesos)
   - **Fechado** (LED Vermelho aceso)
2. O **display OLED** exibe mensagens informativas sobre o status atual do semáforo.
3. Se o **botão de emergência** for pressionado:
   - Os LEDs piscam alternadamente.
   - Os buzzers emitem alertas sonoros intermitentes.
   - O display exibe uma mensagem de **EMERGÊNCIA**.

## 🎥 Demonstração do Projeto
Assista ao vídeo de demonstração no seguinte link:

[📺 Assista ao vídeo]([COLOQUE_AQUI_SEU_LINK_DO_VIDEO](https://youtu.be/dLx91NVbRjA))

## ✒️ Autor
Projeto desenvolvido por **Alan Borges** para o **Desafio EmbarcaTech**.

📌 *Para dúvidas ou sugestões, entre em contato!* 🚀

