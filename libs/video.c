//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// L U E G O L U 3 G O   S T U D I O S   2 0 1 9 /////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////// M S X  C  D E V E L O P M E N T  S D K ////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////// Funciones de Video ///////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include "video.h"
#include "VDP_TMS9918.h"
#include "memoria.h"
#include "io.h"

#define LONG_FONT #0x18C
#define POS_FONT  #0x698
#define BREAK_P    #0xd000

int kbd_r(unsigned char id){
id;
__asm

  push  ix    
  ld  ix,#0
  add ix,sp

  ld b, 4(ix)
  
  in  a,(#0xAA)
  and #0xF0         
  or  b            
  out (#0xAA),a
  in  a,(#0xA9)     
  cpl
  ld  l,a
  ld  h,#0
  pop ix
  ret 
__endasm;

return 0;
}

int strLength(char *str)
 {
     int i = 0;
     while(*(str++))  i++; 
     return i;
 }

void vprint(unsigned char posx, unsigned char posy, char* text)
 {
   int longi = strLength(text);                       // tamaño de la cadena
   unsigned int address = 6144 + (posy * 32) + posx;  // calcula la posicion en la VRAM
   while (longi-->0)
   { 
    vpoke(address++,*(text++)+163);                   // escribe en la VRAM
   } 
 }

 void nprint(unsigned char posx, unsigned char posy, int number)
 {
   

   unsigned int address = 6144 + (posy * 32) + posx;  // calcula la posicion en la VRAM
   
    vpoke(address,#211+number);                       // escribe en la VRAM
    
 }


void set_sprites16(){

__asm

  ld   DE,#0x0100

SETUPSPRITES:
  ld B,#0
  ld A,D
  cp #1
  jr NZ,STSP1
  set #1,b 

STSP1:
  ld A,E
  cp #1
  jr NZ,STSP2
  set #0,b 

STSP2:
  ld HL,#0xF3E0 
  ld A,(HL)
  and #0xfc
  or B
  ld  B,A
  ld  C,#0x01
  call  #0x0047
  
__endasm;

}

void set_sprite(unsigned char *sprite, int slot)
{

copyToVRAM((uint)sprite, #0x3800+(slot*32), #32);

}

void draw_sprite_16( int x, int y, int slot,int color)
{

vpoke (#0x1b00+#(slot*4),#x);
vpoke (#0x1b00+#(slot*4)+1,#y);
vpoke (#0x1b00+#(slot*4)+2,#(slot*4));
vpoke (#0x1b00+#(slot*4)+3,#color);

}


void ei_halt(void){
 __asm
  ei
  halt
  ret
  __endasm;
}

void screen_off(void){
__asm 
   call 0x0041
__endasm;

}

void screen_on(void){

__asm
  
  ei
  halt
  call 0x0044
 
__endasm;


}

void disable_sprite(int orden){

  draw_sprite_16(240,0,orden,0);

}


void load_font(unsigned int tpatron, unsigned int tcolor, int posicion,int color)
{

if (posicion>4){
                copyToVRAM (tpatron,#0x0000+POS_FONT,LONG_FONT);
                if (color)  copyToVRAM (tcolor, #0x2000+POS_FONT,LONG_FONT); else 
                            fillVRAM(0x2000+POS_FONT,LONG_FONT,0xF0);
                }
if (posicion==2 || posicion == 3 || posicion == 6 || posicion == 7 ){
                copyToVRAM (tpatron,#0x0800+POS_FONT,LONG_FONT);
                if (color)  copyToVRAM (tcolor, #0x2800+POS_FONT,LONG_FONT); else
                            fillVRAM(0x2800+POS_FONT,LONG_FONT,0xF0);
                }
if (posicion==1 || posicion == 5 || posicion == 3 || posicion == 7 ){
                copyToVRAM (tpatron,#0x1000+POS_FONT,LONG_FONT);
                if (color)  copyToVRAM (tcolor, #0x3000+POS_FONT,LONG_FONT); else
                            fillVRAM(0x3000+POS_FONT,LONG_FONT,0xF0);
                }

}


void delay(int seconds, int saltable)
{
int frames;
int rango;
int pausa = 1;

if (seconds==0) {rango=6;seconds=1;} else rango=50;

while (seconds-- && pausa){
  frames=rango;
  while (frames-- && pausa )
                              {
                              ei_halt();
                              if ( (kbd_r(8)==0x01 || kbd_r(7)==0x04 || peek((unsigned char*)0xd000)) && saltable) pausa=0;
                              }
                           
}
}

void vprint_step(unsigned char posx, unsigned char posy, char* text)
 {
   if (peek((unsigned char*)BREAK_P)==1) return;
   int pausa = 1;
   int longi = strLength(text);                       // tamaño de la cadena
   unsigned int address = 6144 + (posy * 32) + posx;  // calcula la posicion en la VRAM
   while (longi-->0)
   { 
    if (pausa) delay(0,0);
    vpoke(address++,*(text++)+163);                   // escribe en la VRAM
    if (kbd_r(8)==0x01) pausa=0;
    if (kbd_r(7)==0x04) {poke (BREAK_P,1);return;}
   } 
 }

 void vprint_pause(unsigned char posx, unsigned char posy, char* text, unsigned char tama)
 {
   int leida = 0;
   int longi = strLength(text);                       // tamaño de la cadena
   unsigned int address = 6144 + (posy * 32) + posx;  // calcula la posicion en la VRAM
   while (longi-->0)
   {
    if (leida++>tama-1) { 
                      vpoke(address,222);vpoke(address+1,222);vpoke(address+2,222);
                      while (kbd_read(8)!=0x1);
                      ei_halt();
                      address-=tama;
                      fillVRAM(address,leida+2,227);
                      leida=0;
                      }
    vpoke(address++,*(text++)+163);                   // escribe en la VRAM
   } 
 }
