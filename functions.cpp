#pragma once

#include "functions.h"

//Checkers
///Checks that outfit has not been used before
///outfits: All possible outfits loaded
///num_loaded_outfits: Number of items in outfits
///current_index: How many outfits have been chosen so far
///random_index: Which outfit has been chosen & needs to be checked for validity
bool isOutfitValid(Outfit outfits[], int num_loaded_outfits, int current_index, int random_index)
{
	int times_allowed = 0;

	/*
	Allow duplicates after all outfits are used
	all outfits = current_index*3 because each outfit takes up 3 spots to prevent similarities; its own spot,
	the one before, and the one after it
	*/

	if (current_index > 0)
		times_allowed = (current_index * 3) / num_loaded_outfits;

	//Check that the current index hasn't been worn already
	if (outfits[random_index].times_worn > times_allowed || outfits[random_index + 1].times_worn > times_allowed || outfits[random_index - 1].times_worn > times_allowed)
		return false;

	return true;
}

//Getters
string getDayString(int d)
{
	string day = "";
	switch (d)
	{
	case 0: day = "Sunday";
		break;
	case 1: day = "Monday";
		break;
	case 2: day = "Tuesday";
		break;
	case 3: day = "Wednesday";
		break;
	case 4: day = "Thursday";
		break;
	case 5: day = "Friday";
		break;
	case 6: day = "Saturday";
		break;
	}
	return day;
}

///Gets default file name as a string
string getDefaultFile(char s)
{
	if (s == 'S' || s == 's')
		return "summer-spring.txt";
	else
		return "winter-fall.txt";
}

///Gets a valid file name from the user
string getFileName()
{
	ifstream rs;
	string name = "";
	cout << "Enter the new filename, with our without .txt." << endl;
	cin.ignore();
	getline(cin, name);
	int length = name.length();

	//Add .txt if needed
	if (length < 3 || name.substr(3, length - 5) != ".txt")
		name.append(".txt");

	cout << "Looking for file '" << name << "'" << endl << endl;

	rs.open(name);

	while (!rs)
	{
		cout << "Failed to load outfit file: '" << name << "'. Enter a new filename: " << endl;

		getline(cin, name);

		length = name.length();

		//Add .txt if needed
		if (length < 3 || name.substr(3, length - 5) != ".txt")
			name.append(".txt");

		cout << "Looking for file '" << name << "'" << endl << endl;

		rs.open(name);
	}

	rs.close();

	return name;
}

///Ensures valid season input
char getSeason()
{
	char season = '\0';

	cin >> season;

	while (season != 'S' && season != 's' && season != 'W' && season != 'w' && season != 'F' && season != 'f')
	{
		cout << season << " is an invalid input. Enter S for Spring/Summer, W or F for Winter/Fall." << endl;
		cin >> season;
	}
	return season;
}

///Gets season, depending on the System month of the year
string getSeasonString(int m)
{
	string season = "";
	switch (m)
	{
	default: //Dec
		season = "Winter";
		break;
	case 0: //Jan
	case 1: //Feb
		season = "Winter";
		break;
	case 2: //Mar
	case 3: //Apr
	case 4: //May
		season = "Spring";
		break;
	case 5: //June
	case 6: //July
	case 7: //Aug
		season = "Summer";
		break;
	case 8: //Sept
	case 9: //Oct
	case 10: //Nov
		season = "Fall";
		break;
	}
	return season;
}

///Gets season, depending on the User's chosen season
string getSeasonString(char m)
{
	string season = "";
	switch (m)
	{
		case 's': 
		case 'S':
			season = "Summer/Spring";
			break;
		case 'w':
		case 'W':
		case 'f':
		case 'F':
			season = "Winter/Fall";
			break;
	}
	return season;
}

///Stores previously worn outfits into the outfit array
void getWornOutfits(Outfit o[])
{

}

///Gets the previous outfits worn by the user as a string, and parses them into an integer array, representing worn outfits
void parseOutfits(string s, int worn[])
{

}

//Setters
///Changes console text color
void setcolor(unsigned short color)
{
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hcon, color);
}

//Misc
///Prints all seasons and their colors
void printSeasons()
{
	string s = "";
	cout << "What season is it?" << endl << "S = ";
	setcolor(Season::Summer);
	cout << "Summer";
	setcolor(Season::None);
	cout << " or ";
	setcolor(Season::Spring);
	cout << "Spring" << endl;
	setcolor(Season::None);
	cout << "F = ";
	setcolor(Season::Fall);
	cout << "Fall" << endl;
	setcolor(Season::None);
	cout << "W = ";
	setcolor(Season::Winter);
	cout << "Winter" << endl;
	setcolor(Season::None);
}

///Prints current season with its appropriate color
void printSeason(char s)
{
	cout << "It is: ";

	if (s == 'S' || s == 's')
	{
		setcolor(Season::Summer);
		cout << "Summer";
		setcolor(Season::None);
		cout << " or ";
		setcolor(Season::Spring);
		cout << "Spring";
		setcolor(Season::None);
		cout << '!' << endl;
	}
	else if (s == 'F' || s == 'f')
	{
		setcolor(Season::Fall);
		cout << "Fall";
		setcolor(Season::None);
		cout << '!' << endl;
	}
	else
	{
		setcolor(Season::Winter);
		cout << "Winter";
		setcolor(Season::None);
		cout << '!' << endl;
	}
}

void printAllOutfits(Outfit o[], int num_outfits)
{
	cout << "ALL OUTFITS: " << endl;
	for (int i = 0; i < num_outfits; i++)
	{
		cout << "Outfit " << i << ": " << o[i].outfit << endl;
		cout << "    " << "Worn " << o[i].times_worn << " times" << endl;
	}
}

void resetTimesWorn(Outfit o[], int num_outfits)
{
	for (int i = 0; i < num_outfits; i++)
		o[i].times_worn = 0;
}