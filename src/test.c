#include <stdio.h>

#include "gpio.h"
#include "rk_gpio.h"


static int DEMO_RK_GPIO_INDEX = 19;

static int demo_rk_gpio_init(void)
{
    int ret;
    // 设置SOC平台RK 的 RK3588
    ret = set_rk_gpio_platform(RK3588_GPIO_PLATFORM);
    // 将标号转换为RK gpio的索引
    DEMO_RK_GPIO_INDEX = str_to_rk_gpio("RK_GPIO1_A0");
    printf("index %d\n", DEMO_RK_GPIO_INDEX);

    // 标准GPIO-Sys 操作
    ret = gpio_export(DEMO_RK_GPIO_INDEX);
    ret = gpio_direction_output(DEMO_RK_GPIO_INDEX);
    return ret;
}

static int demo_rk_gpio_on(void)
{
    gpio_set_value(DEMO_RK_GPIO_INDEX, 1);
    return 0;
}

static int demo_rk_gpio_off(void)
{
    gpio_set_value(DEMO_RK_GPIO_INDEX, 0);
    return 0;
}

static int demo_rk_gpio_deinit(void)
{
    gpio_set_value(DEMO_RK_GPIO_INDEX, 0);
    return gpio_unexport(DEMO_RK_GPIO_INDEX);
}

static int _test_rk_gpio(void)
{
    demo_rk_gpio_init();
    return 0;
}
