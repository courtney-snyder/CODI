/*
Courtney Snyder

Last Updated: 7/13/18

Description: The program reads a list of possible outfits and tells the user what to wear for a business week. It tries to
make the outfits as different as possible. Summer and spring outfits are in the same file, winter and fall outfits are in 
the same file as well.

Credits: Outfits not created by me, unfortunately.
Winter/Fall: http://outfitposts.com/2015/12/outfit-post-fallwinter-business-casual_25.html
Summer/Spring: http://outfitposts.com/2015/08/one-suitcase-summer-business-casual_12.html
*/

#define WEEK_LENGTH 5 //Number of outfits needed for a week
#define summer_spring "summer-spring.txt" //Filename for summer and spring outfits
#define winter_fall "winter-fall.txt" //Filename for winter and fall outfits
#define to_wear "to-wear.txt" //Filename for chosen outfits

#include <ctime>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <windows.h>

using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::ifstream;
using std::ofstream;
using std::string;

void setcolor(unsigned short color)                 
{
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hcon, color);
}

typedef enum Season
{
	Fall = 14, Winter = 11, Spring = 10, Summer = 12, None = 15
};

bool isValid(int current_index, int used_indexes[WEEK_LENGTH], int random_index)
{
	for (int k = 0; k < current_index; k++)
	{
		if (random_index == used_indexes[k] || random_index == used_indexes[k] + 1 || random_index == used_indexes[k] + 1)
			return false;
	}
	return true;
}

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

int main()
{
	char season = '\0';
	string total_outfits[180], weekly_outfits[WEEK_LENGTH];
	ifstream is; //Will be summer_spring or winter_fall
	ofstream os; //Will write or append outfits to this file
	int used_indexes[WEEK_LENGTH]; //Will help duplicate/similar outfits occur less in a week

	srand(time(NULL));

	cout << "Welcome to Courtney's Outfit Decider for the Indecisive (CODI)!" << endl;
	cout << "This app will pick " << WEEK_LENGTH <<  " outfits out for you." << endl;
	
	if (WEEK_LENGTH < 6)
		cout << "Looks like you're on your own for the weekend." << endl;

	cout << endl;

	//Determine what season it is
	cout << "What season is it?" << endl << "S = ";
	setcolor(Season::Summer);
	cout << "Summer";
	setcolor(Season::None);
	cout << " or ";
	setcolor(Season::Spring);
	cout << "Spring" << endl;
	setcolor(Season::Fall);
	cout << "F = Fall" << endl;
	setcolor(Season::Winter);
	cout << "W = Winter" << endl;
	setcolor(Season::None);

	cin >> season;
	while (season != 'S' && season != 's' && season != 'W' && season != 'w' && season != 'F' && season != 'f' )
	{
		cout << season << " is an invalid input. Enter S for Spring/Summer, W or F for Winter/Fall." << endl;
		cin >> season;
	}

	cout << endl << "It is: ";

	//User selected Summer or Spring
	if (season == 'S' || season == 's')
	{
		setcolor(Season::Summer);
		cout << "Summer";
		setcolor(Season::None);
		cout << " or ";
		setcolor(Season::Spring);
		cout << "Spring!" << endl;
		setcolor(Season::None);

		is.open(summer_spring);

		//Check that the outfit file opened properly
		if (!is)
			cout << "Failed to load summer and spring outfit file: '" << summer_spring << "'" << endl;

		else
		{
			cout << "Successfully loaded summer and spring outfit file: '" << summer_spring << "'!" << endl;
			string temp = "";
			int i = 0;
			while (is)
			{
				//Read each outfit
				getline(is, temp, '\n');

				//Store in the total_outfit array
				total_outfits[i] = temp;
				i++;
			}
			char choice = '\0';
			cout << "Loaded " << i << " outfits from " << summer_spring << endl;
			cout << "Found previous outfit file " << to_wear << ". Enter A to append new outfits to this file or O to overwrite the file." << endl;
			cin >> choice;
			while (choice != 'A' && choice != 'a' && choice != 'O' && choice != 'o')
			{
				cout << choice << " is an invalid choice. Enter A to append new outfits to this file or O to overwrite the file." << endl;
				cin >> choice;
			}

			if (choice == 'A' || choice == 'a')
				os.open(to_wear, std::ofstream::app);
			else
				os.open(to_wear);

			is.close();

			std::time_t t = std::time(0);   // get time now
			std::tm* now = std::localtime(&t);

			//Write today's date on the file so user remembers when they previously used this
			string day = getDayString(now->tm_wday);
			string season = getSeasonString(now->tm_mon);

			cout << endl << day << ", " << season << ' ' << (now->tm_mon + 1) << '-' << now->tm_mday << '-' << (now->tm_year + 1900) << endl;
			os << day << ", " << season << ' ' << (now->tm_mon + 1) << '-' << now->tm_mday << '-' << (now->tm_year + 1900) << endl;

			for (int j = 0; j < WEEK_LENGTH; j++)
			{
				//Get a random outfit of the i outfits loaded into the total_outfit array
				int index = rand() % i;
				
				bool isUnique = isValid(j, used_indexes, index);

				//Make sure that index + or - 1 has not already been used
				while (!isUnique)
				{
					index = rand() % i;
					isUnique = isValid(j, used_indexes, index);
				}

				//Add index to used_indexes array
				used_indexes[j] = index;

				//Select outfit
				weekly_outfits[j] = total_outfits[index];

				//Show user now
				cout << "Outfit " << j + 1 << ": " << weekly_outfits[j] << endl;

				//Store in text file
				os << "Outfit " << j + 1 << ": " << weekly_outfits[j] << endl;
			}

			os.close();
			cout << "Selected " << WEEK_LENGTH << " outfits. Outfits are stored in " << to_wear << endl;
		}
	}

	//User selected Winter or Fall
	else
	{
		if (season == 'F' || season == 'f')
		{
			setcolor(Season::Fall);
			cout << "Fall!" << endl;
			setcolor(Season::None);
		}
		else
		{
			setcolor(Season::Winter);
			cout << "Winter!" << endl;
			setcolor(Season::None);
		}
		
		is.open(winter_fall);
		
		//Check that the outfit file opened properly
		if (!is)
			cout << "Failed to load winter and fall outfit file: '" << winter_fall << "'" << endl;
		
		else
		{
			cout << "Successfully loaded winter and fall outfit file: '" << winter_fall << "'!" << endl;
			string temp = "";
			int i = 0;
			while (is)
			{
				//Read each outfit
				getline(is, temp, '\n');

				//Store in the total_outfit array
				total_outfits[i] = temp;
				i++;
			}
			char choice = '\0';
			cout << "Loaded " << i << " outfits from " << summer_spring << endl;
			cout << "Found previous outfit file " << to_wear << ". Enter A to append new outfits to this file or O to overwrite the file." << endl;
			cin >> choice;
			while (choice != 'A' && choice != 'a' && choice != 'O' && choice != 'o')
			{
				cout << choice << " is an invalid choice. Enter A to append new outfits to this file or O to overwrite the file." << endl;
				cin >> choice;
			}

			if (choice == 'A' || choice == 'a')
				os.open(to_wear, std::ofstream::app);
			else
				os.open(to_wear);

			is.close();

			std::time_t t = std::time(0);   // get time now
			std::tm* now = std::localtime(&t);

			//Write today's date on the file so user remembers when they previously used this
			string day = getDayString(now->tm_wday);
			string season = getSeasonString(now->tm_mon);

			cout << endl << day << ", " << season << ' ' << (now->tm_mon + 1) << '-' << now->tm_mday << '-' << (now->tm_year + 1900) << endl;
			os << day << ", " << season << ' ' << (now->tm_mon + 1) << '-' << now->tm_mday << '-' << (now->tm_year + 1900) << endl;

			for (int j = 0; j < WEEK_LENGTH; j++)
			{
				//Get a random outfit of the i outfits loaded into the total_outfit array
				int index = rand() % i;

				bool isUnique = isValid(j, used_indexes, index);

				//Make sure that index + or - 1 has not already been used
				while (!isUnique)
				{
					index = rand() % i;
					isUnique = isValid(j, used_indexes, index);
				}

				//Add index to used_indexes array
				used_indexes[j] = index;

				//Select outfit
				weekly_outfits[j] = total_outfits[index];

				//Show user now
				cout << "Outfit " << j + 1 << ": " << weekly_outfits[j] << endl;

				//Store in text file
				os << "Outfit " << j + 1 << ": " << weekly_outfits[j] << endl;
			}

			os.close();
			cout << "Selected " << WEEK_LENGTH << " outfits. Outfits are stored in " << to_wear << endl;
		}
	}

	return 0;
}