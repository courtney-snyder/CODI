#pragma once

#define WEEK_LENGTH 5 //Number of outfits needed for a week
#define MAX_OUTFITS 180 //Maximum number of outfits total in one text file

//Let user decide what these files are called
//#define summer_spring "summer-spring.txt" //Filename for summer and spring outfits
//#define winter_fall "winter-fall.txt" //Filename for winter and fall outfits

#define to_wear "to-wear.txt" //Filename for chosen outfits

#include <ctime>
#include <iostream>
#include <fstream>
#include "functions.h"
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

/*
Text colors for each season.
Fall = Red (Orange would be better)
Winter = Blue
Spring = Green
Summer = Yellow (Might be too similar to Green, but since they are in the same file, it's okay)
*/
typedef enum Season
{
	Fall = 12, Winter = 11, Spring = 10, Summer = 14, None = 15
	//Spring = 10,
};

typedef struct Outfit
{
	string outfit;
	int times_worn;
};

//Checkers
bool isOutfitValid(Outfit outfits[], int num_loaded_outfits, int current_index, int random_index);

//Getters
string getDayString(int d);
string getFileName();
char getSeason();
string getSeasonString(int m);
string getDefaultFile(char s);
void getWornOutfits(Outfit o[]);

//Setters
void setcolor(unsigned short color);

//Misc
void parseOutfits(string s, int worn[]);
void printSeasons();
void printSeason(char s);
void printAllOutfits(Outfit outfits[], int num_outfits);
void resetTimesWorn(Outfit o[], int num_outfits);
void run_random();