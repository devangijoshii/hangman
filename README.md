# Hangman

This is a simple command-line Hangman game written in C++. The game allows the player to choose a theme, select a difficulty level, and guess the hidden word within a certain number of attempts or time limit. The game also includes a hint feature and keeps track of high scores.

## How to Play

1. Download the C++ source code and compile it using a C++ compiler (e.g., g++).
2. Run the compiled executable to start the game.
3. The game will display a menu where you can choose a theme (animals, countries, movies, sports) and difficulty level (easy, medium, hard).
4. The game will randomly select a word from the chosen theme and hide it with underscores.
5. You have to guess the letters of the word one by one, and you have a limited number of attempts based on the difficulty level.
6. If you need help, you can use hints (limited number available) to reveal a random letter of the word.
7. The game ends when you either guess the entire word, run out of attempts, or run out of time (for timed mode).
8. After each game, you have the option to play again or quit the game.
9. Your score will be calculated based on the number of attempts and time taken to guess the word. The higher your score, the better.

## Rules

1. You can guess letters by entering them using your keyboard.
2. You cannot guess the same letter again.
3. If you choose to use a hint, it will reveal a random letter of the word.
4. For timed mode, the game will automatically end if the time limit is exceeded.

## High Scores

The game keeps track of high scores for each theme and difficulty level combination. After each successful game, you will be asked to enter your name, and your score will be added to the high scores list. The top five high scores for each difficulty level are displayed at the end of each game.

## Dependencies

The Hangman game uses standard C++ libraries, so no additional dependencies are required.

## How to Compile

To compile the game, you can use a C++ compiler like g++: ```g++ -o HangmanGame Hangman.cpp ```


## How to Run

After compiling, run the game using the following command: ```./HangmanGame ```


## Additional Notes

1. The game uses the Mersenne Twister algorithm for random number generation, providing better randomness.
2. The game is designed to be played in a terminal or command prompt.
3. The provided word lists can be expanded or modified as desired to include new themes or words.

Enjoy playing Hangman! Have fun guessing the words! 🎉



