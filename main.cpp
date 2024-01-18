// Description: this prgram reads a text file and enable an user to display, sort, search players in the file.
// Student name: Koichi Nakata
// Date: July 2, 2023
// Status: complete

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int PLAYER_NUM = 10;

struct Player
{
  string fn, ln;
  int bDay, bMonth, bYear;
};

// Function prototypes
int chooseMenu();
void showArray(Player[]);
void sortArray(Player[], Player[]);
void searchArray(Player[]);


int main() {
  ifstream playerFile; // Make an input file for reading a text file
  Player playerArr[PLAYER_NUM], sortedArr[PLAYER_NUM]; // Want to keep the original (unsorted) array too.
  int choice;
  
  playerFile.open("soccer_player_info.txt");

  // Transfer each data to the structured instance.
  for (int i = 0; i < PLAYER_NUM; i++)
    {
      playerFile >> playerArr[i].fn;
      playerFile >> playerArr[i].ln;
      playerFile >> playerArr[i].bDay;
      playerFile >> playerArr[i].bMonth;
      playerFile >> playerArr[i].bYear;
    }
  
  playerFile.close();

  do
    {
      choice = chooseMenu();

      if (choice == 1)
      {
        cout << "\n***Unsorted data***\n";
        showArray(playerArr);
      }
      else if (choice == 2)
      {
        sortArray(playerArr, sortedArr);
        cout << "\n***Sorting has been done!***\n";
      }
      else if (choice == 3)
      {
        cout << "\n***Sorted data***\n";
        showArray(sortedArr);
      }
      else if (choice == 4)
        searchArray(playerArr);
      else if (choice == 5)
        cout << "\nThank you for using this program. Bye!\n";
    } while (choice != 5);
}

int chooseMenu()
{
  int choice;
  
  cout << "\nPlease choose an option below.\n";
  cout << "1: Display original data\n2: Sort data by first name\n";
  cout << "3: Display sorted data\n4: Search by last name\n";
  cout << "5: Exit the program\n\nType here: ";
  cin >> choice;
  
  return choice;
}

void showArray(Player arr[])
{
  cout << "First Name\tLast Name\tBday(DD/MM/YYYY)\n";
  for (int i = 0; i < PLAYER_NUM; i++)
    {
      cout << arr[i].fn << "\t\t" << arr[i].ln;
      arr[i].ln.length() < 8? cout << "\t\t": cout << '\t'; // Want to align the appearance.
      cout << arr[i].bDay << '/' << arr[i].bMonth <<
        '/' << arr[i].bYear << endl;
    }
}

void sortArray(Player original[], Player sorted[])
{
  Player temp;
  
  // Anyway, copy the original (unsorted) array so that we can edit the new array.
  for (int i = 0; i < PLAYER_NUM; i++)
    sorted[i] = original[i];

  // Selection sorting
  for (int outer = 0; outer < PLAYER_NUM-1; outer++)
    {
      for (int inner = outer+1; inner < PLAYER_NUM; inner++)
        if (sorted[inner].fn[0] < sorted[outer].fn[0])
        {
          temp = sorted[outer];
          sorted[outer] = sorted[inner];
          sorted[inner] = temp;
        }
        else if (sorted[inner].fn[0] == sorted[outer].fn[0])
        // If the first character is the same, compare the second character.
        {
          if (sorted[inner].fn[1] < sorted[outer].fn[1])
          {
            temp = sorted[outer];
            sorted[outer] = sorted[inner];
            sorted[inner] = temp;
          }
        }
    }
}

void searchArray(Player arr[])
{
  string target;
  int identical, index;
  bool found;
  
  cout << "\nPlease enter one or more letters of the name, or enter '//' to quit this option:\n";
  cin.ignore();
  getline(cin, target);

  while (target != "//")
  {
    index = 0; // Want to display how many players found
    found = false; // Flag variable
    for (int i = 0; i < PLAYER_NUM; i++)
    // Want to iterate each player's name one by one
    {
      identical = 0;
      for (int j = 0; j < target.length(); j++)
      {
        if (arr[i].ln[j] == target[j])
        identical += 1;
      }
      if (identical == target.length())
      // When all the characters are identical, this counter variable "identical" should be the same as the length of the user input string.
      {
        index++;
        cout << index << ": " << arr[i].fn << "\t\t" << arr[i].ln;
        arr[i].ln.length() < 8? cout << "\t\t": cout << '\t';
        cout << arr[i].bDay << '/' << arr[i].bMonth <<  '/' <<
          arr[i].bYear << endl;
        found = true;
      }
    }
    if (!found)
      cout << "\nNot found...\n";

    cout << "\nPlease enter one or more letters of the name, or enter '//' to quit this option:\n";
    getline(cin, target);
  }
}
