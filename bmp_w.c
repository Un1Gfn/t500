// Refer to corebootlibreboot.rst for build cmdline

#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#include "bmp.h"

#define PAD_TO_MULTIPLE_OF(ORIG,FACTOR) ((ORIG+FACTOR-1)/FACTOR*FACTOR)
  static_assert(104==PAD_TO_MULTIPLE_OF(101,4));
  static_assert(104==PAD_TO_MULTIPLE_OF(102,4));
  static_assert(104==PAD_TO_MULTIPLE_OF(103,4));
  static_assert(104==PAD_TO_MULTIPLE_OF(104,4));
  static_assert(108==PAD_TO_MULTIPLE_OF(105,4));
  static_assert(108==PAD_TO_MULTIPLE_OF(106,4));
  static_assert(108==PAD_TO_MULTIPLE_OF(107,4));
  static_assert(108==PAD_TO_MULTIPLE_OF(108,4));

#define Write1B(V) assert(1==fwrite(&(uint8_t){V},1,1,stdout))
#define Write2B(V) assert(1==fwrite(&(uint16_t){htole16((uint16_t)(V))},2,1,stdout))
#define Write4B(V) assert(1==fwrite(&(uint32_t){htole32((uint32_t)(V))},4,1,stdout))

// 100x200
// 8bpp - 1Bpp - 256 colors

// Each row is (padded to) a multiple of 4 bytes

const uint32_t w=100;
const uint32_t h=200;
const uint16_t bpp=8; // 1 Byte per pixel
const uint32_t bufsz=100*200;

const uint32_t filesz=BITMAPFILEHEADER+BITMAPINFOHEADER+bufsz;
uint8_t *buf=NULL;

static inline void writebfh(){

  assert(0==ftell(stdout));

  Write1B('B');
  Write1B('M');
  assert(2==ftell(stdout));

  Write4B(filesz);

  Write2B(0);
  Write2B(0);
  Write4B(BITMAPFILEHEADER+BITMAPINFOHEADER);

  assert(BITMAPFILEHEADER==ftell(stdout));

}

static inline void writedbh(){

  assert(BITMAPFILEHEADER==ftell(stdout));

  // ...

  assert(BITMAPFILEHEADER+BITMAPINFOHEADER==ftell(stdout));

}

static inline void writepixarr(){

  assert(BITMAPFILEHEADER+BITMAPINFOHEADER==ftell(stdout));

  buf=aligned_alloc(4,bufsz);
  assert(buf);
  explicit_bzero(buf,bufsz);

  // cast buf into pointer to array 200 of unsigned char
  #define cast ((unsigned char (*)[PAD_TO_MULTIPLE_OF(w,4)])buf)

  // Fill bottom-up
  for(uint32_t r=0;r<h;++r)
    for(uint32_t c=0;c<w;++c)
      cast[r][c]=(uint32_t)256*c/w;

  // Dump
  // ...

}

int main(){

  assert(!isatty(STDOUT_FILENO));
  assert(!isatty(STDIN_FILENO));

  writebfh();

  // writedbh();

  // writepixarr();

  // assert(filesz==ftell(stdout));

  assert(0==fclose(stdout));
  free(buf);
  return EXIT_SUCCESS;

}
