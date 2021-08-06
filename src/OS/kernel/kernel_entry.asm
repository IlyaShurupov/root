[bits 32]

[extern _entry] ; Define calling point. Must have same name as kernel.c 'main' function
call _entry; Calls the C function. The linker will know where it is placed in memory

