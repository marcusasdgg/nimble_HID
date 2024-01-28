extern "C"{
    #include <stdio.h>
    #include "freertos/FreeRTOS.h"
    #include "freertos/task.h"
    #include "esp_system.h"
    #include "esp_log.h"
    #include "driver/uart.h"
    #include <string.h>
}

#include <string>
#include "usb_serial_interface.h"
#include "bluetooth_wrapper.h"


static const char *TAG = "UART_TASK";

extern "C"
{
    void app_main() {
        esp_log_level_set("*", ESP_LOG_INFO);

        bluetooth_wrapper main(9600);
        if (!main.if_initialized())
        {
            ESP_LOGI(TAG, "UART Task Started unsuccesfully exiting application");
            return;
        }
        main.write_line("hello world\n");

        for(int i = 0 ; i<3 ; i++)
        {
            auto line = main.read_line();
        }
        
    }
}

