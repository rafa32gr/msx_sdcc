/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// L U E G O L U 3 G O   S T U D I O S   2 0 1 9 /////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////// M S X  C  D E V E L O P M E N T  S D K ////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// Funciones de Matematicas ///////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


unsigned char get_random(unsigned char semilla) __z88dk_fastcall {
  semilla;
          __asm
                ld a,h
                rrca
                rrca
                xor h
                rrca
                xor l
                rrca
                rrca
                rrca
                rrca
                xor l
                rra
                adc hl,hl
          __endasm;
return 0;
}


int abs(int valor)
{

return (0x80000000 & valor) ? ~(--valor):valor;

}

