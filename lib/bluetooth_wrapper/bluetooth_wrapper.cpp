

#include "bluetooth_wrapper.h"
#include "usb_serial_interface.h"

#define TAG "Bluetooth Config: "
extern "C"
{
    #include "nvs_flash.h"
    #include "esp_nimble_hci.h"
    #include "nimble/nimble_port.h"
    #include "host/ble_hs.h"
}



bluetooth_wrapper::bluetooth_wrapper(int baud_rate) : usb_serial_interface(baud_rate) 
{
    //need to add nimble initialization stuff
   
    if (nvs_flash_init() != ESP_OK)
    {
        this->write_log("Error NVS Flash was not initialized properly");
    }
    int ret = esp_nimble_hci_and_controller_init();
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "esp_nimble_hci_and_controller_init() failed with error: %d", ret);
        return;
    }
    nimble_port_init();
}