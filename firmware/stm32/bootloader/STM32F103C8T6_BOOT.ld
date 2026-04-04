/*
 * STM32F103C8T6 Internal Flash Linker Script for Bootloader
 * 64KB Flash, 20KB RAM
 */

ENTRY(Reset_Handler)

_estack = 0x20005000;

_Min_Heap_Size = 0x200;
_Min_Stack_Size = 0x400;

MEMORY
{
  FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 64K
  RAM (xrw)   : ORIGIN = 0x20000000, LENGTH = 20K
}

SECTIONS
{
  .isr_vector :
  {
    . = ALIGN(4);
    *(.isr_vector)
    . = ALIGN(4);
  } >FLASH

  .text :
  {
    . = ALIGN(4);
    *(.text)
    *(.text*)
    *(.rodata)
    *(.rodata*)
    . = ALIGN(4);
    _etext = .;
  } >FLASH

  .data :
  {
    . = ALIGN(4);
    _sdata = .;
    *(.data)
    *(.data*)
    . = ALIGN(4);
    _edata = .;
  } >RAM AT>FLASH

  _sidata = LOADADDR(.data);

  .bss :
  {
    . = ALIGN(4);
    _sbss = .;
    *(.bss)
    *(.bss*)
    *(COMMON)
    . = ALIGN(4);
    _ebss = .;
  } >RAM

  .heap :
  {
    . = ALIGN(4);
    _heap_start = .;
    . = . + _Min_Heap_Size;
    _heap_end = .;
  } >RAM

  .stack :
  {
    . = ALIGN(4);
    . = . + _Min_Stack_Size;
    _estack = .;
  } >RAM
}