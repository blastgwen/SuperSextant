/*
 * Mario.h
 *
 *  Created on: 24 oct. 2013
 *      Author: Gwena�l
 */

#ifndef MARIO_H_
#define MARIO_H_

class Mario{
	int haut, bas, y;

public:
	Mario();
	void setHaut(int x);
	void setBas(int x);
	void setY(int y);
	int getHaut();
	int getBas();
	int getY();
};

#endif /* MARIO_H_ */
