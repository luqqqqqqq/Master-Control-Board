# 新的开始

## 选择芯片

打开STM32CubeMX

Commercial Part Number输入STM32F407VET6

在右侧下方的items中选中STM32F407VET6，并双击

## 配置工程

点击Project Manager选项卡，输入工程名，工程地址路径，地址路径不能存在中文

应用结构选择Advanced，工具链和IDE选择MDK-ARM，版本选择Keil可以支持的最大版本，可以打开Keil，在Help-About中查看版本信息

最小堆大小为0x200，最小栈大小为0x400(后续可以更具需求进行修改)

启用多线程支持，线程安全选用4号策略（禁止中断被抢占，可以可抢占的中断优先级）

即不能打断的操作使用vPortEnterCritical();和vPortExitCritical();包住避免被抢占

使用默认固件包

左侧选择Code Generator

软件包，选择复制所有使用的库到工程文件夹

生成文件中，勾选单独生成外设初始化文件.c/.h，重生成时存留用户代码，不重建时删除之前的构建文件

HAL Settings选择将所有空闲引脚设置为模拟态

重建前后的用户批处理为空，生成模板为默认

左侧选择Advance Setting

RCC选择HAL库（LL为精简库，操作寄存器；HAL为抽象库，操作外设动作）

不勾选，不生成调用函数

不使能用户自定义回调函数

## 配置时钟树

点击Clock Configuration选项卡

在HCLK中输入最大频率回车即可(会自己进行配置)

## 配置引脚和设置

点击Pinout & Configuration选项卡，按照下述进行配置，未描述即为默认

RCC-HSE-Crystal

SYS-Debug-Serial Wire

SYS-Timebase-TIM2后续该定时器为FreeRTOS使用不可以用于配置

IWDG-activated-8预分频-4000计数

PB8,PB9配置为CAN1-3分配-9T BS1-4T BS2-开启自动离线管理，自动唤醒，ID优先发送功能

PB5,PB6配置为CAN2-3分配-9T BS1-4T BS2-开启自动离线管理，自动唤醒，ID优先发送功能

PA9,PA10配置为USART1-Asynchronous

PA3配置为USART2-Asynchronous-100000波特率-Receive Only（匹配dji接收机）

PB10,PB11配置为USART3-Asynchronous

PC10,PC11配置为UART4-Asynchronous

PC12,PD2配置为UART5-Asynchronous

PC6,PC7配置为USART6-Asynchronous

SPI1-全双工主机-片选输出-将NSS引脚改为GPIO_Output并初始化为高电平

PB12,PB13,PB14,PB15配置为SPI2

SPI2-全双工主机-片选输出-将NSS引脚改为GPIO_Output并初始化为高电平-预分频为4（bmi270最大为10M）

PA0,PA1,PA2,PB0,PB1保留不配置

GPIO-SPI1_CS-Speed为HIGH

GPIO-SPI2_CS-Speed为HIGH

PE9,PE10,PE11配置为GPIO_Output，命名为LED_R,LED_G,LED_B，初始化输出为低

PC9配置为GPIO_Output，命名为LASER，初始化输出为高

PD8,PD9配置为GPIO_EXIT，设置为下拉，上升触发中断模式，命名为INT1,INT2（bmi270需要匹配高电平为中断信号）

DMA-通道1和通道2添加所有UART，优先级均设置为高，RX均设置为循环

FREERTOS-CMSIS_V1-开启浮点运算单元FPU-堆大小设置为40960

点击NVIC，将EXIT取消freertos handle代理，并且优先级设为4，并使能其他RX中断且均以freertos函数作为handle，can只使能RX0(不使用fifo1)

## 添加的文件

### KEIL配置

加入BMI270文件夹、Peripherals文件夹、Task文件夹

需要在（魔术棒）options of target的c/c++的include path中添加.h文件的路径

需要（3个方块）file extensions中添加.c文件

### UART驱动

在User/Core/stm32f4xx_it.c的USER Include中添加头文件uart_drv.h，并且uart的中断函数中都在USER Core 0里添加UART_IRQHandler(&huartx)；

**需要重写UARTx_IDLE_Handler(&buf)函数，对应信息接收后动作**

### CAN驱动

**需要重写CAN1_RX_Handler(uint32_t rxId, uint8_t *rxBuf)函数，对应信息接收后动作**

### TIM驱动

自行增加enable和set函数中的内容

### GPIO驱动

自行增加gpio操作的宏定义

**需要重写HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)函数，对应外部中断后动作**

### SPI驱动

暂无

### BMI270 API

https://github.com/boschsensortec/BMI270_SensorAPI.git

克隆后，添加api文件和路径（BMI270文件夹中已完成此步）

### Device Enable

在User/Core/main.c的USER Include中包含dev_drv.h后，在MX_FREERTOS_Init()初始化前的用户代码中调用Device_init()即可

### Task and Handler

在User/Core/freertos.c中添加头文件user_task.h，并在MX_FREERTOS_Init()函数的USER CODE BEGIN RTOS_THREADS中添加User_Task_Init();

**user_task.c负责用户自定义任务，仿写任务即可**

**user_handler.c负责重写回调函数**

任务记得写在while里或者用其他方式循环

# 各种解释

## FreeRTOS

CMSIS_V1和CMSIS_V2版本主要的区别在于，CMSIS_V2兼容支持的硬件更多，内存耗费更多；对于常见的-M3、M4、M7芯片，选择V1即可

内存管理默认heap_4方式，任务管理默认抢占式，默认1ms检测一次优先级

TOTAL_HEAP_SIZE是freertos可分配的堆空间，此处使用40K

LIBARY_MAXSYSCALL_SYSCALL_INTERRUPT_PRIORIT用于设定freertos能处理中断的最高优先级mask，当出现mask以下的中断时，相当于加了一个任务，即中断可以被调度；对于mask以上的中断会打断freertos运行

使用freertos只可以用4位主优先级五，无子优先级，mask一般默认为5

由于无多的DMA，因此中断freertos的任务切换来读取SPI数据，由于SPI速度快，因此不影响

- 线程有五种状态
  - 运行态：running
  - 就绪态：ready
  - 阻塞：blocked，等待某件事(时间、事件)
  - 暂停：suspend，被挂起。
  - 暂停：deleted，被删除。

FreeRTOS 在以下情况下必然发生任务切换：
**(1) 运行中的任务调用 vTaskSuspend() 将自己挂起。
(2) 运行中的任务调用了延时函数，要求等待一段时间后再执行。
(3) 运行中的任务需要等待一个未发生的同步事件。**
**(4) 运行中的任务调用了 taskYIELD() 主动要求切换任务。**
**(5) 运行中的任务被更高优先级的任务抢占。
(6) 运行中的任务执行到一个时间片末尾，被同一优先级的任务抢占。**

## FreeRTOS Systick

FreeRTOS默认使用24位的下行计数器SysTick作为内核时钟源，在每个系统滴答时触发SysTick中断（作为一个时间片），完成任务切换等核心工作，FreeRTOS将SysTick中断优先级设置为最低，HAL时基要改为其他定时器以免重要中断被FreeRTOS影响

1. SysTick中断的主要作用是寻找是否有更高优先级的任务需要执行,并在需要时进行任务切换。由于SysTick中断优先级设置为最低,所以它可以被其他高优先级中断抢占和中断。
2. 当在任务执行过程中发生高优先级中断(如定时器中断、串口中断等)时,会先暂停当前任务的执行,转而执行对应的高优先级中断服务程序。
3. 在执行高优先级中断服务程序的过程中,SysTick定时器会继续计数,但由于SysTick中断被抢占无法响应,所以在这段时间内SysTick中断无法执行任务切换等操作。
4. 当高优先级中断服务程序执行完毕后,CPU会先退出该中断,然后才能响应SysTick中断(如果在该中断期间有SysTick中断到来的话)。
5. 一旦响应SysTick中断,FreeRTOS内核会检查是否需要进行任务切换。如果需要,会保存当前任务上下文,并切换到更高优先级的就绪任务继续执行。
6. 因此,虽然SysTick中断被暂时挂起,但它的计数并没有中断,所以不会导致时基不准的情况。
7. 但是,如果高优先级中断的响应时间过长,会导致SysTick中断"丢失"多个节拍,从而影响时基的精确度。

## CAN2.0

can挂载在APB1上，最大频率为42MHz，此处配置3分频，9Tq PBS1，4Tq PBS2，即1/(1/(42Mhz/16)*3)bit/s

- CAN协议总共有5种不同类型的功能帧,分别是:
  1. 数据帧(Data Frame)
  2. 远程帧(Remote Frame)
  3. 错误帧(Error Frame)
  4. 覆盖帧(Overload Frame)
  5. 空闲帧(Idle Frame)

每种功能帧都有标准格式(Standard)和扩展格式(Extended)两种,区别在于标识符(ID)的长度。

- 标准格式ID长度为11位(2.0A)
- 扩展格式ID长度为29位(2.0B)
- 标准帧构成
  1. 1bit 起始位
  2. 11bit ID段，数字越小优先级越高
  3.  RTR IDE r0
  4. 4bit DLC
  5. 0-8BYTE 数据段MBS先行，即高端字节先发
  6. 16bit CRC校验
  7. 2bit ACK段
  8. 7bit EOF段

波特率的选择,500Kbps或750Kbps都是常用设置。通常:

- 500Kbps用于车载较长的内部总线
- 750Kbps用于车载的相对较短总线
- 工控领域则可能选择更高的波特率

为实现时序同步把一个帧中的1bit分为4段（可设置），该分段决定bit速度即can速度

- 1Tq SS同步段检测跳变
- 6Tq PTS传播段
- 5Tq PBS1缓冲段
- 7Tq PBS2缓冲段
- 数据采样在PBS1和PBS2之间
- Jump Width是出现同步误差时,调整采样点位置的最大值

Advanced Parameters （高级参数）-Operationg Mode
Normal(正常模式):可向总线发送或接收数据。
Loopback(回环模式):把数据发送给总线和自己，不能从总线接收数据。
Silent(静默模式):只可向总线发送数据1和接收数据，不能发送数据0。
Loopback combined with Silent(回环静默模式):把数据发送给自己，不能从总线接收也不能发送给总线数据。

[STM32F4之CAN通信CubeMX实现_time quanta in bit segment-CSDN博客](https://blog.csdn.net/weixin_61692649/article/details/127703837)

STM32单片机中CAN中具有两个邮箱，即FIFO0与FIFO1对应RX0和RX1中断，每个邮箱有三层，每一层都可以存放一条报文，与过滤器匹配的报文会被放入FIFO邮箱中

[CAN通信知识梳理及在Stm32上的应用（HAL库） - xiondun - 博客园 (cnblogs.com)](https://www.cnblogs.com/xiondun/p/17648325.html#2CAN_146)

[【stm32f407】CAN总线_stm32f407 can-CSDN博客](https://blog.csdn.net/XiaoXiaoPengBo/article/details/73649819)

[秀！靠这篇我竟然2天理解了CAN协议！实战STM32F4 CAN！_syncjumpwidth-CSDN博客](https://blog.csdn.net/tjcwt2011/article/details/135366770)

[【HAL库】STM32F407----CAN通信----中断详解_can发送中断和接收中断-CSDN博客](https://blog.csdn.net/MQ0522/article/details/130422992)

[【HAL库】STM32F407----CAN通信----过滤器配置_can过滤器-CSDN博客](https://blog.csdn.net/MQ0522/article/details/130067130)

[STM32F4_CAN_筛选器代码解读_can_filtertypedef-CSDN博客](https://blog.csdn.net/weixin_44439003/article/details/126860056)

[CAN总线之CAN ID过滤器分析-CSDN博客](https://blog.csdn.net/GUOXINLAN123/article/details/79398940)

[STM32 CAN调试小记_slavestartfilterbank-CSDN博客](https://blog.csdn.net/feixiaoliao/article/details/88981635)

[CAN过滤器配置以及常见问题总结_can 过滤配置-CSDN博客](https://blog.csdn.net/tjcwt2011/article/details/135366361)

## WDG

分为IWDG独立看门狗和WWDG窗口看门狗，此处用的IWDG时间为Tout=8/32KHz*4000=1000ms

IWDG是独立于系统之外，有独立时钟，但是RC振荡精度低，需要在计数器归零前喂狗则不会复位，主要用于监视硬件错误

WWDG是系统内部的故障探测器，时钟与系统相同，归零产生中断，用于监视软件错误

Debug要把IWDG的init去掉

[独立看门狗（IWDG） - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/664367928)