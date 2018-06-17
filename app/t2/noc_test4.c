#include <hellfire.h>
#include <noc.h>

char p[9][9] = {
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

void dispatcher(void){
	int32_t i, j;
	char buf[9][9];
	int16_t val;
	uint16_t cpu, port, size;
	int8_t status[50];
	int8_t cpus[50];
	int8_t next = 0;
	int8_t temp;
	char** tasks[2];

	tasks[0] = p;

	if (hf_comm_create(hf_selfid(), 100, 0))
		panic(0xff);

	srand(hf_cpuid());

	for (i = 0; i < sizeof(status); i++)
		status[i] = cpus[i] = 0;


	print_puzzle(tasks[0], 9, 9);


	while (1){
		 i = hf_recvprobe();
		 if (i >= 0) {
		 	size = 0;
		 	val = hf_recv(&cpu, &port, buf, &size, i);
			if (val)
				printf("hf_recv(): error %d\n", val);
			printf("[DISPATCHER]:: Recebe de %d na porta %d\n", cpu, port);

			if (size == 10){
				printf("[DISPATCHER]:: Envia problema para %d na porta %d\n", cpu, port);
				if(next < 1){
					printf("[DISPATCHER]: Indo enviar problema para %d na porta %d\n", cpu, port);
					printf("[DISPATCHER]: Mais info: %d\n", next);
					cpus[cpu] = next;
					status[next] = 1;
					val = hf_send(cpu, 3000, tasks[next], 81, hf_cpuid());
					if (val)
						printf("hf_send(): error %d\n", val);
					next++;
				}else{
					printf("[DISPATCHER]: Avisa nenhum problema disponível para %d na porta %d\n", cpu, port);
					val = hf_send(cpu, 3000, buf, 20, hf_cpuid());
					if (val)
						printf("hf_sendack(): error %d\n", val);
				}
			} else {
				printf("[DISPATCHER]:: Recebeu resultado de %d na porta %d\n", cpu, port);
				temp = cpus[cpu];
				status[temp] = 2;
				tasks[temp] = *buf;

				printf("[DISPATCHER]::  Recebe resultado de %d\n", cpu);

				print_puzzle(buf, 9, 9);
			}
		}
	}
}

void worker(void){
	int32_t i,j;
	char buf[9][9];
	int8_t waiting;
	int16_t val, channel;
	uint16_t cpu, port, size;

	if (hf_comm_create(hf_selfid(), 3000, 0))
		panic(0xff);

	delay_ms(10*hf_cpuid());

	srand(hf_cpuid());

	channel = hf_cpuid();
	waiting = 0;
	while (1){
		if (!waiting){
			val = hf_send(0, 100, buf, 10, channel);
			if (val)
				printf("hf_sendack(): error %d\n", val);
			else
				printf("[WORKER %d]:: Pede novo problema \n", channel);
			waiting = 1;
		}

		i = hf_recvprobe();
		if (i >= 0) {
			printf("[WORKER]:: i = %d \n ", i);
			size = 0;
			val = hf_recv(&cpu, &port, buf, &size, i);
			if (val)
				printf("hf_recv(): error %d\n", val);
			printf("[WORKER %d]:: Recebe de %d na porta %d - size %d\n", channel, cpu, port, size);
			if (size == 20){
				printf("[WORKER %d]:: Nenhum problema disponivel\n",channel);
			} else {
				printf("[WORKER %d]:: Resolve Puzzle\n", channel);

				print_puzzle(buf, 9, 9);

				sudoku(buf ,0,0);

				val = hf_send(0, 100, buf, size, channel);
				if (val)
					printf("hf_sendack(): error %d\n", val);
			}
			waiting = 0;
		}
	}
}

void app_main(void)
{
	if (hf_cpuid() == 0){
		hf_spawn(dispatcher, 0, 0, 0, "t0", 4096);
	}else{
//		hf_spawn(worker, 0, 0, 0, "t"+hf_cpuid(), 4096);
		hf_spawn(worker, 0, 0, 0, "t800", 4096);
	}
}