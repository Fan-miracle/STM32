#ifndef _KEY_H
#define _KEY_H

#include "sys.h"
#include "delay.h"
#include "Time.h"


#define KEY_UP    PAin(4)
#define KEY_DWN	  PAin(3)
#define KEY_LFT   PAin(2)
#define KEY_RHT	  PAin(1)
#define KEY_MID   PAin(0)
#define KEY_SET	  PBin(0)
#define KEY_RST   PBin(1)


#define KEY_UP_PRES    1
#define KEY_DWN_PRES	 2
#define KEY_LFT_PRES   3
#define KEY_RHT_PRES	 4
#define KEY_MID_PRES   5

#define KEY_SET_PRES	 6
#define KEY_RST_PRES   7




//#define KEY_1	  PBin(4)
//#define KEY_2   PBin(5)


//#define KEY1_PRES  1
//#define KEY2_PRES	 2

u8 KEY_Scan(u8 mode);
void Key_Init(void);

#endif


