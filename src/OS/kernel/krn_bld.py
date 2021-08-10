
import os
import time


def shell(command):
	print(command)
	os.system(command)

def build(root, out, cdir):
	print(" compiling kernel ")
	shell("gcc -g -m32 -ffreestanding -nostdlib " + cdir + "kernel.c -o " + out + "\\kernel.o")