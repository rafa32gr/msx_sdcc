#define SCREEN7_BACKBUF 0x0D400
#define SCREEN7_OFFSETX 0
#define SCREEN7_OFFSETY 1
#define SCREEN7_SIZEX 512
#define SCREEN7_SIZEY 212
#define CHAR_SIZEX 3
#define CHAR_SIZEY 8
#define BACKBUFFER_LENGTH 85
#define SCREENCOLS 80

// Colors
#define TRANSPARENT    0x00
#define BLACK          0x01
#define MEDIUM_GREEN   0x02
#define LIGHT_GREEN    0x03
#define DARK_BLUE      0x04
#define LIGHT_BLUE     0x05
#define DARK_RED       0x06
#define CYAN           0x07
#define MEDIUM_RED     0x08
#define LIGHT_RED      0x09
#define DARK_YELLOW    0x0A
#define LIGHT_YELLOW   0x0B
#define DARK_GREEN     0x0C
#define MAGENTA        0x0D
#define GRAY           0x0E
#define WHITE          0x0F


/* DOS calls */
#define TERM    #0x62

/* BIOS calls */
#define CHGET  #0x009F
#define CHPUT  #0x00A2
#define CALSLT #0x001C
#define EXPTBL #0xFCC1
#define POSIT  #0x00C6
#define INITXT #0x006C
#define CLS    #0x00C3
#define CHGCLR #0x0062
#define CHGMOD #0x005F
#define WRTVRM #0x004D
#define NRDVRM #0x0174
#define NWRVRM #0x0177
#define FILVRM #0x0056
#define DISSCR #0x0041
#define ENASCR #0x0044

/* Memory variables */
#define LINL40 0xF3AE
#define FORCLR 0xF3E9
#define BAKCLR 0xF3EA
#define BDRCLR 0xF3EB

/* Vram positions */
#define CHARTABLE 0x01000 // 80 cols

#define DOSCALL  call 5
#define BIOSCALL ld iy,(EXPTBL-1)\
call CALSLT

/* Functions */

void setColors(char fcolors,char bgcolors, char incerted);
void exit80colText(int code);
char mygetchar(void) __naked;
void gotoxy(int x, int y);
void cls(void) __naked;
void myputchar(char c);
void vcolorprint(char* str);
void colorPositionPrint(int x, int y, char* str, char fgcolor, char bgcolor, char invert);



