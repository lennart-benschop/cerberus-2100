// *******************************************************************************************************************************
// *******************************************************************************************************************************
//
//		Name:		hardware.cpp
//		Purpose:	Hardware Emulation
//		Created:	25th October 2021
//		Author:		Paul Robson (paul@robsons.org.uk)
//
// *******************************************************************************************************************************
// *******************************************************************************************************************************

#include "sys_processor.h"
#include "hardware.h"
#include "gfxkeys.h"
#include <stdlib.h>

// *******************************************************************************************************************************
//												Reset Hardware
// *******************************************************************************************************************************

void HWReset(void) {	
	HWXSetFrequency(0);
}

// *******************************************************************************************************************************
//												  Reset CPU
// *******************************************************************************************************************************

#include <stdio.h>

void HWSync(void) {
	HWXSyncImplementation(0);
}
