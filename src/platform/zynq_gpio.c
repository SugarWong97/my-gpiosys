#include <stdio.h>
#include <string.h>
#include <math.h>
//#include "dir.h"
#include "gpio.h"
#include "zynq_gpio.h"

static int platform = ZYNQ_7000_GPIO_PLATFORM;

#define DEBUG 1
#define DEBUG_ERROR 1
#if DEBUG == 0
#define gpiosys_debug(format,...)
#else
#define gpiosys_debug printf
#endif

#if DEBUG_ERROR == 0
#define gpiosys_error(format,...)
#else
#define gpiosys_error(format,...) printf
#endif

int set_zynq_gpio_platform(enum ZYNQ_GPIO_PLATFORM pl)
{
    if(pl >= UNKNOW_GPIO_PLATFORM)
    {
        gpiosys_error("[%s] UNKNOW_GPIO_PLATFORM %d/%d\n", __func__, pl, UNKNOW_GPIO_PLATFORM);
        return -1;
    }
    platform = pl;
    return 0;
}

int find_in_dir(char *dirpath, const char *keyword, char* got_filename);

static int find_gpiochip(int *result)
{
    int ret;
    char str_buff[64]= {0};
    char tmp_str[64]= {0};
    if(result == NULL)
    {
        return -1;
    }

    memset(tmp_str, 0, sizeof(tmp_str));
    if(find_in_dir("/sys/class/gpio/", "gpiochip", str_buff))
    {
        str_replace(str_buff, "gpiochip", "", tmp_str, sizeof(tmp_str));
        sprintf(str_buff, "%s", tmp_str);
        ret = sscanf(str_buff, "%d", result);
    }
    return 0;
}

int str_to_zynq_gpio(const char * str)
{
    int base_index, io_pos;
    int is_emio;
    char str_buff[64]= {0};
    char tmp_str[64]= {0};
    int ret;
    int bank = 0, pos = 0;
    char group = 0;
    int pin;

    if(!str)
    {
        gpiosys_error("[%s] NULL\n", __func__);
        return -1;
    }
    if(strlen(str) < 3)
    {
        gpiosys_error("[%s] string [%s] to short.\n", __func__, str);
        return -1;
    }

    memset(tmp_str, 0, sizeof(tmp_str));
    strncpy(str_buff, str, strlen(str));
    gpiosys_debug("Input : %s\n", str_buff);

    str_to_lower(str_buff, strlen(str_buff));
    if(strstr(str_buff, "emio") != NULL)
    {
        is_emio = 1;
    }else
    {
        is_emio = 0;
    }

    memset(tmp_str, 0, sizeof(tmp_str));
    str_replace(str_buff, "emio", "", tmp_str, sizeof(tmp_str));
    sprintf(str_buff, "%s", tmp_str);

    memset(tmp_str, 0, sizeof(tmp_str));
    str_replace(str_buff, "mio", "", tmp_str, sizeof(tmp_str));
    sprintf(str_buff, "%s", tmp_str);

    memset(tmp_str, 0, sizeof(tmp_str));
    str_replace(str_buff, "_", "", tmp_str, sizeof(tmp_str));
    sprintf(str_buff, "%s", tmp_str);


    ret = sscanf(str_buff, "%d", &pos);

    if(platform == ZYNQ_7000_GPIO_PLATFORM)
    {

        base_index = 906;

        find_gpiochip(&base_index);


        if(is_emio == 1)
        {
            io_pos = 54;
        }else
        {
            io_pos = 0;
        }
        pin = base_index + io_pos + pos;
        gpiosys_debug("Pin = %d \t= [ Base(%d) ] + IO_Pos(%d) + id(%d)\n", pin, base_index, io_pos, pos);
    }
    return pin;
}
/*
int test(void)
{

    str_to_zynq_gpio("emio0");
    str_to_zynq_gpio("emio_0");
    str_to_zynq_gpio("mio0");
    str_to_zynq_gpio("mio_0");

    return 0;
}
*/

int zynq_7000_io_setvalue(const char * zynq_gpio_srt, int value)
{
    int test_zynq_gpio_index;
    int ret;

    // 设置SOC平台 的 ZYNQ
    set_zynq_gpio_platform(ZYNQ_7000_GPIO_PLATFORM);
    // 将标号转换为 gpio的索引
    test_zynq_gpio_index = str_to_zynq_gpio(zynq_gpio_srt);
    printf("index %d\n", test_zynq_gpio_index);

    // 标准GPIO-Sys 操作
    ret = gpio_export(test_zynq_gpio_index);
    ret = gpio_direction_output(test_zynq_gpio_index);

    if(value)
    {
        gpio_set_value(test_zynq_gpio_index, 1);
    } else
    {
        gpio_set_value(test_zynq_gpio_index, 0);
    }

    return gpio_unexport(test_zynq_gpio_index);
}

/*
int main(int argc, char * argv[])
{
    if(argc < 3)
    {
        printf("%s  emio0  0/1\n", argv[0]);
        return -1;
    }else
    {
        //zynq_7000_io_setvalue("emio6", 0);
        if(argv[2][0] == '1')
        {
            zynq_7000_io_setvalue(argv[1], 1);
        }else
        {
            zynq_7000_io_setvalue(argv[1], 0);
        }
    }
    return 0;
}
*/
