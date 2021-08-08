bits	16		
org		0x7c00	

	call disk_load
	call [LOAD_ADRESS]
	hlt


disk_load: ; load 'dh' sectors from drive 'dl' into ES:BX
	
	cli

	mov dh, [NSECT_LOAD]
	mov bx, [LOAD_ADRESS]

    pusha
    push dx


    mov ah, 0x02 
    mov al, dh 
    mov cl, 0x02 
    mov ch, 0x00
    mov dh, 0x00
    int 0x13

    jc bsect_error

    pop dx

    cmp al, dh
    jne bsect_error

    popa
    ret

bsect_error:
	mov ah, 0x0e ; tty mode
	mov al, 'E'
	int 0x10


NSECT_LOAD dw 0x0005
LOAD_ADRESS dw 0x1000

times 510 - ($-$$) db 0
dw 0xAA55