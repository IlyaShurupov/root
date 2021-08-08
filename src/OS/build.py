
# ---------------  utils ------------------------- 

import os
import sys
from os.path import *
from shutil import *


def files_of_type(path, ext):
	files = []
	for root, dirs, files in os.walk(path):
		for file in files:
			if(file.endswith(ext)):
				files.append(os.path.join(root,file))
	return files


root = dirname(abspath(__file__))
out = join(root, "out")

def shell(command):
	print(command)
	os.system(command)

def mkdir(path_):
	if not exists(path_):
		os.makedirs(path_)

def add_files(A, B, C):
	open(C,'wb').write(open(A,'rb').read()+open(B,'rb').read())

# --------------- rools ------------------------- 

def clear():
	if exists(out): rmtree(out)

def build():
	mkdir(out)
 
	shell("nasm -f bin boot/boot.asm -o out/boot_tmp.bin")
	shell("nasm -f bin boot/bsect.asm -o out/bsect.bin")
	

def rebuild():
	clear()
	build()

def setup():
	with open("out/boot.bin", "w+") as file:
		pass

	add_files("out/bsect.bin", "out/boot_tmp.bin", "out/boot.bin")
	shell("qemu-img convert -O vmdk out/boot.bin out/drive.vmdk")

def run(vbox):
	if vbox == "qemu":
		shell("qemu -fda out/boot.bin")
	else:
		pass

# ---------------  entry ------------------------- 


for idx in range(1, len(sys.argv)):
	exec(sys.argv[idx])
