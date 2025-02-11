#ifndef DHT22_H
#define DHT22_H

#include <stdint.h>

// Resultados possíveis para a leitura
#define DHT22_OK 0
#define DHT22_ERROR_CHECKSUM -1
#define DHT22_ERROR_TIMEOUT -2

// Função para ler temperatura e umidade do DHT22
int dht22_read(uint32_t pin, float *temperature, float *humidity);


#endif // DHT22_H
