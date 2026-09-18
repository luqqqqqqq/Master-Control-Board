# 开发与验证

[返回项目首页](../README.md) · [文档导航](README.md)

本文记录 `v1.0.0` 固件的 CubeMX/Keil 配置要点。工程目标以 `Luq Board.ioc` 和 Keil 工程中的 `STM32F407VETx` 配置为准；下文源码路径均相对于 [`src/firmware/`](../src/firmware/)。

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

## STM Studio 观察 IMU

使用 STM Studio 打开 [st-studio-imu.tsp](../tools/stm-studio/st-studio-imu.tsp)，它引用同目录的 [st-studio-imu.tsc](../tools/stm-studio/st-studio-imu.tsc)。配置指向本地编译生成的 `src/firmware/MDK-ARM/Luq Board/Luq Board.axf`，用于查看 `test.acc_*`、`test.gyr_*` 和 `test.temp`。

使用前先编译对应固件，并在 STM Studio 中确认或重新导入当前 AXF 的变量地址；配置中保存的历史地址不能代替当前构建的符号信息。日志写入 `tools/stm-studio/st-studio-imu.log`，已加入忽略规则。

## 验证范围

- 已核对 Keil 工程的 54 个源文件引用和 12 个包含目录条目，以及 STM Studio 配置的相对路径。
- 目录整理保持固件源码、工程内部布局、硬件资产、第三方内容与 HEX 镜像不变。
- 静态检查不包含 Keil 编译、烧录、IMU 实测或电气测试。
- 项目有 RM 比赛应用经历，但温漂、振动、长期稳定性与完整电气参数报告仍待完善。

修改 CubeMX 配置或固件功能后，应重新编译并验证实际板卡行为；对外发布时保持 [VERSION](../VERSION)、根 README 和 [更新日志](../CHANGELOG.md) 一致，并保留第三方许可证。
