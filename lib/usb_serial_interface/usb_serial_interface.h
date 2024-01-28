#pragma once
#include <string>
#include <vector>

class usb_serial_interface
{
    public:
        usb_serial_interface(int baud_rate);
        char* read_line();
        bool write_line(std::string s);
        bool write_log(std::string s);
        char read_byte();
        bool if_initialized();
        bool clean_lines();
        ~usb_serial_interface();
    private:
        bool initialized = false;
        std::vector<char*> prior_line_array;
};