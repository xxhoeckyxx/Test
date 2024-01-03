.section __TEXT,__text,regular,pure_instructions

.globl _main

_main:
    # Systemaufrufnummer für write
    mov $0x2000004, %rax

    # Dateideskriptor für die Standardausgabe (STDOUT)
    mov $1, %rdi

    # Zeiger auf die Zeichenkette (Hello, World!\n)
    lea message(%rip), %rsi

    # Länge der Zeichenkette
    mov $13, %rdx

    # Systemaufruf
    syscall

    # Exit-Systemaufruf
    mov $0x2000001, %rax
    xor %rdi, %rdi
    syscall

.section __DATA,__data
message:
    .asciz "Hello, World!\n"
