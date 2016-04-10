
#include <stdlib.h>
#include <stdio.h>
#include <png.h>
#include <unistd.h>

int width, height;
png_byte color_type;
png_byte bit_depth;
png_bytep *row_pointers;

int main(int argc, char *argv[]) {
  FILE *fp = fopen("test.png", "rb");


  fclose(fp);
  return 0;
}
