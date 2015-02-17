/**
 * Programarea Calculatoarelor 2013-2014
 * Tema #3 - Joc de Minesweeper
 *
 * Schelet initial scris pentru Tetris - adaptat pentru Minesweeper
 *
 * Autor: Adrian Scoica <adrian.sc@rosedu.org>
 * Modificat: Stefan-Gabriel Mirea <stefan_gabriel.mirea@cti.pub.ro>
 */

#ifndef __MINESWEEPER_H__
#define __MINESWEEPER_H__

#include <curses.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define NO_KEY_PRESSED (-1)

/**
 * Functia intoarce codul caracterului apasat sau NO_KEY_PRESSED
 * daca niciun caracter nu a fost apasat.
 */
int get_key_pressed() {
	int ch = getch();
	if (ch != ERR) {
		return ch;
	}
	return NO_KEY_PRESSED;
}

/** Structura ce retine careul de Minesweeper. */
typedef struct Screen {
	/* Numarul de linii si de coloane. */
	int rows;
	int cols;
	/* Reprezentarea codificata a careului. */
	int **map;
} Screen;

/** Structura ce retine o pozitie din careul de Minesweeper. */
typedef struct Position {
	int row;
	int col;
} Position;

/**
 * Elibereaza memoria ocupata de careu.
 *
 * @param screen Careul ce va fi distrus.
 */
void destroy_screen(Screen *screen);

/**
 * Deseneaza careul pe ecran, in destinatia lui finala din cadrul interfetei
 * grafice a jocului. _NU UITATI_ ca ultima instructiune din functie sa fie
 * refresh() pentru ca altfel nu se vor vedea modificarile in final.
 *
 * @param screen: Careul ce va fi desenat.
 */
void draw_frame(Screen *s);

#endif
