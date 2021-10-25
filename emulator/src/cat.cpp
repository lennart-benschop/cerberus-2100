// *******************************************************************************************************************************
// *******************************************************************************************************************************
//
//		Name:		cat.cpp
//		Purpose:	CAT code handler.
//		Created:	25th October 2021
//		Author:		Paul Robson (paul@robsons.org.uk)
//
// *******************************************************************************************************************************
// *******************************************************************************************************************************

#include "sys_processor.h"
#include "cat.h"
#include "gfx.h"

static int pendingKey;

static void catbios_setup();

// *******************************************************************************************************************************
//
// 														The Cat Setup function
//
// *******************************************************************************************************************************

void CatSetup(void) {
	pendingKey = 0;
	catbios_setup();
}

// *******************************************************************************************************************************
//
//														 The Cat loop function
//
// *******************************************************************************************************************************

void CatSync(void) {
}

// *******************************************************************************************************************************
//
//										  Returns ASCII of key or 1000+GFX_Key for controls
//
// *******************************************************************************************************************************

int CatKeyHandler(int key,int isInRunMode) {
	if (isInRunMode != 0 && key != 0) {
		pendingKey = GFXToASCII(key,-1);
		if (pendingKey == 0 && key > 0) pendingKey = 1000+key;
	}
	return key;
}

#include "catbios.h"

