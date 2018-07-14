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

#include "functions.h"

int main()
{
	//"Global" variables
	char season = '\0';
	int loaded_outfits = 0; //Number of outfits loaded from the text file
	Outfit total_outfits[MAX_OUTFITS]; //Stores outfit descriptions & number of times worn
	string current_file = "";
	ifstream is; //Reader
	ofstream os; //Writer

	srand(time(NULL));
	setcolor(Season::None);

	std::time_t t = std::time(0); //Get time now
	std::tm* now = std::localtime(&t);

	cout << "Welcome to Courtney's Outfit Decider for the Indecisive (CODI)!" << endl << endl;

	
	/*cout << "What would you like to do?\n1. Pick my outfits randomly\n2. Pick my outfits based on previously worn outfits\n3. Remind me what was previously picked out for me\n\n";

	int option = 0;
	cin >> option;
	
	while (option > 3 || option < 1)
	{
		cout << option << " is not valid.\n1. Pick my outfits based on previously worn outfits\n2. Pick my outfits randomly\n3. Remind me what was previously picked out for me\n\n";
		cin >> option;
	}

	switch (option)
	{
	case 1:
		run_random();
	case 2:
		break;
	case 3:
		break;
	}*/

	cout << "This app will pick " << WEEK_LENGTH <<  " outfits out for you." << endl << endl;

	//Determine what season it is
	printSeasons();
	season = getSeason();
	printSeason(season);

	//Get a file from the user
	cout << "Enter the name of the text file that contains your outfits or use " << getDefaultFile(season) << endl << endl;
	cout << "E = enter new text file. NOTE: This file must exist in the project folder." << endl;
	cout << "Any key = use '" << getDefaultFile(season) << "'" << endl << endl;

	char choice = '\0';
	string name = "";

	cin >> choice;

	//Get a valid file from the user
	if (choice == 'E' || choice == 'e')
		current_file = getFileName();

	//Use the default file for the chosen season
	else
		current_file = getDefaultFile(season);

	//Open the outfit file
	is.open(current_file);

	//Check that the outfit file opened properly
	if (!is)
		cout << "Failed to load " << getSeasonString(season) << " outfit file: '" << current_file << "'" << endl;

	else
	{
		cout << "Successfully loaded " << getSeasonString(season) << " outfit file: '" << current_file << "'!" << endl;
		string temp = "";
		int i = 0;

		//Parse the outfit file
		while (is)
		{
			//Read each outfit
			getline(is, temp, '\n');

			//Store in the total_outfit array, init times worn to 0
			total_outfits[i].outfit = temp;
			total_outfits[i].times_worn = 0;

			i++;
		}
		
		loaded_outfits = i;

		char choice = '\0';

		cout << "Loaded " << loaded_outfits << " outfits from " << current_file << endl;
		cout << "Enter V to view all loaded outfits or any other character to continue." << endl << endl;
		
		cin >> choice;
		
		if (choice == 'V' || choice == 'v')
			printAllOutfits(total_outfits, loaded_outfits);

		system("pause");
		system("cls");

		cout << "Found previous outfit file '" << to_wear << "'. Enter A to append new outfits to this file or O to overwrite the file." << endl;
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

		//Write today's date on the file so user remembers when they previously used this
		string day = getDayString(now->tm_wday);
		string sSeason = getSeasonString(now->tm_mon);

		cout << endl << day << ", " << sSeason << ' ' << (now->tm_mon + 1) << '-' << now->tm_mday << '-' << (now->tm_year + 1900) << endl;
		os << day << ", " << sSeason << ' ' << (now->tm_mon + 1) << '-' << now->tm_mday << '-' << (now->tm_year + 1900) << endl;

		for (int j = 0; j < WEEK_LENGTH; j++)
		{
			//Get a random outfit of the i outfits loaded into the total_outfit array
			int index = rand() % i;
			bool isUnique = isOutfitValid(total_outfits, loaded_outfits, j, index);

			//Make sure that index + or - 1 has not already been used
			while (!isUnique)
			{
				index = rand() % i;
				isUnique = isOutfitValid(total_outfits, loaded_outfits, j, index);
			}

			//Select outfit
			total_outfits[index].times_worn++;

			//Show user now
			cout << "Outfit " << j + 1 << ": " << total_outfits[index].outfit << endl;

			//Store in text file
			os << "Outfit " << j + 1 << ": " << total_outfits[index].outfit << endl;
		}

		os.close();
		cout << "Selected " << WEEK_LENGTH << " outfits. Outfits are stored in '" << to_wear << "'" << endl << endl;
		printAllOutfits(total_outfits, loaded_outfits);
	}

	return 0;
}