#include "Arduino.h"

#define LM35pin 0
#define LM35ref 1

unsigned long elozo_millis = 0;					/**< A legutóbbi iterálsánál rögzített időérték milliszekundumban. */
unsigned long kompresszor_esemeny_millis = 0;	/**< A legutóbbi kompresszoresemény (indítás vagy leállás) ideje milliszekundumban.  */
const unsigned long egyperc = 60000.0;			/**< 1 perc (60000 milliszekundum). */
const unsigned long idokoz = 1000.0; 			/**< 1 másodperc időköz, a főciklusban időzítésre használjuk. */

const int _RELE_PIN = 13;						/**< A kompresszort kapcsoló relét meghajtó pin a boardon. */

const float celhomerseklet = 4.0;				/**< Ezt a hőmérsékletet akarjuk tartani a hűtőben. */
const float homerseklet_epszilon = 1.5; 		/**< A hiszterézis deltája --> így 2,5-5,5°C a tartomány. */
float temperature = 0.0;						/**< Aktuális hőmérséklet. */

bool kompresszor = false;						/**< A kompresszor állapota. */


void setup(){
	Serial.begin(9600);
	pinMode(_RELE_PIN, OUTPUT);
	//digitalWrite(_RELE_PIN, HIGH);
}

// The loop function is called in an endless loop
void loop()
{
	unsigned long mostani_millis = millis();

	if (mostani_millis - elozo_millis >= idokoz) {
		elozo_millis = mostani_millis;
	    temperature = readTemp();
	    Serial.print(temperature);
	    Serial.println(" �C");
	    Serial.print("Futasido: ");
	    Serial.println(millis() / 1000.0);
	    Serial.println("-------------");

	    if (mostani_millis - kompresszor_esemeny_millis >= egyperc) {		// Ha a legutóbbi kompresszoresemény óta eltelt legalább 1 perc
			if (kompresszor == true) {										// Ha éppen megy a kompresszor
				if (temperature <= celhomerseklet - homerseklet_epszilon) { // és már elég hideg van
					kompresszor_ki();										// akkor kikapcsoljuk a hűtést
				}
			} else {														// Ha nem megy a kompresszor
				if (temperature >= celhomerseklet + homerseklet_epszilon) { // és túl meleg van
					kompresszor_be();										// akkor elindítjuk a hűtést
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

