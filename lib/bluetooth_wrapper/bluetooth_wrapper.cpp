

#include "bluetooth_wrapper.h"
#include "usb_serial_interface.h"


#include "nvs_flash.h"
#include "esp_nimble_hci.h"

#define TAG "Bluetooth Config: "

bluetooth_wrapper::bluetooth_wrapper(int baud_rate) : usb_serial_interface(baud_rate) 
{
    //need to add nimble initialization stuff
    esp_nimble_hci_init();
    
}

