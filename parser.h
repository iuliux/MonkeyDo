#ifndef __PARSER
#define __PARSER

#include <string.h>
#include "diskio.h"
#include "pff.h"

#define PARSE_ERR 'F';

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

#endif
