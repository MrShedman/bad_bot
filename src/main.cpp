
#include "constants.h"
#include "pid.h"
#include "beeper.h"
#include "motor.h"
#include "filter.h"

Motor motors[2];

float esc_1, esc_2;

uint32_t loop_start_time;

pt1Filter_t pot_filter;

enum armedState : uint8_t
{
	DISARMED,
	ARMED
};

armedState armed_state = DISARMED;

void calibrateESCs()
{
	int dt = 5;

	for (int i = 0; i < dt; ++i)
	{
		Serial.print(dt - i);
		Serial.println("...");
		delay(1000);
	}

	Serial.println("Beginning ESC Calibration...");

/*
	// Give ESCs a high pulse for approximately 5 seconds
	for (int i = 0; i < 1000; i++)
	{
		digitalWriteFast(MOT1_PIN, HIGH);
		digitalWriteFast(MOT2_PIN, HIGH);

		delayMicroseconds(max_esc_pulse);

		digitalWriteFast(MOT1_PIN, LOW);
		digitalWriteFast(MOT2_PIN, LOW);

		delay(3);
	}
	// Give ESCs a low pulse for approximately 5 seconds
	for (int i = 0; i < 1000; i++)
	{
		digitalWriteFast(MOT1_PIN, HIGH);
		digitalWriteFast(MOT2_PIN, HIGH);

		delayMicroseconds(min_esc_pulse);

		digitalWriteFast(MOT1_PIN, LOW);
		digitalWriteFast(MOT2_PIN, LOW);

		delay(3);
	}*/

    uint32_t pulse_time_ms = 5000; // 5s pulse time

    motors[0].write(max_esc_pulse);
    motors[1].write(max_esc_pulse);
    delay(pulse_time_ms);

    motors[0].write(min_esc_pulse);
    motors[1].write(min_esc_pulse);
    delay(pulse_time_ms);

	Serial.println("ESC Calibration finished");

	while (true);
}

void setup()
{
	pinMode(LED1_PIN, OUTPUT);
	pinMode(LED2_PIN, OUTPUT);

	motors[0].begin(MOT1_PIN, min_esc_pulse, max_esc_pulse);
	motors[1].begin(MOT2_PIN, min_esc_pulse, max_esc_pulse);

	//calibrateESCs();

	//pinMode(BEEP_PIN, OUTPUT);

	analogReadRes(12);
	analogReadAveraging(32);

	beeper(BEEPER_GYRO_CALIBRATED);
}

void loop()
{
    float pot = analogRead(POT_PIN);
	float throttle = map(pot, 0.0, 4095.0, (float)min_esc_pulse, (float)max_esc_pulse);

    armed_state = pot > pot_deadband ? ARMED : DISARMED;

	if (armed_state == ARMED)
	{
		esc_1 = throttle;
		esc_2 = throttle;
	}
	else
	{
		// disarmed
		esc_1 = min_esc_pulse;
		esc_2 = min_esc_pulse;
	}

	while (micros() - loop_start_time  < 1e6 / loop_freq);

	motors[0].write(esc_1);
	motors[1].write(esc_2);

	loop_start_time = micros();
}