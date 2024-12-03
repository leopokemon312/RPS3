// Chapter 7 - Rock Paper Scissors - Part 3.
// This program plays Rock Paper Scissors and stores session results in a file.
// It also allows users to display previous sessions.

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

// Function prototypes
void startNewSession();
void displayPreviousSessions();
string getWinner(char playerChoice, char computerChoice);

int main() {
    int menuChoice;

    do {
        // Display the menu
        cout << "\nRock Paper Scissors Menu:\n";
        cout << "1. Start a New Session\n";
        cout << "2. Display Previous Sessions\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> menuChoice;

        // Process user choice
        switch (menuChoice) {
        case 1:
            startNewSession();
            break;
        case 2:
            displayPreviousSessions();
            break;
        case 3:
            cout << "Goodbye! Thanks for playing.\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (menuChoice != 3);

    return 0;
}

// Function to start a new session
void startNewSession() {
    ofstream outFile("RPS_Sessions.txt", ios::app);
    if (!outFile) {
        cout << "Error: Unable to open file for writing.\n";
        return;
    }

    srand(time(0)); // Seed random number generator
    char playerChoice, computerChoice;
    int rounds;

    cout << "\nStarting a New Session...\n";
    cout << "How many rounds would you like to play? ";
    cin >> rounds;

    int playerWins = 0, computerWins = 0, ties = 0;

    for (int i = 1; i <= rounds; i++) {
        // Get player's choice
        cout << "\nRound " << i << ": Enter R (Rock), P (Paper), or S (Scissors): ";
        cin >> playerChoice;
        playerChoice = toupper(playerChoice);

        // Validate input
        while (playerChoice != 'R' && playerChoice != 'P' && playerChoice != 'S') {
            cout << "Invalid choice! Please enter R, P, or S: ";
            cin >> playerChoice;
            playerChoice = toupper(playerChoice);
        }

        // Generate computer's choice
        int random = rand() % 3;
        if (random == 0) computerChoice = 'R';
        else if (random == 1) computerChoice = 'P';
        else computerChoice = 'S';

        cout << "Computer chose: " << computerChoice << endl;

        // Determine the winner
        string result = getWinner(playerChoice, computerChoice);
        if (result == "Player") {
            playerWins++;
        }
        else if (result == "Computer") {
            computerWins++;
        }
        else {
            ties++;
        }

        cout << "Round result: " << result << endl;
    }

    // Display session summary
    cout << "\nSession Summary:\n";
    cout << "Rounds played: " << rounds << endl;
    cout << "Player wins: " << playerWins << endl;
    cout << "Computer wins: " << computerWins << endl;
    cout << "Ties: " << ties << endl;

    // Save session results to file
    outFile << "New Session:\n";
    outFile << "Rounds played: " << rounds << endl;
    outFile << "Player wins: " << playerWins << endl;
    outFile << "Computer wins: " << computerWins << endl;
    outFile << "Ties: " << ties << endl;
    outFile << "----------------------------\n";

    outFile.close();
}

// Function to display previous sessions
void displayPreviousSessions() {
    ifstream inFile("RPS_Sessions.txt");
    if (!inFile) {
        cout << "No previous sessions found.\n";
        return;
    }

    cout << "\nPrevious Sessions:\n";
    string line;
    while (getline(inFile, line)) {
        cout << line << endl;
    }

    inFile.close();
}

// Function to determine the winner of a round
string getWinner(char playerChoice, char computerChoice) {
    if (playerChoice == computerChoice) {
        return "Tie";
    }
    else if ((playerChoice == 'R' && computerChoice == 'S') ||
        (playerChoice == 'P' && computerChoice == 'R') ||
        (playerChoice == 'S' && computerChoice == 'P')) {
        return "Player";
    }
    else {
        return "Computer";
    }
}
