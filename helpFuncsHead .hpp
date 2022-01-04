// header file
#ifndef MY_CODE
#define MY_CODE
#include <string>
#include <vector>
using namespace std;

// if seat(from given row and col) is taken will return true
bool seatTaken(const int[][20], int givenRow, int givenCol);

// if the given travel class in the given seat chart is full
// will return true
bool isFull(const int[][20], char sec);

// generated a random empty seat from the given seat chart 
// and given travel class
string genSeat(const int[][20], char sec);

// converts the integer of the row into a letter
// to represent the row in letters
string rowToString(int row);

// converts the seat (from given row and col) into a string
string seatToString(int row, int col);

// if there are available rows from the given start and end row
// will return true
bool availRows(const int[][20], int start, int end);

// converts the seat string to an int and only outputs the row
int seatToRow(string seat);

// converts the seat string into an int and only outputs the col
int seatToCol(string seat);

// inserts a given passenger in order by seat
void insertIn(vector<vector<string>>& vec, vector<string> newVec);
 
// sorts the given passenger manifest in alphabetical order
void insertionSort(vector<vector<string>>& vec, int);

#endif /* MY_CODE */
