#include "Arduino_BHY2.h"
#include <ArduinoJson.h>
#include "Nicla_System.h"
#include "Peripheral.hpp"

class IntrusionDetection
{

private:
    Peripheral peripheral;
    DynamicJsonDocument report;
    SensorActivity sensorActivity;
    //const typedef void (&funcConnection)(RGBled, String);

public:
    IntrusionDetection() : report(1024), sensorActivity(SENSOR_ID_AR){};

    void setup()
    {
        Serial.begin(115200);
        BHY2.begin();
        sensorActivity.begin();
        nicla::begin();
        nicla::leds.begin();
        peripheral.setup();
    }

    void detect()
    {
        String act = sensorActivity.getActivity();

        report["reportTpye"] = "ACTIVITY";

        if (!act.equals("Still activity started") &&
        !act.equals("Tilting activity ended"))
        {
            report["description"] = act;
            report["criticalityLevel"] = "MEDIUM";

            Serial.println("Activity status: " + act);

            nicla::leds.setColor(red);
            delay(1000);
            nicla::leds.setColor(off);
            delay(1000);

            peripheral.connectionToCentralDevices(nicla::leds, report.as<String>());
        }
    }
};