#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include <time.h>

# define ROW 33
# define COL 33

void initMap();
void printMap();
void DFS(int x, int y);

int MAP[ROW][COL];
const int xs = 1, ys = 1, xe = ROW - 2, ye = COL - 2;

int main(){

	srand(time(NULL));

	initMap();
	printMap();
	DFS(xs, ys);

	MAP[1][0] = 0; /*entrance*/
	MAP[ROW-2][COL-1] = 0; /*exit*/
	printMap();

	return 0;
}

void initMap() {
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			if (i == 0 || i == ROW - 1 || j == 0 || j == COL - 1) {
				MAP[i][j] = -1;
			}
			else {
				MAP[i][j] = 1;
			}
		}
	}
}

void printMap() {
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			if (MAP[i][j] == 1 || MAP[i][j] == -1) {
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

void DFS(int x, int y) {
	
	int dir;
	MAP[x][y] = 0;

	while (MAP[x][y+2] == 1 || MAP[x][y - 2] == 1 || MAP[x + 2][y] == 1 || MAP[x - 2][y] == 1) { /*not boarder*/
		dir = rand() % 4 + 1;
		switch (dir) {
		case 1 :
			if (MAP[x][y + 2] == 1) { /*right*/
				MAP[x][y + 1] = 0; /*dig the right wall*/
				printMap();
				DFS(x, y + 2);
				break;
			}
		case 2 :
			if (MAP[x - 2][y] == 1) { /*up*/
				MAP[x - 1][y] = 0; /*dig the up wall*/
				printMap();
				DFS(x - 2, y);
				break;
			}
		case 3 :
			if (MAP[x][y - 2] == 1) { /*left*/
				MAP[x][y - 1] = 0; /*dig the left wall*/
				printMap();
				DFS(x, y - 2);
				break;
			}
		case 4 :
			if (MAP[x + 2][y] == 1) { /*down*/
				MAP[x + 1][y] = 0; /*dig the down wall*/
				printMap();
				DFS(x + 2, y);
				break;
			}
		}
		
	}
}