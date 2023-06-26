#include <stdio.h>

#include "gpio.h"


int BEEP_GPIO_INDEX = 19;


int str_to_rk_gpio(const char * str);
int beep_init(void)
{
    int ret;
    BEEP_GPIO_INDEX = str_to_rk_gpio("RK_GPIO1_A0");
    printf("index %d\n", BEEP_GPIO_INDEX);
    ret = gpio_export(BEEP_GPIO_INDEX);
    ret = gpio_direction_output(BEEP_GPIO_INDEX);
    return ret;
}

int beep_on(void)
{
    gpio_set_value(BEEP_GPIO_INDEX, 1);
    return 0;
}

int beep_off(void)
{
    gpio_set_value(BEEP_GPIO_INDEX, 0);
    return 0;
}

int beep_deinit(void)
{
    gpio_set_value(BEEP_GPIO_INDEX, 0);
    return gpio_unexport(BEEP_GPIO_INDEX);
}


int main(int argc, char * argv[])
{
    beep_init();
    return 0;
}
