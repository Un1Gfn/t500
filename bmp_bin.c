// Refer to corebootlibreboot.rst for build cmdline

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#include "bmp.h"

#define eprintf(...) fprintf(stderr,__VA_ARGS__)

#define PAD(FACTOR,ORIG) ((ORIG+FACTOR-1)/FACTOR*FACTOR)

#define Write1B(V) assert(1==fwrite(&(uint8_t){V},1,1,stdout))
#define Write2B(V) assert(1==fwrite(&(uint16_t){htole16((uint16_t)(V))},2,1,stdout))
#define Write4B(V) assert(1==fwrite(&(uint32_t){htole32((uint32_t)(V))},4,1,stdout))

static       uint32_t h=0;
static       uint32_t binsz=0;
static       uint32_t w=0;
static const uint16_t bpp=8; // 1 Byte per pixel
static       uint32_t pixarrsz=0;
static       uint32_t filesz=0;

static uint8_t *readbin_setglobvar(){

  assert(
    0==fseek(stdin,0,SEEK_END) &&
    0==feof(stdin) &&
    0==ferror(stdin)
  );
  assert((long long)ftell(stdin)==4194304);
  binsz=ftell(stdin);
  rewind(stdin);

  w=(binsz+h-1)/h;
  eprintf("%u -> %ux%u\n",binsz,w,h);

  assert(bpp==8);
  pixarrsz=PAD(4,w)*h;
  filesz=PAD(4,BITMAPFILEHEADER+BITMAPINFOHEADER+CTSZ)+pixarrsz;
  eprintf("pixarr(file) %uB(%uB)\n",pixarrsz,filesz);

  // assert(0);

  uint8_t *ret=calloc(1,binsz);
  assert(ret);
  assert((long long)binsz==(long long)fread(ret,1,binsz,stdin));
  assert(0==fclose(stdin));
  return ret;
}

static inline void writebfh(){
  assert(ftell(stdout)==0);
  Write1B('B');
  Write1B('M');
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
  Write2B(bpp);
  Write4B(BI_RGB);
  Write4B(pixarrsz);
  // Fit in 1m x 1m canvas
  // Write4B(MAX(w,h));Write4B(MAX(w,h));
  Write4B(0);Write4B(0);
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

static inline void writepixarr(const uint8_t *const bin){

  assert(ftell(stdout)==PAD(4,BITMAPFILEHEADER+BITMAPINFOHEADER+CTSZ));

  uint8_t *pixarr=aligned_alloc(4,pixarrsz);
  assert(pixarr);
  explicit_bzero(pixarr,pixarrsz);

  // Bottom-up

  // cast pixarr into pointer to array 200 of unsigned char
  #define cast ((unsigned char (*)[PAD(4,w)])pixarr)

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

  // // Ombre (transpose)
  // for(uint32_t c=0;c<w;++c)
  //   for(uint32_t r=0;r<h;++r){
  //     const uint32_t cl=c*0xFF/w;
  //     // assert(cl<0xFF);
  //     cast[r][c]=cl;
  //   }

  // Bin snapshot
  for(uint32_t i=0;i<binsz;++i){
    // cast[r][c]=bin[c*h+r];
    cast[i%h][i/h]=bin[i];
  }

  fwrite(pixarr,pixarrsz,1,stdout);
  free(pixarr);pixarr=NULL;
  assert(filesz==ftell(stdout));

}

int main(const int argc,const char *const *const argv){

  assert(argc==2);
  assert(argv&&argv[1]&&argv[1][0]);
  h=atoi(argv[1]);
  assert(1<=h&&h<=4096);

  assert(!isatty(STDIN_FILENO));
  uint8_t *bin=readbin_setglobvar();

  assert(!isatty(STDOUT_FILENO));
  writebfh();
  writedbh();
  writepalette();
  writegap1();
  writepixarr(bin);

  free(bin);bin=NULL;
  assert(0==fclose(stdout));
  return EXIT_SUCCESS;

}
