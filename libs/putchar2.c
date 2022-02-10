#include "VDPgraph2.h"


void putchar(char c) {
  MMMtask vdptask;
  unsigned char n,m;


  if (escape_sequence == 1) {
    // If previous char was an escape sequence \33
    if (c == 'K') {
      // Delete everything from the cursor position to the end of line
      escape_sequence = 0;

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
      // Cursor
      // TODO
    } else if (c == 'm') {
      // Color
      // Based on ANSI but different
      // Colors from 0 to 15 (+32)
      // inverted 16+32
      escape_sequence_2 = 1;
    } else if (escape_sequence_2 == 1) {
      if (c-32 <= 15) {
        fgcolor = c-32;
      } else {
        if (inverted == 0) {
          inverted = 1;
        } else {
          inverted = 0;
        }
      }
      escape_sequence_2 = 0;
      escape_sequence = 0;
    } else if (c == 'y') {
      // Cursor
      // TODO
    } else if (c == 'H') {
      // Move to top left corner
      gotoxy(0, 0);
      escape_sequence = 0;
    } else if (c == 'Y') {
      // Move cursor to xy position
      escape_sequence_2 = 2;
      escape_sequence_y = 127;
    } else if (escape_sequence_2 == 2) {
      if (escape_sequence_y == 127) {
        escape_sequence_y = c;
      } else {
        gotoxy(c-32, escape_sequence_y-32);
        escape_sequence_2 = 0;
        escape_sequence = 0;
        escape_sequence_y = 0;
      }

    } else {
      escape_sequence = 0;
    }
  } else {
    // If previous char wasn't an escape sequence \33
    if (c >= 0x20) {
      n = c%BACKBUFFER_LENGTH;
      m = c/BACKBUFFER_LENGTH;

      // Set background
      vdptask.X2 = SCREEN7_OFFSETX + cursor_pos.x*CHAR_SIZEX*2;
      vdptask.Y2 = SCREEN7_OFFSETY + cursor_pos.y*CHAR_SIZEY;
      vdptask.DX = CHAR_SIZEX*2;
      vdptask.DY = CHAR_SIZEY;
      vdptask.s0 = (fgcolor<<4) + fgcolor;
      vdptask.DI = 0;
      vdptask.LOP = opHMMV;
      fLMMM(&vdptask);

      // Set char
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
      escape_sequence = 1;
    }
  }
}
