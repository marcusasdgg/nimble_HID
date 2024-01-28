#include<usb_serial_interface.h>
#include<string>
#define TAG "UART_TASK"

extern "C"
{
    #include <stdio.h>
    #include "freertos/FreeRTOS.h"
    #include "freertos/task.h"
    #include "esp_system.h"
    #include "esp_log.h"
    #include "driver/uart.h"
    #include <string.h>
}

    usb_serial_interface::usb_serial_interface(int baud_rate)
        {
            uart_config_t uart_config = {
            .baud_rate = baud_rate,
            .data_bits = UART_DATA_8_BITS,
            .parity    = UART_PARITY_DISABLE,
            .stop_bits = UART_STOP_BITS_1,
            .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
            };
            
            if(uart_param_config(UART_NUM_0, &uart_config) != ESP_OK)
            {
                 ESP_LOGI(TAG, "UART parameter configuration not successful");
            }

            if (uart_set_pin(UART_NUM_0, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE) != ESP_OK)
            {
                 ESP_LOGI(TAG, "UART pin was not set properly");
            }
            

            if (uart_driver_install(UART_NUM_0, 256, 0, 0, NULL, 0) != ESP_OK)
            {
                ESP_LOGI(TAG, "UART driver was not installed properly");
            }

            

            ESP_LOGI(TAG, "UART Task Started successfully");
            initialized = true;
        }
    
    char* usb_serial_interface::read_line()
        {
            auto line = new char[1024];
            int counter = 0;

            while (1) {
                // Read one byte at a time
                int len = uart_read_bytes(UART_NUM_0, (uint8_t*)&line[counter], 1, portMAX_DELAY);
                if (len == 1) {
                    // Check for newline character
                    if (line[counter] == '\n') {
                        break;  // Exit the loop if newline is found
                    }
                    counter++;
                }
            }

            line[counter] = '\0';
            ESP_LOGI(TAG, "Received line: %s", line);
            this->prior_line_array.push_back(line);
            return line;
        }

        bool usb_serial_interface::write_line(std::string s)
        {
            uart_write_bytes(UART_NUM_0,s.c_str(),s.size());
            return true;
        }

        bool usb_serial_interface::write_log(std::string s)
        {
            ESP_LOGI(TAG,"%s",s.c_str());
            return true;
        }

        char usb_serial_interface::read_byte()
        {
            uint8_t info[1];
            uart_read_bytes(UART_NUM_0, info,1,portMAX_DELAY);
            return *info;
        }

        bool usb_serial_interface::if_initialized() {
            return this->initialized;
        }

        bool usb_serial_interface::clean_lines()
        {
            for(auto i : this->prior_line_array)
            {
                delete[] i;
            }
            prior_line_array.clear();
            return true;
        }

        usb_serial_interface::~usb_serial_interface()
        {
            this->clean_lines();
            this->write_log("All prior line pointers are removed.");
        }