/*
*  Student: Soukaina Salihi
*  Course: CIT-284 Advanced C++/OOP
*
*  This project involves writing a C++ program
*  that allows the user to search for German words,
*  their part of speech, and their meaning in English
*  from a dictionary, a file that has 25 words
*  created by the programmer.
*/

// libraries
# include<iostream>
#include<conio.h>
#include<cstdlib>
#include <string>
#include <locale> 
#include <algorithm>
# include <iomanip>
#include <fstream>

using namespace std;


// creating a struct
struct wordData
{
	string germanWord;
	string partSpeech;
	string englishMeaning;
};

// Function prototypes
void sortArray(wordData*&, wordData*&, int);
void getDataFromFile(wordData*&, wordData*&, int);
void printArray(wordData*&, int, string ps);
void getData(wordData*);
string functionKeys();
void openOutputFile();

// Global variables
ifstream inputFile;
ofstream outputFile;
string inputFileName;
string outputFileName;

int main(){

	wordData* arrayPtr = NULL;   // Pointer to int, initialize to nothing.
	wordData*arrayPtrCopy = NULL;   // Pointer to int, initialize to nothing copy of arryPtr.
	wordData allInfo;
	string finder;
	int option;
	bool flag = false;

	const int size = 25;
	arrayPtr = new wordData[size];  // Allocate size ints and save it in ptr.
	arrayPtrCopy = new wordData[size];  // Allocate size ints and save it in ptr.

	// Print the menu
	cout << "	Select Option\n                       " << endl
		<< "	1. Create the word list               " << endl
		<< "	2. German to English nouns	          " << endl
		<< "	3. German to English verbs            " << endl
		<< "	4. German to English prepositions     " << endl
		<< "	5. German to English adjectives       " << endl
		<< "	6. German to English adverbs          " << endl
		<< "	7. German to English cardinal numbers " << endl
		<< "	8. Search for a word                  " << endl
		<< "	9. Quit                               " << endl;

	while (true)
	{
		cout << "\n\nEnter a desired option: ";
		cin >> option;        // Read in the option
		cin.ignore(80, '\n');

		switch (option)
		{
		case 1:

			// Open the file.dictionary.txt is a file that has all the 25 words
			inputFile.open("dictionary.txt");

			// If the file successfully opened, process it.
			if (inputFile)
			{
				getDataFromFile(arrayPtr, arrayPtrCopy, size);
				sortArray(arrayPtr, arrayPtrCopy, size);
				flag = true; // flag that make sure that the user went trough option 1 first.
			}

			// Check for file open error.
			if (inputFile.fail())
			{
				cout << "(line " << __LINE__ << ") Error opening file:  " << "dictionary.txt" << endl;
				openOutputFile();
				for (int i = 0; i < size; i++) {
					getData(&allInfo);    // Pass the address of all Information
					arrayPtr[i] = allInfo;  // Initialize the values of the array to whatever elements entred by users.
				}
				sortArray(arrayPtr, arrayPtrCopy, size);
			}
			inputFile.close();
			cout << "***The list of words have been created!!!***";
			break;

		case 2:
			if (flag)
				printArray(arrayPtrCopy, size, "noun");

			else
				cout << "\nYou have to create the list of words first by choosing option 1 ";

			break;

		case 3:
			if (flag){

				printArray(arrayPtrCopy, size, "verb");
			}
			else
			{
				cout << "\nYou have to create the list of words first by choosing option 1 ";
			}
			break;
		case 4:
			if (flag){

				printArray(arrayPtrCopy, size, "preposition");
			}
			else
			{
				cout << "\nYou have to create the list of words first by choosing option 1 ";
			}

			break;
		case 5:
			if (flag){

				printArray(arrayPtrCopy, size, "adjective/adverb");
			}
			else
			{
				cout << "\nYou have to create the list of words first by choosing option 1 ";
			}

			break;
		case 6:

			if (flag){
				printArray(arrayPtrCopy, size, "adverb");
				printArray(arrayPtrCopy, size, "adjective/adverb");


			}
			else
			{
				cout << "\nYou have to create the list of words first by choosing option 1 ";
			}
			break;
		case 7:
			if (flag)
			{

				printArray(arrayPtrCopy, size, "cardinal number");
			}
			else
			{
				cout << "\nYou have to create the list of words first by choosing option 1 ";
			}
			break;
		case 8:

			if (flag)
			{

				cout << "Please enter the word you want to search for: ";
				//finder = functionKeys();
				unsigned char key, key2;

				string germanInput;

				while ((key = _getch()) != '\r')
				{

					if (key == 0){
						key2 = _getch();

						switch (key2)
						{
						case 59:
							cout << char(132);
							germanInput += char(132);
							break;
						case 60:
							cout << char(129);
							germanInput += char(129);
							break;
						case 61:
							cout << char(148);
							germanInput += char(148);
							break;
						case 62:
							cout << char(153);
							germanInput += char(153);
							break;
						}
					}

					else if (key == 8 || key == 127){
						if (germanInput.size() != 0){
							cout << "\b \b";
							germanInput.erase(germanInput.size() - 1);
						}
					}
					else
					{
						cout << key;
						germanInput += key;
					}
				}

				if (germanInput.find("das") != string::npos){
					germanInput.replace(germanInput.begin(), germanInput.begin() + 4, "");
				}

				if (germanInput.find("die") != string::npos){
					germanInput.replace(germanInput.begin(), germanInput.begin() + 4, "");
				}

				if (germanInput.find("der") != string::npos){
					germanInput.replace(germanInput.begin(), germanInput.begin() + 4, "");
				}
				bool exist = true;

				cout << left << setw(20) << "\n\nGerman word" << setw(30) << "Part of speech"
					<< setw(20) << "English meaning" << endl;
				for (int i = 0; i < size; i++) {

					if ((arrayPtrCopy[i].germanWord == germanInput)){
						cout << left << setw(20) << arrayPtrCopy[i].germanWord << setw(30) << arrayPtrCopy[i].partSpeech
							<< setw(20) << arrayPtrCopy[i].englishMeaning << endl;
						exist = false;
					}
				}
				if (exist){
					cout << "\nSorry!! the word you are looking for doesn't exist!!";
					break;
				}
			}
			else
			{
				cout << "\nYou have to create the list of words first by choosing option 1 ";
			}
			break;
		case 9:return 0; break;

		default:
			cout << "\n Choose only options from 1 to 9!!";
			break;
		}
	}
	return 0;
}

void printArray(wordData*&arrayC, int size, string ps){


	cout << left << setw(20) << "\n\nGerman word" << setw(30) << "Part of speech"
		<< setw(20) << "English meaning" << endl;
	for (int i = 0; i < size; i++) {

		if (arrayC[i].partSpeech == ps){
			cout << left << setw(20) << arrayC[i].germanWord << setw(30) << arrayC[i].partSpeech
				<< setw(20) << arrayC[i].englishMeaning << endl;
		}
	}
}


string functionKeys(){

	unsigned char key, key2;

	string germanInput;

	while ((key = _getch()) != '\r')
	{

		if (key == 0){
			key2 = _getch();

			switch (key2)
			{
			case 59:
				cout << char(132);
				germanInput += 'ä';
				break;
			case 60:
				cout << char(129);
				germanInput += 'ü';
				break;
			case 61:
				cout << char(148);
				germanInput += 'ö';
				break;
			case 62:
				cout << char(153);
				germanInput += 'Ö';
				break;
			}
		}

		else if (key == 8 || key == 127){
			if (germanInput.size() != 0){
				cout << "\b \b";
				germanInput.erase(germanInput.size() - 1);
			}
		}
		else
		{
			cout << key;
			germanInput += key;
		}
	}

	return germanInput;

}

void openOutputFile()
{
	// Output file:  prompt for filename, open file for output.
	cout << "Enter name of output file: ";
	getline(cin, outputFileName);
	outputFile.open(outputFileName);

} // (end function openOutputFile)


//*******************************************************
// Definition of function getData. Uses a pointer to a  *
// moviData structure variable. The user enters word    *
// information, which is stored in the variable.        *
//*******************************************************

void getData(wordData *s)
{
	///openOutputFile();	
	// Get the word name.
	cout << "\nWord name: ";
	s->germanWord = functionKeys();
	outputFile << s->germanWord << "|";
	cout << endl;

	// Get the word partSpeech.
	cout << "Student part of Speech: ";
	getline(cin, s->partSpeech);
	outputFile << s->partSpeech << "|";

	// Get the the course grade .
	cout << " Course grade: ";
	getline(cin, s->englishMeaning);
	outputFile << s->englishMeaning << "|" << endl;
}


void sortArray(wordData *&array, wordData*&arrayC, int size)
{
	int startScan, minIndex;
	string minValueGer, temp1, temp2, temp3;
	int pass = 0;

	for (int i = 0; i < size; i++) {

		replace(array[i].germanWord.begin(), array[i].germanWord.end(), char(132), 'a');
		replace(array[i].germanWord.begin(), array[i].germanWord.end(), char(129), 'u');
		replace(array[i].germanWord.begin(), array[i].germanWord.end(), char(153), 'O');
		replace(array[i].germanWord.begin(), array[i].germanWord.end(), char(148), 'o');

		if (array[i].germanWord.find("das") != string::npos){
			array[i].germanWord.replace(array[i].germanWord.begin(), array[i].germanWord.begin() + 4, "");
		}

		if (array[i].germanWord.find("die") != string::npos){
			array[i].germanWord.replace(array[i].germanWord.begin(), array[i].germanWord.begin() + 4, "");
		}

		if (array[i].germanWord.find("der") != string::npos){
			array[i].germanWord.replace(array[i].germanWord.begin(), array[i].germanWord.begin() + 4, "");
		}
	}


	// Display the sorted values.

	for (startScan = 0; startScan < (size - 1); startScan++)
	{
		pass++;
		minIndex = startScan;
		minValueGer = array[startScan].germanWord;
		temp1 = arrayC[startScan].germanWord;
		temp2 = arrayC[startScan].partSpeech;
		temp3 = arrayC[startScan].englishMeaning;

		for (int index = startScan + 1; index < size; index++)
		{
			if (array[index].germanWord < minValueGer)

			{
				minValueGer = array[index].germanWord;
				temp1 = arrayC[index].germanWord;
				temp2 = arrayC[index].partSpeech;
				temp3 = arrayC[index].englishMeaning;

				minIndex = index;
			}
		}

		// swap lines of wordes
		array[minIndex].germanWord = array[startScan].germanWord;
		array[startScan].germanWord = minValueGer;

		arrayC[minIndex].germanWord = arrayC[startScan].germanWord;
		arrayC[startScan].germanWord = temp1;

		arrayC[minIndex].partSpeech = arrayC[startScan].partSpeech;
		arrayC[startScan].partSpeech = temp2;

		arrayC[minIndex].englishMeaning = arrayC[startScan].englishMeaning;
		arrayC[startScan].englishMeaning = temp3;
	}
}


//******************************************************************************
//write the content form the file to the arrays of struct if the file is open

void getDataFromFile(wordData*&array, wordData*&arrayC, int size){


	std::string mystring;

	for (int j = 0; j < size; j++)
	{

		for (int i = 0; i < 3; i++)

		{
			getline(inputFile, mystring, '|');

			mystring.erase(std::remove(mystring.begin(), mystring.end(), '\n'), mystring.end());

			replace(mystring.begin(), mystring.end(), 'ä', char(132));
			replace(mystring.begin(), mystring.end(), 'ü', char(129));
			replace(mystring.begin(), mystring.end(), 'ö', char(148));
			replace(mystring.begin(), mystring.end(), 'Ö', char(153));


			if (i == 0)
			{
				array[j].germanWord = arrayC[j].germanWord = mystring;
			}
			if (i == 1)
			{
				array[j].partSpeech = arrayC[j].partSpeech = mystring;
			}
			if (i == 2)
			{
				array[j].englishMeaning = arrayC[j].englishMeaning = mystring;
			}
		}
	}

}
