/*
 * main.cpp
 *
 *  Created on: 06.05.2016
 *      Author: ian
 */

#include <Homie.h>
#include <RGBWNode.h>
#include <SensorNode.h>
#include <LoggerNode.h>


/* includes for Libraries, so platformio can find them */
//#include <Wire.h>
//#include <Sensors.h>

#include <InputController.h>

#include <SSD1306.h>

#include "buildnumber.h"
#define FW_NAME "LED-2x_Thermo_Ctrl"
#define FW_VERSION "1.1." BUILD_NUMBER

/* Magic sequence for Autodetectable Binary Upload */
const char *__FLAGGED_FW_NAME = "\xbf\x84\xe4\x13\x54" FW_NAME "\x93\x44\x6b\xa7\x75";
const char *__FLAGGED_FW_VERSION = "\x6a\x3f\x3e\x0e\xe1" FW_VERSION "\xb0\x30\x48\xd4\x1a";
/* End of magic sequence for Autodetectable Binary Upload */

RGBWNode rgbn("LED", 2, 15, 0, 16);
RGBWNode rgbn2("LED2", 12,13,14, 255);
SensorNode sensor;

SSD1306Wire display(0x3c, SDA, SCL);
OLEDDisplayUi ui(&display);


void setup() {
	Homie_setFirmware(FW_NAME, FW_VERSION);
	Homie.disableResetTrigger();
	Homie.disableLedFeedback();
	Serial.begin(74880);
	Serial.println("Setup");
	Serial.flush();
	//Homie.setLoggingPrinter(&display);
	Homie.setLoggingPrinter(&Serial);
	display.setLogBuffer(4,200);
	LN.setLoglevel(LoggerNode::DEBUG);

	ui.setTargetFPS(30);

//	// Customize the active and inactive symbol
//	ui.setActiveSymbol(activeSymbol);
//	ui.setInactiveSymbol(inactiveSymbol);

	// You can change this to
	// TOP, LEFT, BOTTOM, RIGHT
	ui.setIndicatorPosition(BOTTOM);

	// Defines where the first frame is located in the bar.
	ui.setIndicatorDirection(LEFT_RIGHT);

	// You can change the transition that is used
	// SLIDE_LEFT, SLIDE_RIGHT, SLIDE_UP, SLIDE_DOWN
	ui.setFrameAnimation(SLIDE_LEFT);
	ui.disableAutoTransition();
	ui.disableAllIndicators();
	ui.init();

	display.flipScreenVertically();

	Homie.setup();
}

void loop() {
	Homie.loop();
	ui.update();
}
