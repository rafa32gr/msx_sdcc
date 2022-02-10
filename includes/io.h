/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// L U E G O L U 3 G O   S T U D I O S   2 0 1 9 /////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////// M S X  C  D E V E L O P M E N T  S D K ////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// Funciones de Entrada/Salida /////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// Fila 8
#define  KB_RIGHT   0x80    
#define  KB_DOWN    0x40    
#define  KB_UP      0x20    
#define  KB_LEFT    0x10    
#define  KB_DEL     0x08
#define  KB_INS     0x04
#define  KB_HOME    0x02
#define  KB_SPACE   0x01 

// Fila 7
#define  KB_RET     0x80
#define  KB_SELECT  0x40
#define  KB_BS      0x20
#define  KB_STOP    0x10
#define  KB_TAB     0x08
#define  KB_ESC     0x04
#define  KB_F5      0x02
#define  KB_F4      0x01 

// Fila 6
#define  KB_F3      0x80
#define  KB_F2      0x40
#define  KB_F1      0x20
#define  KB_CODE    0x10
#define  KB_CAPS    0x08
#define  KB_GRAPH   0x04
#define  KB_CTRL    0x02
#define  KB_SHIFT   0x01 

#define  CLIKSW     0xF3DB  

/* =============================================================================
 disable_click
 Description : Disable the click that MSX emites when a key is pressed. 
 Input  : none.
============================================================================= */
extern void disable_click(void);
/* =============================================================================
 kbd_read(unsigned char id)
 Description : return the key pressed on row id from the key matrix. 
 Input  : id row.
============================================================================= */
extern int kbd_read(unsigned char id);
/* =============================================================================
 get_stick
 Description : return the direction on the joystick. 
 Input  : joystick port.
============================================================================= */
extern unsigned char get_stick(unsigned char id);
/* =============================================================================
 get_trigger
 Description : return the trigger pressed on the joystick. 
 Input  : joystick port.
============================================================================= */
extern unsigned char get_trigger(unsigned char id);


extern int input_text(char *cadena);