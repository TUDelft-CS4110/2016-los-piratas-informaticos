#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void test(char *input)
{
	char* backdoor = "42\n";

	if(strcmp(input,backdoor) == 0) {
		abort(); // Simulate a crash
	} else {
		printf("Normal execution continues\n");
	}
}

int main(int argc, char** argv) {
	char in[20];
	read(0, in, 8);
	test(in);
}
