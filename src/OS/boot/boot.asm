
[bits 16]
 
mov ah, 0x0e ; tty mode
mov al, 'S'
int 0x10
 
jmp switch_to_pm

db " ****************************** HARDWARE SETUP  ****************************** ", 0

; ----------------------------------- GDT -------------------------------------------- \

gdt_start: ; don't remove the labels, they're needed to compute sizes and jumps
    ; the GDT starts with a null 8-byte
    dd 0x0 ; 4 byte
    dd 0x0 ; 4 byte

; GDT for code segment. base = 0x00000000, length = 0xfffff
; for flags, refer to os-dev.pdf document, page 36
gdt_code: 
    dw 0xffff    ; segment length, bits 0-15
    dw 0x0       ; segment base, bits 0-15
    db 0x0       ; segment base, bits 16-23
    db 10011010b ; flags (8 bits)
    db 11001111b ; flags (4 bits) + segment length, bits 16-19
    db 0x0       ; segment base, bits 24-31

; GDT for data segment. base and length identical to code segment
; some flags changed, again, refer to os-dev.pdf
gdt_data:
    dw 0xffff
    dw 0x0
    db 0x0
    db 10010010b
    db 11001111b
    db 0x0

gdt_end:

; GDT descriptor
gdt_descriptor:
    dw gdt_end - gdt_start - 1 ; size (16 bit), always one less of its true size
    dd gdt_start ; address (32 bit)

; define some constants for later use
CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start

; ----------------------------------- PRINT PM -------------------------------------------- \

  
[bits 32] ; using 32-bit protected mode

VIDEO_MEMORY equ 0xb8000
WHITE_ON_BLACK equ 0x0f 

puts_pm:
    pusha
    mov edx, VIDEO_MEMORY

puts_pm_loop:
    mov al, [ebx] ; [ebx] is the address of our character
    mov ah, WHITE_ON_BLACK

    cmp al, 0 ; check if end of string
    je puts_pm_done

    mov [edx], ax ; store character + attribute in video memory
    add ebx, 1 ; next char
    add edx, 2 ; next video memory position

    jmp puts_pm_loop

puts_pm_done:
    popa
    ret

; ----------------------------------- SWITCH PM -------------------------------------------- \

[bits 16]
switch_to_pm:
    
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax


    cli ; 1. disable interrupts
    lgdt [gdt_descriptor] ; 2. load the GDT descriptor
    mov eax, cr0
    or eax, 0x1 ; 3. set 32-bit mode bit in cr0
    mov cr0, eax

    jmp CODE_SEG:init_pm ; 4. far jump by using a different segment

[bits 32]
init_pm: ; we are now using 32-bit instructions
    
    mov ax, DATA_SEG ; 5. update the segment registers
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov ebp, 0x90000 ; 6. update the stack right at the top of the free space
    mov esp, ebp

 	mov ebx, MSG_PM
    call puts_pm ; Note that this will be written at the top left corner
   

[extern _krnl_entry]
    call _krnl_entry
    hlt


MSG_PM db " PM ", 0

db " ****************************** HARDWARE SETUP END ****************************** ", 0