/*
 * PlateauSextantBros.cpp
 *
 *  Created on: 24 oct. 2013
 *      Author: Matthieu Gutierrez
 */

#include "PlateauSextantBros.h"

// Constructeur du plateau
PlateauSextantBros::PlateauSextantBros(EcranV *e, ClavierV *c) {
	this->ecran = e;
	this->clavier = c;
	this->score = 0;
	this->vie = 3;
	this->niveauTermine = false;
	this->timer = 500;
	this->numLvl = 0;
	this->mario.setBas(23);
	this->mario.setHaut(22);
	this->mario.setY(5);
}

void PlateauSextantBros::bougerMario(char fleche) {

	switch (fleche) {
	case 'q':
		bougerDroite(false);
		break;
	case 'd':
		bougerGauche(false);
		break;
	case 'z':
		sauter();
		break;
	}
}

void PlateauSextantBros::bougerDroite(bool saut) {
	if (this->tabLevel[this->mario.getHaut()][this->mario.getY() + 1].getEtat() == FOND
	&& this->tabLevel[this->mario.getBas()][this->mario.getY() + 1].getEtat() == FOND) {

		// Effacer
		this->tabLevel[this->mario.getHaut()][this->mario.getY()].setCaseFond();
		this->tabLevel[this->mario.getBas()][this->mario.getY()].setCaseFond();

		// Afficher
		this->mario.setY(this->mario.getY() + 1);
		this->tabLevel[this->mario.getHaut()][this->mario.getY()].setCaseMario();
		this->tabLevel[this->mario.getBas()][this->mario.getY()].setCaseMario();

		this->rafraichir();

	}
	if (!saut) {
		this->tomber();
	}
}

void PlateauSextantBros::bougerGauche(bool saut) {
	if (this->tabLevel[this->mario.getHaut()][this->mario.getY() - 1].getEtat() == FOND
	&& this->tabLevel[this->mario.getBas()][this->mario.getY() - 1].getEtat() == FOND) {

		// Effacer
		this->tabLevel[this->mario.getHaut()][this->mario.getY()].setCaseFond();
		this->tabLevel[this->mario.getBas()][this->mario.getY()].setCaseFond();

		// Afficher
		this->mario.setY(this->mario.getY() - 1);
		this->tabLevel[this->mario.getHaut()][this->mario.getY()].setCaseMario();
		this->tabLevel[this->mario.getBas()][this->mario.getY()].setCaseMario();

		this->rafraichir();

	}
	if (!saut) {
		this->tomber();
	}
}

void PlateauSextantBros::sauter() {
	int i = 0;
//Monter
	if (this->tabLevel[this->mario.getBas() + 1][this->mario.getY()].getEtat() != FOND) {
		while (i < 4) {
			if (this->tabLevel[this->mario.getHaut() - 1][this->mario.getY()].getEtat() == FOND) {
				this->tabLevel[this->mario.getHaut()][this->mario.getY()].setCaseFond();
				this->tabLevel[this->mario.getBas()][this->mario.getY()].setCaseFond();
				this->mario.setHaut(this->mario.getHaut() - 1);
				this->mario.setBas(this->mario.getBas() - 1);
				this->tabLevel[this->mario.getHaut()][this->mario.getY()].setCaseMario();
				this->tabLevel[this->mario.getBas()][this->mario.getY()].setCaseMario();
				this->rafraichir();

				char c = clavier->getChar();

				switch (c) {
				case 'q':
					this->bougerGauche(true);
					break;
				case 'd':
					this->bougerDroite(true);
					break;

				}
			} else {
				i = 5;
			}
			i++;
		}
	}

	//Descendre
	this->tomber();

}

void PlateauSextantBros::tomber() {
	switch (this->tabLevel[this->mario.getBas() + 1][this->mario.getY()].getEtat()) {
	case FOND:
		this->tabLevel[this->mario.getHaut()][this->mario.getY()].setCaseFond();
		this->tabLevel[this->mario.getBas()][this->mario.getY()].setCaseFond();
		this->mario.setHaut(this->mario.getHaut() + 1);
		this->mario.setBas(this->mario.getBas() + 1);
		this->tabLevel[this->mario.getHaut()][this->mario.getY()].setCaseMario();
		this->tabLevel[this->mario.getBas()][this->mario.getY()].setCaseMario();
		this->rafraichir();

		break;
	case TROU:
		// Faire perdre une vie !
		break;
	default:
		break;

	}
}

void PlateauSextantBros::introduction() {
	for (int x = 0; x < HAUTEUR; x++) {
		for (int y = 0; y < LARGEUR; y++) {
			tabIntro[x][y].init(x, y);
			this->tabIntro[x][y].setEcran(this->ecran);
		}
	}

	// S
	this->tabIntro[2][15].setCaseBord();
	this->tabIntro[3][15].setCaseBord();
	this->tabIntro[4][15].setCaseBord();
	this->tabIntro[6][15].setCaseBord();
	this->tabIntro[2][16].setCaseBord();
	this->tabIntro[4][16].setCaseBord();
	this->tabIntro[6][16].setCaseBord();
	this->tabIntro[2][17].setCaseBord();
	this->tabIntro[4][17].setCaseBord();
	this->tabIntro[5][17].setCaseBord();
	this->tabIntro[6][17].setCaseBord();

	// U
	this->tabIntro[2][19].setCaseBord();
	this->tabIntro[3][19].setCaseBord();
	this->tabIntro[4][19].setCaseBord();
	this->tabIntro[5][19].setCaseBord();
	this->tabIntro[6][19].setCaseBord();
	this->tabIntro[6][20].setCaseBord();
	this->tabIntro[2][21].setCaseBord();
	this->tabIntro[3][21].setCaseBord();
	this->tabIntro[4][21].setCaseBord();
	this->tabIntro[5][21].setCaseBord();
	this->tabIntro[6][21].setCaseBord();

	// P
	this->tabIntro[2][23].setCaseBord();
	this->tabIntro[3][23].setCaseBord();
	this->tabIntro[4][23].setCaseBord();
	this->tabIntro[5][23].setCaseBord();
	this->tabIntro[6][23].setCaseBord();
	this->tabIntro[2][24].setCaseBord();
	this->tabIntro[4][24].setCaseBord();
	this->tabIntro[2][25].setCaseBord();
	this->tabIntro[3][25].setCaseBord();
	this->tabIntro[4][25].setCaseBord();

	// E
	this->tabIntro[2][27].setCaseBord();
	this->tabIntro[3][27].setCaseBord();
	this->tabIntro[4][27].setCaseBord();
	this->tabIntro[5][27].setCaseBord();
	this->tabIntro[6][27].setCaseBord();
	this->tabIntro[2][28].setCaseBord();
	this->tabIntro[4][28].setCaseBord();
	this->tabIntro[6][28].setCaseBord();
	this->tabIntro[2][29].setCaseBord();
	this->tabIntro[6][29].setCaseBord();

	//R
	this->tabIntro[2][31].setCaseBord();
	this->tabIntro[3][31].setCaseBord();
	this->tabIntro[4][31].setCaseBord();
	this->tabIntro[5][31].setCaseBord();
	this->tabIntro[6][31].setCaseBord();
	this->tabIntro[2][32].setCaseBord();
	this->tabIntro[4][32].setCaseBord();
	this->tabIntro[5][32].setCaseBord();
	this->tabIntro[2][33].setCaseBord();
	this->tabIntro[3][33].setCaseBord();
	this->tabIntro[4][33].setCaseBord();
	this->tabIntro[6][33].setCaseBord();

	// S
	this->tabIntro[2][40].setCaseBord();
	this->tabIntro[3][40].setCaseBord();
	this->tabIntro[4][40].setCaseBord();
	this->tabIntro[6][40].setCaseBord();
	this->tabIntro[2][41].setCaseBord();
	this->tabIntro[4][41].setCaseBord();
	this->tabIntro[6][41].setCaseBord();
	this->tabIntro[2][42].setCaseBord();
	this->tabIntro[4][42].setCaseBord();
	this->tabIntro[5][42].setCaseBord();
	this->tabIntro[6][42].setCaseBord();

	// E
	this->tabIntro[2][44].setCaseBord();
	this->tabIntro[3][44].setCaseBord();
	this->tabIntro[4][44].setCaseBord();
	this->tabIntro[5][44].setCaseBord();
	this->tabIntro[6][44].setCaseBord();
	this->tabIntro[2][45].setCaseBord();
	this->tabIntro[4][45].setCaseBord();
	this->tabIntro[6][45].setCaseBord();
	this->tabIntro[2][46].setCaseBord();
	this->tabIntro[6][46].setCaseBord();

	// X
	this->tabIntro[2][48].setCaseBord();
	this->tabIntro[6][48].setCaseBord();
	this->tabIntro[3][49].setCaseBord();
	this->tabIntro[4][49].setCaseBord();
	this->tabIntro[5][49].setCaseBord();
	this->tabIntro[2][50].setCaseBord();
	this->tabIntro[6][50].setCaseBord();

	// T
	this->tabIntro[2][52].setCaseBord();
	this->tabIntro[2][53].setCaseBord();
	this->tabIntro[3][53].setCaseBord();
	this->tabIntro[4][53].setCaseBord();
	this->tabIntro[5][53].setCaseBord();
	this->tabIntro[6][53].setCaseBord();
	this->tabIntro[2][54].setCaseBord();

	// A
	this->tabIntro[2][56].setCaseBord();
	this->tabIntro[3][56].setCaseBord();
	this->tabIntro[4][56].setCaseBord();
	this->tabIntro[5][56].setCaseBord();
	this->tabIntro[6][56].setCaseBord();
	this->tabIntro[2][57].setCaseBord();
	this->tabIntro[4][57].setCaseBord();
	this->tabIntro[2][58].setCaseBord();
	this->tabIntro[3][58].setCaseBord();
	this->tabIntro[4][58].setCaseBord();
	this->tabIntro[5][58].setCaseBord();
	this->tabIntro[6][58].setCaseBord();

	// N
	this->tabIntro[2][60].setCaseBord();
	this->tabIntro[3][60].setCaseBord();
	this->tabIntro[4][60].setCaseBord();
	this->tabIntro[5][60].setCaseBord();
	this->tabIntro[6][60].setCaseBord();
	this->tabIntro[3][61].setCaseBord();
	this->tabIntro[4][62].setCaseBord();
	this->tabIntro[5][62].setCaseBord();
	this->tabIntro[2][63].setCaseBord();
	this->tabIntro[3][63].setCaseBord();
	this->tabIntro[4][63].setCaseBord();
	this->tabIntro[5][63].setCaseBord();
	this->tabIntro[6][63].setCaseBord();

	// T
	this->tabIntro[2][65].setCaseBord();
	this->tabIntro[2][66].setCaseBord();
	this->tabIntro[3][66].setCaseBord();
	this->tabIntro[4][66].setCaseBord();
	this->tabIntro[5][66].setCaseBord();
	this->tabIntro[6][66].setCaseBord();
	this->tabIntro[2][67].setCaseBord();

	// <-
	this->tabIntro[12][5].setCaseBord();
	this->tabIntro[11][6].setCaseBord();
	this->tabIntro[12][6].setCaseBord();
	this->tabIntro[13][6].setCaseBord();
	this->tabIntro[10][7].setCaseBord();
	this->tabIntro[12][7].setCaseBord();
	this->tabIntro[14][7].setCaseBord();
	this->tabIntro[12][8].setCaseBord();
	this->tabIntro[12][9].setCaseBord();
	this->tabIntro[12][10].setCaseBord();
	this->tabIntro[12][11].setCaseBord();

	// Q
	this->tabIntro[11][14].setCaseBord();
	this->tabIntro[12][14].setCaseBord();
	this->tabIntro[13][14].setCaseBord();
	this->tabIntro[10][15].setCaseBord();
	this->tabIntro[14][15].setCaseBord();
	this->tabIntro[10][16].setCaseBord();
	this->tabIntro[14][16].setCaseBord();
	this->tabIntro[11][17].setCaseBord();
	this->tabIntro[12][17].setCaseBord();
	this->tabIntro[13][17].setCaseBord();
	this->tabIntro[14][17].setCaseBord();
	this->tabIntro[14][18].setCaseBord();

	// ->
	this->tabIntro[19][5].setCaseBord();
	this->tabIntro[19][6].setCaseBord();
	this->tabIntro[19][7].setCaseBord();
	this->tabIntro[19][8].setCaseBord();
	this->tabIntro[19][9].setCaseBord();
	this->tabIntro[18][10].setCaseBord();
	this->tabIntro[19][10].setCaseBord();
	this->tabIntro[20][10].setCaseBord();
	this->tabIntro[17][9].setCaseBord();
	this->tabIntro[19][11].setCaseBord();
	this->tabIntro[21][9].setCaseBord();

	// D
	this->tabIntro[17][14].setCaseBord();
	this->tabIntro[18][14].setCaseBord();
	this->tabIntro[19][14].setCaseBord();
	this->tabIntro[20][14].setCaseBord();
	this->tabIntro[21][14].setCaseBord();
	this->tabIntro[17][15].setCaseBord();
	this->tabIntro[21][15].setCaseBord();
	this->tabIntro[17][16].setCaseBord();
	this->tabIntro[21][16].setCaseBord();
	this->tabIntro[18][17].setCaseBord();
	this->tabIntro[19][17].setCaseBord();
	this->tabIntro[20][17].setCaseBord();

	// / \
	//  |
	this->tabIntro[10][70].setCaseBord();
	this->tabIntro[11][69].setCaseBord();
	this->tabIntro[9][71].setCaseBord();
	this->tabIntro[10][71].setCaseBord();
	this->tabIntro[11][71].setCaseBord();
	this->tabIntro[12][71].setCaseBord();
	this->tabIntro[13][71].setCaseBord();
	this->tabIntro[14][71].setCaseBord();
	this->tabIntro[10][72].setCaseBord();
	this->tabIntro[11][73].setCaseBord();

	//Z
	this->tabIntro[16][68].setCaseBord();
	this->tabIntro[21][68].setCaseBord();
	this->tabIntro[16][69].setCaseBord();
	this->tabIntro[20][69].setCaseBord();
	this->tabIntro[21][69].setCaseBord();
	this->tabIntro[16][70].setCaseBord();
	this->tabIntro[19][70].setCaseBord();
	this->tabIntro[21][70].setCaseBord();
	this->tabIntro[16][71].setCaseBord();
	this->tabIntro[18][71].setCaseBord();
	this->tabIntro[21][71].setCaseBord();
	this->tabIntro[16][72].setCaseBord();
	this->tabIntro[17][72].setCaseBord();
	this->tabIntro[21][72].setCaseBord();
	this->tabIntro[16][73].setCaseBord();
	this->tabIntro[21][73].setCaseBord();

	// S
	this->tabIntro[14][28].setCaseBord();
	this->tabIntro[15][28].setCaseBord();
	this->tabIntro[16][28].setCaseBord();
	this->tabIntro[18][28].setCaseBord();
	this->tabIntro[14][29].setCaseBord();
	this->tabIntro[16][29].setCaseBord();
	this->tabIntro[18][29].setCaseBord();
	this->tabIntro[14][30].setCaseBord();
	this->tabIntro[16][30].setCaseBord();
	this->tabIntro[18][30].setCaseBord();
	this->tabIntro[14][31].setCaseBord();
	this->tabIntro[16][31].setCaseBord();
	this->tabIntro[17][31].setCaseBord();
	this->tabIntro[18][31].setCaseBord();

	// T
	this->tabIntro[14][34].setCaseBord();
	this->tabIntro[14][35].setCaseBord();
	this->tabIntro[14][36].setCaseBord();
	this->tabIntro[15][36].setCaseBord();
	this->tabIntro[16][36].setCaseBord();
	this->tabIntro[17][36].setCaseBord();
	this->tabIntro[18][36].setCaseBord();
	this->tabIntro[14][37].setCaseBord();
	this->tabIntro[14][38].setCaseBord();

	// A
	this->tabIntro[14][41].setCaseBord();
	this->tabIntro[15][41].setCaseBord();
	this->tabIntro[16][41].setCaseBord();
	this->tabIntro[17][41].setCaseBord();
	this->tabIntro[18][41].setCaseBord();
	this->tabIntro[14][42].setCaseBord();
	this->tabIntro[16][42].setCaseBord();
	this->tabIntro[14][43].setCaseBord();
	this->tabIntro[16][43].setCaseBord();
	this->tabIntro[14][44].setCaseBord();
	this->tabIntro[15][44].setCaseBord();
	this->tabIntro[16][44].setCaseBord();
	this->tabIntro[17][44].setCaseBord();
	this->tabIntro[18][44].setCaseBord();

	// R
	this->tabIntro[14][47].setCaseBord();
	this->tabIntro[15][47].setCaseBord();
	this->tabIntro[16][47].setCaseBord();
	this->tabIntro[17][47].setCaseBord();
	this->tabIntro[18][47].setCaseBord();
	this->tabIntro[14][48].setCaseBord();
	this->tabIntro[16][48].setCaseBord();
	this->tabIntro[14][49].setCaseBord();
	this->tabIntro[16][49].setCaseBord();
	this->tabIntro[17][49].setCaseBord();
	this->tabIntro[14][50].setCaseBord();
	this->tabIntro[15][50].setCaseBord();
	this->tabIntro[16][50].setCaseBord();
	this->tabIntro[18][50].setCaseBord();

	// T
	this->tabIntro[14][53].setCaseBord();
	this->tabIntro[14][54].setCaseBord();
	this->tabIntro[14][55].setCaseBord();
	this->tabIntro[15][55].setCaseBord();
	this->tabIntro[16][55].setCaseBord();
	this->tabIntro[17][55].setCaseBord();
	this->tabIntro[18][55].setCaseBord();
	this->tabIntro[14][56].setCaseBord();
	this->tabIntro[14][57].setCaseBord();

	//Mario
	this->tabIntro[this->mario.getBas()][this->mario.getY()].setCaseMario();
	this->tabIntro[this->mario.getHaut()][this->mario.getY()].setCaseMario();

	for (int x = 0; x < HAUTEUR; x++) {
		for (int y = 0; y < LARGEUR; y++) {
			this->tab[x][y] = &(this->tabIntro[x][y]);
		}
	}
}

void PlateauSextantBros::level() {
	for (int x = 0; x < HAUTEUR; x++) {
		for (int y = 0; y < 300; y++) {
			this->tabLevel[x][y].init(x, y);
			this->tabLevel[x][y].setEcran(this->ecran);
		}
	}

	// Sol
	int x = 24;
	for (int y = 0; y < 300; y++) {
		this->tabLevel[x][y].setCaseBord();
	}

	/* TUBES */
	// 1
	this->genererTube(0, 23, 7);
	//2
	this->genererTube(30, 23, 2);
	//3
	this->genererTube(36, 23, 3);
	//4
	this->genererTube(42, 23, 4);
	//5
	this->genererTube(125, 23, 3);
	//6
	this->genererTube(131, 23, 2);
	//7
	this->genererTube(136, 23, 4);
	//8
	this->genererTube(213, 23, 9);
	//9
	this->genererTube(218, 23, 7);
	//10
	this->genererTube(223, 23, 5);
	//11
	this->genererTube(228, 23, 3);
	//12
	this->genererTube(246, 23, 3);
	//13
	this->genererTube(251, 23, 5);
	//14
	this->genererTube(256, 23, 7);

	/* Boite  */
	//1
	this->genererBoite(12, 20, true);
	//2
	this->genererBoite(18, 20, false);
	//3
	this->genererBoite(52, 11, false);
	//4
	this->genererBoite(108, 12, false);
	//5
	this->genererBoite(109, 21, true);
	//6
	this->genererBoite(113, 21, false);
	//7
	this->genererBoite(117, 21, false);
	//8
	this->genererBoite(174, 10, true);

	// Escalier
	this->genererEscalier(77, 23, 6, false);

	this->genererEscalier(86, 23, 6, true);

	this->genererEscalier(204, 23, 7, false);

	this->genererEscalier(236, 23, 4, false);

	this->genererEscalier(261, 23, 9, false);

	this->genererEscalier(272, 12, 4, false);

	// Ligne
	this->genererLigne(18,48,4);
	this->genererLigne(18,54,4);
	this->genererLigne(14,51,4);
	this->genererLigne(20,92,5);
	this->genererLigne(18,98,5);
	this->genererLigne(16,104,5);
	this->genererLigne(21,162,5);
	this->genererLigne(21,171,5);
	this->genererLigne(21,180,5);
	this->genererLigne(17,166,6);
	this->genererLigne(17,175,6);
	this->genererLigne(13,170,6);

	// Pi�ces
	this->tabLevel[22][14].setCasePiece();
	this->tabLevel[22][16].setCasePiece();
	this->tabLevel[22][18].setCasePiece();
	this->tabLevel[20][28].setCasePiece();
	this->tabLevel[20][31].setCasePiece();
	this->tabLevel[19][34].setCasePiece();
	this->tabLevel[17][39].setCasePiece();
	this->tabLevel[17][42].setCasePiece();
	this->tabLevel[16][46].setCasePiece();
	this->tabLevel[16][49].setCasePiece();
	this->tabLevel[16][52].setCasePiece();
	this->tabLevel[16][55].setCasePiece();
	this->tabLevel[22][63].setCasePiece();
	this->tabLevel[22][65].setCasePiece();
	this->tabLevel[22][67].setCasePiece();
	this->tabLevel[22][69].setCasePiece();
	this->tabLevel[22][71].setCasePiece();
	this->tabLevel[18][123].setCasePiece();
	this->tabLevel[18][126].setCasePiece();
	this->tabLevel[21][128].setCasePiece();
	this->tabLevel[20][130].setCasePiece();
	this->tabLevel[18][133].setCasePiece();
	this->tabLevel[17][136].setCasePiece();


	//Mario
	this->tabLevel[this->mario.getBas()][this->mario.getY()].setCaseMario();
	this->tabLevel[this->mario.getHaut()][this->mario.getY()].setCaseMario();

	for (int x = 0; x < HAUTEUR; x++) {
		for (int y = 0; y < LARGEUR; y++) {
			this->tab[x][y] = &(this->tabLevel[x][y]);
		}
	}
}

void PlateauSextantBros::rafraichir() {
	if (this->mario.getY() > 40 && this->mario.getY() < 261) {
		int deb = -41;
		for (int x = 0; x < HAUTEUR; x++) {
			for (int y = 0; y < LARGEUR; y++) {
				this->tab[x][y] =
						&(this->tabLevel[x][this->mario.getY() + deb]);
				deb++;
			}
			deb = -41;
		}
	}
	ecran->effacerEcranV(NOIR);
	for (int x = 0; x < HAUTEUR; x++) {
		for (int y = 0; y < LARGEUR; y++) {
			this->tab[x][y]->paint(x, y);
		}
	}
}

void PlateauSextantBros::genererTube(int posX, int posY, int h) {
	for (int y = posY; y >= (posY - h); y--) {
		if (y == (posY - h)) {
			this->tabLevel[y][posX - 1].setCaseTube();
			this->tabLevel[y][posX + 2].setCaseTube();
		}
		this->tabLevel[y][posX].setCaseTube();
		this->tabLevel[y][posX + 1].setCaseTube();
	}
}

void PlateauSextantBros::genererBoite(int posX, int posY, bool champi) {
	if (champi) {
		this->tabLevel[posY][posX].setCaseBoiteChampi();
		this->tabLevel[posY][posX + 1].setCaseBoiteChampi();
	} else {
		this->tabLevel[posY][posX].setCaseBoitePiece();
		this->tabLevel[posY][posX + 1].setCaseBoitePiece();
	}
}

void PlateauSextantBros::genererEscalier(int posX, int posY, int h,
		bool reverse) {
	int p = h;
	if (reverse) {
		for (int y = posY; y >= (posY - h); y--) {
			for (int x = posX; x < posX + p; x++) {
				this->tabLevel[y][x].setCaseBord();
			}
			p--;
		}

	} else {
		for (int y = posY; y >= (posY - h); y--) {
			for (int x = posX; x < posX + p; x++) {
				this->tabLevel[y][x].setCaseBord();
			}
			posX++;
			p--;
		}
	}
}

void PlateauSextantBros::genererLigne(int posX, int posY, int t){
	for(int y = posY ; y <= posY+t ; y++){
		this->tabLevel[posX][y].setCaseBord();
	}
}

