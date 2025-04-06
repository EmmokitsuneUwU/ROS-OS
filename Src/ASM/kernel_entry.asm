section .text
    [bits 32]
    global _start
    [extern main]

_start:
    mov edi, 0xB8000
    mov eax, 0x2F41
    mov [edi], eax

    mov esp, 0x90000
    mov ebp, esp

    mov edi, 0xB8002
    mov eax, 0x2F42
    mov [edi], eax

    call main

    mov edi, 0xB8004
    mov eax, 0x2F43
    mov [edi], eax

    jmp $
