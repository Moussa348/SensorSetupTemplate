#include <ArduinoBLE.h>
#include <functional>
#include "RGBled.h"

class Peripheral
{

private:
  BLEService bleService;
  BLEStringCharacteristic bleStrCharacteristic;

  void advertising()
  {
    BLE.advertise();
    Serial.print("Peripheral Device MAC : ");
    Serial.println(BLE.address());
    Serial.println("Waiting for connections...");
  }

  void blink(RGBled &leds)
  {
    leds.setColor(yellow);
    delay(1000);
    leds.setColor(off);
    delay(1000);
  }

public:
  Peripheral() : bleService("19B10010-E8F2-537E-4F6C-D104768A1214"), bleStrCharacteristic("19B10012-E8F2-537E-4F6C-D104768A1214", BLERead, 100){};

  void setup()
  {
    if (!BLE.begin())
    {
      Serial.println("Starting BLE Failed...");
      while (1)
        ;
    }

    BLE.setLocalName("Detection_Server");
    BLE.setAdvertisedService(bleService);

    bleService.addCharacteristic(bleStrCharacteristic);
    BLE.addService(bleService);

    advertising();
  }

  void connectionToCentralDevices(RGBled &leds, String value)
  {
    BLEDevice central = BLE.central();

    if (central.connected())
    {
      Serial.print("Connected to central MAC : ");
      Serial.println(central.address());

      blink(leds);

      bleStrCharacteristic.writeValue(value);
    }
  }

};