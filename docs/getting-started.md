# 快速开始

[返回项目首页](../README.md) · [文档导航](README.md)

Master Control Board `v1.0.0` 面向 STM32F407VET6。使用前请确认实际板卡和工程的芯片、供电与接口配置相符。

## 准备环境

| 工具 | 用途 |
| --- | --- |
| STM32CubeMX | 查看或修改芯片、时钟、引脚和中间件配置 |
| Keil MDK-ARM | 编译工程并进行下载、调试 |
| ARM Compiler | 工程记录为 5.06 update 7 (build 960)，使用 ARMCC |
| STM32F4 Device Pack | 工程记录为 Keil.STM32F4xx_DFP 2.11.0 |
| ST-Link 或 J-Link | 连接板卡并烧录、调试 |
| STM Studio（可选） | 通过项目配置观察 IMU 变量 |

工程入口为 [Luq Board.uvprojx](../src/firmware/MDK-ARM/Luq%20Board.uvprojx)，CubeMX 配置为 [Luq Board.ioc](../src/firmware/Luq%20Board.ioc)。表中编译器与 Device Pack 版本来自工程文件，不代表最低兼容版本或本次已完成构建验证。若当前 MDK 默认使用 Arm Compiler 6 / armclang，应先配置工程所需的 ARMCC，或另行完成迁移和验证。仓库没有附带这些开发工具。

## 编译固件

1. 用 Keil 打开 `src/firmware/MDK-ARM/Luq Board.uvprojx`。
2. 确认目标为 `Luq Board`，器件为 STM32F407VETx，并安装缺少的 STM32F4 Device Pack。
3. 执行 Build，确认没有编译或链接错误。
4. 在 `src/firmware/MDK-ARM/Luq Board/` 查看本次生成的 `.hex` 和 `.axf`。

通常无需先重新生成 CubeMX 代码。需要修改外设配置时，保留用户代码区并检查 Keil 文件分组与包含路径，详情见 [开发与验证](development.md)。

## 烧录与观察

使用 ST-Link 或 J-Link 连接实际板卡，按照所用下载工具设置目标芯片与连接方式后，烧录本次构建的 HEX。仓库另保留 [Luq_Board_v1.0.0.hex](../releases/v1.0.0/Luq_Board_v1.0.0.hex) 作为随项目提供的镜像，目录整理没有重新编译该文件。

需要观察 IMU 时，打开 [STM Studio 项目](../tools/stm-studio/st-studio-imu.tsp)，使用与已烧录固件对应的 AXF 更新变量信息。具体相对路径和日志位置见 [开发与验证](development.md#stm-studio-观察-imu)。

## 制作硬件

| 资料 | 入口 |
| --- | --- |
| PCB 工程 | [luq_board.eprj](../hardware/pcb/luq_board.eprj) |
| Gerber、BOM 与贴片坐标 | [制造文件目录](../hardware/pcb/manufacturing/) |
| 外壳与 3D CAD | [机械文件目录](../hardware/mechanical/) |
| 芯片参考资料 | [datasheets](../hardware/datasheets/) |
| 装配照片 | [photos](assets/photos/) |

下单前结合板厂能力核对叠层、板厚、阻抗、器件封装与替代料。制造细节见 [制造资料说明](hardware/manufacturing.md)，组装时参考 [装配注意事项](hardware/assembly-notes.md) 和 [IMU 设计记录](hardware/imu-layout-notes.md)。

## 下一步

源码职责见 [固件目录说明](firmware-layout.md)。实际使用前应验证所需接口、控制逻辑和板卡行为；现有静态路径检查不代替编译、烧录和硬件测试。
