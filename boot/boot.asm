global _start
extern main


section .multiboot
align 4

    dd 0x1BADB002
    dd 0x00000003
    dd -(0x1BADB002 + 0x00000003)



section .bss
align 4096


p4_table:
    resb 4096

p3_table:
    resb 4096

p2_table:
    resb 4096


stack_bottom:
    resb 65536

stack_top:



section .text
bits 32


_start:

    cli

    mov esp, stack_top


; -------------------------
; Page tables
; -------------------------


    mov eax, p3_table
    or eax, 3
    mov [p4_table], eax


    mov eax, p2_table
    or eax, 3
    mov [p3_table], eax



; identity map első 1GB
; 2MB huge pages


    xor ecx, ecx


.map:

    mov eax, ecx
    shl eax, 21

    or eax, 0x83

    mov [p2_table + ecx*8], eax

    mov dword [p2_table + ecx*8 + 4], 0


    inc ecx

    cmp ecx, 512
    jne .map



; CR3

    mov eax, p4_table
    mov cr3, eax



; PAE

    mov eax, cr4
    or eax, 1 << 5
    mov cr4, eax



; Long mode enable

    mov ecx, 0xC0000080
    rdmsr

    or eax, 1 << 8

    wrmsr



; paging enable

    mov eax, cr0
    or eax, 1 << 31
    mov cr0, eax



; GDT

    lgdt [gdt64.pointer]


; ugrás 64 bitbe

    jmp 0x08:_start64




bits 64


_start64:


    mov ax,0

    mov ds,ax
    mov es,ax
    mov ss,ax


    call main



.hang:

    cli
    hlt

    jmp .hang





section .rodata

align 8


gdt64:


dq 0


.code:

dq 0x00AF9A000000FFFF



.pointer:

dw $ - gdt64 - 1

dq gdt64