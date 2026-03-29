.global _start
.type _start, @function
.section .text.startup

_start:
    la sp, _stack_top
    jal zero, boot_main
    ebreak

.size _start, . - _start
