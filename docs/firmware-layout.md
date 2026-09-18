# 固件目录说明

[返回项目首页](../README.md) · [文档导航](README.md) · [快速开始](getting-started.md)

STM32F407VET6 固件位于 [`src/firmware/`](../src/firmware/)。CubeMX、Keil 和各源码目录之间的相对布局保持一致。

## 工程入口

| 文件 | 用途 |
| --- | --- |
| [Luq Board.ioc](../src/firmware/Luq%20Board.ioc) | CubeMX 芯片、时钟、外设与中间件配置 |
| [Luq Board.uvprojx](../src/firmware/MDK-ARM/Luq%20Board.uvprojx) | Keil MDK-ARM 工程，target 为 `Luq Board` |
| [v1.0.0 固件镜像](../releases/v1.0.0/Luq_Board_v1.0.0.hex) | 随项目保存的可烧录 HEX 文件 |

## 源码职责

| 目录 | 内容 |
| --- | --- |
| `Core/` | CubeMX 生成的初始化、中断与 HAL 适配 |
| `Drivers/` | STM32 HAL 与 CMSIS 依赖 |
| `Middlewares/` | FreeRTOS 及 CMSIS-RTOS 接口 |
| `BMI270/` | Bosch BMI270 API |
| `Peripherals/` | CAN、UART、SPI、TIM、GPIO 和 IMU 的项目封装 |
| `Task/` | 用户任务与回调 |
| `MDK-ARM/` | Keil 工程、启动代码与本地构建输出 |

Keil 的本地输出目录为 `src/firmware/MDK-ARM/Luq Board/`，其中的 `.axf`、`.hex` 和中间文件默认忽略。对外提供的固件镜像统一位于 `releases/v1.0.0/`。

重生成 CubeMX 工程或调整文件分组后，应重新核对用户代码区、源文件引用和包含目录。外设配置与维护约定见 [开发与验证](development.md)。
