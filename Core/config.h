#ifndef _CONFIG_H_
#define _CONFIG_H_

#include "license.txt" 

#include "../Interface.h"
#include <math.h>      // atan => PI
#include <thread>
#include <mutex>
#include <condition_variable>

//#define _DEBUG  // defined in VS configuration

// macro to call callback function with just status extHWstatusT
#define EXTIO_STATUS_CHANGE( CB, STATUS )   \
	do { \
	  SendMessage(h_dialog, WM_USER + 1, STATUS, 0); \
	  if (CB) { \
		  DbgPrintf("<==CALLBACK: %s\n", #STATUS); \
		  CB( -1, STATUS, 0, NULL );\
	  }\
	}while(0)

#ifdef VERBOSE_DEBUG
	#define EnterFunction() \
	DbgPrintf("==>%s\n", __FUNCDNAME__)

	#define EnterFunction1(v1) \
	DbgPrintf("==>%s(%d)\n", __FUNCDNAME__, (v1))
#else
	#define EnterFunction()
	#define EnterFunction1(v1)
#endif

#ifdef _DEBUG
#include <cstdio>
#define DbgPrintf(fmt, ...) printf("[SDDC] " fmt, ##__VA_ARGS__)
#else
#define DbgPrintf(fmt, ...) do {} while(0)
#endif

#define SWVERSION           "1.3.0 RC1"	  
#define SETTINGS_IDENTIFIER	"sddc_1.06"
#define SWNAME				"ExtIO_sddc.dll"

#define	QUEUE_SIZE 32
#define WIDEFFTN  // test FFTN 8192 

#define FFTN_R_ADC (8192)       // FFTN used for ADC real stream DDC  tested at  2048, 8192, 32768, 131072

// GAINFACTORS to be adjusted with lab reference source measured with HDSDR Smeter rms mode  
#define BBRF103_GAINFACTOR 	(7.8e-8f)       // BBRF103
#define HF103_GAINFACTOR   	(1.14e-8f)      // HF103
#define RX888_GAINFACTOR   	(0.695e-8f)     // RX888
#define RX888mk2_GAINFACTOR     (1.08e-8f)      // RX888mk2

enum rf_mode { NOMODE = 0, HFMODE = 0x1, VHFMODE = 0x2 }; 

#define HF_HIGH (64000000)    // 64M
#define MW_HIGH ( 2000000)

#define EXT_BLOCKLEN		512	* 64	/* 32768 only multiples of 512 */

#define RFDDCNAME ("NVIA L768M256")
#define RFDDCVER ("v 1.0")

// URL definitions
#define URL1B               "16bit SDR Receiver"
#define URL1               "<a>http://www.hdsdr.de/</a>"
#define URL_HDSR            "http://www.hdsdr.de/"
#define URL_HDSDRA          "<a>http://www.hdsdr.de/</a>"

#define MAXNDEV (4)  // max number of SDR device connected to PC
#define MAXDEVSTRLEN (64)  //max char len of SDR device description

extern bool saveADCsamplesflag;
extern uint32_t  adcnominalfreq;

// transferSize must be a multiple of 16 (maxBurst) * 1024 (SS packet size) = 16384
const uint32_t transferSize = 131072;
const uint32_t transferSamples = transferSize / sizeof(int16_t);
const uint32_t concurrentTransfers = 16;  // used to be 96, but I think it is too high

const uint32_t DEFAULT_ADC_FREQ = 60000000;	// ADC sampling frequency

const uint32_t DEFAULT_TRANSFERS_PER_SEC = DEFAULT_ADC_FREQ / transferSamples;

extern uint32_t MIN_ADC_FREQ;		// ADC sampling frequency minimum
extern uint32_t MAX_ADC_FREQ;		// ADC sampling frequency minimum
extern uint32_t N2_BANDSWITCH;		// threshold 5 or 6 SR bandwidths
#endif // _CONFIG_H_
