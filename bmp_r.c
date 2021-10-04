// cd ~/x200 && { gcc -std=gnu11 -g -O0 -Wextra -Wall -Winline -Werror=shadow -fanalyzer -o bmp_r.out bmp_r.c && { echo; ./bmp_r.out </home/darren/x200/1x1.bmp; echo; }; }

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "bmp.h"

// DIB header type
#define BITMAPINFOHEADER 40

// Compression method
#define BI_RGB 0

#define printfI(...) printf("  "__VA_ARGS__)
#define putsI(S) puts("  "S)

uint8_t *buf=NULL;
uint32_t buf_sz=0;
uint32_t i=0;

// https://stackoverflow.com/questions/5360627/c-c-post-increment-by-more-than-one
#pragma GCC diagnostic ignored "-Wsequence-point"
#define ReadInc2B() (i+=2,(le16toh(*((uint16_t*)(buf+(i-2))))))
#define ReadInc4B() (i+=4,(le32toh(*((uint32_t*)(buf+(i-4))))))

static inline void dump(){
  assert(
    0==fseek(stdin,0,SEEK_END) &&
    0==feof(stdin) &&
    0==ferror(stdin)
  );
  buf_sz=ftell(stdin);
  buf=calloc(1,buf_sz+1);
  assert(buf);
  rewind(stdin);
  assert((uint64_t)buf_sz==(uint64_t)fread(buf,1,buf_sz,stdin));
  assert(0==fclose(stdin));
}

static inline void bfh(){

  puts("1. Bitmap file header (14B)\n");

  assert('B'==buf[i++]);
  assert('M'==buf[i++]);
  putsI("BM\n");

  assert(buf_sz==ReadInc4B());
  printfI("%u bytes\n\n",buf_sz);

  assert(0==ReadInc2B());
  assert(0==ReadInc2B());

  const uint32_t pixel_array_offset=ReadInc4B();
  printfI("bitmap image data (pixel array) starts from byte offset %u\n\n",pixel_array_offset);

  assert(i==14);

}

static inline void dbh(){

  assert(i==14);

  puts("2. DIB header\n");

  const uint32_t dib_header_size=ReadInc4B();
  switch(dib_header_size){
    case BITMAPINFOHEADER:{

      putsI("BITMAPINFOHEADER - Windows NT, 3.1x or later\n");

      printfI("%ldx%ld\n\n",(int64_t)ReadInc4B(),(int64_t)ReadInc4B());

      assert(1==ReadInc2B());
      printfI("%u-bit color depth\n\n",ReadInc2B());

      assert(BI_RGB==ReadInc4B());
      putsI("no compression\n");

      printfI("raw bitmap data %u bytes\n\n",ReadInc4B());

      printfI("density(ppm): %ux%u\n\n",ReadInc4B(),ReadInc4B());

      assert(0==ReadInc4B());
      // printfI("%u colors in the color palette\n\n",ReadInc4B());

      assert(0==ReadInc4B());

    }break;
    default:printf("%u\n\n",dib_header_size);assert(0);break;
  }

}

int main(){

  dump();

  bfh();

  dbh();

  // puts("3. Extra bit masks");
  // puts("4. Color table");
  // puts("5. Gap1");
  // puts("6. Pixel array");
  // puts("7. Gap2");
  // puts("8. ICC color profile");

  printf("(\e[2m%s:\e[0m%s)\n","10#idx","16#val");
  puts("");
  for(;i<100&&i<buf_sz;++i)
    printf("\e[2m%d:\e[0m%02X ",i,buf[i]);
  (i<buf_sz)?printf("..."):0;
  puts("");

  free(buf);buf=NULL;
  return 0;

}
