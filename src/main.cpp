#include <ArduinoBLE.h>
#include "Arduino.h"
#include "Arduino_BHY2.h"
#include <Wire.h>
#include "Nicla_System.h"

Sensor temperature(SENSOR_ID_TEMP);
SensorActivity activity(SENSOR_ID_AR);
Sensor motionDetection(SENSOR_ID_MOTION_DET);
Sensor stepDetection(SENSOR_ID_STC);
Sensor stationnaryDetection(SENSOR_ID_STATIONARY_DET);
SensorOrientation orientation(SENSOR_ID_ORI);
Sensor device_orientation(SENSOR_ID_DEVICE_ORI);
Sensor wakeGesteure(SENSOR_ID_WAKE_GESTURE);
Sensor glanceGesture(SENSOR_ID_GLANCE_GESTURE);
Sensor pickupGesture(SENSOR_ID_PICKUP_GESTURE);
Sensor barometer(SENSOR_ID_BARO);

float step = 0;
float motion = 0;
float value = 0;
float temperatureValue = 0;
SensorConfig config;

void setup()
{
  Serial.begin(115200);
  BHY2.begin();
  // temperature.begin();
  // activity.begin();
  // orientation.begin();
  // motionDetection.begin();
  // stationnaryDetection.begin();
  // stepDetection.begin();
  // wakeGesteure.begin();
  // glanceGesture.begin();
  // pickupGesture.begin();
  barometer.begin();
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
  Serial.print("orientation pitch : ");
  Serial.println(orientation.pitch());
}

void getMotionDetection()
{
  motion = motionDetection.value();
  Serial.print("Motion : ");
  Serial.println(motion);
  delay(500);
}

void getStationnaryDetection()
{
  motion = stationnaryDetection.value();
  Serial.print("Stationnary : ");
  Serial.println(motion);
  delay(500);
}

void getStepDetection()
{
  step = stepDetection.value();
  Serial.print("Step : ");
  Serial.println(step);
  delay(500);
}

void getWakeGesture()
{
  value = wakeGesteure.value();
  Serial.print("Wake Gesture : ");
  Serial.println(value);
  delay(500);
}

void getGlanceGesture()
{
  value = glanceGesture.value();
  Serial.print("Glance Gesture : ");
  Serial.println(value);
  delay(500);
}

void getPickupGesture()
{
  value = pickupGesture.value();
  Serial.print("Pickup Gesture : ");
  Serial.println(value);
  delay(500);
}

void getBarometer()
{
  value = barometer.value();
  Serial.print("Barometer : ");
  Serial.println(value);
  delay(500);
}

void loop()
{
  BHY2.update();
  getBarometer();
}