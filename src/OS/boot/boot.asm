org 0x0	
bits 16
 
mov ah, 0x0e ; tty mode
mov al, 'S'
int 0x10
 
