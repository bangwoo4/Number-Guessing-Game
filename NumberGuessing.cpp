#include <bits/stdc++.h>
using namespace std;

// cd "d:\Projects\NumberGuessingGame" && g++ NumberGuessing.cpp -o NumberGuessing && ./NumberGuessing

// forward declaration
void guessing();
// helper functions
void printBox(string content)
{
    stringstream ss(content);
    string line;
    int maxLength = 0;

    // Tìm chiều dài lớn nhất
    while (getline(ss, line, '\n'))
    {
        if (line.length() > maxLength)
        {
            maxLength = line.length();
        }
    }

    int boxWidth = maxLength + 8;
    string horizontalLine(boxWidth, '=');

    cout << horizontalLine << endl;

    ss.clear();
    ss.str(content);

    while (getline(ss, line, '\n'))
    {
        cout << "=   " << left << setw(maxLength) << line << "   =" << endl;
    }

    cout << horizontalLine << endl;
}

void printInstructions()
{
    string gameModeInstructions = "Please select mode:\n"
                                  "Type 'easy' for easy mode, guess the number between 1 and 100, unlimited attempts and 0 hint\n"
                                  "Type 'medium' for medium mode, guess the number between 1 and 200, 10 attempts and 1 hint\n"
                                  "Type 'hard' for hard mode, guess the number between 1 and 500, 9 attemps and 2 hints";
    printBox(gameModeInstructions);
    cout << endl
         << endl;
}

void checkInvalidInput(int &guess, int &attempts, int maxNumber, int hint)
{
    while (!(cin >> guess))
    {
        cout << endl;
        printBox("Invalid input. Please enter an integer.");
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        attempts++;
        cout << endl
             << "Attempt " << attempts << ", "
                                          "guess the number between 1 and "
             << maxNumber << endl;
        if (hint > 0)
            cout << "Or type 'hint' for a hint" << endl;
    }
}

void handleLargerGuess(int remain)
{
    string messenge = "Guess a lower number! Try again... \n";
    if (remain <= 5 && remain != 1)
    {
        messenge += "You have " + to_string(remain) + " attempts left\n";
    }
    else if (remain == 1)
        messenge += "Last guess\n";
    printBox(messenge);
}

void handleSmallerGuess(int remain)
{
    string messenge = "Guess a higher number! Try again... \n";
    if (remain <= 5 && remain != 1)
    {
        messenge += "You have " + to_string(remain) + " attempts left\n";
    }
    else if (remain == 1)
        messenge += "Last guess\n";
    printBox(messenge);
}

void handleCorrectGuess(int attempts, int randomNumber)
{
    if (attempts != 1)
        printBox("Congratulations! You guessed the number with " + to_string(attempts) + " attempts. The correct number was " + to_string(randomNumber));
    else
        printBox("Congratulations! You guessed the number with 1 attempt. The correct number was " + to_string(randomNumber));
}

bool outOfLimit(int attempts, int limit, int randomNumber)
{
    if (attempts == limit)
    {
        printBox("Failed: You have reached the limit of attempts. The correct number was " + to_string(randomNumber));
        return true;
    }
    return false;
}

void startNewLoop(int &attempts, int maxNumber, int hint)
{
    attempts++;
    cout << endl
         << "Attempt " << attempts << ", "
                                      "guess the number between 1 and "
         << maxNumber << endl;
    if (hint > 0)
        cout << "Or type 'hint' for a hint" << endl;
}

void selectMode(int &randomNumber, int &limit, int &hint, int &maxNumber)
{
    string mode;
    cin >> mode;
    if (mode == "easy")
    {
        randomNumber = rand() % 100 + 1;
        limit = INT_MAX;
        hint = 0;
        maxNumber = 100;
    }
    else if (mode == "medium")
    {
        randomNumber = rand() % 200 + 1;
        limit = 10;
        hint = 1;
        maxNumber = 200;
    }
    else if (mode == "hard")
    {
        randomNumber = rand() % 500 + 1;
        limit = 9;
        hint = 2;
        maxNumber = 500;
    }
    else
    {
        cout << "Invalid mode. Please try again." << endl;
        guessing();
    }
}

// hints
int lastDigit(int n)
{
    return n % 10;
}

bool isPrime(int n)
{
    if (n < 2)
        return false;
    for (int i = 2; i <= sqrt(n); i++)
    {
        if (n % i == 0)
            return false;
    }
    return true;
}

bool isEven(int n)
{
    return n % 2 == 0;
}

void guessing()
{
    srand(time(0));
    int randomNumber, guess, limit, hint, maxNumber, attempts = 0;
    printInstructions();
    selectMode(randomNumber, limit, hint, maxNumber);
    do
    {
        if (outOfLimit(attempts, limit, randomNumber))
            return;

        startNewLoop(attempts, maxNumber, hint);

        // checkInvalidInput(guess, attempts);
        string input;
        cin >> input;
        if (input == "hint")
        {
            if (hint == 0)
            {
                printBox("You have no hint left");
                continue;
            }
            hint--;
            if (isPrime(randomNumber))
            {
                printBox("The number is a prime number");
            }
            else if (isEven(lastDigit(randomNumber)))
            {
                printBox("The number is end with an even number");
            }
            else
            {
                printBox("The number is end with an odd number");
            }
            continue;
        }
        else
        {
            stringstream ss(input);
            ss >> guess;
            if (ss.fail() || !ss.eof())
            {
                printBox("Invalid input. Please enter an integer.");
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                attempts++;
                cout << endl
                     << "Attempt " << attempts << ", "
                                                  "guess the number between 1 and "
                     << maxNumber << endl;
                if (hint > 0)
                    cout << "Or type 'hint' for a hint" << endl;
                continue;
            }
        }

        if (guess > randomNumber)
            handleLargerGuess(limit - attempts);
        else if (guess < randomNumber)
            handleSmallerGuess(limit - attempts);
        else
            handleCorrectGuess(attempts, randomNumber);

    } while (guess != randomNumber);
    return;
}

int main()
{
    guessing();
    return 0;
}