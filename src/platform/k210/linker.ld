/* K210 Linker Script for CScriptEngine Bootloader */

MEMORY
{
    FLASH (rx)  : ORIGIN = 0x00000000, LENGTH = 64K
    SRAM (rwx)  : ORIGIN = 0x20000000, LENGTH = 2M
}

ENTRY(_start)

_stack_top = 0x20200000;

SECTIONS
{
    .text 0x00000000 :
    {
        _stext = .;
        *(.text.startup)
        *(.text)
        *(.text.*)
        . = ALIGN(4);
        _etext = .;
    } > FLASH

    .rodata :
    {
        *(.rodata)
        *(.rodata.*)
        . = ALIGN(4);
    } > FLASH

    .data :
    {
        _sdata = .;
        *(.data)
        *(.data.*)
        . = ALIGN(4);
        _edata = .;
    } > SRAM AT>FLASH

    .bss :
    {
        _bss_start = .;
        *(.bss)
        *(.bss.*)
        *(COMMON)
        . = ALIGN(4);
        _bss_end = .;
    } > SRAM

    _heap_start = .;
    _heap_end = 0x20300000;
}
