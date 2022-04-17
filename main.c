#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

struct gb
{
	int r, c;
	int *mines;
	int *moves;
	int x, y;
};

void initBoard(struct gb *board, int density);
int gameLoop(struct gb *board);
void display(struct gb *board);

int main()
{
	initscr();
	struct gb board;
	time_t t;
	srand((unsigned) time(&t));
	initBoard(&board, 40);
	display(&board);
	getch();
	endwin();
	//while (gameLoop(&board));
}

void initBoard(struct gb *board, int density)
{
	int mx, my;

	getmaxyx(stdscr, mx, my);
	
	board->mines = calloc(mx * my, sizeof(char));
	board->moves = calloc(mx * my, sizeof(char));

	board->r = my;
	board->c = mx;
	
	for (int i = 0; i < my * mx; i++) {
		board->mines[i] = 0;
		board->moves[i] = 0;
	}

	for (int i = 0; i < my; i++) {
		for (int j = 0; j < mx; j++) {
			
			if (rand() % density == 0) {	
				board->mines[i * mx + j] = -1;

				for (int k = i - 1; k < i + 2 && k < my; k++) {
					for (int l = j - 1; l < j + 2 && l < mx; l++) {
				
						if (board->mines[k * mx + l] != -1) {
							board->mines[k * mx + l] ++;
						}
					}
				}
			}
		}
	}
}

int gameLoop(struct gb *board)
{
	display(board);
	return 1;
}


void display(struct gb *board)
{
	for (int i = 0; i < board->r; i++) {
		for (int j = 0; j < board->c; j++) {
			char n = board->mines[i * board->c +j];
			//char n = 0;

			if (n) {
				if (n == -1) {
					mvaddch(j,i,'X');
				} else {
					mvaddch(j,i, n+48);
				}
			} else {
				mvaddch(j, i, ' ');
			}
		}
	}

	refresh();
}
