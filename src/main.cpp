/*
 * main.cpp
 *
 *  Created on: 06.05.2016
 *      Author: ian
 */

#include <Homie.h>
#include <RGBWNode.h>
#include <SensorNode.h>

/* includes for Libraries, so platformio can find them */
#include <Wire.h>
#include <Sensors.h>

RGBWNode rgbn;
SensorNode sensor;

void setup() {
	Homie.disableResetTrigger();
	Homie.setup();
}

void loop() {
	Homie.loop();
}
