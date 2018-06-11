#include <stdio.h>

void print_puzzle(char (*a)[9], int l, int c)
{
	int i, j;

	for (i = 0; i < l; i++){
		for (j = 0; j < c; j++)
			printf("%d ", a[i][j]);
		printf("\n");
	}
}

int is_valid(char number, char (*puzzle)[9], int row, int column)
{
	int i = 0;
	int sector_row = 3 * (row / 3);
	int sector_col = 3 * (column / 3);
	int row1 = (row + 2) % 3;
	int row2 = (row + 4) % 3;
	int col1 = (column + 2) % 3;
	int col2 = (column + 4) % 3;

	while (i < 9){
		if (puzzle[i][column] == number) return 0;
		if (puzzle[row][i] == number) return 0;
		i++;
	}

	if (puzzle[row1 + sector_row][col1 + sector_col] == number) return 0;
	if (puzzle[row2 + sector_row][col1 + sector_col] == number) return 0;
	if (puzzle[row1 + sector_row][col2 + sector_col] == number) return 0;
	if (puzzle[row2 + sector_row][col2 + sector_col] == number) return 0;

	return 1;
}

int sudoku(char (*puzzle)[9], int row, int column)
{
	int nextn = 1;

	if (row == 9)
		return 1;

	if (puzzle[row][column]) {
		if (column == 8) {
			if (sudoku(puzzle, row + 1, 0)) return 1;
		} else {
			if (sudoku(puzzle, row, column + 1)) return 1;
		}
		return 0;
	}

	for( ; nextn < 10; nextn++) {
		if (is_valid(nextn, puzzle, row, column)) {
			puzzle[row][column] = nextn;
			if (column == 8) {
				if (sudoku(puzzle, row + 1, 0)) return 1;
			} else {
				if (sudoku(puzzle, row, column + 1)) return 1;
			}
			puzzle[row][column] = 0;
		}
	}

	return 0;
}

int main()
{
	char puzzle1[9][9] = {
		{0, 0, 0, 9, 0, 4, 0, 0, 1},
		{0, 2, 0, 3, 0, 0, 0, 5, 0},
		{9, 0, 6, 0, 0, 0, 0, 0, 0},
		{8, 0, 0, 0, 4, 6, 0, 0, 0},
		{4, 0, 0, 0, 1, 0, 0, 0, 3},
		{0, 0, 0, 2, 7, 0, 0, 0, 5},
		{0, 0, 0, 0, 0, 0, 9, 0, 7},
		{0, 7, 0, 0, 0, 5, 0, 1, 0},
		{3, 0, 0, 4, 0, 7, 0, 0, 0}
	};

	char puzzle2[9][9] = {
		{8, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 3, 6, 0, 0, 0, 0, 0},
		{0, 7, 0, 0, 9, 0, 2, 0, 0},
		{0, 5, 0, 0, 0, 7, 0, 0, 0},
		{0, 0, 0, 0, 4, 5, 7, 0, 0},
		{0, 0, 0, 1, 0, 0, 0, 3, 0},
		{0, 0, 1, 0, 0, 0, 0, 6, 8},
		{0, 0, 8, 5, 0, 0, 0, 1, 0},
		{0, 9, 0, 0, 0, 0, 4, 0, 0}
	};

	char puzzle3[9][9] = {
		{0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 3, 0, 8, 5},
		{0, 0, 1, 0, 2, 0, 0, 0, 0},
		{0, 0, 0, 5, 0, 7, 0, 0, 0},
		{0, 0, 4, 0, 0, 0, 1, 0, 0},
		{0, 9, 0, 0, 0, 0, 0, 0, 0},
		{5, 0, 0, 0, 0, 0, 0, 7, 3},
		{0, 0, 2, 0, 1, 0, 0, 0, 0},
		{0, 0, 0, 0, 4, 0, 0, 0, 9}
	};

	/* easy puzzle */
	puts("\npuzzle 1\n");
	print_puzzle(puzzle1, 9, 9);
	puts("\nsolving ...\n");
	sudoku(puzzle1, 0, 0);
	print_puzzle(puzzle1, 9, 9);

	/* this one is hard, but recursive backtracking handles it well */
	puts("\npuzzle 2\n");
	print_puzzle(puzzle2, 9, 9);
	puts("\nsolving ...\n");
	sudoku(puzzle2, 0, 0);
	print_puzzle(puzzle2, 9, 9);

	/* this one is VERY hard, breaks recursive backtracking */
	puts("\npuzzle 3\n");
	print_puzzle(puzzle3, 9, 9);
	puts("\nsolving ...\n");
	sudoku(puzzle3, 0, 0);
	print_puzzle(puzzle3, 9, 9);

	return 0;
}
