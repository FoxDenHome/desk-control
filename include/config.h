#pragma once

#include "config_private.h"

#define PIN_SDA 8
#define PIN_SCL 9

#define PIN_RELAY_UP 10
#define PIN_RELAY_DOWN 11

#define PIN_ARROW_UP 17
#define PIN_ARROW_DOWN 18
#define PIN_BUTTON 14

// In mm
#define DESK_HEIGHT_TOLERANCE 2
#define DESK_FINE_ADJUST_RANGE 20
#define DESK_ADJUST_TIMEOUT_PER_MM 75
#define DESK_RANGING_TIMEOUT 1000

#define DESK_CALCULATE_SPEED_TIME 1000
#define DESK_SPEED_MIN 0.01
#define DESK_SPEED_TRIES 3

#define DESK_HEIGHT_MIN 650
#define DESK_HEIGHT_MAX 1100

/* Table of SPAD locations. Each SPAD has a number which is not obvious.
*
* 128,136,144,152,160,168,176,184, 192,200,208,216,224,232,240,248
* 129,137,145,153,161,169,177,185, 193,201,209,217,225,233,241,249
* 130,138,146,154,162,170,178,186, 194,202,210,218,226,234,242,250
* 131,139,147,155,163,171,179,187, 195,203,211,219,227,235,243,251
* 132,140,148,156,164,172,180,188, 196,204,212,220,228,236,244,252
* 133,141,149,157,165,173,181,189, 197,205,213,221,229,237,245,253
* 134,142,150,158,166,174,182,190, 198,206,214,222,230,238,246,254
* 135,143,151,159,167,175,183,191, 199,207,215,223,231,239,247,255
* 127,119,111,103, 95, 87, 79, 71, 63, 55, 47, 39, 31, 23, 15, 7
* 126,118,110,102, 94, 86, 78, 70, 62, 54, 46, 38, 30, 22, 14, 6
* 125,117,109,101, 93, 85, 77, 69, 61, 53, 45, 37, 29, 21, 13, 5
* 124,116,108,100, 92, 84, 76, 68, 60, 52, 44, 36, 28, 20, 12, 4
* 123,115,107, 99, 91, 83, 75, 67, 59, 51, 43, 35, 27, 19, 11, 3
* 122,114,106, 98, 90, 82, 74, 66, 58, 50, 42, 34, 26, 18, 10, 2
* 121,113,105, 97, 89, 81, 73, 65, 57, 49, 41, 33, 25, 17, 9, 1
* 120,112,104, 96, 88, 80, 72, 64, 56, 48, 40, 32, 24, 16, 8, 0 /*Pin 1*/

#define RANGING_DISTANCE_MODE 1
#define RANGING_ROI_CENTER 199
#define RANGING_ROI_WIDTH 4
#define RANGING_ROI_HEIGHT 16
#define RANGING_TIMING_BUDGET 100
#define RANGING_TIMEOUT 1000
