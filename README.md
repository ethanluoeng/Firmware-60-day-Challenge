# Firmware-60-day-Challenge

## Introduction
At the time, I was fearful that AI would replace me. I also wanted to learn more about embedded systems but because my understanding was pretty shallow, I didn't have an idea for a project. Therefore, I did the only thing that engineers do in 2026, which was to ask AI! Specifically, I prompted Claude to generate me a 2-month (60 day) roadmap that I could follow religiously to teach me the fundementals and skills that firmware employers were looking for. 

## Structure

```
Firmware-60-day-Challenge/
├── Week1-C/
├── Week 2 - STM32 toolchain, ARM Cortex-M/
├── Week3-Debugging/
│   └── UART_command_line_interface/
├── Week6-FreeRTOS/
├── Daily_Logs.txt
└── embedded_2month_plan.pdf
```

## Weekly Breakdown

### Daily Logs
Daily_Logs is where I kept track of everything new I had learned.

### Week 1 - C

### Week 2 - STM32 Toolchain, ARM Cortex-M

### Week 3 - Debugging

### Week 6 - FreeRTOS

## Tools & Hardware
Refer to page 2 of embedded_2month_plan.pdf

## AI Documentation

### Prompts Used to Create the Plan
```
I'm currently studying mechatronics. Acting as a senior engineer with deep, current knowledge of the field and a strong sense of where it's heading, recommend 5 skills worth investing significant time in — ones I can realistically learn using just my laptop (plus maybe a few affordable components/hardware). Each skill should have strong potential to lead to a well-paying job in the next few years. 

The skills don't need to be strictly mechatronics, but they should meaningfully overlap with my education so the effort compounds rather than scatters. For each skill, briefly explain: why it's in demand now, why you expect that to hold or grow, and what a realistic learning path looks like from scratch. Please research current job market trends and industry signals rather than relying purely on general assumptions.
```

```
Create a focused 2-month learning plan covering exactly this scope — nothing more, nothing less:

Topics to learn: C programming in depth (memory layout, undefined behavior, linker scripts), one RTOS (FreeRTOS or Zephyr — note Zephyr's rising adoption), ARM Cortex-M architecture, peripheral programming (I2C, SPI, UART, CAN), interrupt handling, and hands-on use of a logic analyzer and oscilloscope.

Hardware to buy: an STM32 Nucleo board (~$20), a Raspberry Pi Pico (~$5), a budget logic analyzer/Saleae clone (~$15), and a decent multimeter (~$50) — no other purchases.

End goal: build one real, substantial project (e.g., a brushless motor controller, a sensor logger, or a CAN bus sniffer) and publish it on GitHub with documentation and captured scope/logic-analyzer traces. This portfolio piece is meant to substitute for the "years of experience" credential gap.

Structure the plan week-by-week, sequencing topics so hardware purchases align with when they're needed and the final project builds naturally out of the skills learned earlier. Include a clearly organized shopping list (item, purpose, approximate price) separate from the weekly plan.

Once the plan is finalized, compile it into a PDF.
```

### AI Errors
- In the plan: "Add Phil's Lab on YouTube (@PhilsLab) — his videos use VS Code + PlatformIO, closer to professional practice." This is not true, PhilsLab mainly uses STM32CubeIDE.

## Reflection
Overall, this challenge was a success. By commiting around 2 hours everyday for 2 months, I'd deepened my understanding on microcontrollers, bare-metal programming, DMA, the gritty linker-scripts that run under the hood, communication protocals, and FreeRTOS. All of which have increased my confidence towards this field. The AI plan was very logical, told me exactly what to buy, and guided me through the course with quality resources (with an exception that I'll address), and I never had to pause and think about what I should learn next. However, there were a few downsides. Mostly, it was pretty boring at times. Since I told Claude to make it "intensive", the plan is quite thorough and repetitive. Because of this, I ended up skipping 2 weeks, and then switched to a different project as soon as I had a good idea. My recommendation is to stick with it until it gets to the point were you are undoubtebly inspired to work on something else.

## Next Steps
- Come back and learn CAN if school courses do not cover it.
- Week 8 tasks include: Wiring photo or schematic, Logic analyzer screenshots, 'bugs I fixed' section, and a 1500–2500 word technical blog on the most interesting bug I fixed. These are some great ideas for a different project or a capstone project.
