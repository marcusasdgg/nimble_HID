#pragma once

#include "usb_serial_interface.h"

class bluetooth_wrapper : public usb_serial_interface {
public:
    bluetooth_wrapper(int baud_rate);
    bool send_HID_char(char c);
    bool send_HID_line(std::string s);
private:
    bool send_HID_report();
};