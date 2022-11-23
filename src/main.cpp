#include "Arduino_BHY2.h"
#include <ArduinoJson.h>
#include "Nicla_System.h"
#include "services/IntrusionDetection.hpp"

DynamicJsonDocument report(1024);
IntrusionDetection intrusionDetection;
SensorActivity sensorActivity(SENSOR_ID_AR);

void setup()
{
  intrusionDetection.setup(sensorActivity);
}

void loop()
{
  BHY2.update();
  intrusionDetection.detect(report, sensorActivity);
}
