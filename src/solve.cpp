#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

#define SIZE 1024

struct Cube {
	int row;
	int col;
};
typedef struct Cube Cube;

struct Stack {
	Cube data[SIZE];
	int top = -1;
};

typedef struct Stack Stack;

void printMap();
int isRoad(Cube c);
int isFull(Stack* ps);
void push(Stack* ps, Cube c);
int isEmpty(Stack* ps);
Cube pop(Stack* ps);
int DFS(Stack* ps, int i, int j);
void DFS2(Stack* ps, int i, int j);
void mark(Stack* ps, int i, int j, Cube pre);
void loadMap();
void printPath();
void init();

int ROW = 0, COL = 0;
int MAP[SIZE][SIZE];
Cube predecessor[SIZE][SIZE];
int path[SIZE][SIZE];

int xs = 1, ys = 0;
int xe, ye;

int main() {
	Stack stack;

	loadMap();
	
	
	init();

	printMap();
	DFS2(&stack, xs, ys);
	printPath();
	return 0;
}

void printMap() {
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			if (MAP[i][j] == 1 || MAP[i][j] == 3) {
				printf("#");
			}
			else if (MAP[i][j] == 2) {
				printf("@");
			}
			else {
				printf(" ");
			}
		}
		printf("\n");
	}
	printf("============\n");
}

int isRoad(Cube c) {
	if (c.row < 0 || c.row >(ROW - 1) || c.col < 0 || c.col >(COL - 1)) return 0; //out of maze
	if (MAP[c.row][c.col] != 0) return 0; //is wall
	return 1;
}

int isFull(Stack* ps) {
	if (ps != NULL) {
		if (ps->top == SIZE - 1) return 1;
		else return 0;
	}
	return -1;
}
void push(Stack* ps, Cube c) {
	if (ps != NULL && !isFull(ps)) {
		ps->top++;
		ps->data[ps->top] = c;

	}
}

int isEmpty(Stack* ps) {
	if (ps != NULL) {
		if (ps->top == -1) return 1;
		else return 0;
	}
}
Cube pop(Stack* ps) {
	if (ps != NULL && !isEmpty(ps)) {
		Cube pt_top;
		pt_top = ps->data[ps->top];
		ps->top--;
		return pt_top;
	}
}

int DFS(Stack* ps, int i, int j) {
	Cube p;
	p.row = i;
	p.col = j;

	if (p.row == xe && p.col == ye) {
		push(ps, p);
		printf("0\n");
		printMap();
		return 1;
	}

	if (isRoad(p)) {
		MAP[p.row][p.col] = 2; /*visited*/
		if (DFS(ps, p.row, p.col + 1) || DFS(ps, p.row + 1, p.col) || DFS(ps, p.row, p.col - 1) || DFS(ps, p.row - 1, p.col)) {
			push(ps, p);
			return 1;
		}
		else { /*backtrace*/
			return 0;
		}
	}
	else {
		return 0;
	}
}

void DFS2(Stack* ps, int i, int j) {
	Cube p;
	p.row = xs;
	p.col = ys;

	MAP[p.row][p.col] = 2;
	push(ps, p);

	while (!isEmpty(ps)) {
		p = pop(ps);
		if (p.row == xe && p.col == ye) break; /*goal*/
		if (p.col + 1 < COL && MAP[p.row][p.col + 1] == 0) mark(ps, p.row, p.col + 1, p); /*right*/
		if (p.row + 1 < ROW && MAP[p.row + 1][p.col] == 0) mark(ps, p.row + 1, p.col, p); /*down*/
		if (p.col - 1 >= 0 && MAP[p.row][p.col - 1] == 0) mark(ps, p.row, p.col - 1, p); /*left*/
		if (p.row - 1 >= 0 && MAP[p.row - 1][p.col] == 0) mark(ps, p.row - 1, p.col, p); /*up*/

		/*printMap();*/
	}

	if (p.row == xe && p.col == ye) {
		path[p.row][p.col] = 2;
		printf("(%d, %d)\n", p.row, p.col);
		while (predecessor[p.row][p.col].row != -1) {
			p = predecessor[p.row][p.col];
			path[p.row][p.col] = 2;
			printf("(%d, %d)\n", p.row, p.col);
		}
	}
	else {
		printf("No path!\n");
	}
}

void mark(Stack* ps, int i, int j, Cube pre) {
	Cube visited;
	visited.row = i;
	visited.col = j;
	MAP[visited.row][visited.col] = 2;
	predecessor[visited.row][visited.col] = pre;
	push(ps, visited);
	printMap();
}

void loadMap() {
	FILE* fptr = NULL;

	fptr = fopen("maze.txt", "r");

	fscanf(fptr, "%d", &ROW);
	fscanf(fptr, "%d", &COL);

	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < ROW; j++) {
			fscanf(fptr, "%d", &MAP[i][j]);
		}
	}
	fclose(fptr);
}

void printPath() {
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			if (MAP[i][j] == 3 || MAP[i][j] == 1) path[i][j] = 1;
			if (path[i][j] == 1) printf("#");
			else if (path[i][j] == 2) printf("@");
			else printf(" ");
		}
		printf("\n");
	}
}

void init() {
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			predecessor[i][j].row = -1;
			predecessor[i][j].col = -1;
		}
	}
	xe = ROW - 2;
	ye = COL - 1;
}