// acquired from http://41j.com/blog/2012/12/progressive-png-rendering-using-libpng-quick-example/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include <png.h>
 
#define PNG_DEBUG 3
 
int width, height;
int pixel_depth;


struct png_infop {
  int height;
  int width;
  int pixel_depth;
png_bytep * row_pointers;  
};

png_structp png_ptr;
png_infop   info_ptr;
png_bytep * row_pointers;

 
/* This function is called (as set by png_set_progressive_read_fn() above) when enough data has been supplied so all of the header has been read.  */
void info_callback(png_structp png_ptr, png_infop info) {
/* Do any setup here, including setting any of the transformations mentioned in the Reading PNG files section. For now, you _must_ call either png_start_read_image() or png_read_update_info() after all the transformations are set (even if you don’t set any). You may start getting rows before png_process_data() returns, so this is your last chance to prepare for that.  */
 
  printf("callback\n");
}
 
int get_pixel(char *row,int pixel_depth,int idx) { 
  return 0;
}
 
/* This function is called when each row of image data is complete */
void row_callback(png_structp png_ptr, png_bytep new_row, png_uint_32 row_num, int pass) {
  /* If the image is interlaced, and you turned on the interlace handler, this function will be called for every row in every pass. Some of these rows will not be changed from the previous pass. When the row is not changed, the new_row variable will be NULL. The rows and passes are called in order, so you don’t really need the row_num and pass, but I’m supplying them because it may make your life easier.  For the non-NULL rows of interlaced images, you must call png_progressive_combine_row() passing in the row and the old row. You can call this function for NULL rows (it will just return) and for non-interlaced images (it just does the memcpy for you) if it will make the code easier. Thus, you can just do this for all cases: */
  printf("row callback\n");
}
 
 
int file_end=0;
void end_callback(png_structp png_ptr, png_infop info) {
/* This function is called after the whole image has been read, including any chunks after the image (up to and including the IEND). You will usually have the same info chunk as you had in the header, although some data may have been added to the comments and time fields.  Most people won’t do much here, perhaps setting a flag that marks the image as finished.  */
  printf("processing complete\n");
  file_end=1;
}
 
/* An example code fragment of how you would initialize the progressive reader in your application. */
int initialize_png_reader() {
  png_ptr = png_create_read_struct (PNG_LIBPNG_VER_STRING, (png_voidp)NULL,NULL,NULL);
  if(!png_ptr) return 1;
  info_ptr = png_create_info_struct(png_ptr);
  if(!info_ptr) {
    png_destroy_read_struct(&png_ptr, (png_infopp)NULL, (png_infopp)NULL);
    return 1;
  }
  if(setjmp(png_jmpbuf(png_ptr))) {
    png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);
    return 1;
  }
  /* This one’s new. You can provide functions to be called when the header info is valid, when each row is completed, and when the image is finished. If you aren’t using all functions, you can specify NULL parameters. Even when all three functions are NULL, you need to call png_set_progressive_read_fn(). You can use any struct as the user_ptr (cast to a void pointer for the function call), and retrieve the pointer from inside the callbacks using the function png_get_progressive_ptr(png_ptr); which will return a void pointer, which you have to cast appropriately.  */
  png_set_progressive_read_fn(png_ptr, (void *)NULL, info_callback, row_callback, end_callback);
  return 0;
}
 
/* A code fragment that you call as you receive blocks of data */
int process_data(png_bytep buffer, png_uint_32 length) {
printf("prebranch");
int ret = 1;
ret = setjmp(png_jmpbuf(png_ptr));
  if (ret) {
    printf("branch1");
    png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);
    return 1;
  } else {
    printf("branch2");
  }
printf("postbranch");

  /* This one’s new also. Simply give it a chunk of data from the file stream (in order, of course). On machines with segmented memory models machines, don’t give it any more than 28 64K. The library seems to run fine with sizes of 4K. Although you can give it much less if necessary (I assume you can give it chunks of 1 byte, I haven’t tried less then 256 bytes yet). When this function returns, you may want to display any rows that were generated in the row callback if you don’t already do so there.  */
  png_process_data(png_ptr, info_ptr, buffer, length);

  return 0;
}
 
int main(int argc, char **argv) {
  initialize_png_reader();
  char buffer[1025];
  int length = read(0, buffer,1024);
  process_data(buffer,length);
 
  return 0;
}
