
#include <iostream>

using namespace std;









class SCI {
public:

	Dict<Str, void*> scit;

	SCI() {
		scit.Put("__alloc", __alloc);
	}

};

struct Opcd {
	Opcd(char size_byte, char code, char args_len) 
		: args_size_byte(args_size_byte), code(code), args_len(args_len) 
	{}

	char args_size_byte;
	char args_len;
	char code;
};

class OPCtx64 {
public:

	Dict<Str, Tuple<char, char>> ops;

	OPCtx64() {
		ops.Put("call", Opcd(0xe8, 5, 1));
		ops.Put("ret", Opcd(0xe8, 0, 0));
		ops.Put("nop", Opcd(0x90, 0, 0));
	}

};

bool get_symbol(Str& str, Range in, Range& out) {
}

bool load_exec(void* load_adress, File& file, OPCtx64& opct, SCI& scit) {

	Str assembly;
	assembly.clear();
	assembly.str = file.buff;
	assembly.length = file.size;

	int line_start = 0;
	int line_end = 0;

	while (line_end != -1) {
		line_end = assembly.find('\n', Range(line_start, assembly.length));

		int line_end_no_comment = assembly.find("\\", Range(line_start, assembly.length));
		if (line_end_no_comment != -1) {
			line_end_no_comment = line_end;
		}

		bool line_is_empty = true;
		
		for (int idx = line_start; idx < line_end_no_comment; idx++) {
			if (assembly[idx] != ' ') {
				break;
			}
		}

		if (line_is_empty) {
			continue;
		}

		Range symbol_range;
		while (get_symbol(assembly, Range(), symbol_range)) {

		}

		line_start = line_end + 1;
	}
}

int main(int argc, char* argv[]) {

	File assembly((argc == 1) ? "D:\\Dev\\intern\\rtc\\tmp\\test.rtc" : argv[1]);
	
	SCI sci;
	OPCtx64 opct;

	void* el_adress = alloc_rwe(1000);
	
	load_exec(el_adress, assembly, opct, sci);

	((void (*)())el_adress)();

	//int bcode_len;
	//char* bcode = hexcode2bin(hexcode.buff, hexcode.size, &bcode_len);

	//int g = ((int (*)(int))bcode)(g);

	cout << g;
	cin >> g;
}