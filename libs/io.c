/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// L U E G O L U 3 G O   S T U D I O S   2 0 1 9 /////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////// M S X  C  D E V E L O P M E N T  S D K ////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////// Funciones de Entrada/Salida //////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "io.h"
#include "memoria.h"
#include "video.h"

#define JIFFY #0xFC9F
#define JIFFO #0xFC9E

int time_on;

void disable_click(){
__asm

  xor A
  ld (#CLIKSW),A

__endasm;
}



int kbd_read(unsigned char id){
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

unsigned char get_stick(unsigned char id)  {
id;
__asm

  push  ix    
  ld  ix,#0
  add ix,sp

  f_gtstck .equ 0x00D5

  push hl
  push de
  push bc
  push ix

  ld a, 4(ix)
  call #0x00d5

  pop ix
  pop bc
  pop de
  pop hl
  
  ld l, a

  pop ix           
  ret

__endasm;
return 0;
}

unsigned char get_trigger(unsigned char id)  {
id;
__asm

  push  ix    
  ld  ix,#0
  add ix,sp

  f_gttrgr .equ 0x00D8

  push hl
  push de
  push bc
  push ix

  ld a, 4(ix)
  call #0x00d8

  pop ix
  pop bc
  pop de
  pop hl
  
  ld l, a

  pop ix           
  ret

__endasm;
return 0;  
}

int sLength(char *str)
 {
     int i = 0;
     while(*(str++))  i++; 
     return i;
 }
int pos_matrix(int valor){

if (valor==0x01) return 0;
if (valor==0x02) return 1;
if (valor==0x04) return 2;
if (valor==0x08) return 3;
if (valor==0x10) return 4;
if (valor==0x20) return 5;
if (valor==0x40) return 6;
if (valor==0x80) return 7;

return 0;

}
int input_text(char *cadena)
{
  // FC9Eh
  int posicion;
  int row[6][8]={
    {0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37},
    {0x38,0x39,0x3A,0x3B,0x3C,0x3D,0x3E,0x3F},
    {0x00,0x00,0x2e,0x2c,0x00,0x00,0x41,0x42},
    {0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4A},
    {0x4B,0x4C,0x4D,0x4E,0x4F,0x50,0x51,0x52},
    {0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5A},
    };
  
  int marca;
  int fila;
 


  marca=0;
  posicion=sLength(cadena);

  if (kbd_read(7)==KB_BS && posicion>0){
    posicion--;
    cadena[posicion]=0;
    delay(0,0);
    return 1;
  } 
  if (posicion<30){
  if (kbd_read(8)==KB_SPACE){
     cadena[posicion]=0x40;
     cadena[posicion+1]=0;
     delay(0,0);
     return 1;
  } else 
  {
    for (fila=0;fila<6;fila++){
      if (marca=kbd_read(fila)){
        if ((((((peek((char *)JIFFY))*255)+(peek((char *)JIFFO)))-time_on))<100 && (cadena[posicion-1]==row[fila][pos_matrix(marca)])) return 0;
        cadena[posicion]=row[fila][pos_matrix(marca)];
        cadena[posicion+1]=0;
        time_on=((peek((char *)JIFFY))*255)+(peek((char *)JIFFO));
        return 1;
        }
      }
    }
}
time_on=0;
return 0;


}