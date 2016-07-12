/*
 * huto_termosztat.h
 *
 *  Created on: 2016. júl. 6.
 *      Author: Nemes Dávid
 */

#ifndef HUTO_TERMOSZTAT_H_
#define HUTO_TERMOSZTAT_H_


#define LM35pin 0
#define LM35ref 1

unsigned long elozo_millis;					/**< A legutóbbi iterálsánál rögzített idõérték milliszekundumban. */
unsigned long kompresszor_esemeny_millis;	/**< A legutóbbi kompresszoresemény (indítás vagy leállás) ideje milliszekundumban.  */
const unsigned long egyperc = 60000.0;		/**< 1 perc (60000 milliszekundum). */
const unsigned long idokoz = 1000.0;		/**< 1 másodperc idõköz, a fõciklusban idõzítésre használjuk. */

const int _RELE_PIN = 13;					/**< A kompresszort kapcsoló relét meghajtó pin a boardon. */

const float celhomerseklet = 4.0;			/**< Ezt a hõmérsékletet akarjuk tartani a hûtõben. */
const float homerseklet_epszilon = 1.5; 	/**< A hiszterézis deltája --> így 2,5-5,5°C a tartomány. */
float temperature;							/**< Aktuális hõmérséklet. */
float homerseklet_tomb[10];					/**< A legutóbbi 10 mérés eredményét tároló tömb. */

bool kompresszor;							/**< A kompresszor állapota. */

void setup();
void loop();
float readTemp();
void kompresszor_be();
void kompresszor_ki();
void uj_ertek_tombbe(float, float*);
float tombatlag(float*);


#endif /* HUTO_TERMOSZTAT_H_ */
