
#define FILE_MODE_BINARY 0x4
extern uint8_t c_fileOpen(char*, char);
extern void c_fileClose();
extern char c_fileGetChar();
extern void c_filePutChar(char);
extern void c_fileWriteBytes(uint8_t *, uint16_t);
extern uint16_t c_fileReadBytes(uint8_t *, uint16_t);
extern void c_fileSeekAbsolute(long);
extern void c_fileSeekRelative(long);
extern void c_fileRewind();
extern void c_fileEnd();
extern long int c_fileGetPosition();
extern uint8_t c_filePeek(long);
extern void c_filePoke(long, uint8_t);
extern int c_fileReadLine(char*,int);
extern char* c_getCurrentFileName ();
extern char* c_getNextFile (char*);
extern char* c_getFirstFile(char*);
extern char* c_getFirstDirEntry();
extern char* c_getNextDirEntry();
extern int c_isThisFileOpen(char*);
extern int c_fileOK();
extern int c_dirOpen();
extern int c_dirUp();

#define fileOpen c_fileOpen
#define fileClose c_fileClose
#define fileGetChar c_fileGetChar
#define filePutChar c_filePutChar
#define fileWriteBytes c_fileWriteBytes
#define fileReadBytes c_fileReadBytes
#define fileSeekAbsolute c_fileSeekAbsolute
#define fileSeekRelative c_fileSeekRelative
#define fileRewind c_fileRewind
#define fileEnd c_fileEnd
#define fileGetPosition c_fileGetPosition
#define filePeek c_filePeek
#define filePoke c_filePoke
#define fileReadLine c_fileReadLine
#define getCurrentFileName  c_getCurrentFileName
#define getNextFile  c_getNextFile
#define getFirstFile  c_getFirstFile
#define getFirstDirEntry  c_getFirstDirEntry
#define getNextDirEntry  c_getNextDirEntry
#define isThisFileOpen c_isThisFileOpen
#define fileOK c_fileOK
#define dirOpen c_dirOpen
#define dirUp c_dirUp

#define fileSetPosition(n)  (c_fileSeekAbsolute(n))

uint32_t checksum;

int initCRC(){
    
    if( !checksum ){
	int i;
	for( i=0; i<sizeof(MemoryROM); ++i )
	    checksum += MemoryROM[i];
    }

    char savefile[30];
    snprintf(savefile, 30, "%08X.SAV", checksum);
    if( fileOpen(savefile, FILE_MODE_BINARY) != 0 ){
	snprintf(savefile, 30, "%08X.SAV Missing", checksum);
	SetUserMsg( savefile );
	return 0;
    }
    return 1;
}

void LoadGame(void) {
    if( !initCRC() ) return;
    
    uint32_t tmp;
    fileReadBytes( &tmp, 4 );

    if( tmp != *(uint32_t *) "ZB01" ) return;

    fileReadBytes( &Register, sizeof(Register) );
    InterruptsState = fileGetChar();
    HaltBug = fileGetChar();
    HaltState = fileGetChar();
    fileReadBytes( &TimerC, sizeof(TimerC) );
    fileReadBytes( &TotalCycles, sizeof(TotalCycles) );
    

    fileReadBytes( &DividerCycleCounter, sizeof(DividerCycleCounter) );

  /* filePutChar(JoyOldReg); */
    fileReadBytes( &VideoClkCounterMode, sizeof(VideoClkCounterMode) );
    fileReadBytes( &VideoClkCounterVBlank, sizeof(VideoClkCounterVBlank) );

    CurLY = fileGetChar();
    LastLYdraw = 0; // filePutChar();
    CurRamBank = fileGetChar();
    CurRomBank = fileGetChar();
  
    fileReadBytes( _MemoryInternalRAM, sizeof(_MemoryInternalRAM) );
    fileReadBytes( _MemoryInternalHiRAM, sizeof(_MemoryInternalHiRAM) );
    fileReadBytes( _MemoryBankedRAM, sizeof(_MemoryBankedRAM) );
    fileReadBytes( _VideoRAM, sizeof(_VideoRAM) );
    fileReadBytes( _SpriteOAM, sizeof(_SpriteOAM) );
    fileReadBytes( _IoRegisters, sizeof(_IoRegisters) );
    fileReadBytes( RAMette, sizeof(RAMette) );

    fileClose();
    SetUserMsg("GAME LOADED");
}

void SaveGame(void) {
    if( !initCRC() ) return;
    SetUserMsg("SAVING...");
  
  /* /\* Write header *\/ */
  fileWriteBytes("ZB01", 4);
  /* /\* Write CPU Registers *\/ */
  fileWriteBytes( &Register, sizeof(Register) );
  
  /* /\* Write the IME *\/ */
  filePutChar((InterruptsState & 0xFF));
  /* /\* Write internal counters and flags *\/ */
  filePutChar((HaltBug & 0xFF));
  filePutChar((HaltState & 0xFF));
  fileWriteBytes( &TimerC, sizeof(TimerC) );
  fileWriteBytes( &TotalCycles, sizeof(TotalCycles) );
  fileWriteBytes( &DividerCycleCounter, sizeof(DividerCycleCounter) );

  /* filePutChar(JoyOldReg); */
  fileWriteBytes( &VideoClkCounterMode, sizeof(VideoClkCounterMode) );
  fileWriteBytes( &VideoClkCounterVBlank, sizeof(VideoClkCounterVBlank) );

  filePutChar(CurLY);
  /* /\*filePutChar(LastLY, FileHandler); *\/ */
  /* filePutChar(0); /\* Write a useless byte *\/ */
  filePutChar(LastLYdraw);
  filePutChar(CurRamBank);
  filePutChar(CurRomBank);
  
  fileWriteBytes( _MemoryInternalRAM, sizeof(_MemoryInternalRAM) );
  fileWriteBytes( _MemoryInternalHiRAM, sizeof(_MemoryInternalHiRAM) );
  fileWriteBytes( _MemoryBankedRAM, sizeof(_MemoryBankedRAM) );
  fileWriteBytes( _VideoRAM, sizeof(_VideoRAM) );
  fileWriteBytes( _SpriteOAM, sizeof(_SpriteOAM) );
  fileWriteBytes( _IoRegisters, sizeof(_IoRegisters) );
  fileWriteBytes( RAMette, sizeof(RAMette) );
  
  /* for (x = 0xC000; x < 0xE000; x++) filePutChar(MemoryInternalRAM[x]); */
  /* for (x = 0xFF80; x <= 0xFFFF; x++) filePutChar(MemoryInternalHiRAM[x]); */
  /* for (x = 0xA000; x < RomInfos.RamSize; x++) filePutChar(MemoryBankedRAM[x]);  /\* Check RAM size (if any) via RomInfos.RamSize *\/ */
  /* for (x = 0x8000; x < 0xA000; x++) filePutChar(VideoRAM[x]); */
  /* for (x = 0xFE00; x < 0xFEA0; x++) filePutChar (SpriteOAM[x]); */
  /* for (x = 0xFF00; x < 0xFF4C; x++) filePutChar(IoRegisters[x]); */
  /* // for (x = 0; x <= 0xFFFF; x++) filePutChar(MemoryMAP[x]); */
  /* filePutChar(CurRamBank); */
  /* filePutChar(Mbc1Model); */
  /* /\*filePutChar(Mbc1RamRomSelect); *\/ */
  /* filePutChar(0); /\* write a dummy byte *\/ */
  /* /\*filePutChar(BootRomEnabledFlag);*\/ */
  /* filePutChar(0); /\* write a dummy byte *\/ */
  
  fileClose();
  SetUserMsg("GAME SAVED");

}
