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
  
  RAMette[0] = MemoryROM + (CurRomBank<<14) - 0x4000;
}


void MBC1Write( uint32_t memaddr, uint8_t DataByte, uint8_t *buffer ){
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
    else if (CurRomBank == 0x20) CurRomBank = 0x21;  /* Should I do that? Not super sure... */
    else if (CurRomBank == 0x40) CurRomBank = 0x41;  /* Should I do that? Not super sure... */
    else if (CurRomBank == 0x60) CurRomBank = 0x61;  /* Should I do that? Not super sure... */
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
      else if (CurRomBank == 0x20) CurRomBank = 0x21;  /* Should I do that? Not super sure... */
      else if (CurRomBank == 0x40) CurRomBank = 0x41;  /* Should I do that? Not super sure... */
      else if (CurRomBank == 0x60) CurRomBank = 0x61;  /* Should I do that? Not super sure... */
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

  RAMette[0] = MemoryROM + (CurRomBank<<14) - 0x4000;

}

const WriteHandlerT writeHandlers[] = {
  MBC1Write,
  RAMWrite,
  RAMWrite,
  RAMWrite,
  RAMWrite,
  IOWrite,  
  RAMWrite,
  RAMWrite,
  MBC1Write
};


