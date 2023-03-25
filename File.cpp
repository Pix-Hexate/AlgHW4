#include <string>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <sstream>
#include <iomanip>  
#include <set>
using namespace std;

// NOTE
//
// Please try to follow formatting as much as possible, the program has some degree of error detection
// but was not designed to be foolproof. If you enter invalid information you'll probably break it
//
// Specifically, the preference lists do not have a checker, so if you enter 1, 1, 1, or a negative number, 
// or a number higher than total number of people, it will probably brick the algorithm

int main() {
	int num_people;
	string boy_long_string;
	string girl_long_string;
	vector<string> boy_names;
	vector<string> girl_names;

	//Getting boy/girl pairs
	cout << "How many boys/girl pairs to be matched : ";
	cin >> num_people;
	cin.ignore();
	//getting boy names
	cout << "Please input the list of boy names, in this format 'Jack, James, Will'" << endl << "Do not include the ''" << endl << "Boy Name List : ";
	getline(cin, boy_long_string);
	cout << endl;
	cin.clear();
	//getting girl names
	cout << "Please input the list of girl names, in this format 'Jill, Mary, May'" << endl << "Do not include the ''" << endl << "Girl Name List : ";
	getline(cin, girl_long_string);
	cout << endl;

	//------------------------Section 1------------------------------
	//Put long strings into vectors

	stringstream boys(boy_long_string);
	stringstream girls(girl_long_string);
	string substr; //Substring method as in last HW used to get substrings

	while (boys.good()) { //Sticking the long input into vectors
		while (boys.peek() == ' ') { //This ignores the spaces between 'name, name'
			boys.get();
		}
		getline(boys, substr, ','); //Grab the single boy's name
		boy_names.push_back(substr); //and stick it into boy_names vector
	}
	while (girls.good()) { //Same as above but for girls
		while (girls.peek() == ' ') {
			girls.get();
		}
		getline(girls, substr, ',');
		girl_names.push_back(substr);
	}

	//Test for name vectors
	/*
	for (int i = 0; i < boy_names.size(); i++) {
		cout << boy_names[i] << " ";
	}
	cout << endl;
	for (int i = 0; i < girl_names.size(); i++) {
		cout << girl_names[i] << " ";
	}
	*/

	//Error checking
	//check of matching number of names / equal to num_people
	if ((boy_names.size() != girl_names.size()) || (boy_names.size() != num_people)) {
		cout << "There was some error with the number of boy/girl names, please check inputs";
		return -1;
	}

	//----------------------------------Section 2---------------------------------------
	//Inserting preference lists
	//Note : Having the user insert names as preference instead of numbers was considered. Then I realized the user probably
	//Does not want to type 2(n^2) names and would rather type 2(n^2) numbers

	cout << "Please insert preference lists. Starting with the boys." << endl;
	cout << "An example input for Jack / Jill, Mary would be '1, 2' if he prefered Jill over Mary" << endl;
	cout << "Starting with the boys' preferences, the girls in order are :" << endl;

	for (int i = 0; i < girl_names.size(); i++) { //Print out girls list in their order, relative to numbers
		cout << girl_names[i] << ", ";
	}
	cout << endl << endl;

	string str_pref_list_temp; //We take raw user input as a string
	stringstream pref_list_ss; // and stick it into a string stream for organization into a vector
	vector <int> int_pref_list_temp; //This is the vector to store a single person's preference list
	vector <vector<int>> boy_pref_list; //This is the vector of vectors to store the entire gender's preference list
	vector <vector<int>> girl_pref_list;

	for (int i = 0; i < boy_names.size(); i++) { //For each boy we need to make their preference list
		int_pref_list_temp.clear(); //Clear data from before, if any
		pref_list_ss.clear();

		cout << "Please enter " << boy_names[i] << "'s preference list : ";
		getline(cin, str_pref_list_temp); //Get raw input
		pref_list_ss << str_pref_list_temp; //Put raw input into strema

		while (pref_list_ss.good()) { //Sticking the long input into vectors, copied from above
			while (pref_list_ss.peek() == ' ') { //Skip spaces
				pref_list_ss.get();
			}
			getline(pref_list_ss, substr, ','); //Get the value and store into temp int vector
			int_pref_list_temp.push_back(stoi(substr) - 1); //This -1 is to make it consistent with vectors (0 to n-1)
		}

		/* Test to see if SS list appending is working

		for (int i = 0; i < int_pref_list_temp.size(); i++) {
			cout << int_pref_list_temp[i] << " ";
		}
		*/

		boy_pref_list.push_back(int_pref_list_temp); //Finally insert the temp int vector into the vector of vectors

	}

	//-------------------------------------Section 2 (Girls)----------------------------------------
	//Everything here is a copy of above but slightly modified to the girl's list
	cout << endl << endl << "Now inserting preference lists for the girls" << endl;
	cout << "The boys in order are : " << endl;

	for (int i = 0; i < boy_names.size(); i++) {
		cout << boy_names[i] << ", ";
	}

	cout << endl << endl;

	for (int i = 0; i < girl_names.size(); i++) {
		int_pref_list_temp.clear();
		pref_list_ss.clear();

		cout << "Please enter " << girl_names[i] << "'s preference list : ";
		getline(cin, str_pref_list_temp);
		pref_list_ss << str_pref_list_temp;

		while (pref_list_ss.good()) {
			while (pref_list_ss.peek() == ' ') {
				pref_list_ss.get();
			}
			getline(pref_list_ss, substr, ',');
			int_pref_list_temp.push_back(stoi(substr) - 1);
		}

		girl_pref_list.push_back(int_pref_list_temp);

	}


	//---------------------------------------Section 3----------------------------------------
	// Outputting preference Graphs for boys

	cout << "Outputting Graph for Boy Preferences" << endl << endl; //This is simply a bunch of formatting cout statments
	cout << setw(15) << left << "Pref Rank";
	for (int i = 0; i < girl_names.size(); i++) {
		cout << setw(15) << left << i + 1;
	}

	cout << endl;
	for (int i = 0; i < girl_names.size(); i++) {
		cout << "----------------";
	}
	cout << endl;

	for (int i = 0; i < boy_names.size(); i++) {
		cout << setw(14) << left;
		cout << boy_names[i] << setw(1) << "|" << setw(15);

		for (int j = 0; j < boy_pref_list[i].size(); j++) {
			cout << setw(15) << left << girl_names[boy_pref_list[i][j]];
		}
		cout << endl;
	}

	cout << endl << endl;

	//-------------------------------------Section 3 (girls)-----------------------------------------
	//Outputting graphs for girls now

	cout << "Outputting Graph for Girl Preferences" << endl << endl;
	cout << setw(15) << left << "Pref Rank";
	for (int i = 0; i < boy_names.size(); i++) {
		cout << setw(15) << left << i + 1;
	}

	cout << endl;
	for (int i = 0; i < boy_names.size(); i++) {
		cout << "----------------";
	}
	cout << endl;

	for (int i = 0; i < girl_names.size(); i++) {
		cout << setw(14) << left;
		cout << girl_names[i] << setw(1) << "|" << setw(15);

		for (int j = 0; j < girl_pref_list[i].size(); j++) {
			cout << setw(15) << left << boy_names[girl_pref_list[i][j]];
		}
		cout << endl;
	}


	//--------------------------------Section 4------------------------------------------
	//Gale-Shalpey Algorithm here

	vector<int> boys_to_match;
	vector<int> girl_matches;
	int curr_boy = 0;
	int curr_boy_placement = 0;
	int contestant = 0;
	int contestant_placement = 0;
	int curr_girl = 0;
	int counter = 0;
	bool matched = false;
	//Bunch of vars to be used

	for (int i = 0; i < num_people; i++) { boys_to_match.push_back(i); } //This creates a list of all boys to be matched
	for (int i = 0; i < num_people; i++) { girl_matches.push_back(-1); } //List of girls' matches, starting at -1 to mean no match yet


	while (boys_to_match.size() != 0) { //This loops until there are no more matches to be done
		curr_boy = boys_to_match[0]; //This sets the current boy we are trying to match, it does not matter what order we do them in so I just pick the first one
		matched = false; //Loop until this match is done
		counter = 0; //This counter is used to see what 

		while (matched == false) {

			if (girl_matches[boy_pref_list[curr_boy][counter]] == -1) { //boy_pref_list[curr_boy][counter] = Girl number; This auto matches if girl is unmatched
				girl_matches[boy_pref_list[curr_boy][counter]] = curr_boy; //Auto match girl to boy
				boy_pref_list[curr_boy].erase(boy_pref_list[curr_boy].begin()); //This removes the girl from the boy's preference list so if viewed later, the girl won't be re-looked at 
				matched = true;
			}
			else {
				contestant = girl_matches[boy_pref_list[curr_boy][counter]]; //The currently matched partner to compare to
				curr_girl = boy_pref_list[curr_boy][counter]; //This grabs the actual "girl" value, rather than the girl's position on the boy's preference list
				curr_boy_placement = distance(girl_pref_list[curr_girl].begin(), find(girl_pref_list[curr_girl].begin(), girl_pref_list[curr_girl].end(), curr_boy)); //These two long statements are basically figuring out how much
				contestant_placement = distance(girl_pref_list[curr_girl].begin(), find(girl_pref_list[curr_girl].begin(), girl_pref_list[curr_girl].end(), contestant)); // the girl likes each boy
				//By seeing the placement of the boy's value in her list, lower is better
				//The find function is for finding the iterator of the value, the distance function is required to convert that iterator into an int

				if (curr_boy_placement < contestant_placement) { //If current boy is a lower placement (better liked) than girl's current partner
					girl_matches[boy_pref_list[curr_boy][counter]] = curr_boy; //Match girl to current boy
					boys_to_match.push_back(contestant); //Re-enter the boy that was unmatched to be matched again
					matched = true;
					boy_pref_list[curr_boy].erase(boy_pref_list[curr_boy].begin()); //This removes the girl from the boy's preference list so if viewed later, the girl won't be re-looked at (again)

				}
				else {
					counter = counter + 1; //If the girl likes her current match more, then we move on to the girl the boy likes next most
				}

				//boy_pref_list[curr_boy].erase(boy_pref_list[curr_boy].begin()); //This removes the girl from the boy's preference list so if viewed later, the girl won't be re-looked at (again)
				//This is here because regardless of match or not, it has failed so it can never succeed again
				//Never mind this is wrong, this belongs up in the if statement
				//Why is this in the if statement but not in the else statement?
			}

		}
		boys_to_match.erase(boys_to_match.begin()); //Remove the boy that was just matched from list


	} //And then this goes until all matched

	//--------------------------------------------------Section 5----------------------------------------------
	//output stable pairings

	cout << endl << "Stable pairing are :" << endl;
	for (int i = 0; i < num_people; i++) {
		cout << girl_names[i] << " and " << boy_names[girl_matches[i]] << endl;
	}

}
