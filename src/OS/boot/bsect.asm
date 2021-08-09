bits	16		
org		0x7c00	

	call disk_load
	call [LOAD_ADRESS]

disk_load: ; load 'dh' sectors from drive 'dl' into ES:BX
	
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax

	cli

    mov ah, 0x0e
    mov al, 'E'
    int 0x10

	mov dh, [NSECT_LOAD]
	mov bx, [LOAD_ADRESS]

    pusha
    push dx

   ;z mov dl, 0x80
    mov ah, 0x02 
    mov al, dh
    mov cl, 0x02 
    mov ch, 0x00
    mov dh, 0x00
    int 0x13

    jc drive_error

    pop dx

    cmp al, dh
    jne nload_error

    popa
    ret

print_str_rm:
    

nload_error:
	mov ah, 0x0e
	mov al, 'N'
	int 0x10
    hlt

drive_error:
    mov ah, 0x0e
    mov al, 'D'
    int 0x10
    hlt

times 512 - ($-$$) - (data_end - data_start) db 0

data_start:
    
    LOAD_ADRESS dw 0x1000
    NSECT_LOAD dw 0x0000
    dw 0xAA55

data_end: