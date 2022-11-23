#include "Arduino_BHY2.h"
#include <ArduinoJson.h>
#include "Nicla_System.h"

class IntrusionDetection
{

public:
    void setup(SensorActivity &sensorActivity)
    {
        Serial.begin(115200);
        BHY2.begin();
        sensorActivity.begin();
        nicla::begin();
        nicla::leds.begin();
    }

    void detect(DynamicJsonDocument &report, SensorActivity &sensorActivity)
    {
        String act = sensorActivity.getActivity();

        report["reportTpye"] = "ACTIVITY";

        if (act.compareTo("Still activity ended") == 0 )
        {
            report["description"] = act;
            report["criticalityLevel"] = "MEDIUM";

            Serial.println("Activity status: " + act);

            nicla::leds.setColor(red);
            delay(1000);
            nicla::leds.setColor(off);
            delay(1000);
        }
    }
};