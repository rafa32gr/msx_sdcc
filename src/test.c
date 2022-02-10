#include <stdio.h>
#include "text.h"


int main(char **argv, int argc) {

  init80colText();  // Initializing VDP to write on 80 cols color text
  
  gotoxy(0, 0);

  setColors(LIGHT_RED,LIGHT_YELLOW,1);
  vcolorprint("TEST");
  setColors(LIGHT_RED,LIGHT_YELLOW,0);
  vcolorprint("TEST");

  gotoxy(10, 5);

  setColors(LIGHT_GREEN,LIGHT_YELLOW,1);
  vcolorprint("TEST");
  setColors(LIGHT_GREEN,LIGHT_YELLOW,0);
  vcolorprint("TEST");

  gotoxy(20, 10);
  setColors(LIGHT_BLUE,LIGHT_YELLOW,1);
  vcolorprint("TEST");
  setColors(LIGHT_BLUE,LIGHT_YELLOW,0);
  vcolorprint("TEST");

  colorPositionPrint(35, 20, "Hit a key.", WHITE, TRANSPARENT, 0);

  mygetchar(); // wait to push a key to return to MSXDOS

  exit80colText(0); // Secure exit from VDP color text mode.
}
