// Hangman.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <cstring>
#include <set>


using namespace std;

void runGame();
char guess();
string repeat(string s, int n);

int main()
{
    cout << "Hangman \nBegin? (Y/N) \n";
    string start;
    cin >> start;
    while (!(start == "Y" || start == "N")) {
        cout << "Invalid Input. \nBegin? (Y/N) \n";
        cin >> start;
    }

    if (start == "Y") {
        runGame();
    }

    else {
        cout << "Game Over!\n";
    }
  
}

void runGame()
{
    //GAME SETUP
    
    //Alphabet string
    const string alphabet = "abcdefghijklmnopqrstuvwxyz";

    //Word to guess by the player
    char wordToGuess[] = "Hamzah";
    const string word = wordToGuess;

    //Make the word to guess lowercase
    string lowerWordToGuess;
    for (int i = 0; i < strlen(wordToGuess); i++) {
        lowerWordToGuess += tolower(wordToGuess[i]);
    }
    
    //Keep track of which letters were guessed, regardless of whether they are wrong or right
    set<char> lettersGuessed;

    //Set of all incorrect letters, i.e. letters not in the word to guess.
    set<char> wrongLetters;
    for (int p = 0; p < alphabet.length(); p++) {
        if (lowerWordToGuess.find(alphabet[p]) == string::npos) {
            wrongLetters.insert(alphabet[p]);
        }
    }

    //Two win conditions: lives > 0 && wordGuessed = true
        //Corresponding to drawing the hangman
    int lives = 10;
        //Becomes true when wordProgess has no _ in it
    bool wordGuessed = false;

    //Keeps track of how many blanks are left in the word
    string wordProgress = repeat("_ ", lowerWordToGuess.length());

    while (!wordGuessed && lives > 0) {
        cout << "\nCurrent Progress: " << wordProgress;
        cout << "\nLives: " << lives;
        cout << "\nLetters guessed: ";
        for (auto it = lettersGuessed.begin(); it !=lettersGuessed.end(); ++it)
            cout << ' ' << *it;

        char gss = tolower(guess());

        if (lettersGuessed.find(gss) == lettersGuessed.end()) {
    
            lettersGuessed.insert(gss);

            if (wrongLetters.find(gss) != wrongLetters.end()) {
                lives -= 1;
            }

            if (lowerWordToGuess.find(gss) != string::npos) {
                int guessCount = count(lowerWordToGuess.begin(), lowerWordToGuess.end(), gss);
                for (int m = 0; m < guessCount; m++) {
                    int indexFound = lowerWordToGuess.find(gss);
                    char charToSwitch = lowerWordToGuess[indexFound];
                    wordProgress[indexFound * 2] = charToSwitch;
                    lowerWordToGuess[indexFound] = '_';
                }
            }  
        }
        else {
            cout << "\nYou already guessed this letter! Try again.\n";
        }
        if (count(lowerWordToGuess.begin(), lowerWordToGuess.end(), '_') == lowerWordToGuess.length()) {
            wordGuessed = true;

        }
    }

    if (wordGuessed){
        cout << "\nYou win! The word was " << word << ".\n" << "Play again ? (Y / N)";
        }
    else {
        cout << "You lost. Play again? (Y/N)";
        }
    string playAgain;
    cin >> playAgain;
    while (!(playAgain == "Y" || playAgain == "N")) {
        cout << "Invalid Input. \nBegin? (Y/N) \n";
        cin >> playAgain;
    }

    if (playAgain == "Y") {
        runGame();
    }

    else {
        cout << "\nGame Over!\n";
    }

    }
    


char guess()
{
    string userGuess;

    cout << "\nGuess a letter: \n";
    cin >> userGuess;
    while (userGuess.size() != 1) {
        cout << "\nInvalid input.\nGuess a single letter:\n";
        cin >> userGuess;
    }

    char guess = userGuess[0];

    return guess;
}

string repeat(string s, int n)
{
    string sCopy = s;

    for (int i = 1; i < n; i++) {
        s += sCopy;
    }

    return s;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
