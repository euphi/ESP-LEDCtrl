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

//#include <InputController.h>

#include <SSD1306.h>

#include "buildnumber.h"
#define FW_NAME "LED-2x_Thermo_Ctrl"
#define FW_VERSION "1." COMMIT_COUNTER "." BUILD_NUMBER

/* Magic sequence for Autodetectable Binary Upload */
const char *__FLAGGED_FW_NAME = "\xbf\x84\xe4\x13\x54" FW_NAME "\x93\x44\x6b\xa7\x75";
const char *__FLAGGED_FW_VERSION = "\x6a\x3f\x3e\x0e\xe1" FW_VERSION "\xb0\x30\x48\xd4\x1a";
/* End of magic sequence for Autodetectable Binary Upload */

RGBWNode rgb("LED", 14, 15, 16, RGBWNode::NOPIN);
RGBWNode w1("LED_W1", RGBWNode::NOPIN,RGBWNode::NOPIN,RGBWNode::NOPIN, 0);
RGBWNode w2("LED_W2", RGBWNode::NOPIN,RGBWNode::NOPIN,RGBWNode::NOPIN, 2);

SensorNode sensor;

void setup() {
	Homie_setFirmware(FW_NAME, FW_VERSION);
	Homie.disableResetTrigger();
	Homie.disableLedFeedback();
	Serial.begin(74880);
	Serial.flush();
	Serial.println("\nSetup");
	Serial.flush();
	Wire.begin(SDA, SCL);
	//Homie.setLoggingPrinter(&display);
	Homie.setLoggingPrinter(&Serial);
	LN.setLoglevel(LoggerNode::DEBUG);
	Homie.setup();
}

void loop() {
	Homie.loop();
}
