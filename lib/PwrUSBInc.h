#ifndef _PWRUSBINC_H_
#define _PWRUSBINC_H_

#ifdef __cplusplus
#define EXTERN_C extern "c"
#else
#define EXTERN_C 
#endif

#ifdef PWRUSBDLL_EXPORTS
#define class_declspec EXTERN_C __declspec(dllexport)
#else
#define class_declspec EXTERN_C __declspec(dllimport)
#endif

class_declspec int InitPowerUSB(int *mode);
class_declspec int ClosePowerUSB();
class_declspec int CheckStatusPowereUSB();
class_declspec int SetPortPowerUSB(int port1, int port2);
class_declspec int SetDefaultStatePowerUSB(int state1, int state2);



#endif
