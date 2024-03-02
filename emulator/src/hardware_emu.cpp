// ****************************************************************************
// ****************************************************************************
//
//		Name:		hardware_emu.c
//		Purpose:	Hardware Emulation (Emulator Specific)
//		Created:	25th October 2021
//		Author:		Paul Robson (paul@robsons.org.uk)
//
// ****************************************************************************
// ****************************************************************************

#include "sys_processor.h"
#include "hardware.h"
#include "gfxkeys.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

#include <stdlib.h>
#include "gfx.h"

//
//		Really annoying.
//
#ifdef LINUX
#define MKSTORAGE()	mkdir("storage", S_IRWXU)
#else
#define MKSTORAGE()	mkdir("storage")
#endif

// ****************************************************************************
//								  Sync CPU
// ****************************************************************************

void HWXSyncImplementation(LONG32 iCount) {
}

// ****************************************************************************
//						Get System time in 1/1000s
// ****************************************************************************

LONG32 HWXGetSystemClock(void) {
	return (GFXTimer());
}

// ****************************************************************************
// 						Set frequency of beeper,0 = off
// ****************************************************************************

void HWXSetFrequency(int frequency) {
	GFXSetFrequency(frequency);
}

// ****************************************************************************
//								Load file in
// ****************************************************************************


WORD16 HWXLoadFile(char * fileName,BYTE8 *target,unsigned int *bytes_read) {
	char fullName[128];
        char *p=fullName;
	if (fileName[0] == 0) return 1;
	MKSTORAGE();
	sprintf(fullName,"%sstorage%c%s",SDL_GetBasePath(),FILESEP,fileName);
	// Sometimes the filename passed is delimited by a space instead of 0.
	while (*p) {
	  if (*p==' ') {
	    *p=0;
	    break;
	  }
	  p++;
	}
	  
	FILE *f = fopen(fullName,"rb");
	int c = 0;
	if (f != NULL) {
		while (!feof(f)) {
			int data = fgetc(f);
			if (data != EOF)
			  *target++ = data;
			c++;
		}
		fclose(f);
	}
	if (bytes_read != NULL)
	  *bytes_read = c;
	return (f != NULL) ? 0 : 1;
}

WORD16 HWXDeleteFile(char * fileName) {
	char fullName[128];
        char *p=fullName;
	if (fileName[0] == 0) return 1;
	MKSTORAGE();
	sprintf(fullName,"%sstorage%c%s",SDL_GetBasePath(),FILESEP,fileName);
	// Sometimes the filename passed is delimited by a space instead of 0.
	while (*p) {
	  if (*p==' ') {
	    *p=0;
	    break;
	  }
	  p++;
	}
	remove(fullName);
	return 0;
};

// ****************************************************************************
//							  Load Directory In
// ****************************************************************************
static DIR *dp;
void HWXLoadDirectoryStart(void) {
	char fullName[128];
	MKSTORAGE();
	sprintf(fullName,"%sstorage",SDL_GetBasePath());
	dp = opendir(fullName);  
}

void HWXLoadDirectoryEntry(BYTE8 *target, unsigned int *length) {
	struct dirent *ep;
	FILE *f;
	char fullName[128];
	if (dp != NULL) {
	retry:	  
	  if (ep = readdir(dp)) {
	    if (ep->d_name[0] != '.') {
	      char *p = ep->d_name;
	      while (*p != '\0') *target++ =*p++;
	      *target++ = '\0';
	      // Open the file for reading just to find out the length.
	      sprintf(fullName,"%sstorage%c%s",SDL_GetBasePath(),FILESEP,(char*)ep->d_name);
	      f = fopen(fullName,"rb");
	      if (f) {
		fseek(f,0,SEEK_END);
		*length=ftell(f);
		fclose(f);
	      }		      	      
	    } else {
	      goto retry;
	    }
	  } else {
	    closedir(dp);
	    dp = NULL;
	  }
	}
	*target = '\0';
}

// ****************************************************************************
//								Save file out
// ****************************************************************************

WORD16 HWXSaveFile(char *fileName,BYTE8 *data,WORD16 size) {
	char fullName[128];
        char *p=fullName;
	MKSTORAGE();
	sprintf(fullName,"%sstorage%c%s",SDL_GetBasePath(),FILESEP,fileName);
	// Sometimes the filename passed is delimited by a space instead of 0.
	while (*p) {
	  if (*p==' ') {
	    *p=0;
	    break;
	  }
	  p++;
	}
	  
	FILE *f = fopen(fullName,"wb");
	if (f != NULL) {
		for (int i = 0;i < size;i++) {
			fputc(*data++,f);
		}
		fclose(f);
	}
	return (f != NULL) ? 0 : 1;
}

