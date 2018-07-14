Hello, thanks for using Courtney's Outfit Decider for the Indecisive (COD)I! Here are a few tips to help you personalize the content and behavior of this app.

Adding outfits to existing files:
Feel free to add your own outfits to the existing summer-spring and winter-fall text files.
Just make sure they are separated by an "Enter" (newline) character so that the program can parse the outfits properly.
	Tip:
	Alphabetize the outfits as much as possible.

Adding new files / Replacing files
You can do this a couple ways.

1. Redefine the file strings on the #define lines within the source code. They should be at about lines 16 and 17. You will need to add these files to the project
   folder so that they can be found when the program runs.
	Example: Replace the winter-fall.txt with newfile.txt
		1. Move newfile.txt to the CODI folder
			1.2. (Optional) Delete winter-fall.txt
		2. Find line 17 (the line that says #define winter_fall "winter-fall.txt")
		3. Change the .txt file to "newfile.txt"
			3.2. Line 17 should now read: #define winter_fall "newfile.txt"
		4. (Optional) Rename winter_fall to newvar by highlighting it and clicking "Rename...". This will rename all instances of the winter_fall variable in
			      the solution.
			4.2. Line 17 should now read: #define newvar "newfile.txt"

2. Add new #define lines and define your own files. This could be done for several reasons (eg to separate the seasons so Spring, Summer, Fall, Winter 
   each have their own outfits).
   Note that these files must exist since they will be opened as ifstream objects, for reading.
   This will also require some refactoring of the code. Here are a few things I can think of:
	Using 'S' to choose Spring/Summer will no longer work; that must be differentiated.

Getting more than 5 outfits per program run
You will need to mess with the #define WEEK_LENGTH variable in the source code for this. Basically, change 5 to whatever positive number (greater than 0) you want.