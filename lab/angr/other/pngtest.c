#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void infloop()
{
	while(1) {
		printf("lol");
	}
}

void test(char *input)
{
	char* backdoor = "42";

	if(strcmp(input,backdoor) == 0) {
		printf("Backdoor found\n");
	} else {
		printf("No problem here\n");
	}
}

int main(int argc, char** argv) {
	char in[20];
	read(0, in, 8);
	test(in);
}


