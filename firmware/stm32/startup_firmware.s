/**
 * @brief STM32 Firmware Startup Code
 *
 * This is a minimal startup for firmware that runs from RAM.
 * The bootloader loads this firmware to RAM and jumps to _start.
 */

.syntax unified
.cpu cortex-m3
.fpu softvfp
.thumb

.global _start
.global _estack

.extern _etext
.extern _sdata
.extern _edata
.extern _sbss
.extern _ebss
.extern main

.section .text._start
.type _start, %function

_start:
    ldr r0, =_estack
    mov sp, r0

    movs r1, #0
    b check_copy

copy_loop:
    ldr r3, =_sidata
    ldr r3, [r3, r1]
    ldr r2, =_sdata
    add r2, r2, r1
    str r3, [r2]
    adds r1, r1, #4

check_copy:
    ldr r2, =_sdata
    ldr r3, =_edata
    adds r2, r2, r1
    cmp r2, r3
    bcc copy_loop

    ldr r2, =_sbss
    ldr r3, =_ebss
    b check_zero

zero_loop:
    movs r3, #0
    str r3, [r2], #4

check_zero:
    cmp r2, r3
    bcc zero_loop

    bl SystemInit

    bl main

loop_forever:
    b loop_forever

.size _start, .-_start
