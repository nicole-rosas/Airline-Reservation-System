// Lucy Ying & Nicole Rosas
// Oct 17, 2021
// Airplane Reservation System: allows user to reserve seat on airplane, view seat chart, read passenger manifest, cancel reserved seat, and load and save plane seating
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstring>
#include <typeinfo>
#include <unistd.h>
#include <bits/stdc++.h>
#include "udFuncDec.hpp"
#include <string.h>
#include <stdio.h>
using namespace std;

int main() {
  // initializes seatChart of airplane with every element empty
  int seatChart[7][20];
  for(int i = 0; i < 7; i++) {
    for(int j = 0; j < 20; j++) {
      seatChart[i][j] = 0;
    }
  }

  // initializes the passenger manifest
  vector<vector<string>> passManif;

  while (true) {
    //STARTING MENU
    cout << "Airline Reservations System" << endl;
    cout << "Select Menu Option:" << endl
    << "\t1. Load Previous Assignment" << endl
    << "\t2. Save Current Assignment" << endl
    << "\t3. Choose Seat " << endl
    << "\t4. Cancel Seat Assignment" << endl
    << "\t5. Print Boarding Pass" << endl
    << "\t6. Display Seating Chart" << endl
    << "\t7. Print Passenger Manifest" << endl
    << "\t8. Quit Program" << endl;

    //GET MENU SELECTION
    char menuOpt;
    cin >> menuOpt;
    
    //PERFORM SELECT MENU FUNCTION
    switch (menuOpt){
      case '1': // loading previous file
      {
        cout << "Loading Previous Assignment and Manifest..." << endl;
        
        ifstream prevSeating ("savedSeating.txt");
        // no previous seating file exists
        if (!prevSeating) {
          cout << "No seatings saved." << endl;
          break;
        }
        if (prevSeating.is_open()){
          //Redefining seatChart and add in already reserved seats
          for (int i = 0; i < 7; i++) {
            for (int j = 0; j < 20; j++) {
              prevSeating >> seatChart[i][j];
            }
          }
          // close previous seat chart file
          prevSeating.close();
        }

        ifstream prevManif("savedManifest.txt");
        // no previous passenger manifest exists
        if (!prevManif) {
          cout << "No seatings saved." << endl;
          break;
        }

        // clear the current passenger manifest
        passManif.clear();
        string line;

        if (prevManif.is_open()){
          // gets each line of the file
          while(getline(prevManif, line)) {
            // adds the name and seat of each passenger into a string vector
            // and adds it to the passenger manifest
            int spaceInd = line.find_last_of(" ");
            vector<string> passenger;
            string name = line.substr(0, spaceInd);
            string seat = line.substr(spaceInd + 1);
            passenger.push_back(name);
            passenger.push_back(seat);
            passManif.push_back(passenger);
          }
          // closes the file
          prevManif.close();
        }
        break;
      }
      case '2': // save current files
      {
        cout << "Saving..." << endl;
        
        //Delete past saved copies to prevent build up
        if(remove( "savedSeating.txt" ) != 0 ) {
          perror( "Error deleting file" );
        }
        if(remove( "savedManifest.txt" ) != 0 ) {
          perror( "Error deleting file" );
        }

        // opens the already cleared seating chart file
        ofstream newSeating ("savedSeating.txt");
        if (newSeating.is_open())  {
          // goes through the row and col and adds either 0 or 1 if empty or not
          for (int r = 0; r < 7; r++) {
            for (int c = 0; c < 20; c++) {
              newSeating << seatChart[r][c] << " ";
            }

            newSeating << endl;
          }
          newSeating.close(); //closing the editing to the file
        }

        // opens the already cleared passenger manifest file
        ofstream newManifest ("savedManifest.txt");
        if (newManifest.is_open())  {
          // goes through and adds the passenger's name and seat to the file as a new line
          for (vector<string> p : passManif) {
            newManifest << p[0] << " " << p[1] << endl;
          }
          newManifest.close(); //closing the editing to the file
        }
        break;
      }
      case '3': // choose a seat on plane
      {
        cout << endl;
        cout << "Enter your full name: " << endl;
        // saves user input for name
        string name;
        cin.ignore(100, '\n');
        getline(cin, name);
        cout << endl;

        char sec;
        cout << "Select a Travel Class" << endl;
        cout << "Enter 'F' for First class" << endl;
        cout << "Enter 'B' for Business class" << endl;
        cout << "Enter any other key for Economy class" << endl;
        // saves user input for travel class
        cin >> sec;
        cout << endl;

        while(true) {
          // if user chooses first class
          if (sec == 'F') {
            // if first class is full
            if (isFull(seatChart, 'F')){
              char yon;
              cout << "First class has already been filled. Is business class okay?\n\t'y' for yes\n\t'n' for no" << endl;
              // saves user input to downgrade if full
              cin >> yon;
              // if yes, we change their class choice to business
              if (yon == 'y') {
                sec = 'B';
                continue;
              }
              // else we have them return to the menu 
              else {
                cout << "We are so sorry to hear that. Unfortunately, there are no other options available, ";
                cout << "but we hope to catch you on another flight!\nSending back to main menu..."<< endl;
                break;
              }
            }
            // if not full we generate a random seat for them
            string seat = genSeat(seatChart, sec);
            int downgrade;
            cout << "We have found a seat for you in First Class. Would you like to:";
            cout << "\n\t1. Downgrade to Business\n\t2. Stay in First Class" << endl;
            // saves user input to downgrade if wanted
            cin >> downgrade;
            // if user choses to downgrade
            if (downgrade == 1) {
              sec = 'B';
              continue;
            } 
            // user chooses to stay in initial seat
            else { 
              char isOk;
              cout << "Your seat assignment is: " + seat + ". Is this assignment ok?\n\ty for yes\n\tn for no" << endl;
              // saves user input to confirm seat choice
              cin >> isOk;
              // if chooses to confirm seat we save their seat in passenger manifest and seat assignment
              if (isOk == 'y'){
                cout << "Great! Your final seat assignment is: " + seat + "." << endl;
                vector<string> reservation = {name, seat};
                // passManif.push_back(reservation);
                insertIn(passManif, reservation);

                int rowNum = seatToRow(seat);
                int colNum = seatToCol(seat);
                seatChart[rowNum][colNum] = 1;
                break;
              }
              // if user chooses not to select seat we end loop and send back to menu
              if (isOk == 'n') {
                cout << "We are so sorry to hear that. We hope to catch you on another flight!";
                cout << "Sending back to main menu..." << endl;
                break;
              }
            }
          } 
          // if user chooses business class
          else if (sec == 'B') {
            // if business class is full directt them to chosing economy seating or cancelling seat
            if (isFull(seatChart, sec)) {
              char yon;
              cout << "Business class has already been filled. Is Economy Seating okay?\n\ty for yes\n\tn for no" << endl;
              // saves user response if they wish to downgrade or not
              cin >> yon;
              // if yes, change their selection to economy
              if (yon == 'y') {
                sec = 'E';
                continue;
              } 
              // if not cancel their reservation and send them to the menu
              else {
                cout << "We are so sorry to hear that. Unfortunately, there are no other options available, ";
                cout << "but we hope to catch you on another flight!\nSending back to main menu..." << endl;
                break;
              }
            }
            // generates a business section seat
            string seat = genSeat(seatChart, sec);
            
            int com;
            cout << "We have found a seat for you in Business. Would you like to \n\t1. Upgrade to First class\n\t2. Downgrade to Economy\n\t3. Stay in Business" << endl;
            // saves user input if they wish to change their class or stay
            cin >> com;
            // if the user chooses to upgrade change their section
            if (com == 1) {
              sec = 'F';
              continue;
            } 
            // if user chooses to downgrade change their section
            else if (com == 2) {
              sec = 'E';
              continue;
            } 
            // if user chooses to stay in ther section
            else {
              char makeFinal;
              cout << "Your seat assignment is: " + seat + ". Is this assignment okay?\n\ty for yes\n\tn for no" << endl;
              // saves answer if they want that seat assignment
              cin >> makeFinal;
              // if they choose that seat then save their seat and name to passenger manifest and seating chart
              if (makeFinal == 'y') {
                cout << "Great! Your final seat assignment is: " + seat + "." << endl;
                vector<string> reservation = {name, seat};
                // passManif.push_back(reservation);
                insertIn(passManif, reservation);

                int rowNum = seatToRow(seat);
                int colNum = seatToCol(seat);
                seatChart[rowNum][colNum] = 1;
                break;
              } 
              // else we cancel their reservation and send them back to the menu
              else {
                cout << "We are so sorry to hear that. We hope to catch you on another flight!";
                cout << "Sending back to main menu..." << endl;
                break;
              }
            }
          } 
          // else they are to chose a economy seat
          else {
            // if economy seating is full we cancel their seating arrangement and send them back to the main menu
            if (isFull(seatChart, sec)) {
              cout << "Sorry, there seems to be no seats available for this class." ;
              cout << "We hope to catch you on another flight! Sending back to main menu..." << endl;
              break;
            }
            // else we generate an economy section seat
            string seat = genSeat(seatChart, sec);
            int upgrade;
            cout << "We have found a seat for you in Economy. Would you like to:";
            cout << "\n\t1. Upgrade to Business\n\t2. Stay in Economy" << endl;
            // saves user input if they wish to upgrade
            cin >> upgrade;
            // if they choose to upgrade change their section to business
            if (upgrade == 1) {
              sec = 'B';
              continue;
            } 
            // else we save their seat and name to passenger manifest and seating chart
            else {
              cout << "Your seat assignment is: " + seat + "." << endl;
              vector<string> reservation = {name, seat};
              // passManif.push_back(reservation);
              insertIn(passManif, reservation);

              int rowNum = seatToRow(seat);
              int colNum = seatToCol(seat);
              seatChart[rowNum][colNum] = 1;
              break;
            }
          }
        }
        break;
      }
      case '4': // cancel seat
      {
        //INSTRUCTIONS
        cout << "Enter seat number to cancel assignment: ";
        
        //GETTING USER RESPONSE OF SEAT
        string seat;
        cin >> seat;
        cout << seat;
        
        // put their input into integers to find their seat as row and cols in seatChart
        int rowNum = seatToRow(seat);
        int colNum = seatToCol(seat);
        
        //REOPENING AVAILABILITY TO THE SEAT
        seatChart[rowNum][colNum] = 0;
        
        //REMOVING PASSENGER FROM THE MANIFEST
        for (int i = 0; i < passManif.size(); i++) {
          if (passManif[i][1].compare(seat) == 0) {
            passManif.erase(passManif.begin() + i);
          }
        }
        break;
      }
      case '5': // print boarding pass of seat
      {
        //INSTRUCTIONS
        cout << "Enter seat number to print boarding pass: ";

        //TAKING IN USER INPUT
        string inNum;
        cin >> inNum;

        string sec; //class
        // declare and initialize boolean as false if the seat is not assigned
        bool found = false;
        for (vector <string> p : passManif) {
          //getting column number
          
          // make row and col into integers that we can use for seatChart
          int incolNum = seatToRow(inNum);
          int pcolNum = seatToCol(inNum);
          
          //getting the class
          if(incolNum == pcolNum) {
            if(incolNum < 4) {
              sec = "First Class";
            } else if (incolNum < 8) {
              sec = "Business Class";
            } else {
              sec = "Economy Class";
            }

            found = true;

            //PRINTING BOARDING PASS
            cout << left << p[0] << ", SEAT: " <<  setw(5) << p[1] << ", LEVEL: " + sec << endl;
            break; //break out of case
          }
        }

        // if the seat is not found in passenger manifest then we return that the seat is not assigned
        if (!found) {
          cout << "Seat  Unassigned  -  No  Boarding  pass  available. Try Again!" << endl;
        }
        break;
      }
      case '6': // display seating chart of plane
      {
        // prints out the seating map of plane
        cout << endl;
        cout << "Seating Map: " << endl;
        for (int r = 0; r < 7; r++) {
          //Adding in the aisles
          if (r == 2 || r == 5) {
            for (int c = 0; c < 20; c++) {
              if (c == 0) {
                cout << "  "; //for aesthetic spacing
              }
              cout << left << setw(3) << (c + 1); //print row number
            }
            cout << endl;
          }
          
          //Printing out the columns
          cout << rowToString(r) << " ";
          for (int c = 0; c < 20; c++) {
            if (seatChart[r][c] == 1) {
              cout << left << setw(3) << "X";
            } else {
              cout << left << setw(3) << "O";
            }
          }
          cout << endl;
        }
        cout << endl;
        break;  
      }
      case '7': // print the passenger manifest
      {
        int order;
        cout << "Would you like to view the Passenger Manifest in:";
        cout << "\n\t1. Seating order\n\t2. Alphabetical order" << endl;
        // saves the input if the user wants to read the passenger manifest in seating or alphabetical order
        cin >> order;
        // if they chose to sort alphabetically, sorts the passenger manifest
        if (order == 2) {
          insertionSort(passManif, 1);
        } 
        
        // prints out the passenger manifest
        for (vector<string> p : passManif) {
          cout << p[0] << " " << p[1] << endl;
        }
        cout << endl;
        break;
      }
      case '8': // quits the airplane reservation system
      {
        // ends program and menu does not appear again
        return 0;
        break;
      }
      default: 
      // if they type in an invalid input they try again and return to menu
        cout << "Invalid input! Try Again!" << endl;
    }
  }
}