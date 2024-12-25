#include <stdio.h>
#include <string.h>
#include "str.h"
#include "gpio.h"
#include "rk_gpio.h"

static int platform = RK3588_GPIO_PLATFORM;

#define DEBUG 1
#define DEBUG_ERROR 1
#if DEBUG == 0
#define rkgpio_debug(format,...)
#else
#define rkgpio_debug printf
#endif

#if DEBUG_ERROR == 0
#define rkgpio_error(format,...)
#else
#define rkgpio_error(format,...) printf
#endif



int set_rk_gpio_platform(enum RK_GPIO_PLATFORM pl)
{
    if(pl >= RKUNKNOW_GPIO_PLATFORM)
    {
        rkgpio_error("[%s] RKUNKNOW_GPIO_PLATFORM %d/%d\n", __func__, pl, RKUNKNOW_GPIO_PLATFORM);
        return -1;
    }
    platform = pl;
    return 0;
}

int str_to_rk_gpio(const char * str)
{
    char str_buff[64]= {0};
    char tmp_str[64]= {0};
    int ret;
    int bank = 0, pos = 0;
    char group = 0;
    int pin;
    if(!str)
    {
        rkgpio_error("[%s] NULL\n", __func__);
        return -1;
    }
    if(strlen(str) < 3)
    {
        rkgpio_error("[%s] string [%s] to short.\n", __func__, str);
        return -1;
    }

    memset(tmp_str, 0, sizeof(tmp_str));
    strncpy(str_buff, str, strlen(str));
    rkgpio_debug("Input : %s\n", str_buff);

    str_to_lower(str_buff, strlen(str_buff));

    memset(tmp_str, 0, sizeof(tmp_str));
    str_replace(str_buff, "gpio", "", tmp_str, sizeof(tmp_str));
    sprintf(str_buff, "%s", tmp_str);

    memset(tmp_str, 0, sizeof(tmp_str));
    str_replace(str_buff, "_", "", tmp_str, sizeof(tmp_str));
    sprintf(str_buff, "%s", tmp_str);

    memset(tmp_str, 0, sizeof(tmp_str));
    str_replace(str_buff, "rk", "", tmp_str, sizeof(tmp_str));
    sprintf(str_buff, "%s", tmp_str);

    memset(tmp_str, 0, sizeof(tmp_str));
    str_replace(str_buff, "rockchip", "", tmp_str, sizeof(tmp_str));
    sprintf(str_buff, "%s", tmp_str);


    //ret = sscanf(str_buff, "gpio%d_%c%d", &bank, &group, &pos);
    ret = sscanf(str_buff, "%d%c%d", &bank, &group, &pos);

    if(platform == RK3588_GPIO_PLATFORM || platform == RK3568_GPIO_PLATFORM)
    {
        pin = bank * 32 + (((group - 'a') * 8) + pos);
        rkgpio_debug("pin = %d \t= [ bank(%d) * 32 ] + [ group(%c->%d) * 8 ] + pos(%d)\n", pin, bank, group, group - 'a', pos);
        rkgpio_debug("\t\t= %d + %d + %d\n", bank * 32, (group - 'a') * 8, pos);
    }
    return pin;
}

int rk_io_setvalue(const char * rk_gpio_srt, int value)
{
    int test_rk_gpio_index = 19;
    int ret;

    // 设置SOC平台RK 的 RK3588
    ret = set_rk_gpio_platform(RK3588_GPIO_PLATFORM);
    // 将标号转换为 gpio的索引
    //str_to_rk_gpio("GPIO1_A0");
    //str_to_rk_gpio("1a0");
    //str_to_rk_gpio("gpio1_a6");
    //str_to_rk_gpio("GPIO4_C6");
    //str_to_rk_gpio("gpio4_c6");
    //str_to_rk_gpio("4_c6");
    //str_to_rk_gpio("4c6");
    test_rk_gpio_index = str_to_rk_gpio(rk_gpio_srt);
    printf("index %d\n", test_rk_gpio_index);

    // 标准GPIO-Sys 操作
    ret = gpio_export(test_rk_gpio_index);
    ret = gpio_direction_output(test_rk_gpio_index);

    if(value)
    {
        gpio_set_value(test_rk_gpio_index, 1);
    } else
    {
        gpio_set_value(test_rk_gpio_index, 0);
    }

    return gpio_unexport(test_rk_gpio_index);
}

/*
int main(int argc, char * argv[])
{
    if(argc < 3)
    {
        printf("%s  RK_GPIO1_A0  0/1\n", argv[0]);
        return -1;
    }else
    {
        //rk_io_setvalue("rk_gpio1_a6", 0);
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
*/
