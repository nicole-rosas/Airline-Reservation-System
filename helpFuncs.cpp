// file to store helper functions
#include <iostream>
#include <array>
#include <string>
#include <vector>
#include "udFuncDec.hpp"
using namespace std;

string rowToString(int row) {
  // finds the given row in switch case and returns string
  switch(row + 1) {
		case 1:
			return "A";
		case 2:
			return "B";
		case 3:
			return "D";
		case 4:
			return "E";
		case 5:
			return "F";
		case 6:
			return "H";
		default:
			return "I";
	}
}

string seatToString(int row, int col){
  // declares and creates an empty string
  string seat = "";
  // adds the row to the string
	seat += rowToString(row);
  // adds the col to the string
	seat += to_string(col + 1);
	return seat;
}


bool seatTaken(const int seatChart[][20] , int givenRow, int givenCol){
  // goes into the seat chart and if the given index of the seat chart does not return a 0 then it the seat is taken
  return (seatChart[givenRow][givenCol] != 0);
}

bool isFull(const int seatChart[][20], char sec){
  // if the section is first class
  if (sec == 'f') {
    // checks the rows of first class to see if it is available
		return (!availRows(seatChart, 1, 3));
	}
  // if section is business class
	else if (sec == 'b') {
    // checks the rows of business class to see if it is available
		return (!availRows(seatChart, 4, 7));
	}
  // if the section is economy class
	else {
    // checks the rows of economy class to see if it is available
		return (!availRows(seatChart, 8, 20));
	}
}

string genSeat(const int seatChart[][20], char sec){
  int row, col;
  // makes it so the random numbers are generated everytime
  srand (time(0));
  // if the section is first class
  if (sec == 'F') {
    // generate a seat in specific rows and cols
		col = rand() % 3;
		row = rand() % 6;
    // if seat is taken generate another
		if (seatTaken(seatChart, row, col)) {
			genSeat(seatChart, sec);
		} 
	}
  // if the section is business class
	else if (sec == 'B'){
    // generate a seat in specific rows and cols
		col = rand() % 4 + 3;
		row = rand() % 6;
    // if seat is taken generate another
		if (seatTaken(seatChart, row, col)) {
			genSeat(seatChart, sec);
		} 
	} 
  // if the section is economy class
  else {
    // generate a seat in specifit col and row
		col = rand() % 12 + 8;
		row = rand() % 6;
    // if seat is taken generate another
		if (seatTaken(seatChart, row, col)) {
			genSeat(seatChart, sec);
		} 
	}
  // returns the seat as a string
  return seatToString(row, col);
}

bool availRows(const int seatChart[][20], int start, int end){
  // declare and initialize boolean as false
  bool isAvailable = false;
  // go through the specific rows and cols
  for (int c = start; c < end; c++) {
    for(int r = 0; r < 7; r++) {
      // if one of the seats are not taken make booleans true
      if (!seatTaken(seatChart, r, c)) {
        isAvailable = true;
      }
    }
  }
  // return the boolean if the section is available
  return isAvailable;
}

int seatToRow(string seat) {
  // take the first char of seat string
  char c = seat.at(0);
  // find the char in switch cases and return the int it represents as a letter
  switch (c) {
    case 'A':
      return 0;
    case 'B':
      return 1;
    case 'D':
      return 2;
    case 'E':
      return 3;
    case 'F':
      return 4;
    case 'H':
      return 5;
    default:
      return 6;
  }
}

int seatToCol(string seat) {
  // takes the substring of the char at index 1 to the rest and return it as an integer
  int num = stoi(seat.substr(1));
  return num - 1;
}

void insertIn(vector<vector<string>>& vec, vector<string> newVec) {
  int index = 0; 
  //iterates through the current vector
  for(int j = 0; j < vec.size(); j++) {
    string seatVec = vec[j][1];
    int rowVec = seatToRow(seatVec);
    int colVec = seatToCol(seatVec);
    
    string seatNew = newVec[1];
    int rowNew = seatToRow(seatNew);
    int colNew = seatToCol(seatNew);

    //if new is less than old col number
    if(colNew < colVec) {
      index = j;
      break;
    } else if (colNew == colVec) { //if col are the same
      if(rowNew < rowVec) { //check that row is less than 
        index = j;
        break;
      }
    } 
    else { //else move on (specifically for last element case)
      index = j + 1;
    }
        
  }
  //insert the new vector into the previously calculated spot
  if(index >= vec.size()) {
    vec.push_back(newVec);
  } else {
    vec.insert(vec.begin() + index, newVec);
  }
}

void insertionSort(vector<vector<string>>& vec, int isSeat) {
  // go through elements in vector starting from one
  for(int j = 1; j < vec.size(); j++) {
    // sets the key elements we want to compare and use to sort
    vector<string> keyVec = vec[j];
    string key = keyVec[isSeat];

    // to compare the element previous to it
    int i = j - 1;
    // if the current element is less then stored element 
    while(i >= 0 && vec[i][isSeat].compare(key) > 0) {
      // we move the already iterated elements over
      vec[i + 1] = vec[i];
      i--;
    }
    // else we go to next element to iterate
    vec[i+1] = keyVec;
  }
  cout << endl << endl;
}
