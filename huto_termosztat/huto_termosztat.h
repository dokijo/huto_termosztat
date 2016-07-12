/*
 * huto_termosztat.h
 *
 *  Created on: 2016. j�l. 6.
 *      Author: Nemes D�vid
 */

#ifndef HUTO_TERMOSZTAT_H_
#define HUTO_TERMOSZTAT_H_


#define LM35pin 0
#define LM35ref 1

unsigned long elozo_millis;					/**< A legut�bbi iter�ls�n�l r�gz�tett id��rt�k milliszekundumban. */
unsigned long kompresszor_esemeny_millis;	/**< A legut�bbi kompresszoresem�ny (ind�t�s vagy le�ll�s) ideje milliszekundumban.  */
const unsigned long egyperc = 60000.0;		/**< 1 perc (60000 milliszekundum). */
const unsigned long idokoz = 1000.0;		/**< 1 m�sodperc id�k�z, a f�ciklusban id�z�t�sre haszn�ljuk. */

const int _RELE_PIN = 13;					/**< A kompresszort kapcsol� rel�t meghajt� pin a boardon. */

const float celhomerseklet = 4.0;			/**< Ezt a h�m�rs�kletet akarjuk tartani a h�t�ben. */
const float homerseklet_epszilon = 1.5; 	/**< A hiszter�zis delt�ja --> �gy 2,5-5,5�C a tartom�ny. */
float temperature;							/**< Aktu�lis h�m�rs�klet. */
float homerseklet_tomb[10];					/**< A legut�bbi 10 m�r�s eredm�ny�t t�rol� t�mb. */

bool kompresszor;							/**< A kompresszor �llapota. */

void setup();
void loop();
float readTemp();
void kompresszor_be();
void kompresszor_ki();
void uj_ertek_tombbe(float, float*);
float tombatlag(float*);


#endif /* HUTO_TERMOSZTAT_H_ */
