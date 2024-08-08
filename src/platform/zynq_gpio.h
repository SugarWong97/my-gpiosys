#ifndef __ZYNQ_GPIO_H__
#define __ZYNQ_GPIO_H__


enum ZYNQ_GPIO_PLATFORM
{
    ZYNQ_7000_GPIO_PLATFORM,
    ZYNQ_MPSOC_GPIO_PLATFORM,
    UNKNOW_GPIO_PLATFORM
};

// 配置RK 的GPIO 平台
int set_zynq_gpio_platform(enum ZYNQ_GPIO_PLATFORM pl);

// 将RK GPIO的标号转换为索引
int str_to_zynq_gpio(const char * str);

#endif/*__ZYNQ_GPIO_H__*/