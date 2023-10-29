#include <stdio.h>
#include <stdint.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/adc.h"

#define ADC_CHANNEL ADC1_CHANNEL_0  // Pino analógico para leitura do sensor de pH
#define V_REF      1100             // Tensão de referência em mV 
float convertToPH(uint32_t);

void app_main() {
    // Configuração do ADC
    adc1_config_width(ADC_WIDTH_12Bit);
    adc1_config_channel_atten(ADC_CHANNEL, ADC_ATTEN_DB_11);

    while (1) {
        
        uint32_t adc_reading = adc1_get_raw(ADC_CHANNEL);
        float ph_value = convertToPH(adc_reading);
        ESP_LOGI("pH Sensor", "Valor de pH: %.2f", ph_value);
        vTaskDelay(pdMS_TO_TICKS(5000));  // Aguarda 5 segundos
    }
}

// Função de conversão de leitura ADC para valor de pH 
float convertToPH(uint32_t adc_reading) {

    float ph_value = (float)adc_reading * (14.0*0.656 / (4095.0)); 
    return ph_value;
}
