

#include "bluetooth_wrapper.h"
#include "usb_serial_interface.h"
#include "hid_definitions.h"

bluetooth_wrapper::bluetooth_wrapper(int baud_rate) : usb_serial_interface(baud_rate) 
{
    //need to add nimble initialization stuff
}