// Refer to corebootlibreboot.rst for build cmdline

/*

8bpp - 1Bpp - 256 colors

+---+---+
|       | h=100
+---+---+
  w=200

Each row is (padded to) a multiple of 4 bytes

*/

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
// #include <sys/param.h> // MAX()
// #include <time.h> // time()

#include "bmp.h"

#define PAD(FACTOR,ORIG) ((ORIG+FACTOR-1)/FACTOR*FACTOR)
  static_assert(100==PAD(4,100));
  static_assert(104==PAD(4,101));
  static_assert(104==PAD(4,102));
  static_assert(104==PAD(4,103));
  static_assert(104==PAD(4,104));
  static_assert(108==PAD(4,105));

#define Write1B(V) assert(1==fwrite(&(uint8_t){V},1,1,stdout))
#define Write2B(V) assert(1==fwrite(&(uint16_t){htole16((uint16_t)(V))},2,1,stdout))
#define Write4B(V) assert(1==fwrite(&(uint32_t){htole32((uint32_t)(V))},4,1,stdout))

const uint32_t w=200;
const uint32_t h=100;
const uint16_t bpp=8; // 1 Byte per pixel
const uint32_t bufsz=PAD(4,w)*h;

const uint32_t filesz=PAD(4,BITMAPFILEHEADER+BITMAPINFOHEADER+CTSZ)+bufsz;
uint8_t *buf=NULL;

static inline void writebfh(){

  assert(ftell(stdout)==0);

  Write1B('B');
  Write1B('M');
  assert(2==ftell(stdout));

  Write4B(filesz);

  Write2B(0);
  Write2B(0);
  Write4B(PAD(4,BITMAPFILEHEADER+BITMAPINFOHEADER+CTSZ)); // Offset of pixarr

  assert(ftell(stdout)==BITMAPFILEHEADER);

}

static inline void writedbh(){

  assert(ftell(stdout)==BITMAPFILEHEADER);

  Write4B(BITMAPINFOHEADER);
  Write4B(w);
  Write4B(h);

  Write2B(1);
  Write2B(8);

  Write4B(BI_RGB);
  Write4B(bufsz);

  // Fit in 1m x 1m canvas
  // Write4B(MAX(w,h));
  // Write4B(MAX(w,h));
  Write4B(0);
  Write4B(0);

  Write4B(COLORS);
  Write4B(0);

  assert(ftell(stdout)==BITMAPFILEHEADER+BITMAPINFOHEADER);

}

static inline void writepalette(){

  assert(ftell(stdout)==BITMAPFILEHEADER+BITMAPINFOHEADER);

  for(uint16_t i=0;i<COLORS;++i){
    Write1B(i);
    Write1B(i);
    Write1B(i);
    Write1B(0x00);
  }

  assert(ftell(stdout)==BITMAPFILEHEADER+BITMAPINFOHEADER+CTSZ);

}

static inline void writegap1(){

  assert(ftell(stdout)==BITMAPFILEHEADER+BITMAPINFOHEADER+CTSZ);

  for(uint32_t i=BITMAPFILEHEADER+BITMAPINFOHEADER+CTSZ;i<PAD(4,BITMAPFILEHEADER+BITMAPINFOHEADER+CTSZ);++i)
    Write1B(0x00);

  assert(ftell(stdout)==PAD(4,BITMAPFILEHEADER+BITMAPINFOHEADER+CTSZ));

}

static inline void writepixarr(){

  assert(ftell(stdout)==PAD(4,BITMAPFILEHEADER+BITMAPINFOHEADER+CTSZ));

  buf=aligned_alloc(4,bufsz);
  assert(buf);
  explicit_bzero(buf,bufsz);

  // Bottom-up

  // cast buf into pointer to array 200 of unsigned char
  #define cast ((unsigned char (*)[PAD(4,w)])buf)

  // // Grid4
  // for(uint32_t r=0;r<h/2;++r){
  //   for(uint32_t c=0;c<w/2;++c){cast[r][c]=0x00;}
  //   for(uint32_t c=w/2;c<w;++c){cast[r][c]=0x55;}
  // }
  // for(uint32_t r=h/2;r<h;++r){
  //   for(uint32_t c=0;c<w/2;++c){cast[r][c]=0xAA;}
  //   for(uint32_t c=w/2;c<w;++c){cast[r][c]=0xFF;}
  // }

  // // White noise
  // srand(time(NULL));
  // for(uint32_t r=0;r<h;++r)for(uint32_t c=0;c<w;++c)cast[r][c]=random();

  // Ombre (transpose)
  for(uint32_t c=0;c<w;++c)for(uint32_t r=0;r<h;++r)cast[r][c]=c*0xFF/w;

  fwrite(buf,bufsz,1,stdout);
  free(buf);buf=NULL;
  assert(filesz==ftell(stdout));

}

int main(){

  assert(!isatty(STDOUT_FILENO));
  assert(!isatty(STDIN_FILENO));

  writebfh();
  writedbh();
  writepalette();
  writegap1();
  writepixarr();

  assert(0==fclose(stdout));
  return EXIT_SUCCESS;

}
