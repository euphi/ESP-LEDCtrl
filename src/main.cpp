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

#include <Atm_encoder.hpp>

#include <InputController.h>

#include <SSD1306.h>

RGBWNode rgbn("LED", 15, 2, 0, 16);
RGBWNode rgbn2("LED2", 12,14,13, 255);
SensorNode sensor;

SSD1306Wire display(0x3c, SDA, SCL);
OLEDDisplayUi ui(&display);
InputController ictrl;


void setup() {
	Serial.begin(115200);
	Serial.println("Setup");
	Serial.flush();
	Homie_setFirmware("LEDCtrl_Küche", "0.5")
	Homie.disableResetTrigger();
	Homie.disableLedFeedback();
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
	ictrl.loop();
	Homie.loop();
	ui.update();
}
