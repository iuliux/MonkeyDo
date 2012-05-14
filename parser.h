#ifndef __PARSER
#define __PARSER

#define F_CPU 16000000

#include <stdlib.h>
#include <stdio.h>
#include "diskio.h"
#include "pff.h"

#include <util/delay.h>
#include "seven_segment.h"

#define PARSE_ERR 0xFF

#define DIR_MASK 0x0F
#define ACC_MASK 0xF0

#define ACC_NON 0x00
#define ACC_FWD 0x10
#define ACC_BKD 0x20
#define ACC_BRK 0x30

#define DIR_NON 0x00
#define DIR_LFT 0x01
#define DIR_RGT 0x02

unsigned char parse_movement(void);

unsigned int parse_duration(void);

#endif
