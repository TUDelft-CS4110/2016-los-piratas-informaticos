#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char** argv) {
	char in[20];
	read(0, in, 8);

	char* secret = "42";

	while(strcmp(in,secret) != 0) {
		read(0, in, 8);
	}
}
