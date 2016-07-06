#include "Arduino.h"

#define LM35pin 0
#define LM35ref 1

unsigned long elozo_millis = 0;					/**< A legut�bbi iter�l�sn�l r�gz�tett id��rt�k milliszekundumban. */
unsigned long kompresszor_esemeny_millis = 0;	/**< A legut�bbi kompresszoresem�ny (ind�t�s vagy le�ll�s) ideje milliszekundumban.  */
const unsigned long egyperc = 60000.0;			/**< 1 perc (60000 milliszekundum). */
const unsigned long idokoz = 1000.0; 			/**< 1 m�sodperc id�k�z, a f�ciklusban id�z�t�sre haszn�ljuk. */

const int _RELE_PIN = 13;						/**< A kompresszort kapcsol� rel�t meghajt� pin a boardon. */

const float celhomerseklet = 4.0;				/**< Ezt a h�m�rs�kletet akarjuk tartani a h�t�ben. */
const float homerseklet_epszilon = 1.5; 		/**< A hiszter�zis delt�ja --> �gy 2,5-5,5�C a tartom�ny. */
float temperature = 0.0;						/**< Aktu�lis h�m�rs�klet. */

bool kompresszor = false;						/**< A kompresszor �llapota. */


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

	    if (mostani_millis - kompresszor_esemeny_millis >= egyperc) {		// Ha a legut�bbi kompresszoresem�ny �ta eltelt legal�bb 1 perc
			if (kompresszor == true) {										// Ha �ppen megy a kompresszor
				if (temperature <= celhomerseklet - homerseklet_epszilon) { // �s m�r el�g hideg van
					kompresszor_ki();										// akkor kikapcsoljuk a h�t�st
				}
			} else {														// Ha nem megy a kompresszor
				if (temperature >= celhomerseklet + homerseklet_epszilon) { // �s t�l meleg van
					kompresszor_be();										// akkor elind�tjuk a h�t�st
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

