# STM32ClionTemplateProject
Clion的STM32项目的模板
### 备忘
* 使用arm-none-gcc作为编译工具
* 使用CMake管理工程
* [toolchain](./toolchain)里面有针对不同处理器的CMake Toolchain file，使用-DCMAKE_TOOLCHAIN_FILE=xxx指定即可
* [toolchain](./toolchain)里面还有对应的链接脚本，在链接器参数中使用-T传入绝对路径
* [startup](./STM32F40_41xxx/startup)里面是启动汇编
* [stdperiphlib](./STM32F40_41xxx/stdperiphlib)里面是ST的外设库，可以删除不需要的外设源文件
* 安装openOCD之后可以在Clion里设置一键下载
* 在Clion中还可以设置使用ST-Link Utility CLI下载
* 中断函数在interrupts里面而不是在stm32f4xx_it里面
### Todo
* 添加别的设备