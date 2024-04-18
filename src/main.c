#include <stdio.h>

#include "gpio.h"
#include "rk_gpio.h"


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
            rk_io_setvalue(argv[1], 1);
        }else
        {
            rk_io_setvalue(argv[1], 0);
        }
    }
    return 0;
}
