/*

    Part of WildLand, an artificial organism environment gambling game, main part
    Copyright (C) 2011 stringzzz, Ghostwarez Co.

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.


Wild Land: Organism Environment Simulator version 1.0
Tigers vs. Cats vs. Mice vs. Bugs

Food Chain:

1. Tigers
2. Cats
3. Mice
4. Bugs
5. Food

Each organism is capable of eating anything below it on the chain.

*/

#include <iostream>
#include <thread> //No need for Windows
#include <chrono> //Same as above line
#include "WLHeader.h"
//#include <Windows.h> //WINDOWS USAGE: For Sleep() function on Windows
using namespace std;

int main()
{
    srand(time(0));

    int credits = 20;
    char goAgain = 'y';
    
    while (goAgain == 'y' && credits != 0) {
        Land Plains;
        string winner = "None";
        Plains.growFood(60);

        //Place bet
        int bet = 0;
        while (bet < 1) {
            Plains.displayLand();
            cout << "Credits: " << credits << "\n";
            cout << "Enter your bet: ";
            cin >> bet;
            if (bet > credits) {
                cout << "Insufficient credits!\n";
                continue;
            }
        }

        //Choose which organism to bet on
        char choice = '0';
        while (choice != 't' && choice != 'c' && choice != 'm' && choice != 'b') {
            cout << "Enter your choice:\n't': Tigers 2:1\n'c': Cats 3:1\n'm': Mice 4:1\n'b': Bugs 5:1\n";
            cin >> choice;
        }

        Plains.displayLand();
        cout << "Bet: " << bet << "\tChoice: " << choice << "\n";
        cout << "Press enter to start game:\n";
        cin.get();

        for (int n = 1; n <= 3000; n++) {
            //Loop through 3000 turns, all organisms usually die out before this
            Plains.growFood(3);
            Plains.move();
            Plains.reproduce();
            Plains.die();
            Plains.displayLand();
            Plains.displayPopCounts();
            
            this_thread::sleep_for(0.2s); //Comment this out for windows usage, windows library may also need to be included in this code for Sleep
            //Sleep(200); //WINDOWS USAGE 
            
            if (Plains.gameOver()) {
                cout << "GAME OVER!\n";
                winner = Plains.declareWinner();
                cout << winner;
                break;
            }
            
        }
        
        betAftermath(choice, winner, credits, bet); //Deals with the bet
        cout << "Credits: " << credits << "\n";

        if (credits == 0) {
            cout << "Out of credits!\n";
            break;
        }
        
        cout << "Go again? (y/n): "; //Repeat simulation? (yes/no)
        cin >> goAgain;
        
    }

    return 0;
}
