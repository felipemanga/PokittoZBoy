/*
   --------------------------------------
   This file is part of the zBoy project.
   Copyright (C) Mateusz Viste 2010
   --------------------------------------

   * MBC1 short documentation *

   MBC1 can operate in two modes:
   16Mbit ROM / 8 KByte RAM (default at power on)
   4Mbit ROM / 32 KByte RAM

   Write a byte into 6000-7FFF to select the mode:
   Any EVEN byte selects 16/8 mode, any UNEVEN byte selects 4/32 mode (only the last bit is looked at).

   Write a byte into 2000-3FFF to select the ROM bank for 4000-7FFF (bank #0 will point to bank #1 anyway)
   Only 5 least significant bits are looked at (xxxBBBBB)

   For mode 4/32, you need to select the RAM bank to be used (at A000-C000): to do that, write a byte into
   4000-5FFF. The 2 least significant bits of this byte (xxxxxxBB) are telling what RAM bank to use.
   Also, before using any RAM bank, you need to enable it by writing xxxx1010 into 0000-1FFF (writing there
   any non-xxxx1010 value disables the RAM bank).

   For mode 16/8, 5 bits is not enough to address all 128 banks (each bank is 16KiB big). Write a byte into
   4000-5FFF. The 2 least significant bits of this byte (xxxxxxBB) will be used as the two most significant
   bits (that is bits 5 and 6) of the ROM address.

   Note: The content of the MBC1 RAM can be saved during poweroff if the cartridge comes with a battery.
*/

// uint32_t RomOffset;

void setBank( int b ){
  CurRomBank = b;
  // RomOffset = (b<<14) - 0x4000;
  RAMette[0] = MemoryROM + (b<<14) - 0x4000;
}

void indexRAM(){
  int i=0;
  for(; i<0x4000>>5; i++ )
    ramidx[i] = 8;
  for(; i<0x8000>>5; i++ )
    ramidx[i] = 0;
  for(; i<0xA000>>5; i++ )
    ramidx[i] = 1;
  for(; i<0xC000>>5; i++ )
    ramidx[i] = 7;
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
  setBank(1);
}

inline uint8_t MemoryReadPC( int ReadAddr ){
  int id = ramidx[ReadAddr>>5];
  uint8_t *buffer = RAMette[ id ];
  // if( !id ) buffer += RomOffset;
  PCBuffer = buffer + ReadAddr;
  return *PCBuffer;
}

inline uint8_t MemoryRead(int ReadAddr) {
  int id = ramidx[ReadAddr>>5];
  uint8_t *buffer = RAMette[ id ];
// if( !id ) buffer += RomOffset;

  return buffer[ ReadAddr ];

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


void MBC1Write( uint32_t memaddr, uint8_t DataByte ){
  uint32_t OldRomBank = CurRomBank;
  if ( memaddr < 0x2000 ){
    // nop
  } else if ( memaddr < 0x4000 ) {
    /* Select current ROM or RAM bank on MBC1 */
    /* TODO checklist #784632 */
    if (Mbc1Model == MBC1_16_8) {  /* Mode 16/8 */
      CurRomBank &= bx01100000;
      CurRomBank |= (DataByte & bx00011111);
    } else {  /* Mode 4/32 */
      CurRomBank = (DataByte & bx00011111);
    }
    if (CurRomBank == 0x00) CurRomBank = 0x01;  /* Should I do that? Not super sure... */
    if (CurRomBank == 0x20) CurRomBank = 0x21;  /* Should I do that? Not super sure... */
    if (CurRomBank == 0x40) CurRomBank = 0x41;  /* Should I do that? Not super sure... */
    if (CurRomBank == 0x60) CurRomBank = 0x61;  /* Should I do that? Not super sure... */
    PrintDebug("switched ROM bank to %d\n", CurRomBank);
    
  } else if ((memaddr >= 0x4000) && (memaddr < 0x6000)) {
    
    if (Mbc1Model == MBC1_16_8) {

      // For mode 16/8, 5 bits is not enough to address all
      // 128 banks (each bank is 16KiB big). Write a
      // byte into 4000-5FFF. The 2 least significant bits
      // of this byte (xxxxxxBB) will be used as the two most
      // significant bits of the ROM address.
      CurRomBank &= bx00011111;
      CurRomBank |= ((DataByte << 5) & bx01100000);

      if (CurRomBank == 0x00) CurRomBank = 0x01;  /* Should I do that? Not super sure... */
      if (CurRomBank == 0x20) CurRomBank = 0x21;  /* Should I do that? Not super sure... */
      if (CurRomBank == 0x40) CurRomBank = 0x41;  /* Should I do that? Not super sure... */
      if (CurRomBank == 0x60) CurRomBank = 0x61;  /* Should I do that? Not super sure... */
      PrintDebug("switched ROM bank to %d\n", CurRomBank);
      
    } else {   /* For mode 4/32, you need to select the RAM bank to be used (at A000-C000). to do that, write a */
      CurRamBank = (DataByte & bx00000011);    /* byte into 4000-5FFF. The 2 least significant bits of this */
    }                                            /* byte (xxxxxxBB) are telling what RAM bank to use. */
  } else if ((memaddr >= 0x6000) && (memaddr < 0x8000)) {   /* Configuration for the MBC1 chip (selection of mem model) */
    if ((DataByte & bx00000001) == 0) {
      Mbc1Model = MBC1_16_8;   /* 16/8 model */
      /* SetUserMsg("MBC 16/8"); */
      PrintDebug("switched MBC1 mode to 16/8\n");
    } else {
      Mbc1Model = MBC1_4_32;   /* 4/32 model */
      /* SetUserMsg("MBC 4/32"); */
      PrintDebug("switched MBC1 mode to 4/32\n");
    }
  }

  if( OldRomBank != CurRomBank ){
    setBank( CurRomBank );
  }

}

inline void MemoryWrite(uint32_t WriteAddr, uint8_t DataHolder) {
  PrintDebug("MemoryWrite 0x%04X [%02Xh]\n", WriteAddr, DataHolder);

  uint8_t *bank = RAMette[ ramidx[WriteAddr>>5] ];
  if( bank != IoRegisters ){
    bank += WriteAddr;
    if( ((uint32_t) bank) > 0x10000000 ){
      *bank = DataHolder;
    }else{
      MBC1Write( WriteAddr, DataHolder );
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


uint8_t MBC1_MemoryRead(int memaddr) {
  if ((memaddr >= 0xA000) && (memaddr < 0xC000)) {        /* RAM bank n */
    if (Mbc1Model == MBC1_4_32) {   /* 4/32 mode */
        return(MemoryBankedRAM[(CurRamBank << 13) + memaddr]);     /* SHL 13 is the same than *8192 (but faster) */
      } else {   /* 16/8 mode */
        return(MemoryBankedRAM[memaddr]);
    }
  } else if ((memaddr >= 0x4000) && (memaddr < 0x8000)) {    /* ROM bank #n */
        if (RomInfos.RomSize == 32768) {
            return(MemoryROM[memaddr]);
          } else {
            /*if (Mbc1Model == 2) {  */   /*  4/32 */
                if (((CurRomBank << 14) + (memaddr - 0x4000)) > RomInfos.RomSize) {  /* SHL 14 is the same than *16384 (but faster) */
                  // printf("INVALID ROM ADDRESS! [bank %d, offset %d]\n", CurRomBank, memaddr);
                  exit(1);
                }
                return(MemoryROM[(CurRomBank << 14) + (memaddr - 0x4000)]);  /* SHL 14 is the same than *16384 (but faster) */
            /*  } else { */   /* 16/8 */
            /*    if ((((CurRomBank | (Mbc1RamRomSelect << 5)) << 14) + (memaddr - 0x4000)) > RomInfos.RomSize) { */  /* SHL 14 is the same than *16384 (but faster) */
            /*    if (((CurRomBank << 14) + (memaddr - 0x4000)) > RomInfos.RomSize) { */
            /*      printf("INVALID ROM ADDRESS!"); */ /* & CHR(10) & "CURBANK=" & CurRomBank & CHR(10) & "MBC1 MODEL=" & Mbc1Model) */
            /*      return(0); */
            /*    } */
            /*    //return(MemoryROM[((CurRomBank | (Mbc1RamRomSelect << 5)) << 14) + (memaddr - 0x4000)]); */ /* SHL 14 is the same than *16384 (but faster) */
            /*    return(MemoryROM[(CurRomBank << 14) + (memaddr - 0x4000)]); */ /* SHL 14 is the same than *16384 (but faster) */
            /*} */
        }
  } else {                                                  /* Else it's something I don't know about */
    /*IF (memaddr > 0xFFFF) THEN */
    /*  PrintMsg("MMU FATAL ERROR!" & CHR(10) & "MEMORYREAD() -> INVALID MEMADDR! [" & HEX(memaddr) & "]") : PressAnyKey() : END */
    /*END IF */
    /*PRINT "MMU fatal error: Tried to read from an unknown memory address: " & HEX(memaddr) & "h" */
    /*SLEEP */
    /*QuitEmulator = 1 */
    // return(MemoryMAP[memaddr]);
  }
}


void MBC1_MemoryWrite(int memaddr, uint8_t DataByte) {
  if (memaddr < 0x2000) {   /* Enables / disables current RAM bank (not supported yet) */
    /* Before using any RAM bank, you need to enable it by writing xxxx1010 into 0000-1FFF (writing there
       any non-xxxx1010 value disables the RAM bank). */
    /*if ((DataByte & bx00001111) == bx00001010) { */  /* Enables currently selected RAM bank */
    /*    RamBankWrite = 1; */
    /*  } else { */ /* Disables currently selected RAM bank */
          /*UserMessage = "RAM BANK DISABLED" */
    /*    RamBankWrite = 0; */
    /*} */
  } else if ((memaddr >= 0x2000) && (memaddr < 0x4000)) {       /* Select current ROM or RAM bank on MBC1 */
    /* TODO checklist #784632 */
    if (Mbc1Model == MBC1_16_8) {  /* Mode 16/8 */
        CurRomBank &= bx01100000;
        CurRomBank |= (DataByte & bx00011111);
      } else {  /* Mode 4/32 */
        CurRomBank = (DataByte & bx00011111);
    }
    if (CurRomBank == 0x00) CurRomBank = 0x01;  /* Should I do that? Not super sure... */
    if (CurRomBank == 0x20) CurRomBank = 0x21;  /* Should I do that? Not super sure... */
    if (CurRomBank == 0x40) CurRomBank = 0x41;  /* Should I do that? Not super sure... */
    if (CurRomBank == 0x60) CurRomBank = 0x61;  /* Should I do that? Not super sure... */
    PrintDebug("switched ROM bank to %d\n", CurRomBank);
  } else if ((memaddr >= 0x4000) && (memaddr < 0x6000)) {
    if (Mbc1Model == MBC1_16_8) {         /* For mode 16/8, 5 bits is not enough to address all 128 banks (each bank is 16KiB big). Write a */
        CurRomBank &= bx00011111; /* byte into 4000-5FFF. The 2 least significant bits of this byte (xxxxxxBB) will be used as the two most */
        CurRomBank |= ((DataByte << 5) & bx01100000);  /*  significant bits of the ROM address. */
        if (CurRomBank == 0x00) CurRomBank = 0x01;  /* Should I do that? Not super sure... */
        if (CurRomBank == 0x20) CurRomBank = 0x21;  /* Should I do that? Not super sure... */
        if (CurRomBank == 0x40) CurRomBank = 0x41;  /* Should I do that? Not super sure... */
        if (CurRomBank == 0x60) CurRomBank = 0x61;  /* Should I do that? Not super sure... */
        PrintDebug("switched ROM bank to %d\n", CurRomBank);
      } else {   /* For mode 4/32, you need to select the RAM bank to be used (at A000-C000). to do that, write a */
        CurRamBank = (DataByte & bx00000011);    /* byte into 4000-5FFF. The 2 least significant bits of this */
    }                                            /* byte (xxxxxxBB) are telling what RAM bank to use. */
  } else if ((memaddr >= 0x6000) && (memaddr < 0x8000)) {   /* Configuration for the MBC1 chip (selection of mem model) */
    if ((DataByte & bx00000001) == 0) {
        Mbc1Model = MBC1_16_8;   /* 16/8 model */
        /* SetUserMsg("MBC 16/8"); */
        PrintDebug("switched MBC1 mode to 16/8\n");
      } else {
        Mbc1Model = MBC1_4_32;   /* 4/32 model */
        /* SetUserMsg("MBC 4/32"); */
        PrintDebug("switched MBC1 mode to 4/32\n");
    }
  } else if ((memaddr >= 0xA000) && (memaddr < 0xC000)) {    /* RAM bank n */
    if (Mbc1Model == MBC1_4_32) {   /* 4/32 mode */
        /*MemoryBankedRAM[(Mbc1RamRomSelect << 13) + memaddr] = DataByte; */    /* SHL 13 is the same than * 8192 (but faster) */
        MemoryBankedRAM[(CurRamBank << 13) + memaddr] = DataByte;     /* SHL 13 is the same than * 8192 (but faster) */
      } else {   /* 16/8 mode */
        MemoryBankedRAM[memaddr] = DataByte;
    }
  } else {                                                   /* Else it's something I don't know about */
    /*PRINT "MMU fatal error: Tried to write to an unknown memory address: "; HEX(memaddr) */
    /*QuitEmulator = 1 */
    // MemoryMAP[memaddr] = DataByte;
  }
}
