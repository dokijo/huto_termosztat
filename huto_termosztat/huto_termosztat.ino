#include "Arduino.h"
#include "huto_termosztat.h"

void setup(){
	elozo_millis = 0;
	kompresszor_esemeny_millis = 0;
	temperature = 0.0;
	kompresszor = false;

	Serial.begin(9600);
	pinMode(_RELE_PIN, OUTPUT);
}

// The loop function is called in an endless loop
void loop()
{
	unsigned long mostani_millis = millis();

	if (mostani_millis - elozo_millis >= idokoz) {
		elozo_millis = mostani_millis;
	    temperature = readTemp();
	    Serial.print(temperature);
	    Serial.println(" °C");
	    Serial.print("Futasido: ");
	    Serial.println(millis() / 1000.0);
	    Serial.println("-------------");

	    if (mostani_millis - kompresszor_esemeny_millis >= egyperc) {		// Ha a legutóbbi kompresszoresemény óta eltelt legalább 1 perc
			if (kompresszor == true) {										// Ha éppen megy a kompresszor
				if (temperature <= celhomerseklet - homerseklet_epszilon) { // és már elég hideg van
					kompresszor_ki();										// akkor kikapcsoljuk a hûtést
				}
			} else {														// Ha nem megy a kompresszor
				if (temperature >= celhomerseklet + homerseklet_epszilon) { // és túl meleg van
					kompresszor_be();										// akkor elindítjuk a hûtést
				}
			}
	    }

	}


}

float readTemp() {
  int analogVal = 0;
  for (int i = 0; i < 10; i++) {
    analogVal += (analogRead(LM35pin) - analogRead(LM35ref));
    delay(10);
  }
  return (5.0 * analogVal * 10) / 1024;
}

void kompresszor_be() {
  digitalWrite(13, HIGH);
  kompresszor = true;
  kompresszor_esemeny_millis = millis();
}

void kompresszor_ki() {
  digitalWrite(13, LOW);
  kompresszor = false;
  kompresszor_esemeny_millis = millis();
}

