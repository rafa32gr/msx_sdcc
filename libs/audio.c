/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// L U E G O L U 3 G O   S T U D I O S   2 0 1 9 /////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////// M S X  C  D E V E L O P M E N T  S D K ////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////// Funciones de Audio //////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "audio.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// funcion que para la reproduccion de la melodia //////////////////////////////////////////////////////////////////////////

void music_stop(void){

 __asm
                LD HL,PLYDIR+2     // Carga en la interrupcion la direccion de parada
                LD (#0xFDA0),HL   
                LD A,#0xC3     
                LD (#0xFD9F),A
                EI
__endasm;

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// funcion que inicializa la melodia cargada previamente /////////////////////////////////////////////////////////////////////

void init_music(){

// La melodia a inicializar ha de encontrarse en #0xd772

__asm

  ld HL,MSCSLT   // llamada a la inicializacion del Arkos player
  ld A,#0         // Selecciona la melodia
  call PLYDIR    // Ejecuta el Player
  
// Establece la interrupcion en la que se llama al player

  LD HL,PLYDIR+3   // Direccion a la que salta en cada interrupcion
  LD (#0xFDA0),HL   
  LD A,#0xC3      // Frecuencia con la que se llama
  LD (#0xFD9F),A
  EI
__endasm;

}
void play_sfx(int sonido){
sonido;

  __asm
  

FX_Play:

  
  push bc
  push de
  push hl
  push ix
  push iy
 // ld l, a     // effect
  ld a, #1     // channel B
  ld h, #15    // volume
  ld e, #36    // C4 ??
  ld d, #0
  ld bc, #0
  call #0xd00c
  pop iy
  pop ix
  pop hl
  pop de
  pop bc
  ret
FX_Play_nofx:
  pop hl
  ret



  ret
  __endasm;
}

void init_sfx(){

// La melodia a inicializar ha de encontrarse en #0xd772

__asm

  ld DE,SFXSLT   // llamada a la inicializacion del Arkos player
  //ld A,#0         // Selecciona la melodia
  call PLYDIR+9    // Ejecuta el Player
  
// Establece la interrupcion en la que se llama al player

  //call PLYDIR+1

//  LD HL,PLYDIR+3   // Direccion a la que salta en cada interrupcion
//  LD (#0xFDA0),HL   
//  LD A,#0xC3      // Frecuencia con la que se llama
//  LD (#0xFD9F),A
//  EI
__endasm;

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Carga la melodia en memoria ///////////////////////////////////////////////////////////////////////////////////////////////

void load_song(unsigned int d_origen , unsigned int longitud){

d_origen;
longitud;

__asm
  push ix
  ld ix,#0
  add ix,sp
      
  ld  L,4(ix) // Carga en HL la direccion donde se encuetra el origen de la melodia
  ld  H,5(ix)
    
  ld E,6(ix) // Carga en DE la longitud de la melodia
  ld D,7(ix)
   
  ld b,d
  ld c,e

  ld DE,MSCSLT // Carga la direccion donde poner la melodia

  ldir
    
  pop IX
  ret

__endasm;

}

void load_sfx(unsigned int d_origen , unsigned int longitud){

d_origen;
longitud;

__asm
  push ix
  ld ix,#0
  add ix,sp
      
  ld  L,4(ix) // Carga en HL la direccion donde se encuetra el origen de la melodia
  ld  H,5(ix)
    
  ld E,6(ix) // Carga en DE la longitud de la melodia
  ld D,7(ix)
   
  ld b,d
  ld c,e

  ld DE,SFXSLT // Carga la direccion donde poner la melodia

  ldir
    
  pop IX
  ret

__endasm;

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Carga Arkos player en memoria /////////////////////////////////////////////////////////////////////////////////////////////

void load_player(unsigned int d_origen ){

d_origen;


__asm
  push ix
  ld ix,#0
  add ix,sp
      
    ld  L,4(ix)           // Carga en HL la direccion pasada a la funcion
    ld  H,5(ix)
    ld BC,MSCSLT-PLYDIR   // Longitud del Player
    ld DE,PLYDIR          // Direccin donde tiene que estar el Player
        
    ldir

    pop IX
    ret

  __endasm;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////