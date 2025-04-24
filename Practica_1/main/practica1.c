#include <stdio.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
// Define CONFIG_FREERTOS_HZ 
#ifndef CONFIG_FREERTOS_HZ
#define CONFIG_FREERTOS_HZ 100
#endif
#include "freertos/task.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_adc/adc_continuous.h"
#include "esp_adc/adc_cali.h"
#include "esp_adc/adc_cali_scheme.h"

//Aplicación principal
void app_main(void)
{
    // Todas las configuraciones de los pines van aqui
    // Esta función se ejecuta al iniciar el programa
    // 1. Configurar el ADC
    adc_oneshot_unit_init_cfg_t init_config = {
        .unit_id = ADC_UNIT_2, // ADC2
    };
    adc_oneshot_unit_handle_t adc_handle;
    adc_oneshot_new_unit(&init_config, &adc_handle);

    // Configurar canal (GPIO2 - D2 es ADC1_CHANNEL_2)
    adc_oneshot_chan_cfg_t config = {
        .bitwidth = ADC_BITWIDTH_12,  // Nueva constante para 12 bits
        .atten = ADC_ATTEN_DB_12, // Nueva constante para 12 dB
    };
    adc_oneshot_config_channel(adc_handle, ADC_CHANNEL_2, &config);

    // Inicializa el BUCLE o el loop
    while (true)
    {
        // 2. Realizar lectura one-shot
        int val;
        adc_oneshot_read(adc_handle, ADC_CHANNEL_2, &val);
        double voltage=val*3.3/4095;
        printf("Valor ADC: %d\n", val);
        printf("Voltaje ADC: %.2f\n", voltage);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}