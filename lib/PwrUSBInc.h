#ifndef _PWRUSBINC_H_
#define _PWRUSBINC_H_

#ifdef __cplusplus
#define EXTERN_C extern "C"
#else
#define EXTERN_C 
#endif

#ifdef PWRUSBDLL_EXPORTS
#define CLASS_DECLSPEC EXTERN_C __declspec(dllexport)
#else
#define CLASS_DECLSPEC EXTERN_C __declspec(dllimport)
#endif

// Functions for Version 1 and 2 Firmware PowerUSB
///////////////////////////////////////////////////////////
// Main Power Strip functions
CLASS_DECLSPEC int InitPowerUSB(int *mode);
CLASS_DECLSPEC int ClosePowerUSB();
CLASS_DECLSPEC int SetCurrentPowerUSB(int count);
CLASS_DECLSPEC int CheckStatusPowereUSB();
CLASS_DECLSPEC int SetPortPowerUSB(int port1, int port2);
CLASS_DECLSPEC int SetDefaultStatePowerUSB(int state1, int state2);


// Functions for Version 2 and later Firmware PowerUSB
///////////////////////////////////////////////////////////
// these functions are available starting with Nov 2010 release of PowerUSB
CLASS_DECLSPEC int ReadPortState(int *state1, int *state2);
CLASS_DECLSPEC int ReadDefaultPortState(int *state1, int *state2);
CLASS_DECLSPEC int GetFirmwareVersion();


// Watchdog related functions. Available only for Watchdog firmware version of the PowerUSB
CLASS_DECLSPEC int StartWatchdogTimer(int HbTime, int numHbMisses, int resetTime);
CLASS_DECLSPEC int StopWatchdogTimer();
CLASS_DECLSPEC int GetWatchdogStatus();	// returns 0=IDLE(off), 1=Running, 2=Resetting
CLASS_DECLSPEC int SendHeartBeat();
CLASS_DECLSPEC int PowerCycle(int resetTime);





#endif
