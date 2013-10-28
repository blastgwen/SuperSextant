/*
 * Gumpa.h
 *
 *  Created on: 24 oct. 2013
 *      Author: Gwena�l
 */

#ifndef GUMPA_H_
#define GUMPA_H_

#include <sextant/Activite/Threads.h>

class Gumpa : public Threads{

	int borneInf, borneSup, position, direction;
public:
	Gumpa();
	Gumpa(int inf, int sup, int position);

	void bouger();
	void changerDirection();
	void run();
	void detruire();
};

#endif /* GUMPA_H_ */
