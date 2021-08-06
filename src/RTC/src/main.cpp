
#include "Types.h"

#include <Windows.h>

void* alloc_rwe(int size) {
	LPVOID lpvBase;
	LPTSTR lpPtr;
	lpvBase = VirtualAlloc(NULL, size, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	lpPtr = (LPTSTR)lpvBase;
	return lpPtr;
}

char* hexcode2bin(char* buff_in, int buff_size, uint4* out_size) {
	int length = 0;
	for (int i = 0; i < buff_size; i++) {

		if (buff_in[i] == ' ' || buff_in[i] == '\n') {
			continue;
		}

		length++;
	}

	char* bytecode = (char*)alloc_rwe((length / 2) * sizeof(char));

	length = 0;
	for (int i = 0; i < buff_size; i++) {

		if (buff_in[i] == ' ' || buff_in[i] == '\n') {
			continue;
		}

		if (length & 1) {
			char hex[3] = { buff_in[i - 1], buff_in[i], '\0' };
			char* p;
			bytecode[length / 2] = strtol(hex, &p, 16);
		}

		length++;
	}

	*out_size = length;
	return bytecode;
}

void __alloc(aligned size, aligned out) {
	out = (aligned)malloc(size);
}

struct SYSCALLS : Array<void*> {
	
	SYSCALLS() {
		PushBack(__alloc);
	}

};

//#include <bitset>

uint4 invert_bits_32(uint4 in) {

	for (int i = 0; i < 32; i++) {
		in ^= 1UL << i;
	}

	return in;
}

uint4 twosc_32(uint4 in) {
	return invert_bits_32(in) + 1;
}

void relosve_syscalls(Array<char>& binary, SYSCALLS& syscalls) {
	
	Array<char> call_pattern(232, 0, 0, 0);

	for (int i = 0; i < binary.length; i++) {

		bool found = true;
		for (int j = 0; j < call_pattern.length; j++) {
			if (binary[i + j] != call_pattern[j]) {
				found = false;
				break;
			}
		}

		if (found) {

			void* func_adress = syscalls[binary[i + 4]];
			void* opcode_adress = (uint8*)binary.buff + i;
			uint8* invoke_adress = (uint8*)(binary.buff + i + 1);

			uint8 jmp_offset = (uint8)func_adress - (uint8)opcode_adress;
			uint4 jmp_offset_32bit = (uint4)jmp_offset;

			jmp_offset_32bit = invert_bits_32(jmp_offset_32bit) + 1;

			*((char*)invoke_adress + 0) = *((char*)(&jmp_offset_32bit) + 3);
			*((char*)invoke_adress + 1) = *((char*)(&jmp_offset_32bit) + 2);
			*((char*)invoke_adress + 2) = *((char*)(&jmp_offset_32bit) + 1);
			*((char*)invoke_adress + 3) = *((char*)(&jmp_offset_32bit) + 0);

			//*invoke_adress = jmp_offset_32bit;
		}
	}
}

int main(int argc, char* argv[]) {

	File hexcode((argc == 1) ? "D:\\Dev\\intern\\rtc\\test.rtc" : argv[1]);
	
	Array<char> binary;
	binary.buff = hexcode2bin(hexcode.buff, hexcode.size, &binary.length);

	SYSCALLS syscalls;
	relosve_syscalls(binary, syscalls);

	((void (*)())binary.buff)();
	

	while (1) {}
}