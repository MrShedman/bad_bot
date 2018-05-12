#pragma once

#include "Arduino.h"

const uint8_t LED1_PIN = 3;
const uint8_t LED2_PIN = 4;

const uint8_t MOT1_PIN = 21;
const uint8_t MOT2_PIN = 20;

const uint8_t POT_PIN = 5;

const uint8_t BEEP_PIN = 15;

const uint32_t min_esc_pulse = 125;
const uint32_t max_esc_pulse = 250;

const uint32_t loop_freq = 500;

const uint32_t pot_deadband = 100;