
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
 
	# compile
	shell("nasm -g -f bin boot/boot.asm -o out/boot_tmp.bin")
	shell("nasm -g -f bin boot/bsect.asm -o out/bsect.bin")
	
	# align boot size with 512 bytes
	boot_size = os.path.getsize("out/boot_tmp.bin")
	alignment = 512 - (boot_size % 512)
	with open("out/boot_tmp.bin", "r+b") as file:
		fiil = 0
		file.seek(boot_size)
		for idx in range(alignment):
			file.write(fiil.to_bytes(1, 'big'))
	boot_size += alignment

	# combine binaries
	with open("out/boot.bin", "w+") as file:
		pass

	add_files("out/bsect.bin", "out/boot_tmp.bin", "out/boot.bin")
	shell("qemu-img convert -O vmdk out/boot.bin out/drive.vmdk")

	# tell the size of binaries to bsect
	fh = open("out/boot.bin", "r+b")
	fh.seek(508)
	fh.write(int(boot_size / 512).to_bytes(2, 'little'))

	
	copyfile("out/boot.bin", "out/boot.iso")


def rebuild():
	clear()
	build()


def run(vbox, commands):
	if vbox == "qemu":
		shell("qemu " + commands + " -hda out/boot.bin")
	else:
		pass

# ---------------  entry ------------------------- 


try:
	for idx in range(1, len(sys.argv)):
		exec(sys.argv[idx])

except Exception as e:
	import traceback
	import logging
	logging.error(traceback.format_exc())
    # Logs the error appropriately. 




shell("timeout 3")
