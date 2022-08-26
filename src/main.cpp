#include <ArduinoBLE.h>
#include "Arduino.h"
#include "Arduino_BHY2.h"
#include <Wire.h>
#include "Nicla_System.h"

SensorActivity activity(SENSOR_ID_AR);
BLEService ledService("180A"); // BLE LED Service
BLEByteCharacteristic switchCharacteristic("2A57", BLERead | BLEWrite);
/*
  TODO
    -Send the Report through BLE to Portenta
    -Portenta will add the id + ip
*/

enum ReportType
{
  GAZ,
  ACTIVITY
};
enum CriticalityLevel
{
  LOW,
  MEDIUM,
  HIGH
};
struct Report
{
  String id;
  String description;
  CriticalityLevel CriticalityLevel;
  ReportType ReportType;
} report;

void setup()
{
  Serial.begin(115200);
  BHY2.begin();
  activity.begin();
  nicla::begin();
  nicla::leds.begin();
  BLE.setLocalName("Nicla Sense ME");
  BLE.setAdvertisedService(ledService);
  BLE.advertise();
  BLEDevice central = BLE.central();
}

void getActivity()
{
  String act = activity.getActivity();

  report.ReportType = ReportType::ACTIVITY;

  if (act.compareTo("Still activity started") != 0 && act.compareTo("Waiting to detect valid activity") != 0)
  {
    report.description = act;
    report.CriticalityLevel = CriticalityLevel::MEDIUM;
    Serial.println("Activity status: " + act);
    nicla::leds.setColor(red);
    delay(1000);
    nicla::leds.setColor(off);
    delay(1000);
  }
}

void loop()
{
  BHY2.update();
  getActivity();
}