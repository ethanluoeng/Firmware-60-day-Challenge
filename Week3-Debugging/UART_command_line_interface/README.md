# UART Command-Line Interface

A serial command interpreter for an STM32 Nucleo board. Send plain-text
commands over UART (via the ST-Link virtual COM port) and the MCU parses
them and executes — toggling an LED, or setting a PWM duty cycle. Reception is fully interrupt-driven.

This project is located in: Week3_Workspace/UART_command_line_interface

## Available commands

| Command       | Effect                                      |
|---------------|----------------------------------------------|
| `led on`      | Turns the onboard LED (LED2) on               |
| `led off`     | Turns the onboard LED off                     |
| `pwm <0-100>` | Sets TIM3 CH1 PWM duty cycle to N percent     |

Unrecognized commands or malformed arguments are meant to get an error
reply.

## How it works

Serial input → UART RX interrupt pushes each byte into a ring buffer → main loop drains the buffer into a line buffer -> after a newline, the line is parsed into a command and dispatched.

## Hardware

- **UART:** USART2 — PA2 (TX) / PA3 (RX), wired to the ST-Link's virtual
  COM port. 115200 baud, 8N1.
- **LED:** onboard LED2 (BSP_LED_On/Off).
- **PWM:** TIM3 Channel 1, output on **PA6**. Internal
  clock, prescaler 0, ARR 65535 → PWM frequency ≈ 763 Hz.

## Firmware structure

```
Core/
  Inc/ringbuffer.h     ring buffer struct + function prototypes
  Src/ringbuffer.c      ring buffer functions
  Src/main.c             USART2 IT setup, RxCpltCallback, line assembly loop,
                          String_Parse_Compare (command dispatch), TIM3/PWM setup
```

## What I learned

- **`volatile` matters for ISR-shared state.** Ring buffer head/tail
  indices are written by the ISR and read by the main loop — without
  `volatile`, the compiler is free to cache stale values in registers
  under optimization, producing bugs that only appear in release builds.
- **The ring buffer full/empty ambiguity.** With just head and tail
  indices, `head == tail` means both "empty" and "full" — solved here by
  sacrificing one slot (array size = usable capacity + 1) so `head == tail`
  is unambiguous.
- **`HAL_UART_Receive_IT` is one-shot.** It has to be explicitly re-armed
  inside the callback after every single byte, or subsequent bytes vanish
  silently.
- **Arrays decay to pointers, and `&array` is a trap.** Passing
  `&rb_storage` instead of `rb_storage` (or `&line_buf` instead of
  `line_buf`) produces a differently-typed pointer (`T (*)[N]` instead of
  `T *`) that looks superficially fine but is wrong — a mistake made (and
  caught) more than once during this build.
- **Header/implementation signature drift breaks the build in confusing
  ways.** "Conflicting types" and "too many arguments" errors, most of the
  time, trace back to a `.h` prototype and `.c` definition disagreeing
  after one side got edited and the other didn't.
- **`strtok` mutates the original string in place**, planting `'\0'` at
  each delimiter rather than copying — meaning the buffer it's given has
  to be writable, and is no longer one contiguous string afterward.
- **HAL's `TIM_CHANNEL_x` macros are bit-offsets, not sequential
  numbers** (`TIM_CHANNEL_1 == 0`, `TIM_CHANNEL_2 == 4`, ...). Passing a
  literal `1` where `TIM_CHANNEL_1` was meant silently enables the wrong
  bit in hardware — a bug with no compiler warning, only found by tracing
  through what the macro actually expands to.
- **PWM frequency is `clock / ((PSC+1) × (ARR+1))`**, and on STM32, APB
  timer clocks are automatically doubled whenever their bus prescaler
  isn't `/1` — worth checking the clock tree diagram directly rather than
  assuming PCLK == timer clock.
- **CubeMX regeneration is non-destructive to `USER CODE` blocks** — it
  overwrites the same project in place, preserving anything written
  between `USER CODE BEGIN/END` markers and regenerating everything
  outside them.

## Verifying it with PulseView

Captured PA6 (Nucleo CN10 pin 13) with a logic analyzer at
1 MHz sample rate, after sending `pwm 10` and `pwm 80` over the terminal.

```
![PulseView PWM capture](/PWM_10_to_80_percent_readings.png)
```


