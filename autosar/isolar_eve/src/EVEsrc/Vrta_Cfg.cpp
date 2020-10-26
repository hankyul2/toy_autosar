/** \file         Vrta_Cfg.cpp
  *
  * \brief        Target initialization and timing functions for ISOLAR-EVE ( target platform: VRTA-ux/VRTA-win )
  *
  * [$crn:2007:dox
  * \copyright Copyright 2014 ETAS GmbH
  * $]
  *
  * \note         PLATFORM DEPENDENT [yes/no]: yes
  *
  * \note         TO BE CHANGED BY USER [yes/no]: no
  *
  * $Id: Vrta_Cfg.cpp 2014-08-10 12:55:57Z duv9yok $
  */

#include "vrtaDevice.h"
#include "Vrta_Cfg.h"


static void( *flashhandler)(void) = NULL;
static void( *Porthandler)(void) = NULL;
static void( *Adchandler)(void) = NULL;
static void( *Pwmhandler)(void) = NULL;
static void( *Icuhandler)(void) = NULL;
static void( *Canhandler)(void) = NULL;
static void( *CanTrcvhandler)(void) = NULL;

void vrtaActionHandler(void){
	if(flashhandler){
		(*flashhandler)();
	}
	if(Porthandler){
		(*Porthandler)();
	}
	if(Adchandler){
		(*Adchandler)();
	}
	if(Pwmhandler){
		(*Pwmhandler)();
	}
	if(Canhandler){
		(*Canhandler)();
	}
	if(Icuhandler){
		(*Icuhandler)();
	}
	if(CanTrcvhandler){
		(*CanTrcvhandler)();
	}
}

void EnableVrtaFlash(void(*f)(void)){
	flashhandler = f;
}

void EnableVrtaPort(void(*f)(void)){
	Porthandler = f;
}

void EnableVrtaAdc(void(*f)(void)){
	Adchandler = f;
}

void EnableVrtaPwm(void(*f)(void)){
	Pwmhandler = f;
}

void EnableVrtaIcu(void(*f)(void)){
	Icuhandler = f;
}

void EnableVrtaCan(void(*f)(void)){
	Canhandler = f;
}

void EnableVrtaCanTrcv(void(*f)(void)){
	CanTrcvhandler = f;
}
