#include <Arduino.h>

#include <ezTime.h>
#include <WiFi.h>

void setup()
{

	Serial.begin(115200);
	while (!Serial)
	{
		;
	} // wait for Serial port to connect. Needed for native USB port only
	WiFi.begin("BAANFARANG_O", "tAssy@#28");

	// Uncomment the line below to see what it does behind the scenes
	setDebug(INFO);

	waitForSync();

	Serial.println();
	Serial.println("UTC:             " + UTC.dateTime());

	Timezone myTZ;

	// Provide official timezone names
	// https://en.wikipedia.org/wiki/List_of_tz_database_time_zones
	myTZ.setLocation(F("Asia/Bangkok"));
	Serial.print(F("Thailand:     "));
	Serial.println(myTZ.dateTime());

	// Wait a little bit to not trigger DDoS protection on server
	// See https://github.com/ropg/ezTime#timezonedropnl
	delay(5000);

	// Or country codes for countries that do not span multiple timezones
	myTZ.setLocation(F("de"));
	Serial.print(F("Germany:         "));
	Serial.println(myTZ.dateTime());

	// Same as above
	delay(5000);

	// See if local time can be obtained (does not work in countries that span multiple timezones)
	Serial.print(F("Local (GeoIP):   "));
	if (myTZ.setLocation())
	{
		Serial.println(myTZ.dateTime());
	}
	else
	{
		Serial.println(errorString());
	}
}

void loop()
{
	events();
}