#include<stdio.h>
#include<time.h>
#define N 5
#define NUM_POSSIBLE_MOVES 8
#define VISITED_FIRST 1
#define NOT_VISITED 0
#define OUTPUT_FILE "output.txt"
#define PRINT_GRID 0

/**
 * Stores the details of a move a knight can take
 */
typedef struct {
	int y;
	int x;
} Move;

/**
 * Possible moves a knight can take
 */
Move moves[] = {{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, {1, -2},
                {1, 2}, {2, -1}, {2, 1}};

/**
 * File pointer used to write program output
 */
FILE *fp;


void solve(short x, short y);

void recursive_solver(short board[N][N], short visited[N * N], short visited_count, short x, short y);

void output_to_file(short visited[N*N]);

void print_order_grid(short board[N][N]);

short is_valid_move(short x, short y, short board_value);


/**
 * Writes all possible tours from the knight's tour to the OUTPUT_FILE.
 * @return status code
 */
int main() {
	fp = fopen(OUTPUT_FILE, "w");

	if (fp == NULL) {
		printf("Opening file failed. Exiting.");
		return 1;
	}

	// run program for each square in N*N grid
	short x, y = 0;
	for (y = 0; y < N; y++) {
		for (x = 0; x < N; x++) {
			solve(x, y);
		}
	}
	fclose(fp);
	return 0;
}


/**
 * Solve for all Knights Tours starting at the specified x, y coordinates.
 * @param x x-coordinate to start the knight at
 * @param y y-coordinate to start the knight at
 */
void solve(short x, short y) {

	short visited[N*N];
	visited[0] = y * N + x + 1;

	// initialize the board and visit where the knight starts
	short board[N][N] = {NOT_VISITED};
	board[y][x] = VISITED_FIRST;

	recursive_solver(board, visited, 1, x, y);
}


/**
 * Recursively explores steps further into the tour.
 *
 * If all squares have been visited, print to the file. If PRINT_GRID is truthy, prints a numbered grid to console.
 *
 * @param board a 2D NxN array that stores when each square was visited
 * @param visited order of positions visited. Values can range from 1-N. Length N*N.
 * @param visited_count number of positions visited.
 * @param x y-coordinate the knight is positioned at
 * @param y x-coordinate the knight is positioned at
 */
void recursive_solver(short board[N][N], short visited[N * N], short visited_count, short x, short y) {
	// all spots have been visited. write to file
	if (visited_count == N * N) {
		output_to_file(visited);
		if (PRINT_GRID)
			print_order_grid(board);
		return;
	}

	short i, new_y, new_x;

	// explore each possible move
	for (i = 0; i < NUM_POSSIBLE_MOVES; i++) {
		new_x = x + moves[i].x;
		new_y = y + moves[i].y;

		// if visited already or is not a square on board
		if (board[new_y][new_x] != NOT_VISITED || new_x >= N || new_x < 0 || new_y < 0 || new_y >= N)
			continue;

		board[new_y][new_x] = visited_count + 1;
		visited[visited_count] = new_y * N + new_x + 1;

		recursive_solver(board, visited, visited_count + 1, new_x, new_y);
		board[new_y][new_x] = NOT_VISITED;
	}
}


/**
 * Write a complete tour to file.
 * @param visited array storing the order of squares during the tour
 */
void output_to_file(short visited[N * N]) {
	short i;
	fprintf(fp, "%d", visited[0]);
	for (i = 1; i < N * N; i++) {
		fprintf(fp, ",%d", visited[i]);
	}
	fprintf(fp, "\n");
}


/**
 * Prints a board of numbers to the console to show order squares were visited.
 * @param board a NxN 2D array that stores the order each square was visited
 */
void print_order_grid(short board[N][N]) {
	short y, x;

	for (y = 0; y < N; y++) {
		for (x = 0; x < N; x++) {
			printf("%3d", board[y][x]);
		}
		printf("\n");
	}
	printf("\n");
}

