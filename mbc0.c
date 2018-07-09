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

const WriteHandlerT writeHandlers[9] = {
  NULLWrite,
  RAMWrite,
  RAMWrite,
  RAMWrite,
  RAMWrite,
  IOWrite,
  RAMWrite,
  RAMWrite,
  NULLWrite
};

