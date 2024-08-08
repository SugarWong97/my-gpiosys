#include <stdio.h>

#include "gpio.h"
#include "rk_gpio.h"

//#define io_servalue rk_io_setvalue
#define io_servalue zynq_7000_io_setvalue

int main(int argc, char * argv[])
{
    if(argc < 3)
    {
        printf("%s  gpio_str  0/1\n", argv[0]);
        return -1;
    }else
    {
        if(argv[2][0] == '1')
        {
            io_servalue(argv[1], 1);
        }else
        {
            io_servalue(argv[1], 0);
        }
    }
    return 0;
}
