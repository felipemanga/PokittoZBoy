extern "C" {
uint16_t bw;
    
    uint8_t 	c_fileOpen(char *name, char mode){
	bw = 0;
	return fileOpen(name, mode); 
    }

    void 	c_fileClose(){
	if( bw ){
	    PFFS::pf_write(0,0,&bw);
	    bw = 0;
	}
	return fileClose(); 
    }

    char 	c_fileGetChar(){ 
	return fileGetChar(); 
    }

    void 	c_filePutChar(char ch){
	uint16_t tbw;
	PFFS::pf_write(&ch, 1, &tbw);
	bw += tbw;
//	return filePutChar( ch ); 
    }

    void 	c_fileWriteBytes(uint8_t *bytes, uint16_t count){
	uint16_t tbw;

	while( count-- )
	    PFFS::pf_write(bytes++, 1, &tbw);
	bw += tbw;

//	PFFS::pf_write(bytes, count, &bw);
//	return fileWriteBytes( bytes, count ); 
    }

    uint16_t 	c_fileReadBytes(uint8_t *bytes, uint16_t count){ 
	return fileReadBytes(bytes, count); 
    }

    void 	c_fileSeekAbsolute(long pos){ 
	return fileSeekAbsolute(pos); 
    }

    void 	c_fileSeekRelative(long pos){ 
	return fileSeekRelative(pos); 
    }

    void 	c_fileRewind(){ 
	return fileRewind(); 
    }

    void 	c_fileEnd(){ 
	return fileEnd(); 
    }

    long int 	c_fileGetPosition(){ 
	return fileGetPosition(); 
    }

    uint8_t 	c_filePeek(long n){ 
	return filePeek(n); 
    }

    void 	c_filePoke(long n, uint8_t c ){ 
	return filePoke( n, c ); 
    }

    int 	c_fileReadLine(char *bytes, int count){ 
	return fileReadLine( bytes, count ); 
    }

    char* 	c_getCurrentFileName (){ 
	return getCurrentFileName(); 
    }

    char* 	c_getNextFile (char *ext){ 
	return getNextFile(ext); 
    }

    char* 	c_getFirstFile(char *ext){ 
	return getFirstFile(ext); 
    }

    char* 	c_getFirstDirEntry(){ 
	return getFirstDirEntry(); 
    }

    char* 	c_getNextDirEntry(){ 
	return getNextDirEntry(); 
    }

    int 	c_isThisFileOpen(char *buff){ 
	return isThisFileOpen( buff ); 
    }

    int 	c_fileOK(){ 
	return fileOK(); 
    }

    int 	c_dirOpen(){ 
	return dirOpen(); 
    }

    int 	c_dirUp(){ 
	return dirUp(); 
    }

}
