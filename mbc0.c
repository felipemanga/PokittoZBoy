/*
  --------------------------------------
  This file is part of the zBoy project.
  Copyright (C) Mateusz Viste 2010, 2011
  --------------------------------------
 
  ROM-ONLY support
*/

void indexRAM(){
  int i=0;
  for(; i<0x8000>>5; i++ )
    ramidx[i] = 0;
  for(; i<0xA000>>5; i++ )
    ramidx[i] = 1;  
  for(; i<0xE000>>5; i++ )
    ramidx[i] = 2;
  for(; i<0xFE00>>5; i++ )
    ramidx[i] = 3;
  for(; i<0xFEA0>>5; i++ )
    ramidx[i] = 4;
  for(; i<0xFF80>>5; i++ )
    ramidx[i] = 5;
  for(; i<0x10000>>5; i++ )
    ramidx[i] = 6;  
}

inline uint8_t MemoryRead(int ReadAddr) {
  return RAMette[ ramidx[ReadAddr>>5] ][ ReadAddr ];
  //   PrintDebug("MemoryRead 0x%04X\n", ReadAddr);
  //   if (ReadAddr < 0x4000) {                                     /* ROM bank #0 */
    //     return(MemoryROM[ReadAddr]);
    //   } else if ( ReadAddr < 0xE000 ) {    /* Internal 8KiB RAM */
    //     return(MemoryInternalRAM[ReadAddr]);
    //   } else if ( ReadAddr < 0xFE00 ) {    /* RAM mirror */
    //     return(MemoryInternalRAM[ReadAddr - 8192]);
    //   } else if ( ReadAddr < 0xFEA0 ) {    /* Sprite OAM memory */
    //     return(SpriteOAM[ReadAddr]);
    //   } else if ((ReadAddr >= 0xFF80) && (ReadAddr <= 0xFFFF)) {   /* Hi RAM area */
    //     return (MemoryInternalHiRAM[ReadAddr]);
    //   } else if ((ReadAddr >= 0xFF00) && (ReadAddr <= 0xFF4B)) {   /* I/O registers */
    //     return(IoRegisters[ReadAddr]);
    //   } else if ((ReadAddr >= 0x8000) && (ReadAddr < 0xA000)) {    /* Video RAM (8KiB) */
    //     return(VideoRAM[ReadAddr]);
    //   } else {
    //     return 0;
    //   }
}


inline void MemoryWrite(uint32_t WriteAddr, uint8_t DataHolder) {
  PrintDebug("MemoryWrite 0x%04X [%02Xh]\n", WriteAddr, DataHolder);

  uint8_t *bank = RAMette[ ramidx[WriteAddr>>5] ];
  if( bank != IoRegisters ){
    bank += WriteAddr;
    if( ((uint32_t) bank) > 0x10000000 ){
      *bank = DataHolder;
    }
    return;
  }
  IOWrite( WriteAddr, DataHolder );
  
  // if ((WriteAddr >= 0xC000) && (WriteAddr < 0xE000)) {    /* Internal 8KiB RAM */
    //   MemoryInternalRAM[WriteAddr] = DataHolder;
    // } else if ((WriteAddr >= 0xE000) && (WriteAddr < 0xFE00)) {    /* RAM mirror */
    //   MemoryInternalRAM[WriteAddr - 8192] = DataHolder;
    // } else if ((WriteAddr >= 0xFE00) && (WriteAddr < 0xFEA0)) {    /* Sprite OAM memory */
    //   SpriteOAM[WriteAddr] = DataHolder;
    // } else if ((WriteAddr >= 0xFF80) && (WriteAddr <= 0xFFFF)) {   /* Hi RAM area */
    //   MemoryInternalHiRAM[WriteAddr] = DataHolder;
    // } else if ((WriteAddr >= 0x8000) && (WriteAddr < 0xA000)) {   /* Video RAM (8KiB) */
    //   VideoRAM[WriteAddr] = DataHolder;
    // } else

}


uint8_t MBC0_MemoryRead(int memaddr) {
  if (memaddr < 0x8000) {                                   /* ROM memory [0000-7FFF] */
    return(MemoryROM[memaddr]);
  } else {                                                  /* Else it's something I don't know about */
    /* IF (memaddr > 0xFFFF) THEN
         PrintMsg("MMU FATAL ERROR!" & CHR(10) & "MEMORYREAD() -> INVALID MEMADDR! [" & HEX(memaddr) & "]") : PressAnyKey() : END
       END IF
       PRINT "MMU fatal error: Tried to read from an unknown memory address: " & HEX(memaddr) & "h"
       SLEEP
       QuitEmulator = 1 */
    return 0; // (MemoryMAP[memaddr]);
  }
}


void MBC0_MemoryWrite(int memaddr, uint8_t DataByte) {
  /*PRINT "MMU fatal error: Tried to write to an unknown memory address: "; HEX(memaddr)
    QuitEmulator = 1 */
  // MemoryMAP[memaddr] = DataByte;
}
