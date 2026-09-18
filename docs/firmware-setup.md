# 固件开发说明

本文记录 `v1.0.0` 固件的 CubeMX/Keil 配置要点。工程目标以 `Luq Board.ioc` 和 Keil 工程中的 `STM32F407VETx` 配置为准；文中的路径均相对于 `v1.0.0/firmware/`。

## 快速构建

1. 使用 STM32CubeMX 打开 `Luq Board.ioc`，芯片选择 STM32F407VET6、LQFP100。
2. 使用 Keil MDK-ARM 打开 `MDK-ARM/Luq Board.uvprojx`。
3. 安装对应版本的 STM32F4xx Device Pack，选择 `Luq Board` target 后编译。
4. 使用 ST-Link 或 J-Link 烧录生成的 `.hex` 文件。

## 外设概览

- **CAN1、CAN2**：CubeMX 当前配置为 1 Mbps，启用自动离线管理和自动唤醒。
- **USART1/2/3、UART4/5、USART6**：串口接收使用 DMA/中断组合，具体引脚以 `.ioc` 为准。
- **SPI1、SPI2**：SPI2 连接 BMI270，片选由 GPIO 控制。
- **FreeRTOS**：任务入口在 `Task/Src/user_task.c`，回调集中在 `Task/Src/user_handler.c`。
- **IWDG**：用于基础运行时看门狗保护。

## 工程约定

- `Core/` 保存 CubeMX 生成的初始化、中断和 HAL glue code。
- `Peripherals/` 提供 CAN、UART、SPI、TIM、GPIO 等项目驱动封装。
- `BMI270/` 保留 Bosch BMI270 Sensor API 及其适配代码。
- 重生成 CubeMX 工程时，保留用户代码区，并检查 Keil 工程中的 include path 和 source group。
- 任务逻辑优先放入 `Task/`，设备初始化放在 `Peripherals/Src/dev_drv.c`，对应头文件位于 `Peripherals/Inc/dev_drv.h`。

## 关键配置

### 时钟与系统

- 使用外部高速晶振，系统时钟按 STM32F407VET6 的最高允许频率配置。
- HAL 时基使用 TIM2，FreeRTOS 使用 SysTick。
- 开启 FPU、IWDG 和 CMSIS-RTOS v1；FreeRTOS 堆大小在 CubeMX 工程中设置。

### 接口分配

最终引脚、DMA stream、NVIC 优先级和 CAN 时序均以 `Luq Board.ioc` 为准。修改 CubeMX 配置后，需要重新检查 Keil 工程的用户文件分组和 include path。

### 项目驱动

- `uart_drv.*`：串口 DMA/空闲线接收封装。
- `can_drv.*`：CAN 收发和接收回调封装。
- `tim_drv.*`：定时器功能扩展点。
- `gpio_drv.*`：LED、激光和外部中断相关 GPIO 宏与操作。
- `bmi_drv.*`：BMI270 初始化和数据读取适配。

本文对应 Master Control Board `v1.0.0`。修改 CubeMX 配置或固件功能后，请在仓库根目录的 [CHANGELOG.md](../CHANGELOG.md) 中记录变更。
