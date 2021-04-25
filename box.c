/*

gcc -O0 -g -std=gnu11 -Wall -Wextra $(pkg-config --cflags ncurses) -o box.out box.c $(pkg-config --libs ncurses) && \
./box.out \
winbond \
25Q32BVSIG \
1222

box drawing character
https://en.wikipedia.org/wiki/Box-drawing_character

GitHub advanced search
https://docs.github.com/en/github/searching-for-information-on-github/understanding-the-search-syntax
https://github.community/t/how-to-exclude-user-repository-or-organization-repository-from-a-search/3147
https://docs.github.com/en/github/searching-for-information-on-github/understanding-the-search-syntax

https://github.com/search?q=user:Un1Gfn -repo:Un1Gfn/lfs initscr&type=code

*/

#include <assert.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

int main(const int argc, const char *const *argv){

  const WINDOW *const r=initscr();
  assert(r&&r==stdscr/*curs_variables(3X)*/);
  assert(OK==noraw());
  assert(OK==nocbreak());
  assert(OK==refresh());

  size_t lenM=0;
  size_t len[argc];
  bzero(len,argc*sizeof(size_t));

  for(int i=1;i<argc;++i){
    len[i]=strlen(argv[i]);
    if(len[i]>lenM)
      lenM=len[i];
  }

  WINDOW *w=newwin((argc-1)+2,lenM+2,0,0);
  assert(w);
  wborder(w,'|','|','-','-','+','+','+','+');
  // box(w,0,0);
  curs_set(0);
  for(int i=1;i<argc;++i){
    mvwprintw(w,i,1,"%s",argv[i]);
  }
  wrefresh(w);

  // getchar();
  char *line=NULL;
  getline(&line,&(size_t){0},stdin);
  free(line);
  line=NULL;
  assert(OK==delwin(w));
  w=NULL;

  curs_set(1);
  assert(OK==endwin());
  assert(TRUE==isendwin());

}