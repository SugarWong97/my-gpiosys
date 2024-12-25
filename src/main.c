#include <stdio.h>

#include "gpio.h"

#if 0
#include "rk_gpio.h"
#define io_servalue rk_io_setvalue
#endif

#if 1
#include "zynq_gpio.h"
#define io_servalue zynq_7000_io_setvalue
#endif

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
