#pragma once

#include "Arduino.h"

class Motor
{
public:

	void begin(uint8_t pin, float min, float max)
	{
		if (!digitalPinHasPWM(pin))
		{
			Serial.print("Pin: ");
			Serial.print(pin);
			Serial.println(" does not support PWM!");
		}

		m_pin = pin;
		m_min = min;
		m_max = max;

		setFrequency(8000.0);
		analogWriteResolution(12);

		pinMode(m_pin, OUTPUT);
		write(m_min);
	}

	void setFrequency(float freq)
	{
		m_frequency = freq;
		analogWriteFrequency(m_pin, m_frequency);
	}

	void write(float usec)
	{
		usec = constrain(usec, m_min, m_max);
		uint32_t duty = (uint32_t)(usec / (1e6 / m_frequency) * 4096.0);
		analogWrite(m_pin, duty);
	}

private:

	float m_frequency;

	uint8_t m_pin;
	float m_min;
	float m_max;
};