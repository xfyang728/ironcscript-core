/*
 * STM32F103C8T6 RAM Linker Script for IronCScript VM Firmware
 *
 * This firmware is loaded into internal SRAM by the bootloader from
 * external SPI Flash (W25Q64).
 *
 * IMPORTANT: This firmware runs entirely from RAM, not from FLASH!
 * The FLASH memory region here is only used to store the .bin file
 * before it is programmed to external SPI Flash.
 */

ENTRY(_start)

_estack = 0x20005000;

_Min_Heap_Size = 0x2000;
_Min_Stack_Size = 0x1000;

MEMORY
{
  FLASH (rx)  : ORIGIN = 0x08001000, LENGTH = 60K
  RAM (xrw)   : ORIGIN = 0x20000000, LENGTH = 20K
}

SECTIONS
{
  .isr_vector :
  {
    . = ALIGN(4);
    _svector = .;
    *(.isr_vector)
    . = ALIGN(4);
    _evector = .;
  } >RAM

  .text :
  {
    . = ALIGN(4);
    _stext = .;
    *(.text)
    *(.text*)
    *(.rodata)
    *(.rodata*)
    . = ALIGN(4);
    _etext = .;
  } >RAM

  .data :
  {
    . = ALIGN(4);
    _sdata = .;
    *(.data)
    *(.data*)
    . = ALIGN(4);
    _edata = .;
  } >RAM

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
    _sstack = .;
    . = . + _Min_Stack_Size;
    . = ALIGN(4);
    _estack = .;
  } >RAM
}

_prog_start = _stext;
_firmware_size = _ebss - _stext;
