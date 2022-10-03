
/*
  I, Wael Harba, student number 000787960, certify that what I am submitting is my own work;
  that I have not copied it from any other source. I also certify that I have not allowed my work to be copied by others.
*/

// ******************************************************************
// Dallas Semiconductor DS18B20 Temperature Sensor Demo Program
// COMP-10184
// Mohawk College

// library for Arduino framework
#include <Arduino.h>
// 1-Wire sensor communication libary
#include <OneWire.h>
// DS18B20 sensor library
#include <DallasTemperature.h>

// Pin that the  DS18B20 is connected to
const int oneWireBus = D3;

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(oneWireBus);

// Pass our oneWire reference to Dallas Temperature sensor
DallasTemperature DS18B20(&oneWire);

// variable that will hold the 8 byte address of the sensor
DeviceAddress sensorAddress;

void setup()
{
  // configure the USB serial monitor
  Serial.begin(115200);

  // Start the DS18B20 sensor
  DS18B20.begin();

  Serial.println("\nTemperature Application");

  // Checking if there's a sensor connected
  if (DS18B20.getAddress(sensorAddress, 0) == 0)
  {
    // Print a message to user that there's no sensor connected
    Serial.println("No DS18B20 temperature sensors are installed!");
  }
  // In the case of a sensor connected
  else
  {
    Serial.print("Found DS18 with address: ");
    // Loop through the 8 byte sensor address
    for (int i = 0; i < 8; i++)
    {
      // print the byte on hand of the sensor address
      Serial.print(sensorAddress[i], HEX);
    }
    // Printing a new line
    Serial.println("");
  }
}

/// @brief function that will return a judgement of the temperature
/// @param temp temperature as a float
/// @return judgement of the temperature
String getTemperatureJudgement(float temp)
{
  // Checking if temperature is less than 10, we return cold
  if (temp < 10)
  {
    return "Cold!";
  }
  // Checking if temperature is 10-15, we return cool
  else if (temp >= 10 && temp < 15)
  {
    return "Cool";
  }
  // Checking if temperature is 15-25, we return perfect
  else if (temp >= 15 && temp < 25)
  {
    return "Perfect";
  }
  // Checking if temperature is 25-30, we return warm
  else if (temp >= 25 && temp < 30)
  {
    return "Warm";
  }
  // Checking if temperature is 30-35, we return hot
  else if (temp >= 30 && temp < 35)
  {
    return "Hot";
  }
  // Checking if temperature is higher than 35, we return too hot
  else if (temp >= 35)
  {
    return "Too Hot!";
  }

  // otherwise return unknown
  return "Unkown";
}

void loop()
{
  // Check if there's a sensor connected
  if (DS18B20.getAddress(sensorAddress, 0))
  {
    float fTemp; // variable that will hold the temperature

    // ask DS18B20 for the current temperature
    DS18B20.requestTemperatures();

    // fetch the temperature.  We only have 1 sensor, so the index is 0.
    fTemp = DS18B20.getTempCByIndex(0);

    // print the temp to the USB serial monitor with the temperature judgement
    Serial.println("Current temperature is: " + String(fTemp) + "° C or " + getTemperatureJudgement(fTemp));

    // wait 5s (5000ms) before doing this again
    delay(5000);
  }
}