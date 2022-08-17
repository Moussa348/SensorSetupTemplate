#include <ArduinoBLE.h>
#include "Arduino.h"
#include "Arduino_BHY2.h"
#include <Wire.h>
#include "Nicla_System.h"

Sensor temperature(SENSOR_ID_TEMP);
SensorActivity activity(SENSOR_ID_AR);
Sensor device_orientation(SENSOR_ID_DEVICE_ORI);
SensorOrientation orientation(SENSOR_ID_ORI);

float temperatureValue = 0;

void setup()
{
  Serial.begin(115200);
  BHY2.begin();
  temperature.begin();
  activity.begin();
  orientation.begin();
}

void getTemperature()
{
  temperatureValue = temperature.value();
  Serial.print("Temperature :");
  Serial.println(temperatureValue);
}

void getActivity()
{
  Serial.print("Activity status: ");
  Serial.println(activity.getActivity());
  delay(500);
}

void getOrientation()
{
  Serial.print("orientation pitch :");
  Serial.println(orientation.pitch());
  delay(500);
}

void loop()
{
  BHY2.update();
  getOrientation();
}