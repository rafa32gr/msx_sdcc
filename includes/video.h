//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// L U E G O L U 3 G O   S T U D I O S   2 0 1 9 /////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////// M S X  C  D E V E L O P M E N T  S D K ////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////// Funciones de Video ///////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#define  GRPACX  0xFCB7 
#define  GRPACY  0xFCB9

int strLength(char *str);
void vprint(unsigned char posx, unsigned char posy, char* text);
void nprint(unsigned char posx, unsigned char posy, int number);
void set_sprites16(void);
void set_sprite(unsigned char *sprite, int slot);
void draw_sprite_16( int x, int y,int slot, int color);
void ei_halt(void);
void screen_off(void);
void screen_on(void);
void disable_sprite(int orden);
void load_font( unsigned int tpatron, unsigned int tcolor, int posicion, int color);
/* =============================================================================
 delay
 Description : wait N seconds but can be skippable if SALTABLE flag is 1. 
 Input  : N seconds and SALTABLE flag.
============================================================================= */
void delay(int seconds, int saltable);
void vprint_step(unsigned char posx, unsigned char posy, char* text);
void vprint_pause(unsigned char posx, unsigned char posy, char* text, unsigned char tama);