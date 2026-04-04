#include <_ansi.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "stm32f10x.h"

extern caddr_t _end;

caddr_t _sbrk(int incr) {
    static unsigned char *heap = NULL;
    unsigned char *prev_heap;
    if (heap == NULL) {
        heap = (unsigned char *)&_end;
    }
    prev_heap = heap;
    heap += incr;
    return (caddr_t)prev_heap;
}

void _exit(int status) {
    (void)status;
    while (1) {
        __asm__ volatile ("WFI");
    }
}

int _close(int file) {
    (void)file;
    return -1;
}

int _fstat(int file, struct stat *st) {
    (void)file;
    st->st_mode = S_IFCHR;
    return 0;
}

int _getpid(void) {
    return 1;
}

int _isatty(int file) {
    (void)file;
    return 1;
}

int _kill(int pid, int sig) {
    (void)pid;
    (void)sig;
    return -1;
}

int _lseek(int file, int ptr, int dir) {
    (void)file;
    (void)ptr;
    (void)dir;
    return 0;
}

int _open(const char *name, int flags, int mode) {
    (void)name;
    (void)flags;
    (void)mode;
    return -1;
}

int _read(int file, char *ptr, int len) {
    (void)file;
    (void)ptr;
    (void)len;
    return 0;
}

int _write(int file, char *ptr, int len) {
    (void)file;
    int i;
    for (i = 0; i < len; i++) {
        uint8_t ch = (uint8_t)ptr[i];
        while ((USART1->SR & USART_SR_TXE) == 0);
        USART1->DR = ch;
        if (ch == '\n') {
            while ((USART1->SR & USART_SR_TXE) == 0);
            USART1->DR = '\r';
        }
    }
    return len;
}

void _kill_r(struct _reent *r, int pid, int sig) {
    (void)r;
    (void)pid;
    (void)sig;
}

int _getpid_r(struct _reent *r) {
    (void)r;
    return 1;
}

void _exit_r(struct _reent *r, int status) {
    (void)r;
    (void)status;
    while (1) {
        __asm__ volatile ("WFI");
    }
}

void _fini(void) {
}

void __libc_init_array(void) {
}

void __libc_fini_array(void) {
}

void __dso_handle(void) {
}