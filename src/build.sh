#!/bin/bash

## 指定的输出文件名
APP_NAME=gpio_test.elf

# 指定输出目录(主目录是在编译目录中，需要使用"../"或者"绝对路径")
TOP_DIR=`pwd`
OUTPUT_DIR=$TOP_DIR/out

BUILD_DIR=$TOP_DIR/.build

function build_target()
{
    local with_gcc="$1"

    local gcc_cmd=""

    if [ ! -z "$with_gcc"  ];then
        gcc_cmd="-DCROSS_COMPILE=$with_gcc"
    fi

    cd $TOP_DIR
    rm $BUILD_DIR -rf
    mkdir $BUILD_DIR -p

    cd $BUILD_DIR
    cmake .. -DOUTPUT_APPNAME=$APP_NAME -DOUTPUT_DIRNAME=${OUTPUT_DIR}
    make -j16
}

build_target
#build_target  "arm-linux-"
