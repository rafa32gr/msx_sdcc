char escape_sequence = 0;
char escape_sequence_2 = 0;
char escape_sequence_y = 0;

#define SCREEN7_BACKBUF 0x0D400
#define SCREEN7_OFFSETX 0
#define SCREEN7_OFFSETY 1
#define SCREEN7_SIZEX 512
#define SCREEN7_SIZEY 212
#define CHAR_SIZEX 3
#define CHAR_SIZEY 8
#define BACKBUFFER_LENGTH 85
#define SCREENCOLS 80

struct coord {
  int x, y;
};

struct coord cursor_pos;

char fgcolor;
char bgcolor;
char inverted;

/*
Set the position of the text cursor.

x -> Column
y -> Row

example:
gotoxy(0,0);

*/
void gotoxy(int x, int y) {
  cursor_pos.x = x;
  cursor_pos.y = y;
}