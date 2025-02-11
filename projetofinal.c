#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "dht22.h"
#include <math.h>
#include "ssd1306.h"

#define LDR_PIN 28 // GPIO28 (ADC2)
#define RS 2000    // Resistor fixo de 2kΩ
#define GAMMA 0.7  
#define RL10 50    

#define DHT_PIN 16   

// Definição dos pinos de alerta
#define BUZZER1 10
#define BUZZER2 21
#define LED_RED 13
#define LED_GREEN 11
#define LED_BLUE 12

// Definição do pino do relé
#define RELAY_PIN 17

// Definição dos pinos I2C
#define SDA_PIN 14
#define SCL_PIN 15
#define I2C_PORT i2c1

ssd1306_t oled; // Variável para o OLED

void adc_init_lux() {
    adc_init();
    adc_gpio_init(LDR_PIN);
    adc_select_input(2);
}

uint16_t read_lux() {
    return adc_read();
}

float adc_to_lux(uint16_t adc_value) {
    float voltage = adc_value / 4095.0f * 3.3f;
    if (voltage == 3.3f) return 0.0f;
    float resistance = RS * voltage / (1 - voltage / 3.3f);
    return pow(RL10 * 1e3 * pow(10, GAMMA) / resistance, (1 / GAMMA));
}

void setup() {
    stdio_init_all(); 
    gpio_init(DHT_PIN);
    gpio_set_dir(DHT_PIN, GPIO_IN);
    adc_init_lux();

    // Configuração dos pinos de saída para alerta
    gpio_init(BUZZER1);
    gpio_set_dir(BUZZER1, GPIO_OUT);
    gpio_init(BUZZER2);
    gpio_set_dir(BUZZER2, GPIO_OUT);
    gpio_init(LED_RED);
    gpio_set_dir(LED_RED, GPIO_OUT);
    gpio_init(LED_GREEN);
    gpio_set_dir(LED_GREEN, GPIO_OUT);
    gpio_init(LED_BLUE);
    gpio_set_dir(LED_BLUE, GPIO_OUT);

    // Configuração do pino do relé
    gpio_init(RELAY_PIN);
    gpio_set_dir(RELAY_PIN, GPIO_OUT);
    gpio_put(RELAY_PIN, 0); // Desliga o relé inicialmente

    // Inicialização do I2C para o OLED
    i2c_init(I2C_PORT, 400 * 1000);
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(SDA_PIN);
    gpio_pull_up(SCL_PIN);

    ssd1306_init(&oled, 128, 64, 0x3C, I2C_PORT);
    ssd1306_clear(&oled);
}

// Função para gerar som mais alto no buzzer
void buzzer_alerta(int ativar) {
    if (ativar) {
        for (int i = 0; i < 100; i++) {  // Loop para alternar rapidamente
            gpio_put(BUZZER1, 1);
            gpio_put(BUZZER2, 1);
            sleep_ms(2);
            gpio_put(BUZZER1, 0);
            gpio_put(BUZZER2, 0);
            sleep_ms(2);
        }
    } else {
        gpio_put(BUZZER1, 0);
        gpio_put(BUZZER2, 0);
    }
}

// Função para controle do LED e chamada do buzzer
void alerta(int ativar) {
    if (ativar) {
        gpio_put(LED_RED, 1);
        gpio_put(LED_GREEN, 0);
        buzzer_alerta(1);
    } else {
        gpio_put(LED_RED, 0);
        gpio_put(LED_GREEN, 1);
        buzzer_alerta(0);
    }
}

// Função para exibir dados no OLED
void exibir_no_oled(float temperature, float humidity, float lux, int condicao_adversa) {
    char temp_str[16], hum_str[16], lux_str[16], status_str[32];
    snprintf(temp_str, sizeof(temp_str), "Temp: %.2f C", temperature);
    snprintf(hum_str, sizeof(hum_str), "Hum: %.2f %%", humidity);
    snprintf(lux_str, sizeof(lux_str), "Lux: %.2f lx", lux);

    // Exibe status (normal ou alerta)
    if (condicao_adversa) {
        snprintf(status_str, sizeof(status_str), "ALERTA!!!");
    } else {
        snprintf(status_str, sizeof(status_str), "Cond. Normais");
    }

    ssd1306_clear(&oled);
    ssd1306_draw_string(&oled, 0, 0, 1, temp_str);
    ssd1306_draw_string(&oled, 0, 16, 1, hum_str);
    ssd1306_draw_string(&oled, 0, 32, 1, lux_str);
    ssd1306_draw_string(&oled, 0, 48, 1, status_str); // Exibe a condição no display
    ssd1306_show(&oled);
}

int main() {
    setup();
    float temperature = 0.0f, humidity = 0.0f;
    
    while (1) {
        uint16_t ldr_value = read_lux();
        float lux = adc_to_lux(ldr_value);
        int result = dht22_read(DHT_PIN, &temperature, &humidity);

        if (result == DHT22_OK) {
            printf("\n--------------------------\n");
            printf("Lux: %.2f lx\n", lux);
            printf("Temperatura: %.2f°C\n", temperature);
            printf("Umidade: %.2f%%\n", humidity);

            int condicao_adversa = 0;

            // Verificação de condições adversas
            if (temperature < 15 || temperature > 30) {
                printf("⚠️ ALERTA: Temperatura fora da faixa segura!\n");
                condicao_adversa = 1;
            }

            if (humidity < 30 || humidity > 70) {
                printf("⚠️ ALERTA: Umidade fora da faixa segura!\n");
                condicao_adversa = 1;
            }

            if (lux > 1500) {
                printf("⚠️ ALERTA: Nível de luz fora da faixa segura!\n");
                condicao_adversa = 1;
            }

            if (!condicao_adversa) {
                printf("✅ Condições Normais.\n");
            }

            // Controle do relé
            if (condicao_adversa) {
                gpio_put(RELAY_PIN, 1); // Ativa o relé
                printf("🔌 Relé Ativado!\n");
            } else {
                gpio_put(RELAY_PIN, 0); // Desativa o relé
                printf("🔌 Relé Desativado!\n");
            }

            alerta(condicao_adversa);

            // Exibe as informações no OLED, incluindo o status
            exibir_no_oled(temperature, humidity, lux, condicao_adversa);
        } else {
            printf("Erro ao ler DHT22\n");
        }
        
      sleep_ms(2000);
    }
}