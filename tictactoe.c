// Ozzy Callooh
// August 20th, 2018

#include <stdio.h>

// Simple bools
#define bool int
#define true (1)
#define false (0)

// Mark constants
#define MARK_NONE 0
#define MARK_X 1
#define MARK_O 2

// Game state
int board[9];
int turn;

// A poor man's screen clear
void clear_screen() {
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

char get_mark(int mark) {
	switch (mark) {
		case MARK_NONE:
			return ' ';
		case MARK_X:
			return 'X';
		case MARK_O:
			return 'O';
		default:
			return '?';
	}
}

void clear_board() {
	int i;
	for (i = 0; i < 9; i++) board[i] = MARK_NONE;
}

bool is_board_full() {
	int i;
	for (i = 0; i < 9; i++)
		if (board[i] == MARK_NONE)
			return false;
	return true;
}

int get_winner() {
	// Horizontal
	if (board[0] != MARK_NONE && board[0] == board[1] && board[1] == board[2]) return board[0];
	if (board[3] != MARK_NONE && board[3] == board[4] && board[4] == board[5]) return board[3];
	if (board[6] != MARK_NONE && board[6] == board[7] && board[7] == board[8]) return board[6];

	// Vertical
	if (board[0] != MARK_NONE && board[0] == board[3] && board[3] == board[6]) return board[0];
	if (board[1] != MARK_NONE && board[1] == board[4] && board[4] == board[7]) return board[1];
	if (board[2] != MARK_NONE && board[2] == board[5] && board[5] == board[8]) return board[2];

	// Diagonal
	if (board[0] != MARK_NONE && board[0] == board[4] && board[4] == board[8]) return board[0];
	if (board[2] != MARK_NONE && board[2] == board[4] && board[4] == board[6]) return board[2];

	return MARK_NONE;
}

void game_reset() {
	clear_board();
	turn = MARK_X;
}

void print_reference_board() {
	// To help players pick cells, print a board with 1-9 on it
	printf(" 1 \xb3 2 \xb3 3\n");
	printf(" \xc4\xc4\xc5\xc4\xc4\xc4\xc5\xc4\xc4\n");
	printf(" 4 \xb3 5 \xb3 6\n");
	printf(" \xc4\xc4\xc5\xc4\xc4\xc4\xc5\xc4\xc4\n");
	printf(" 7 \xb3 8 \xb3 9\n");
}

void print_board() {
	// Symbols reference:
	// \xb3    │
	// \xc5    ┼
	// \xc4    ─
	printf(" %c \xb3 %c \xb3 %c\n", get_mark(board[0]), get_mark(board[1]), get_mark(board[2]));
	printf(" \xc4\xc4\xc5\xc4\xc4\xc4\xc5\xc4\xc4\n");
	printf(" %c \xb3 %c \xb3 %c\n", get_mark(board[3]), get_mark(board[4]), get_mark(board[5]));
	printf(" \xc4\xc4\xc5\xc4\xc4\xc4\xc5\xc4\xc4\n");
	printf(" %c \xb3 %c \xb3 %c\n", get_mark(board[6]), get_mark(board[7]), get_mark(board[8]));
}

void print_state() {
	print_board();
	printf("\n");
	print_reference_board();
	printf("\n");
	printf("Turn: %c\n", get_mark(turn));
}

int input_cell() {
	int i = -1;
	do {
		if (i != -1) printf("Invalid cell\n");
		printf("Cell (1-9): ");
		scanf("%i", &i);
	} while (i < 1 || i > 9);
	return i - 1;
}

int input_blank_cell() {
	int i = -1;
	do {
		if (i != -1) printf("Cell must be blank\n");
		i = input_cell();
	} while (board[i] != MARK_NONE);
	return i;
}

void game_loop() {
	int i;
	while (!is_board_full()) {
		// Show board state
		clear_screen();
		print_state();

		// Prompt for move
		printf("\n");
		i = input_blank_cell();
		board[i] = turn;

		// Check for winner
		i = get_winner();
		if (i != MARK_NONE) break;

		// Advance turn
		if (turn == MARK_X)
			turn = MARK_O;
		else
			turn = MARK_X;
	}
	clear_screen();
	print_board();
	printf("\n");
	if (i == MARK_NONE) {
		printf("It's a tie!\n");
	} else {
		printf("Winner: %c\n", get_mark(i));
	}
}

int main() {
	game_reset();
	game_loop();
}