#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <unordered_set>
#include <algorithm>
#include <random>

using namespace std;
using namespace std::chrono;

// Themed word lists
const vector<string> animals = {"elephant", "tiger", "giraffe", "panda", "dolphin", "kangaroo"};
const vector<string> countries = {"japan", "brazil", "france", "india", "canada", "egypt"};
const vector<string> movies = {"inception", "avatar", "titanic", "jurassic", "matrix", "frozen"};
const vector<string> sports = {"football", "tennis", "basketball", "cricket", "swimming", "golf"};

// Difficulty levels
const int EASY = 0;
const int MEDIUM = 1;
const int HARD = 2;

const vector<string> wordsByDifficulty[3] = {animals, countries, movies}; // Use movies for HARD difficulty

const int TIME_LIMIT = 60;         // Time limit for Timed Mode in seconds
const int HINTS_ALLOWED = 2;      // Number of hints allowed per game
const int MAX_HINTS = 1;          // Maximum hints given at a time

struct Player {
    string name;
    int score;
};

string getRandomWord(const vector<string>& wordList) {
    static mt19937 mt(static_cast<unsigned int>(time(0))); // Use Mersenne Twister for better random number generation
    uniform_int_distribution<int> dist(0, wordList.size() - 1);
    int index = dist(mt);
    return wordList[index];
}

string getHiddenWord(const string& word, const unordered_set<char>& guessedLetters) {
    string hiddenWord(word.length(), '_');
    for (size_t i = 0; i < word.length(); ++i) {
        char letter = word[i];
        if (guessedLetters.count(letter)) {
            hiddenWord[i] = letter;
        }
    }
    return hiddenWord;
}

void printHangman(int attempts) {
    cout << endl;
    switch (attempts) {
        case 6:
            cout << "  ____\n";
            cout << " |    O\n";
            cout << " |   /|\\\n";
            cout << " |   / \\\n";
            cout << " |\n";
            break;
        case 5:
            cout << "  ____\n";
            cout << " |    O\n";
            cout << " |   /|\\\n";
            cout << " |   /\n";
            cout << " |\n";
            break;
        case 4:
            cout << "  ____\n";
            cout << " |    O\n";
            cout << " |   /|\\\n";
            cout << " |\n";
            cout << " |\n";
            break;
        case 3:
            cout << "  ____\n";
            cout << " |    O\n";
            cout << " |    |\n";
            cout << " |\n";
            cout << " |\n";
            break;
        case 2:
            cout << "  ____\n";
            cout << " |    O\n";
            cout << " |\n";
            cout << " |\n";
            cout << " |\n";
            break;
        case 1:
            cout << "  ____\n";
            cout << " |\n";
            cout << " |\n";
            cout << " |\n";
            cout << " |\n";
            break;
        default:
            cout << "  ____\n";
            cout << " |\n";
            cout << " |\n";
            cout << " |\n";
            cout << " |\n";
            break;
    }
}

// Function to check if the time limit has been exceeded
bool isTimeUp(time_point<steady_clock> startTime) {
    time_point<steady_clock> currentTime = steady_clock::now();
    duration<double> elapsedSeconds = currentTime - startTime;
    return elapsedSeconds.count() >= TIME_LIMIT;
}

bool playAgain() {
    char choice;
    cout << "\nDo you want to play again? (y/n): ";
    cin >> choice;
    return (choice == 'y' || choice == 'Y');
}

bool useHint(const string& word, unordered_set<char>& guessedLetters) {
    static mt19937 mt(static_cast<unsigned int>(time(0))); // Use Mersenne Twister for better random number generation
    uniform_int_distribution<int> dist(0, word.length() - 1);

    int hintIndex;
    while (true) {
        hintIndex = dist(mt);
        if (guessedLetters.count(word[hintIndex]) == 0) {
            guessedLetters.insert(word[hintIndex]);
            return true;
        }
    }
}

int main() {
    cout << "Welcome to Hangman!" << endl;

    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator

    bool playGame = true;
    vector<Player> highScores;

    while (playGame) {
        cout << "Choose a theme: " << endl;
        cout << "1. Animals" << endl;
        cout << "2. Countries" << endl;
        cout << "3. Movies" << endl;
        cout << "4. Sports" << endl;
        cout << "5. Quit" << endl;

        int themeChoice;
        cout << "Enter your choice (1-5): ";
        cin >> themeChoice;

        if (themeChoice == 5) {
            cout << "Thank you for playing Hangman! Goodbye." << endl;
            return 0;
        }

        if (themeChoice < 1 || themeChoice > 4) {
            cout << "Invalid choice. Exiting the game." << endl;
            return 0;
        }

        // Difficulty level selection
        cout << "Choose a difficulty level: " << endl;
        cout << "0. Easy" << endl;
        cout << "1. Medium" << endl;
        cout << "2. Hard" << endl;

        int difficultyChoice;
        cout << "Enter your choice (0-2): ";
        cin >> difficultyChoice;

        if (difficultyChoice < 0 || difficultyChoice > 2) {
            cout << "Invalid choice. Exiting the game." << endl;
            return 0;
        }

        vector<string> wordList = wordsByDifficulty[difficultyChoice];

        string word = getRandomWord(wordList);
        unordered_set<char> guessedLetters;

        int maxAttempts = 6;
        int attempts = 0;
        int hintsLeft = HINTS_ALLOWED;

        // Timed mode: Start the timer
        time_point<steady_clock> startTime = steady_clock::now();

        while (attempts < maxAttempts) {
            string hiddenWord = getHiddenWord(word, guessedLetters);

            cout << "Theme: ";
            switch (themeChoice) {
                case 1:
                    cout << "Animals";
                    break;
                case 2:
                    cout << "Countries";
                    break;
                case 3:
                    cout << "Movies";
                    break;
                case 4:
                    cout << "Sports";
                    break;
                default:
                    break;
            }
            cout << "\n\n";

            printHangman(attempts);

            cout << "\nGuess the word: " << hiddenWord << endl;
            cout << "Attempts remaining: " << maxAttempts - attempts << endl;

            if (hintsLeft > 0) {
                cout << "Hints left: " << hintsLeft << endl;
            } else {
                cout << "No more hints available." << endl;
            }

            char guess;

            if (hintsLeft > 0) {
                cout << "Enter your choice (g - guess, h - hint, q - quit): ";
                cin >> guess;

                if (guess == 'q' || guess == 'Q') {
                    cout << "Thank you for playing Hangman! Goodbye." << endl;
                    return 0;
                } else if (guess == 'h' || guess == 'H') {
                    if (useHint(word, guessedLetters)) {
                        hintsLeft--; // Decrement hintsLeft only if the hint was useful
                        continue;
                    } else {
                        cout << "No more hints available for this word." << endl;
                    }
                } else if (guess == 'g' || guess == 'G') {
                    cout << "Enter your guess: ";
                    cin >> guess;
                } else {
                    cout << "Invalid choice. Try again!" << endl;
                    continue;
                }
            } else {
                cout << "Enter your guess: ";
                cin >> guess;
            }

            if (guessedLetters.count(guess)) {
                cout << "You already guessed that letter. Try again!" << endl;
                continue;
            }

            guessedLetters.insert(guess);

            if (word.find(guess) != string::npos) {
                cout << "Correct guess!" << endl;
            } else {
                cout << "Incorrect guess!" << endl;
                attempts++;
            }

            // Timed mode: Check if time is up
            if (isTimeUp(startTime)) {
                cout << "Time's up! You ran out of time. The word was: " << word << endl;
                break;
            }

            // End of the game
            if (word == getHiddenWord(word, guessedLetters)) {
                cout << "Congratulations! You guessed the word: " << word << endl;

                // Calculate the score based on attempts and time taken
                int timeTaken = duration_cast<seconds>(steady_clock::now() - startTime).count();
                int score = maxAttempts - attempts + (TIME_LIMIT - timeTaken);

                cout << "Your score: " << score << endl;

                // Add player to high scores
                Player player;
                cout << "Enter your name: ";
                cin >> player.name;
                player.score = score;
                highScores.push_back(player);

                // Sort high scores
                sort(highScores.begin(), highScores.end(), [](const Player& a, const Player& b) {
                    return a.score > b.score;
                });

                // Show high scores
                cout << "\nHigh Scores:" << endl;
                for (size_t i = 0; i < highScores.size() && i < 5; ++i) {
                    cout << highScores[i].name << ": " << highScores[i].score << endl;
                }

                break;
            }
        }

        if (attempts >= maxAttempts && !isTimeUp(startTime)) {
            cout << "Sorry, you ran out of attempts. The word was: " << word << endl;
        }

        // Ask if the user wants to play again
        playGame = playAgain();
        if (playGame) {
            guessedLetters.clear();
            hintsLeft = HINTS_ALLOWED;
        }
    }

    cout << "Thank you for playing Hangman! Goodbye." << endl;

    return 0;
}
