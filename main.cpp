
#include "Pokitto.h"

using namespace Pokitto;

extern "C" {
#include "drv.h"

  

void write_command_16(uint16_t data)
{
   CLR_CS; // select lcd
   CLR_CD; // clear CD = command
   SET_RD; // RD high, do not read
  *LCD = uint32_t(data) << 3;
   CLR_WR_SLOW;  // WR low
   SET_WR;  // WR low, then high = write strobe
   SET_CS; // de-select lcd
}

void write_data_16(uint16_t data)
{
  CLR_CS;
  SET_CD;
  SET_RD;
  *LCD = uint32_t(data) << 3;
  CLR_WR;
  SET_WR;
  SET_CS;
}

int zboymain(int argc, char **argv);

}


// extern uint8_t *framebuffer;

/* initialization of the I/O subsystem. This is called by zBoy once, when the
 * emulator starts. screenwidth and screenheight must contain the size of
 * requested virtual screen, joyid is either the id of the joystick that have
 * to be polled (0..x) or -1 if no joystick support is required. */
extern "C" int drv_init(int screenwidth, int screenheight, int joyid){
  // framebuffer = Pokitto::Display::screenbuffer;
  return 0;
}

uint32_t prevTime;
extern uint32_t frameCount;

uint32_t reported = 0, changes = 0, selectbtn = 0;
/* returns the next input event in queue */
int drv_keypoll(void){
  
  if( (changes & (1<<UPBIT)) && !(reported & (1<<UPBIT)) ){
    reported |= 1<<UPBIT;
    if( Buttons::buttons_state & (1<<UPBIT) )
      return DRV_INPUT_KEYDOWN | DRV_INPUT_KEYBOARD | DRV_INPUT_KEY_UP;
    else 
      return DRV_INPUT_KEYUP | DRV_INPUT_KEYBOARD | DRV_INPUT_KEY_UP;
  }
  
  if( (changes & (1<<DOWNBIT)) && !(reported & (1<<DOWNBIT)) ){
    reported |= 1<<DOWNBIT;
    if( Buttons::buttons_state & (1<<DOWNBIT) )
      return DRV_INPUT_KEYDOWN | DRV_INPUT_KEYBOARD | DRV_INPUT_KEY_DOWN;
    else 
      return DRV_INPUT_KEYUP | DRV_INPUT_KEYBOARD | DRV_INPUT_KEY_DOWN;
  }

  if( (changes & (1<<LEFTBIT)) && !(reported & (1<<LEFTBIT)) ){
    reported |= 1<<LEFTBIT;
    if( Buttons::buttons_state & (1<<LEFTBIT) )
      return DRV_INPUT_KEYDOWN | DRV_INPUT_KEYBOARD | DRV_INPUT_KEY_LEFT;
    else 
      return DRV_INPUT_KEYUP | DRV_INPUT_KEYBOARD | DRV_INPUT_KEY_LEFT;
  }

  if( (changes & (1<<RIGHTBIT)) && !(reported & (1<<RIGHTBIT)) ){
    reported |= 1<<RIGHTBIT;
    if( Buttons::buttons_state & (1<<RIGHTBIT) )
      return DRV_INPUT_KEYDOWN | DRV_INPUT_KEYBOARD | DRV_INPUT_KEY_RIGHT;
    else 
      return DRV_INPUT_KEYUP | DRV_INPUT_KEYBOARD | DRV_INPUT_KEY_RIGHT;
  }

  if( (changes & (1<<CBIT)) && !(reported & (1<<CBIT)) ){
    reported |= 1<<CBIT;
    if( Buttons::buttons_state & (1<<CBIT) )
      return DRV_INPUT_KEYDOWN | DRV_INPUT_KEYBOARD | DRV_INPUT_KEY_RET;
    else 
      return DRV_INPUT_KEYUP | DRV_INPUT_KEYBOARD | DRV_INPUT_KEY_RET;
  }

  if( (changes & (1<<ABIT)) && !(reported & (1<<ABIT)) ){
    reported |= 1<<ABIT;
    if( Buttons::buttons_state & (1<<ABIT) )
      return DRV_INPUT_KEYDOWN | DRV_INPUT_KEYBOARD | DRV_INPUT_KEY_LALT;
    else 
      return DRV_INPUT_KEYUP | DRV_INPUT_KEYBOARD | DRV_INPUT_KEY_LALT;
  }

  if( (changes & (1<<BBIT)) && !(reported & (1<<BBIT)) ){
    reported |= 1<<BBIT;
    if( Buttons::buttons_state & (1<<BBIT) )
      return DRV_INPUT_KEYDOWN | DRV_INPUT_KEYBOARD | DRV_INPUT_KEY_LCTRL;
    else 
      return DRV_INPUT_KEYUP | DRV_INPUT_KEYBOARD | DRV_INPUT_KEY_LCTRL;
  }

  if( (changes & (1<<7)) && !(reported & (1<<7)) ){
    reported |= 1<<7;
    if( selectbtn )
      return DRV_INPUT_KEYDOWN | DRV_INPUT_KEYBOARD | DRV_INPUT_KEY_TAB;
    else 
      return DRV_INPUT_KEYUP | DRV_INPUT_KEYBOARD | DRV_INPUT_KEY_TAB;
  }
  
  reported = 0;
  Buttons::pollButtons();
  
  changes = Buttons::buttons_state ^ (Buttons::buttons_held | Buttons::buttons_released);

  if( !*((uint8_t *) 0xA0000001) ){
    if( !selectbtn )
      changes |= 1<<7;
    selectbtn = 1;
  }else if( selectbtn ){
    changes |= 1<<7;
    selectbtn = 0;
  }
  
  return DRV_INPUT_NONE;
  
}

/* loads a palette of colors into zBoy. *palette must be an array of at least
 * 256 color values written in 32bits each as RGB triplets */
int drv_loadpal(uint32_t *palette){
  return 0;
}

/* returns a monotonously increasing counter that increases by 1 every
 * milisecond */
unsigned long drv_getticks(void){
  return Pokitto::Core::getTime();
}

extern "C" void indexRAM();

extern "C" uint32_t palette[];

int main () {
  
  Core::begin();

  char *args[] = {""};
  *reinterpret_cast<uint32_t *>(0x40048080) |= 3 << 26;

  /* * Grayscale /
  Display::palette[0] = Display::RGBto565( 0xFF, 0xFF, 0xFF );
  Display::palette[1] = Display::RGBto565( 0xAA, 0xAA, 0xAA );
  Display::palette[2] = Display::RGBto565( 0x55, 0x55, 0x55 );
  Display::palette[3] = Display::RGBto565( 0x00, 0x00, 0x00 );
  /*/

  /* * Green Tint /
  Display::palette[3] = Display::RGBto565( 0x24, 0x31, 0x37 );
  Display::palette[2] = Display::RGBto565( 0x3f, 0x50, 0x3f );
  Display::palette[1] = Display::RGBto565( 0x76, 0x84, 0x48 );
  Display::palette[0] = Display::RGBto565( 0xac, 0xb5, 0x6b );
  /*/

  /* * /

  palette[3] = uint32_t(Display::RGBto565( 0x33,0x2c,0x50 ))<<3;
  palette[2] = uint32_t(Display::RGBto565( 0x46,0x87,0x8f ))<<3;
  palette[1] = uint32_t(Display::RGBto565( 0x94,0xe3,0x44 ))<<3;
  palette[0] = uint32_t(Display::RGBto565( 0xe2,0xf3,0xe4 ))<<3;

  /* */
 
  /* DRMARIO */
  #ifdef DRMARIOPALETTE
  palette[ 7 ] = uint32_t(Display::RGBto565(0, 0, 0))<<3;
  palette[ 6 ] = uint32_t(Display::RGBto565(95, 87, 79))<<3;
  palette[ 5 ] = uint32_t(Display::RGBto565(194, 195, 199))<<3;
  palette[ 4 ] = uint32_t(Display::RGBto565(141, 173, 255))<<3;
  // palette[ 4 ] = uint32_t(Display::RGBto565(255, 241, 232))<<3;

  palette[ 11 ] = uint32_t(Display::RGBto565(126, 37, 83))<<3;
  palette[ 10 ] = uint32_t(Display::RGBto565(255, 0, 77))<<3;
  palette[ 8 ] = uint32_t(Display::RGBto565(255, 119, 168))<<3;
  palette[ 9 ] = uint32_t(Display::RGBto565(255, 204, 170))<<3;

  palette[ 15 ] = uint32_t(Display::RGBto565(0, 135, 81))<<3;
  palette[ 14 ] = uint32_t(Display::RGBto565(255, 163, 0))<<3;
  palette[ 13 ] = uint32_t(Display::RGBto565(0, 228, 54))<<3;
  palette[ 12 ] = uint32_t(Display::RGBto565(255, 236, 39))<<3;
  
  palette[ 3 ] = uint32_t(Display::RGBto565(29, 43, 83))<<3;
  palette[ 2 ] = uint32_t(Display::RGBto565(171, 82, 54))<<3;
  palette[ 1 ] = uint32_t(Display::RGBto565(131, 118, 156))<<3;
  palette[ 0 ] = uint32_t(Display::RGBto565(255, 241, 232))<<3;
  /* */
  #endif

  
  #ifdef TETRISPALETTE
  palette[ 15 ] = uint32_t(Display::RGBto565(0, 0, 0))<<3;
  palette[ 14 ] = uint32_t(Display::RGBto565(95, 87, 79))<<3;
  palette[ 13 ] = uint32_t(Display::RGBto565(194, 195, 199))<<3;
  palette[ 12 ] = uint32_t(Display::RGBto565(141, 173, 255))<<3;
  // palette[ 4 ] = uint32_t(Display::RGBto565(255, 241, 232))<<3;

  palette[ 3 ] = uint32_t(Display::RGBto565(126, 37, 83))<<3;
  palette[ 2 ] = uint32_t(Display::RGBto565(255, 0, 77))<<3;
  palette[ 1 ] = uint32_t(Display::RGBto565(255, 119, 168))<<3;
  palette[ 0 ] = uint32_t(Display::RGBto565(255, 204, 170))<<3;
  
  palette[ 7 ] = uint32_t(Display::RGBto565(0, 135, 81))<<3;
  palette[ 6 ] = uint32_t(Display::RGBto565(255, 163, 0))<<3;
  palette[ 5 ] = uint32_t(Display::RGBto565(0, 228, 54))<<3;
  palette[ 4 ] = uint32_t(Display::RGBto565(255, 236, 39))<<3;
  
  palette[ 11 ] = uint32_t(Display::RGBto565(29, 43, 83))<<3;
  palette[ 10 ] = uint32_t(Display::RGBto565(171, 82, 54))<<3;
  palette[ 8 ] = uint32_t(Display::RGBto565(131, 118, 156))<<3;
  palette[ 9 ] = uint32_t(Display::RGBto565(255, 241, 232))<<3;
  
  #endif


  #ifdef BBGHSTPALETTE
  palette[ 15 ] = uint32_t(Display::RGBto565(0, 0, 0))<<3;
  palette[ 14 ] = uint32_t(Display::RGBto565(95, 87, 79))<<3;
  palette[ 13 ] = uint32_t(Display::RGBto565(194, 195, 199))<<3;
  palette[ 12 ] = uint32_t(Display::RGBto565(141, 173, 255))<<3;
  // palette[ 4 ] = uint32_t(Display::RGBto565(255, 241, 232))<<3;

  palette[ 3 ] = uint32_t(Display::RGBto565(126, 37, 83))<<3;
  palette[ 2 ] = uint32_t(Display::RGBto565(255, 0, 77))<<3;
  palette[ 1 ] = uint32_t(Display::RGBto565(255, 119, 168))<<3;
  palette[ 0 ] = uint32_t(Display::RGBto565(255, 204, 170))<<3;
  
  palette[ 11 ] = uint32_t(Display::RGBto565(0, 135, 81))<<3;
  palette[ 10 ] = uint32_t(Display::RGBto565(255, 163, 0))<<3;
  palette[ 8 ] = uint32_t(Display::RGBto565(0, 228, 54))<<3;
  palette[ 9 ] = uint32_t(Display::RGBto565(255, 236, 39))<<3;
  
  palette[ 7 ] = uint32_t(Display::RGBto565(29, 43, 83))<<3;
  palette[ 6 ] = uint32_t(Display::RGBto565(171, 82, 54))<<3;
  palette[ 5 ] = uint32_t(Display::RGBto565(131, 118, 156))<<3;
  palette[ 4 ] = uint32_t(Display::RGBto565(255, 241, 232))<<3;
  
  #endif
  

  #ifdef TENNISPALETTE
  palette[ 3 ] = uint32_t(Display::RGBto565(0, 0, 0))<<3;
  palette[ 2 ] = uint32_t(Display::RGBto565(95, 87, 79))<<3;
  palette[ 1 ] = uint32_t(Display::RGBto565(194, 195, 199))<<3;
  palette[ 0 ] = uint32_t(Display::RGBto565(141, 173, 255))<<3;
  // palette[ 4 ] = uint32_t(Display::RGBto565(255, 241, 232))<<3;

  palette[ 11 ] = uint32_t(Display::RGBto565(126, 37, 83))<<3;
  palette[ 10 ] = uint32_t(Display::RGBto565(255, 0, 77))<<3;
  palette[ 8 ] = uint32_t(Display::RGBto565(255, 119, 168))<<3;
  palette[ 9 ] = uint32_t(Display::RGBto565(255, 204, 170))<<3;
  
  palette[ 15 ] = uint32_t(Display::RGBto565(0, 135, 81))<<3;
  palette[ 14 ] = uint32_t(Display::RGBto565(255, 163, 0))<<3;
  palette[ 13 ] = uint32_t(Display::RGBto565(0, 228, 54))<<3;
  palette[ 12 ] = uint32_t(Display::RGBto565(255, 236, 39))<<3;
  
  palette[ 4 ] = uint32_t(Display::RGBto565(29, 43, 83))<<3;
  palette[ 7 ] = uint32_t(Display::RGBto565(171, 82, 54))<<3;
  palette[ 6 ] = uint32_t(Display::RGBto565(131, 118, 156))<<3;
  palette[ 5 ] = uint32_t(Display::RGBto565(255, 241, 232))<<3;
  
  #endif
  
  indexRAM();


  Pokitto::lcdClear();

  #ifdef SCALING
  Pokitto::setWindow( 0, 10, 176, 199+10 );
  #else
  Pokitto::setWindow( 16, 30, 144+15, 159+30 );
  #endif

  SET_MASK_P2;
  write_command_16(0x03); write_data_16(0x1038);
  write_command_16(0x22);
  CLR_CS_SET_CD_RD_WR;

  zboymain(0, args);
  
}

