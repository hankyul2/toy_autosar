/** \file         Vrta_Cfg.h
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
  * $Id: Vrta_Cfg.h 2379 2014-08-10 12:55:57Z duv9yok $
  */

#ifdef __cplusplus
extern "C"{
void vrtaActionHandler(void);
void EnableVrtaFlash ( void (*f) (void));
void EnableVrtaAdc ( void (*f) (void));
void EnableVrtaPwm ( void (*f) (void));
void EnableVrtaPort ( void (*f) (void));
void EnableVrtaIcu ( void (*f) (void));
void EnableVrtaCan ( void (*f) (void));
void EnableVrtaCanTrcv ( void (*f) (void));
}
#endif
