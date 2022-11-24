#include "Arduino_BHY2.h"
#include <ArduinoJson.h>
#include "Nicla_System.h"
#include "services/DetectionService.hpp"

DetectionService detectionService;

void setup()
{
  detectionService.setup();
}

void loop()
{
  BHY2.update();
  detectionService.detect();
}
