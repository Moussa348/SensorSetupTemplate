#include "Arduino_BHY2.h"
#include <ArduinoJson.h>
#include "Nicla_System.h"
#include "PeripheralService.hpp"

class DetectionService
{

private:
    PeripheralService peripheralService;
    DynamicJsonDocument report;
    SensorActivity sensorActivity;

    void blink(RGBled &leds, RGBColors color)
    {
        leds.setColor(color);
        delay(1000);
        leds.setColor(off);
        delay(1000);
    }

public:
    DetectionService() : report(1024), sensorActivity(SENSOR_ID_AR){};

    void setup()
    {
        Serial.begin(115200);
        BHY2.begin();
        sensorActivity.begin();
        nicla::begin();
        nicla::leds.begin();
        peripheralService.setup();
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

            blink(nicla::leds, red);

            peripheralService.connectionToCentralDevices(nicla::leds, report.as<String>());
        }
    }
};