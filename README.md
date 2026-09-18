# Master Control Board

<div align="center">

**面向机器人控制系统的开源 STM32 主控板**<br>
*An open-source STM32 control board for robotics projects*

[![Version](https://img.shields.io/github/v/tag/luqqqqqqq/Master-Control-Board?label=version&color=2563eb)](https://github.com/luqqqqqqq/Master-Control-Board/tree/v1.0.0)
[![License](https://img.shields.io/badge/license-GPL--3.0-7c3aed.svg)](LICENSE)

</div>

<p align="center">
  <img src="v1.0.0/hardware/photos/assembly-final.jpg" alt="Assembled Master Control Board" width="48%" />
  <img src="v1.0.0/hardware/photos/assembly-early.jpg" alt="Early assembly" width="48%" />
</p>

## 项目简介

Master Control Board 是一块以 **STM32F407VET6** 为核心、集成 **BMI270 六轴 IMU** 的机器人主控板，定位类似 DJI C Board 的通用控制核心。当前稳定版本已经在 RM 比赛项目中实际使用，仓库同时提供 PCB、固件、外壳和制造资料。

The repository contains the complete `v1.0.0` hardware and firmware snapshot. The design is usable, but formal electrical and environmental parameter testing is still incomplete.

## 主要特性

| 模块 | 配置 |
| --- | --- |
| MCU | STM32F407VET6，LQFP100，Cortex-M4F |
| IMU | Bosch BMI270，SPI2 接口 |
| 实时系统 | FreeRTOS / CMSIS-RTOS v1 |
| 总线 | CAN1、CAN2（当前 CubeMX 配置为 1 Mbps） |
| 串行接口 | USART1/2/3/6、UART4/5 |
| 其他外设 | SPI1、SPI2、IWDG、RGB 指示灯、激光/外部中断接口 |

## 目录结构

```text
.
├── v1.0.0/
│   ├── firmware/                 # CubeMX、Keil 工程和应用/驱动源码
│   │   ├── Core/                 # HAL 初始化与中断
│   │   ├── Drivers/              # STM32 HAL、CMSIS 等第三方驱动
│   │   ├── BMI270/               # BMI270 驱动
│   │   ├── Peripherals/          # CAN、UART、SPI、TIM、GPIO 等封装
│   │   ├── Task/                 # 用户任务与回调
│   │   ├── MDK-ARM/              # Keil 工程文件
│   │   └── releases/              # 可直接烧录的固件镜像
│   └── hardware/
│       ├── pcb/                  # PCB 工程、制造文件、BOM
│       ├── mechanical/           # 外壳与 3D CAD 文件
│       ├── datasheets/           # 芯片参考资料
│       └── photos/               # 装配照片
├── docs/                         # 开发与制造说明
├── CHANGELOG.md
└── LICENSE
```

## 快速开始

### 编译固件

1. 安装 STM32CubeMX 和 Keil MDK-ARM，并准备 STM32F4 Device Pack。
2. 用 Keil 打开 [`Luq Board.uvprojx`](v1.0.0/firmware/MDK-ARM/Luq%20Board.uvprojx)。
3. 选择 `Luq Board` target 后执行 Build。Keil 会在本地生成中间文件和 `.hex`，这些构建产物默认不会提交。
4. 使用 ST-Link 或 J-Link 将固件烧录到 STM32F407VET6。仓库内也提供了 [v1.0.0 预编译镜像](v1.0.0/firmware/releases/Luq_Board_v1.0.0.hex)。

CubeMX 工程位于 [`Luq Board.ioc`](v1.0.0/firmware/Luq%20Board.ioc)。更完整的外设配置和驱动说明见 [`docs/firmware-setup.md`](docs/firmware-setup.md) 与 [`firmware/README.md`](v1.0.0/firmware/README.md)。

### 制作硬件

- PCB 工程：[`v1.0.0/hardware/pcb/luq_board.eprj`](v1.0.0/hardware/pcb/luq_board.eprj)
- 制造资料：[`hardware/pcb/manufacturing/`](v1.0.0/hardware/pcb/manufacturing/)，包含 BOM、贴片坐标和 Gerber 压缩包
- 机械文件：[`hardware/mechanical/`](v1.0.0/hardware/mechanical/)，提供直插/弯插两种外壳方案
- 装配注意事项：[`assembly-notes.md`](v1.0.0/hardware/mechanical/assembly-notes.md)

下单前请根据板厂能力重新确认叠层、阻抗、板厚和器件封装。PCB 中的陀螺仪区域需要尽量减少机械应力，相关设计记录见 [`imu-layout-notes.md`](v1.0.0/hardware/pcb/imu-layout-notes.md)。

## 当前状态

- **版本：** `v1.0.0` / Stable
- **验证：** 已在 RM 比赛项目中投入使用
- **待完善：** 温漂、振动、长期稳定性和完整电气参数测试尚未形成正式报告
- **兼容性：** 工程配置以 STM32F407VET6 为准；旧目录名中的 `VGT6` 是历史命名

## 致谢

感谢 **SZU PR 战队** 提供设备支持和测试条件。

## 许可证

项目顶层采用 [GNU GPL-3.0](LICENSE)。STM32 HAL、CMSIS、FreeRTOS 和 BMI270 API 等第三方代码保留其原始许可证与版权声明；分发时请一并遵守对应目录中的许可文件。
