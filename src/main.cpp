/*
 * main.cpp
 *
 *  Created on: 06.05.2016
 *      Author: ian
 */

#include <Homie.h>


bool stripHandler(String property, String value); // Forward declaration
bool secondStripHandler(String property, String value); // Forward declaration
void updateLED(); // Forward declaration

HomieNode stripNode("RGBW-Strip", "RGBW", stripHandler, true); // last true: subscribe to all properties
HomieNode stripNode2("RGB-Strip", "RGB", secondStripHandler, true); // last true: subscribe to all properties

enum RGB_MAP {
	R, G, B, W
};

enum RGBW_PINMAP {
	REDPIN = 13, BLUEPIN = 12, GREENPIN = 14, WHITEPIN = 16
};

enum RGB_PINMAP {
	Z_REDPIN = 13, Z_BLUEPIN = 12, Z_GREENPIN = 14
};

const uint8 rgbw_pins[4] = {REDPIN, GREENPIN, BLUEPIN, WHITEPIN};
const uint8 rgb_pins[3] = {Z_REDPIN, Z_GREENPIN, Z_BLUEPIN};

uint16 rgbw_values[4] = { 0, 0, 0, 0 };
uint16 rgb_values[3] = { 0, 0, 0 };

bool stripHandler(String property, String value) {
	Serial.printf("Striphandler received  property %s (value=%s).\n", property.c_str(), value.c_str());
	int value_int = value.toInt();
	switch (property[0]) {
	case 'r':
		rgbw_values[R] = value_int;
		break;

	case 'g':
		rgbw_values[G] = value_int;
		break;

	case 'b':
		rgbw_values[B] = value_int;
		break;

	case 'w':
		rgbw_values[W] = value_int;
		break;
	default:
		return false;
	}
	updateLED();
	return true;
}

bool secondStripHandler(String property, String value) {
	Serial.printf("Striphandler received property %s (value=%s).\n", property.c_str(), value.c_str());
	int value_int = value.toInt();
	switch (property[0]) {
	case 'r':
		rgb_values[R] = value_int;
		break;

	case 'g':
		rgb_values[G] = value_int;
		break;

	case 'b':
		rgb_values[B] = value_int;
		break;

	default:
		return false;
	}
	updateLED();
	return true;
}

void updateLED() {
	Serial.print("Update All [rgbw rgb]: ");
	for (uint_fast8_t i=0;i<4;i++)
	{
		analogWrite(rgbw_pins[i], rgbw_values[i]);
		Serial.print(rgbw_values[i]);
		Serial.print('\t');
	}
	for (uint_fast8_t i=0;i<3;i++)
	{
		analogWrite(rgb_pins[i], rgb_values[i]);
		Serial.print(rgb_values[i]);
		Serial.print('\t');
	}
	Serial.println('.');
}


void setup() {
	Homie.disableResetTrigger();
	//	Homie.setLoopFunction(loopHandler);
	Homie.registerNode(stripNode);
	Homie.registerNode(stripNode2);
	Homie.setup();
}

void loop() {
	Homie.loop();
}
