#include <WiFi.h>
#include "file.h"
#include "camera.h"
#include "lapse.h"

const char* ssid = "[redacted]";
const char* password = "[redacted]";

void startCameraServer();

void setup()
{
	Serial.begin(115200);
	Serial.setDebugOutput(true);
	Serial.println();
	initFileSystem();
	initCamera();

  Serial.print("Setting AP (Access Point)…");
	// Remove the password parameter, if you want the AP (Access Point) to be open
	WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  
	Serial.println("");
	startCameraServer();
	Serial.print("Camera Ready! Use 'http://");
	Serial.print(IP);
	Serial.println("' to connect");

  //switch FlashLED off
  pinMode(4, OUTPUT);
  digitalWrite(4, 0);
 
}

void loop()
{
	unsigned long t = millis();
	static unsigned long ot = 0;
	unsigned long dt = t - ot;
	ot = t;
	processLapse(dt);
}
