
void dummy_test_entrypoint() {
}

void krnl_entry() {
    char* video_memory = (char*) 0xb8000;
    *video_memory = 'X';


	unsigned char* p = (unsigned char*) 0xa0000;

    while (1) {
    	int g = 0;
    	g ++;
    }
}
