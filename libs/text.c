#include "VDPgraph2.h"
#include "text.h"

struct coord {
  int x, y;
};

char fgcolor;
char bgcolor;
char inverted;

struct coord cursor_pos;
char mescape_sequence = 0;
char mescape_sequence_2 = 0;
char mescape_sequence_y = 0;


unsigned char char_table[8*255];

void getCharacterset();
void vputchar_vram(unsigned char c, unsigned int addr);
void fillvram(char data, int length, int address) __naked;
void exit(int code) __naked;
void color(char fg, char bg, char bd) __naked;
void screen(char mode) __naked;
void vpoke(unsigned int address, unsigned char value) __naked;
void initxt(char columns) __naked;
unsigned char vpeek(unsigned int address) __naked ;


/*
Change the colors for write on screen

    fcolors -> Foreground Color
    bgcolors -> Background Color
    inverteds -> 0 - No inversion 1 - Inversion

Colors are:

    TRANSPARENT, BLACK, MEDIUM_GREEN ,LIGHT_GREEN, DARK_BLUE, 
    LIGHT_BLUE, DARK_RED, CYAN, MEDIUM_RED, LIGHT_RED ,DARK_YELLOW,
    LIGHT_YELLOW ,DARK_GREEN, MAGENTA , GRAY , WHITE

example:
setColors(BLACK,TRANSPARENT,0);

*/
void setColors(char fcolors,char bgcolors, char inverteds) {
  fgcolor = fcolors;
  bgcolor = bgcolors;
  inverted = inverteds;
}

void getCharacterset(){
    int n;
    for (n = 0; n < 8*255; n++) {
        char_table[n] = vpeek(CHARTABLE + n);
    }
    
}
/*
Exit from the 80 cols mode with color.

code -> the code you want to give to the MSXDOS when you exit.

Mandatory to call this function to returm to MSXDOS. Call it when you want to return to MSXDOS.

example:

exit80colText(0);
*/
void exit80colText(int code){
    initxt(80);
    exit(code);
}

/*
Initializes the VDP to write text on 80 cols and colors

Mandatory to write on screen call this function at the begining of your code.

example:
init80colText();
*/
void init80colText(){
    int n,y, x;
    Save_VDP();
    initxt(80);
    getCharacterset();
    color(WHITE, BLACK, BLACK);
    screen(7);
    SetFasterVDP();	
    SetPage(0);
    SetBorderColor(0);

    setColors(WHITE,BLACK,0);

    y = -1;
    x = 0;
    for (n = 0; n < 255; n++) {
        if (n%BACKBUFFER_LENGTH == 0) {
        y++;
        x=0;
        }
        vputchar_vram(n, SCREEN7_BACKBUF + x*CHAR_SIZEX + y*SCREEN7_SIZEX/2*CHAR_SIZEY);
        x++;
    }
}

void initxt(char columns) __naked {
  columns;
  __asm
    push ix
    ld ix,#4
    add ix,sp

    ld a,(ix)
    ld (LINL40),a

    ld ix,INITXT
    BIOSCALL

    pop ix
    ret
  __endasm;
}


/*
Wait until a key is pressed and return the code from de key pressed.

example:
pushed = mygetchar();
*/
char mygetchar(void) __naked {
  __asm
    push ix

    ld ix,CHGET
    BIOSCALL
    ld h, #0x00
    ld l,a 

    pop ix
    ret
  __endasm;
}



void gotoxy(int x, int y) {
  cursor_pos.x = x;
  cursor_pos.y = y;
}

void cls(void) __naked {
  __asm
    push ix
    cp a
    ld ix,CLS
    BIOSCALL
    pop ix
    ret
  __endasm;
}

void exit(int code) __naked {
  code;
  __asm
    push ix
    ld ix,#4
    add ix,sp

    ld b,(ix)
    ld c, TERM
    DOSCALL

    pop ix
    ret
  __endasm;
}


void color(char fg, char bg, char bd) __naked {
  fg;
  bg;
  bd;
  __asm
    push ix
    ld ix,#4
    add ix,sp

    ld a,0(ix)
    ld(#FORCLR),a
    ld a,1(ix)
    ld(#BAKCLR),a
    ld a,2(ix)
    ld(#BDRCLR),a

    ld ix,CHGCLR
    BIOSCALL

    pop ix
    ret
  __endasm;
}

void screen(char mode) __naked {
  mode;
  __asm
    push ix
    ld ix,#4
    add ix,sp

    ld a,0(ix)
    ld ix,CHGMOD
    BIOSCALL

    pop ix
    ret
  __endasm;
}

void vpoke(unsigned int address, unsigned char value) __naked {
  address;
  value;
  __asm
    push ix
    ld ix,#4
    add ix,sp

    ld l,0(ix)
    ld h,1(ix)
    ld a,2(ix)
    ld ix,NWRVRM
    BIOSCALL

    pop ix
    ret
  __endasm;
}

unsigned char vpeek(unsigned int address) __naked {
  address;
  __asm
    push ix
    ld ix,#4
    add ix,sp

    ld l,0(ix)
    ld h,1(ix)
    ld ix,NRDVRM
    BIOSCALL

    ld h, #0x00
    ld l,a

    pop ix
    ret
  __endasm;
}

void fillvram(char data, int length, int address) __naked {
  data;
  length;
  address;
  __asm
    push ix
    ld ix,#4
    add ix,sp

    ld a,0(ix)
    ld c,1(ix)
    ld b,2(ix)
    ld l,3(ix)
    ld h,4(ix)
    ld ix,FILVRM
    BIOSCALL

    pop ix
    ret
  __endasm;
}


void myputchar(char c) {
  MMMtask vdptask;
  unsigned char n,m;


  if (mescape_sequence == 1) {

    if (c == 'K') {

      mescape_sequence = 0;

      vdptask.X2 = SCREEN7_OFFSETX + cursor_pos.x*CHAR_SIZEX*2;
      vdptask.Y2 = SCREEN7_OFFSETY + cursor_pos.y*CHAR_SIZEY;
      vdptask.DX = SCREEN7_SIZEX - cursor_pos.x*CHAR_SIZEX*2;
      vdptask.DY = CHAR_SIZEY;
      vdptask.s0 = 0x11;
      vdptask.DI = 0;
      vdptask.LOP = opHMMV;
      fLMMM(&vdptask);

      cursor_pos.x = SCREENCOLS;
    } else if (c == 'x') {

    } else if (c == 'm') {

      mescape_sequence_2 = 1;
    } else if (mescape_sequence_2 == 1) {
      if (c-32 <= 15) {
        fgcolor = c-32;
      } else {
        if (inverted == 0) {
          inverted = 1;
        } else {
          inverted = 0;
        }
      }
      mescape_sequence_2 = 0;
      mescape_sequence = 0;
    } else if (c == 'y') {

    } else if (c == 'H') {

      gotoxy(0, 0);
      mescape_sequence = 0;
    } else if (c == 'Y') {

      mescape_sequence_2 = 2;
      mescape_sequence_y = 127;
    } else if (mescape_sequence_2 == 2) {
      if (mescape_sequence_y == 127) {
        mescape_sequence_y = c;
      } else {
        gotoxy(c-32, mescape_sequence_y-32);
        mescape_sequence_2 = 0;
        mescape_sequence = 0;
        mescape_sequence_y = 0;
      }

    } else {
      mescape_sequence = 0;
    }
  } else {

    if (c >= 0x20) {
      n = c%BACKBUFFER_LENGTH;
      m = c/BACKBUFFER_LENGTH;

      vdptask.X2 = SCREEN7_OFFSETX + cursor_pos.x*CHAR_SIZEX*2;
      vdptask.Y2 = SCREEN7_OFFSETY + cursor_pos.y*CHAR_SIZEY;
      vdptask.DX = CHAR_SIZEX*2;
      vdptask.DY = CHAR_SIZEY;
      vdptask.s0 = (fgcolor<<4) + fgcolor;
      vdptask.DI = 0;
      vdptask.LOP = opHMMV;
      fLMMM(&vdptask);

      vdptask.X = n*CHAR_SIZEX*2;
      vdptask.Y = 212+m*CHAR_SIZEY;
      vdptask.DX = CHAR_SIZEX*2;
      vdptask.DY = CHAR_SIZEY;
      vdptask.X2 = SCREEN7_OFFSETX + cursor_pos.x*CHAR_SIZEX*2;
      vdptask.Y2 = SCREEN7_OFFSETY + cursor_pos.y*CHAR_SIZEY;
      vdptask.s0 = 0;
      vdptask.DI = 0;
      if (inverted == 0) {
        vdptask.LOP = LOGICAL_AND;
      } else {
        vdptask.LOP = LOGICAL_XOR;
      }
      fLMMM(&vdptask);

      cursor_pos.x++;
    } else if (c == '\n') {
      cursor_pos.y++;
    } else if (c == '\r') {
      cursor_pos.x = 0;
    } else if (c == '\33') {
      mescape_sequence = 1;
    }
  }
}

void vputchar_vram(unsigned char c, unsigned int addr) {
  int x,y;
  unsigned char b, p1, p2, p3;

  for (y=0; y<CHAR_SIZEY; y++) {
    b = char_table[c*CHAR_SIZEY + y];
    for (x=0; x<CHAR_SIZEX; x++) {
      p1 = ((b >> (CHAR_SIZEX*2)-x*2+1) & 1U) * fgcolor;
      p2 = ((b >> (CHAR_SIZEX*2)-x*2) & 1U) * fgcolor;
      if (p1 == 0) p1 = bgcolor;
      if (p2 == 0) p2 = bgcolor;
      p3 = (p1 << 4) + p2;
      vpoke(addr + x + y*SCREEN7_SIZEX/2 ,p3);
    }
  }
}

/*
Write on screen a string with previously defined colors with setColors() function

str -> The string you want to write

example: 
vcolorprint("Hello");

*/
void vcolorprint(char* str) {
  int x=0;

  while (str[x] != '\0') {
    myputchar(str[x]);
    gotoxy(cursor_pos.x++,cursor_pos.y);
    x++;
  }
}


/*
Write on screen a string with defined colors and at position given

str -> The string you want to write
x -> Column to start writing on
y -> Row to start writing on
fgcolor -> Foreground color to write
bgcolor -> Background color to write
invert -> Show Background? 0 -> No, 1 -> Yes

Colors are:

    TRANSPARENT, BLACK, MEDIUM_GREEN ,LIGHT_GREEN, DARK_BLUE, LIGHT_BLUE, DARK_RED, CYAN, MEDIUM_RED, LIGHT_RED ,DARK_YELLOW,LIGHT_YELLOW ,DARK_GREEN, MAGENTA , GRAY , WHITE

example: 
colorPositionPrint(33, 20, "Hit a key", DARK_GREEN, TRANSPARENT, 0);

*/
void colorPositionPrint(int x, int y, char* str, char fgcolor, char bgcolor, char invert){
  gotoxy(x,y);
  setColors(fgcolor, bgcolor, invert);
  vcolorprint(str);
}