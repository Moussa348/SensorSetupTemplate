#include "Arduino_BHY2.h"
#include <ArduinoJson.h>
#include "Nicla_System.h"
#include "services/IntrusionDetection.hpp"

IntrusionDetection intrusionDetection;

void setup()
{
  intrusionDetection.setup();
}

void loop()
{
  BHY2.update();
  intrusionDetection.detect();
}
