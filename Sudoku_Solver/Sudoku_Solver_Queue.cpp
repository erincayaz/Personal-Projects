#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/***************************************************
This program is a sudoku solver which use self implemented
Dynamic Queue and Sudoku Table Class. The logic behind this
program is it manually try numbers and see if it fits. If it
fits, then it continues to other index which is (y++) or when
y = 8, (x++, y = 0). If it is not, then it take coordinate from
queue and change the previous index. And continue until sudoku
is solved. 

Queue Class Methods:
bool isEmpty()
void enqueue(int x, int y)
void dequeue(int & x, int & y)

Sudoku Class Methods:
Constructor which creates a 9x9 sudoku table
void inputMatrix() takes input of an sudoku table from user
bool isTrue(int x, int y) checks if the given index is fit
bool isFinished() checks if the sudoku is finished
void change(int x, int y, int number) change the value of the given index
int number(int x, int y) returns the given index
int bNumber(int x, int y) returns if the given index is fixed number or not
void plusOne(int x, int y) increment the given index by one
void printTable()


***************************************************/


struct node {
	node * next;
	int x, y;

	node() : next(NULL), x(-1), y(-1) {}
	node(int x, int y, node * n) : next(n), x(x), y(y) {}
};

class Queue {
public:
	bool isEmpty() {
		if(head == NULL)
			return true;
		return false;
	}
	void enqueue(int x, int y) {
		node * temp = new node(x, y, NULL);
		if(isEmpty())
			head = temp;
		else {
			temp->next = head;
			head = temp;
		}
	}
	void dequeue(int & x, int & y) {
		if(isEmpty())
			return;
		x = head->x;
		y = head->y;
		node * temp = head->next;
		delete head;
		head = temp;
	}


private:
	node * head;
};

class Sudoku {
public:
	Sudoku() {
		vector <vector <int>> m(9, vector<int> (9));
		vector <vector <bool>> bM(9, vector <bool> (9, false));
		bMatrix = bM;
		matrix = m;
	}

	void inputMatrix() {
		int number;
		for(int i = 0; i < 9; i++) {
			for(int j = 0; j < 9; j++) {
				cin >> number;
				matrix[i][j] = number;
				if(number != 0)
					bMatrix[i][j] = true;
			}
		}
	}

	bool isTrue(int x, int y) {
		int number = matrix[x][y];
		for(int i = 0; i < 9; i++) {
			if(y != i) {
				if(matrix[x][i] == number)
					return false;
			}
		}
		for(int i = 0; i < 9; i++) {
			if(x != i) {
				if(matrix[i][y] == number)
					return false;
			}
		}

		int areaX = ((x / 3) * 3), areaY = ((y / 3) * 3);
		for(int i = 0; i < 3; i++) {
			for(int j = 0; j < 3; j++) {
				if(x != areaX + i || y != areaY + j) {
					if(matrix[areaX + i][areaY + j] == number) {
						return false;
					}
				}
			}
		}
		return true;
	}

	bool isFinished() {
		for(int i = 0; i < 9; i++) {
			for(int j = 0; j < 9; j++) {
				if(matrix[i][j] == 0)
					return false;
			}
		}
		return true;
	}

	void change(int x, int y, int number) {
		matrix[x][y] = number;
	}

	int number(int x, int y) {
		return matrix[x][y];
	}

	int bNumber(int x, int y) {
		return bMatrix[x][y];
	}

	void plusOne(int x, int y) {
		matrix[x][y]++;
	}

	void printTable() {
		for(int i = 0; i < 9; i++) {
			for(int j = 0; j < 9; j++) {
				cout << matrix[i][j] << " ";
			}
			cout << endl;
		}
	}

private:
	vector <vector <int>> matrix;
	vector <vector <bool>> bMatrix;
};


int main()
{
	Queue list;
	Sudoku table;
	cout << "Please enter Sudoku Table: " << endl;
	table.inputMatrix();
	int x = 0, y = 0, steps = 0;
	while(true) {
		steps++;
		cout << x << " " << y << endl;
		if(table.number(x, y) == 0) {
			for(int i = 1; i <= 9; i++) {
				table.change(x, y, i);
				if(table.isTrue(x, y)) {
					list.enqueue(x, y);
					break;
				} else
					table.change(x, y, 0);
			}
			if(table.number(x, y) == 0) {
				list.dequeue(x, y);
				continue;
			}
		} else if(!table.bNumber(x, y)) {
			for(int i = 0; i < 9; i++) {
				table.plusOne(x, y);
				if(table.number(x, y) == 10) {
					break;
				} else if(table.isTrue(x, y)) {
					list.enqueue(x, y);
					break;
				}
			}
			if(table.number(x, y) == 10) {
				table.change(x, y, 0);
				list.dequeue(x, y);
				continue;
			}
		}
		if(table.isFinished())
			break;

		if(y != 8) {
			y++;
		} else if(x != 8){
			y = 0;
			x++;
		}
	}

	cout << "Solved Sudoku Table: " << endl;
	table.printTable();
	cout << "Number of steps: " << steps << endl;

	return 0;
}