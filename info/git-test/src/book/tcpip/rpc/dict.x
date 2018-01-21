const MAX_WORD = 50;
const DIC_SIZE = 100;

struct example {
	int ex_field_1;
	int ex_field_2;
};

program DICT_PROGRAM {
	version DICT_VERSION {
		int INIT(void) = 1;
		int INSERT(string) = 2;
		int DELETE(string) = 3;
		int LOOKUP(string) = 4;
	} = 1;
} = 0x20130325;