org 0x0	
bits 16
 
mov ah, 0x0e ; tty mode
mov al, 'H'
int 0x10
 


 
times 512 db 0
dw 0xAAaa