// ---------------------------------------------------------------------------
// Name: Dakota Bell
// Course-Section: CS255-01
// Assignment: Project #1
// Date due: 08/31/2023
// Description: ADD A DESCRIPTION a short description of the program’s purpose
// should go here. The description may take more than one line.
// ---------------------------------------------------------------------------

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

#include "tornInfo.h"

using namespace std;

// FUNCTIONS I HAVE ALREADY UPDATED FOR YOU
void initializeArray(tornInfo[], const int);
int loadProducts(tornInfo[], string);

// FUNCTIONS WHICH DON'T NEED TO BE UPDATED
int menu();

/* OLD FUNCTION DEFINITIONS WHICH NEED TO BE UPDATED
void displayAll(int[], string[], string[], double[], int[], const int);
void numByYear(int[], const int, int&);
int vicByYear(int[], int[], const int);
void tornByCounty(int[], string[], string[], double[], int[], const int, int&);
*/
void displayAll(tornInfo[], int);
void numByYear(tornInfo[], int, int&);
int vicByYear(tornInfo[], int, int&);
void tornByCounty(tornInfo[], int, int&);

//NEW FUNCTION YOU NEED TO WRITE for **NEW** Option 6
//Put the new function declaration HERE
void avgWindByYear(tornInfo[], int, int&, int);


int main()
{
    cout<<fixed<<setprecision(2);
    const int maxSize = 100;
    
    tornInfo tnds[maxSize];
    
    int numTorn=0;
    int choice;
    

    initializeArray(tnds, maxSize);

    string filename;
    cout<<"Enter the filename of your tornado database."<<endl;
    getline(cin, filename);
    numTorn = loadProducts(tnds, filename);

    int result;
    choice = menu();
    while(choice != 7)
    {
        if(choice == 1)
        {
        	result = numTorn;  
        }
        else if(choice == 2)
        {
        	//1.*** UPDATE THIS FUNCTION CALL
        	displayAll(tnds, numTorn);
          result = numTorn;
        }
        else if(choice == 3)
        {
        	//2.*** UPDATE THIS FUNCTION CALL
        	numByYear(tnds, numTorn, result);
        }
        else if(choice == 4)
        {
        	//3.*** UPDATE THIS FUNCTION CALL
        	result = vicByYear(tnds, numTorn, result);
        }
        else if(choice == 5)
        {
        	//4.*** UPDATE THIS FUNCTION CALL
        	tornByCounty(tnds, numTorn, result);
        }
        else if(choice == 6)
        {
        	//5.*** FUNCTION CALL for NEW FUNCTION (**NEW** Option 6)
        	//Will need more than just a single line of code.
        	int choice;
        	cout << "Enter the year you want to know the average wind speed for: ";
			cin >> choice;
			avgWindByYear(tnds, numTorn, result, choice);
        }
        
        cout<<"Result: "<<result<<endl;
        choice = menu();
    }
    cout<<"Goodbye.  Have a nice day!"<<endl;
}

//---------------------------------------------------------------------------
/* initializeArray() initializes the year array to all default values, -1.
*     Because we have arrays that have a maxSize and we don't expect to actually
*     have as many items as maxSize, most of our arrays will be empty.  Having
*     a sentinal value for empty slots COULD help us when processing data.
*     INCOMING DATA: an int array, a const int representing maxSize
*     OUTGOING DATA: nothing returned, updated array to default values*/
void initializeArray(tornInfo tnds[], const int mS)
{
    for(int i=0; i<mS; i++){
        tnds[i].year = -1;
    }
}

//---------------------------------------------------------------------------
/* loadProducts() loads the information about our products into an array of
*	 struct type.
*     INCOMING DATA: array of tornInfo, and a filename string
*     OUTGOING DATA: integer value number of tornadoes */
int loadProducts(tornInfo tnds[], string fN)
{
    ifstream file(fN);
    string line;
    int count = 0;
    int next_year, next_victims;
    string next_county, next_category, temp;
    double next_maxwind;
    while(getline(file,line)){
        int pos = 0;
        //parse the next line
        pos = line.find(", ");
        temp = line.substr(0, pos);
        next_year = stoi(temp);
        
        line.erase(0, pos+2);
        pos = line.find(", ");
        next_county = line.substr(0, pos);
        
        line.erase(0, pos+2);
        pos = line.find(", ");
        next_category = line.substr(0, pos);
        
        line.erase(0, pos+2);
        pos = line.find(", ");
        temp = line.substr(0, pos);
        next_maxwind = stod(temp);
        
        line.erase(0, pos+2);
        next_victims = stoi(line);
        
        tnds[count].year = next_year;
        tnds[count].county = next_county;
        tnds[count].category = next_category;
        tnds[count].wind = next_maxwind;
        tnds[count].victims = next_victims;
        
        count++;
    }
    file.close();
    return count;
}

//---------------------------------------------------------------------------
/* menu() Prints menu option information to the user and returns selection.
*     Displays a numbered menu options 1 - 6: calc ttl number of tornadoes, 
*	 display all tornadoes in db, calculate num for a year, calculate num 
*	 victims for a year, display all tornado information for a specific county,
*	 and quit, respectively.
*     INCOMING DATA: none
*     OUTGOING DATA: integer choice selected*/
int menu()
{
    int choice;
    cout<<endl;
    cout<<"Select an Option:"<<endl;
    cout<<"\t 1. Calculate number of tornadoes in the database."<<endl;
    cout<<"\t 2. Display all tornado data."<<endl;
    cout<<"\t 3. Calculate the number of tornadoes for a certain year."<<endl;
    cout<<"\t 4. Calculate the number of victims of tornadoes for a year."<<endl;
    cout<<"\t 5. Display all tornado information for a specific county."<<endl;
    cout<<"\t 6. Display average wind speed of tornadoes in a year."<<endl;
    cout<<"\t 7. Quit"<<endl;

    cin>>choice;
    return choice;
}

/*
    **PLACE OTHER FUNCTION IMPLEMENTATIONS BELOW
    **There are four (4) functions which need to be updated.  
    **Follow the example of the provided functions and code given in class.
    **YOUR FUNCTION IMPLEMENTATIONS GO BELOW
*/

//---------------------------------------------------------------------------
/* displayAllFunction displays the data in an appropriately formatted
*	 manner for all the tornado data, one tornado per numbered line.
*     INCOMING DATA: tnds array and the number of tornadoes in the database
*     OUTGOING DATA: none*/
void displayAll(tornInfo tnds[], int numTorn)
{
	cout << "Number \t Year \t\t County \t Category \t Max Wind \t Victims " << endl;
	for(int i = 0; i < numTorn; i++)
	{
		cout << setw(2) << i + 1 << ":" << setw(10);
		cout << tnds[i].year << setw(18); // set width so that there is uniform space between the all information
		cout << tnds[i].county << setw(15);
		cout << tnds[i].category << setw(18);
		cout << tnds[i].wind << setw(15);
		cout << tnds[i].victims;
		cout << endl;	
	}		
}

//---------------------------------------------------------------------------
/* numByYear() function asks the user for a specific year, and accepts that 
*	 input from the user.  Function uses that input to process that database
*	 and calculate the total number of tornadoes for the given year.
*     INCOMING DATA: tnds array, number of tornadoes in db, PBR int result
*     OUTGOING DATA: int result*/
void numByYear(tornInfo tnds[], int numTorn, int& result)
{
	int choice = 0;
	result = 0; /* assign result the value of 0 so the math is always correct when running this function 
				   otherwise the program may use the result from a different and ADD to that previous 
				   result making the result incorrect*/
	cout << "Enter the year you want to know the number of tornadoes from: ";
	cin >> choice;
	
	for(int i = 0; i < numTorn; i++) // runs the program the same amount of times that numTorn is assigned
	{
		if(tnds[i].year == choice)// if the year value is equal to the user's choice then 
		{					// incrament the result (pass-by-reference)
			result++;
		}
	}
	
	cout << "There were " << result << " number of tornadoes in " << choice << endl;	
}

//---------------------------------------------------------------------------
/* vicByYear() function asks the user for a specific year, and accepts that 
*	 input from the user.  Function uses that input to process that database
*	 and calculate the total number of victims across all tornadoes 
*	 for the given year.
*     INCOMING DATA: tnds array, number of tornadoes, PBR int result
*     OUTGOING DATA: int result*/
int vicByYear(tornInfo tnds[], int numTorn, int& result)
{
	result = 0;/* assign result the value of 0 so the math is always correct when running this function 
				   otherwise the program may use the result from a different and ADD to that previous 
				   result making the result incorrect*/
	int choice = 0;
	
	cout << "Enter the year you want to know the amount of victims that passed from that year's torando: ";
	cin >> choice;
	for(int i = 0; i < numTorn; i++) // runs program the same amount of time there are tornadoes
	{
		if(tnds[i].year == choice) // checks if the year value is equal to the choice the user enters
		{
			result += tnds[i].victims; // add-assign the number of victims to result
		}
	}
	
	return result;	
}

//---------------------------------------------------------------------------
/* tornByCount() function asks the user for a specific county, and accepts that 
*	 input from the user.  Function uses that input to process the database
*	 and display ALL tornado data for that specific county in a numbered list.
*     INCOMING DATA: tnds array, number of tornadoes, PBR result
*     OUTGOING DATA: int result*/
void tornByCounty(tornInfo tnds[], int numTorn, int& result)
{
	string name; // create ID for user to enter the name of a county
	result = 0; /* assign result the value of 0 so the math is always correct when running this function 
				   otherwise the program may use the result from a different function and ADD to that 
				   previous result, making the final result incorrect*/
	cout << "Enter the name of the county to see the number of tornadoes they have total: ";
	cin >> name;
	cout << endl;
	cout << "Number \t Year \t\t County \t Category \t Max Wind \t Victims " << endl;
	for(int i = 0; i < numTorn; i++) // runs program the same amount of time there are tornadoes
	{
		//cout << setw(2) << i + 1 << ". \t";
		if(tnds[i].county == name) // checks how many time that county shows up in the .txt file
		{
			cout << setw(2) << result + 1 << ":" << setw(10);
			cout << tnds[i].year << setw(18); // set width so that there is uniform space between the all information
			cout << tnds[i].county << setw(15);
			cout << tnds[i].category << setw(18);
			cout << tnds[i].wind << setw(15);
			cout << tnds[i].victims;
			cout << endl;
			result++;
		}
	}
	cout << endl;
}
/**WRITE (Implement) THE NECESSARY NEW FUNCTION HERE**/

//---------------------------------------------------------------------------
/* maxWindByYear() will get the user choice from main and get a PBC of the choice 
*				   and then will get the number of times the function gets a 
*				   windspeed from the tnds array and divide that by the sum
* 				   of all the max wind speeds in the year the user enters
*     INCOMING DATA: tnds array, number of tornadoes, PBR result
*     OUTGOING DATA: none */
void avgWindByYear(tornInfo tnds[], int numTorn, int& result, int choice)
{
	result = 0;
	double temp = 0; // ID to hold the sum of the value of the winds
	double avgWind = 0; // ID for the average wind
	int counter = 0; // ID for how many times the max wind is added to the temp var
	for(int i = 0; i < numTorn; i++) // while there are tornadoes in the file this will run
	{
		if(tnds[i].year == choice)
		{
			temp += tnds[i].wind;
			counter++; // counts how many times the tnds[i].year matches the user entry
			result++; // does the same thing counter does and returns the result PBR
		}
	}
	avgWind = temp / counter; /* gets the average of the wind by using the sum from
							  	 */ 
	cout << "Average wind speed for the year " << choice << ": " << avgWind << " mph" << endl;	
}