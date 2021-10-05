// Refer to corebootlibreboot.rst for build cmdline

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>
#include <ctype.h> // isgraph()
#include <getopt.h> // struct option

#include "bmp.h"

#define eprintf(...) fprintf(stderr,__VA_ARGS__)

#define PAD(FACTOR,ORIG) ((ORIG+FACTOR-1)/FACTOR*FACTOR)

#define Write1B(V) assert(1==fwrite(&(uint8_t){V},1,1,stdout))
#define Write2B(V) assert(1==fwrite(&(uint16_t){htole16((uint16_t)(V))},2,1,stdout))
#define Write4B(V) assert(1==fwrite(&(uint32_t){htole32((uint32_t)(V))},4,1,stdout))

static const char*    program_name=NULL;
static       int      upsidedown=false;
static       uint32_t h=512;
static       uint32_t binsz=0;
static       uint32_t w=0;
static const uint16_t bpp=8; // 1 Byte per pixel
static       uint32_t pixarrsz=0;
static       uint32_t filesz=0;

// https://github.com/coreutils/coreutils/blob/master/src/uname.c
static inline int help(){
  eprintf("Usage: %s [-f|-u|--flip|--upside-down] [-h|--height==512] 0<dump.rom 1>|image.bmp\n",program_name);
  eprintf("       %s --help\n",program_name);
  exit(EXIT_FAILURE);
  return EXIT_FAILURE;
}

static uint8_t *readbin(){

  assert(
    0==fseek(stdin,0,SEEK_END) &&
    0==feof(stdin) &&
    0==ferror(stdin)
  );
  assert((long long)ftell(stdin)==4194304);
  binsz=ftell(stdin);
  rewind(stdin);

  w=(binsz+h-1)/h;
  eprintf("%u - %ux%u - %s",
    binsz,
    w,
    h,
    upsidedown?"flip":"normal"
  );

  assert(bpp==8);
  pixarrsz=PAD(4,w)*h;
  filesz=PAD(4,BITMAPFILEHEADER+BITMAPINFOHEADER+CTSZ)+pixarrsz;
  eprintf("pixarr(file) %uB(%uB)\n",pixarrsz,filesz);

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

  // Bin snapshot (transpost)
  if(upsidedown)
    for(uint32_t i=0;i<binsz;++i)
      // cast[r][c]=bin[c*h+r];
      cast[i%h][i/h]=bin[i];
  else
    for(uint32_t i=0;i<binsz;++i)
      cast[h-i%h-1][i/h]=bin[i];

  fwrite(pixarr,pixarrsz,1,stdout);
  free(pixarr);pixarr=NULL;
  assert(filesz==ftell(stdout));

}

static inline void args(const int argc,char *const argv[]){

  // // ! " # $ % & ' ( ) * + , . /
  // // 0 1 2 3 4 5 6 7 8 9
  // // < = > ? @
  // // A B C D E F G H I J K L M N O P Q R S T U V W X Y Z
  // // [ \ ] ^ _ `
  // // a b c d e f g h i j k l m n o p q r s t u v w x y z
  // // { | } ~
  // for(int i=0x00;i<=0xFF;++i){
  //   if( i!='-' && i!=':' && i!=';' && 0!=isgraph(i) )
  //     printf("%c ",i);
  // }

  (argc<=1)?help():0;

  // int height_found=0;
  const struct option longopts[]={
    {"flip"       ,no_argument      ,NULL,'f'},
    {"upside-down",no_argument      ,NULL,'u'},
    {"height"     ,required_argument,NULL,'h'},
    {"help"       ,no_argument      ,NULL, 0 },
    {NULL,0,NULL,0}
  };

  optind=0; // getopt(3)#NOTES
  assert(opterr==1);
  int ch=0;
  int longindex=-1;
  while(-1!=(ch=getopt_long(argc,argv,"+""fu""h:",longopts,&longindex)))switch(ch){
    case 'f':
    case 'u':
      assert(!optarg);upsidedown=true;break;
    case 'h':
      assert(optarg&&optarg[0]);h=atoi(optarg);break;
    case '?':
    case  0 :
      assert(!optarg);help();break;
    // case 0:switch(longindex){
    //     case 0:assert(upsidedown);break;
    //     case 1:assert(upsidedown);break;
    //     case 2:assert(height_found);break;
    //     default:assert(0);break;
    //   }break;
    default:
      // printf("%c",ch);
      // if(optarg&&optarg[0])printf(" = %s",optarg);
      assert(0);break;
  }

  assert(optind==argc);

}

int main(const int argc,char *const argv[]){

  program_name=argv[0];
  args(argc,argv);
  assert((int32_t)h>0);
  uint32_t tmp=h;
  for(;;){
    if(tmp==128)break;
    assert(tmp>128);
    tmp/=2;
  }

  // assert(0);
  assert(!isatty(STDIN_FILENO));
  uint8_t *bin=readbin();

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
