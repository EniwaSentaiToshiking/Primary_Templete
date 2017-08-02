#include "RemoteStart.h"

RemoteStart::RemoteStart()
{
    
    /* Open Bluetooth file */
    bt = ev3_serial_open_file(EV3_SERIAL_BT);
    assert(bt != NULL);
    CMD_START = '1';
}

RemoteStart::~RemoteStart() {
    fclose(bt);         /*bluetooth*/
}

bool RemoteStart::remote_start()
{
    bool start = false;
    
    uint8_t c = fgetc(bt); /* ŽóM */
    
    if(c == CMD_START)
        start = true;
    
    
    fputc(c,bt);
    
    
    return start;
}
