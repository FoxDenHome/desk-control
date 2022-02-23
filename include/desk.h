#pragma once

#include <Arduino.h>

void deskSetup();
void deskAdjustHeight(int16_t _target, const char *_mqttId);
void deskLoop();
int8_t deskIsMoving();
void deskStop();
