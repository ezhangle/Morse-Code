// MorseCode.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <ios>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <conio.h>

#define OneUnit 225 //Time to wait in milliseconds, all timings are based off this unit
#define Frequency 0x2BC //This is 700 Hz, in hexidecimal
void Dash()
{
	//Make a longer beep
	Beep(Frequency,OneUnit*3);
	printf("Dash ");
}

void Dot()
{
	//Make a Beep
	Beep(Frequency,OneUnit);
	printf("Dot ");
}

void LetterGap()
{
	//Wait for letter time
	Sleep(OneUnit);
}

void WordGap()
{
	//Wait for Word time
	Sleep(OneUnit * 7);
}

void InterpretLetter(char letter)
{
	//Huge switch statement that has all the patterns for each character
	char CasedLetter = tolower(letter);
	switch (CasedLetter)
	{
	case 'a':
		Dot();
		Dash();
		break;
	case 'b':
		Dash();
		Dot();
		Dot();
		Dot();
		break;
	case 'c':
		Dash();
		Dot();
		Dash();
		Dot();
		break;
	case 'd':
		Dash();
		Dot();
		Dot();
		break;
	case 'e':
		Dot();
		break;
	case  'f':
		Dot();
		Dot();
		Dash();
		Dot();
		break;
	case 'g':
		Dash();
		Dash();
		Dot();
		break;
	case 'h':
		Dot();
		Dot();
		Dot();
		Dot();
		break;
	case 'i':
		Dot();
		Dot();
		break;
	case 'j':
		Dot();
		Dash();
		Dash();
		Dash();
		break;
	case 'k':
		Dash();
		Dot();
		Dash();
		break;
	case 'l':
		Dot();
		Dash();
		Dot();
		Dot();
		break;
	case 'm':
		Dash();
		Dash();
		break;
	case 'n':
		Dash();
		Dot();
		break;
	case 'o':
		Dash();
		Dash();
		Dash();
		break;
	case 'p':
		Dot();
		Dash();
		Dash();
		Dot();
		break;
	case 'q':
		Dash();
		Dash();
		Dot();
		Dash();
		break;
	case 'r':
		Dot();
		Dash();
		Dot();
		break;
	case 's':
		Dot();
		Dot();
		Dot();
		break;
	case 't':
		Dash();
		break;
	case 'u':
		Dot();
		Dot();
		Dash();
		break;
	case 'v':
		Dot();
		Dot();
		Dot();
		Dash();
		break;
	case 'w':
		Dot();
		Dash();
		Dash();
		break;
	case 'x':
		Dash();
		Dot();
		Dot();
		Dash();
		break;
	case 'y':
		Dash();
		Dot();
		Dash();
		Dash();
		break;
	case 'z':
		Dash();
		Dash();
		Dot();
		Dot();
		break;

	default:
		printf("Sorry I broke on letter:%c\n", CasedLetter);
		break;
	}
}

void ParseLine(std::string Line)
{
	std::vector<std::string> WordArray;

	//Split Line into words, separating by spaces
	std::istringstream iss(Line);
	std::string temp;
	while (getline(iss,temp, ' '))
	{
		WordArray.push_back(temp);
	}

	//Read Word Array, Word is set equal to the next Word in the list per itteration
	for (auto Word : WordArray)
	{
		//Split the word into its letters
		for (size_t i = 0; i < Word.length(); i++)
		{
			//Make the beeps for the letter
			InterpretLetter(Word[i]);
			//Wait between letter
			LetterGap();
		}
		//End of a Word
		std::cout << "[Space] ";
		//Wait between Word
		WordGap();
	}
}

void ClearScreen()
{
	HANDLE                     hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD                      count;
	DWORD                      cellCount;
	COORD                      homeCoords = { 0, 0 };

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE) return;

	/* Get the number of cells in the current buffer */
	if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
	cellCount = csbi.dwSize.X *csbi.dwSize.Y;

	/* Fill the entire buffer with spaces */
	if (!FillConsoleOutputCharacter(
		hStdOut,
		(TCHAR) ' ',
		cellCount,
		homeCoords,
		&count
		)) return;

	/* Fill the entire buffer with the current colors and attributes */
	if (!FillConsoleOutputAttribute(
		hStdOut,
		csbi.wAttributes,
		cellCount,
		homeCoords,
		&count
		)) return;

	/* Move the cursor home */
	SetConsoleCursorPosition(hStdOut, homeCoords);
}

int _tmain(int argc, _TCHAR* argv[])
{
	while (true)
	{
		//Clear the Screen for next run
		ClearScreen();
		//Tell retards how to use it
		std::cout << "Morse Code Generator\n" << "Enter the Text your want translated then press enter twice\nP.S. [Enter] means the end of a word\n\nTranslate: ";

		//Add multiple lines of input into one line
		std::string Temp;
		std::string Line;
		//Grab the line and check if it's empty or not
		while (getline(std::cin, Temp) && !Temp.empty())
		{
			Line += Temp;
		}
		//Output the line, 
		std::cout << "\n \nTranslating: " << Line << "\n\nTo: ";
		//Start parsing the line, word by word, then letter by letter
		ParseLine(Line);
		std::cout << "\n";

		//Wait for user to press a key before allowing them to translate multiple words without restarting
		_getch();
		//Wait so we don't break the universe
		Sleep(50);
	}
	return 0;
}

