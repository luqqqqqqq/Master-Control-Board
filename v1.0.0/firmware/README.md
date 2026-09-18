# Firmware

Firmware for the STM32F407VET6 control board.

## Build entry points

- CubeMX configuration: [`Luq Board.ioc`](Luq%20Board.ioc)
- Keil MDK-ARM project: [`MDK-ARM/Luq Board.uvprojx`](MDK-ARM/Luq%20Board.uvprojx)
- Flashable release image: [`releases/Luq_Board_v1.0.0.hex`](releases/Luq_Board_v1.0.0.hex)

The source is organized around the CubeMX-generated `Core/` tree, STM32/HAL and CMSIS dependencies in `Drivers/`, the BMI270 API in `BMI270/`, and project-specific drivers/tasks in `Peripherals/` and `Task/`.

Open the Keil project, select the `Luq Board` target, and build. Keil output folders are intentionally ignored; only source, project configuration and the release image are versioned.
