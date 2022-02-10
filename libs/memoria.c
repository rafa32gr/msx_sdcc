/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// L U E G O L U 3 G O   S T U D I O S   2 0 1 9 /////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////// M S X  C  D E V E L O P M E N T  S D K ////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// Funciones de Memoria //////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void set_page_slot1(int pagina)

{

__asm
    push ix        
    ld ix,#0
    add ix,sp
    ld  l,4(ix)  ; load page to change
    ld a,l
    ld a, l
    ld (0x6800),a
__endasm;
pagina=pagina;

}


void set_page_slot2(int pagina)
{

 __asm
        push ix        
        ld ix,#0
        add ix,sp
        ld  l,4(ix)  ; load page to change
        ld a,l
        ld a, l
        ld (0x7000),a
__endasm;
pagina=pagina;
}



void set_page_slot3(int pagina) __z88dk_fastcall
{

__asm
  push ix        
  ld ix,#0
  add ix,sp
  ld  l,4(ix)  ; load page to change
  ld a,l
  ld (0x7800),a
pop ix       
__endasm;
pagina=pagina;
}

void search(void)
{
    
    __asm
        call 0x0138 ;RSLREG
        rrca
        rrca
        and #0x03
        ; Secondary Slot
        ld c,a
        ld hl,#0x0FCC1
        add a,l
        ld l,a
        ld a,(hl)
        and #0x80
        or c
        ld c,a
        inc l
        inc l
        inc l
        inc l
        ld a,(hl)
        ; Define slot ID
        and #0x0C
        or c
        ld h,#0x80
        ; Enable
        call 0x0024 ;ENASLT
    __endasm;
}




char peek(unsigned char *addr)
{

return *addr;  
}



void poke(unsigned int direccion, char valor)

{

direccion;
valor;

__asm

  push IX
  ld   IX,#0
  add  IX,SP
  

  ld   L,4(IX)
  ld   H,5(IX)
  ld   A,6(IX)
  ld   (HL),A

  pop  IX

__endasm;

}
