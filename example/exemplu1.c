/**
 * Programarea Calculatoarelor 2013-2014
 * Tema #3 - Joc de Minesweeper
 *
 * Exemplu de utilizare a bibliotecii curses
 *
 * Autor: Adrian Scoica <adrian.sc@rosedu.org>
 * Completat: Stefan-Gabriel Mirea <stefan_gabriel.mirea@cti.pub.ro>
 */

#include <curses.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* Doua macro-uri utile pentru minimul si maximul dintre doua numere */
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) < (b) ? (b) : (a))

/* Constanta simbolica pentru codul lui Escape */
#define KEY_ESCAPE 27

int main()
{
	/* Urmatoarea linie este obligatoriu si initializeaza ecranul pentru a putea
	 * desena pe el. */
	WINDOW* wnd = initscr();

	/* Din fereastra initializata, aflam care este numarul de linii si care este
	 * numarul de coloane. */
	int nrows, ncols;
	getmaxyx(wnd, nrows, ncols);

	/* Ascundem cursorul de pe ecran. */
	curs_set(0);

	/* Sterge ecranul si pozitioneaza cursorul la coordonatele (0, 0). */
	clear();

	/* Opreste afisarea caracterelor tastate pe ecran. */
	noecho();

	/* Citeste direct caracterele introduse, fara a se mai astepta tasta ENTER. */
	cbreak();

	/* Permite folosirea tastelor sageti. */
	keypad(wnd, TRUE);

	/* Reduce decalajul de dupa apasarea tastei ESC la 25 de milisecunde. */
	set_escdelay(25);

	/* Afiseaza incepand de la linia si coloana date ca parametri 1 si 2, sirul
	 * de caractere dat ca parametrul al treilea. */
	mvaddstr(0, 0, "Puteti sa mutati steluta folosind sagetile sau tastele:");
	mvaddstr(1, 2, "A - stanga");
	mvaddstr(2, 2, "D - dreapta");
	mvaddstr(3, 2, "W - sus");
	mvaddstr(4, 2, "S - jos");
	mvaddstr(5, 10, "Pentru iesire, apasati mai intai Escape.");

	/* O variabila care retine daca s-a apasat mai intai Escape */
	int esc_pressed = 0;

	/* Linia si coloana cursorului, precum si caracterul citit */
	int row, col, p;

	/* Plaseaza cursorul la (5, 1). */
	row = 5;
	col = 1;
	move(row, col);

	/* Afiseaza un caracter "*" la pozitia curenta a cursorului. */
	addch('*');
	refresh();

	/* Toate programele cu interfata grafica au o bucla principala infinita.
	 * Acest program functioneaza in modul urmator:
	 *
	 * 1) Asteapta sa se apese o tasta.
	 *
	 * 2) In functie de tasta apasata, fie iese din program, fie muta cursorul pe
	 *		ecran si asteapta apasarea unei noi taste.
	 */
	while (1) {

		/* Citeste o tasta. */
		p = getch();

		/* Iesirea din program se face cu ajutorul tastei Escape, urmata de "q". */
		if (tolower(p) == 'q' && esc_pressed) {
			break;
		}

		/* Verificam daca nu cumva tasta citita va misca cursorul: */
		switch (tolower(p)) {

			/* La stanga, cu 'A' sau sageata stanga. */
			case 'a':
			case KEY_LEFT:
				col = MAX(col - 1, 0);
				break;

			/* La dreapta, cu 'D' sau sageata dreapta. */
			case 'd':
			case KEY_RIGHT:
				col = MIN(col + 1, ncols - 1);
				break;

			/* In sus, cu 'W' sau sageata sus. */
			case 'w':
			case KEY_UP:
				row = MAX(row - 1, 0);
				break;

			/* In jos, cu 'S' sau sageata jos. */
			case 's':
			case KEY_DOWN:
				row = MIN(row + 1, nrows - 1);
				break;

			/* Verificam daca s-a apasat Esc. */
			case KEY_ESCAPE:
				esc_pressed = 1;
				mvaddstr(6, 10, "Acum apasati q.");
		}

		/* Miscam cursorul in noua pozitie si afisam din nou '*'. */
		move(row, col);
		addch('*');

		/* Pentru ca modificarile sa fie desenate efectiv pe ecran, trebuie sa
		 * apelati neaparat functia refresh(). */
		refresh();
	}

	/* Inainte de a iesi din program, trebuie sa distrugeti fereastra. */
	endwin();

	return 0;
}
