#ifndef __RK_GPIO_H__
#define  __RK_GPIO_H__

enum RK_GPIO_PLATFORM
{
    RK3568_GPIO_PLATFORM,
    RK3588_GPIO_PLATFORM,
    RKUNKNOW_GPIO_PLATFORM
};

// 配置RK 的GPIO 平台
int set_rk_gpio_platform(enum RK_GPIO_PLATFORM pl);

// 将RK GPIO的标号转换为索引
int str_to_rk_gpio(const char * str);

// 修改RK的IO输出值
int rk_io_setvalue(const char * rk_gpio_srt, int value);

#endif/* __RK_GPIO_H__*/
