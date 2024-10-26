/***************************************************

COMSC 210 | Lab 24 | Skylar Robinson | IDE Used: Eclipse

*****************************************************/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <set>
#include "Goat.h"
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25, MAX_AGE = 20;

int select_goat(set<Goat>);
void delete_goat(set<Goat> &);
void add_goat(set<Goat>&, string [], string []);
void display_trip(set<Goat>);
int main_menu();

int main() {
    srand(time(0));

    // read & populate arrays for names and colors
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++]);
    fin.close();
    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++]);
    fin1.close();

    //menu loop
    set<Goat> trip;
    int choice;
    do {
    	choice = main_menu();
    	switch (choice) {
    	case 1: add_goat(trip, names, colors); break;
    	case 2: delete_goat(trip); break;
    	case 3: display_trip(trip); break;
    	default: break;
    	}

    } while (choice != 4);

    return 0;
}

int select_goat(set<Goat> trip) {
	int choice;
	display_trip(trip);
	cout << "\nSelect a goat by number: ";
	cin >> choice;
	while (choice < 1 || choice > trip.size()) {
		cout << "Invalid input, enter a number 1-" << trip.size() << ": ";
		cin >> choice;
	}
	return choice;
}

void delete_goat(set<Goat> &trip) {
	if (trip.empty()) {
		cout << "\nSet is empty.\n";
		return;
	}
	int toDel = select_goat(trip);
	auto current = trip.begin();
	for (int i = 1; i < toDel; i++)
		current++;
	trip.erase(current);
	cout << "Deleted goat #" << toDel << endl;
}

void add_goat(set<Goat> &trip, string n[] , string c[]) {
	Goat temp(n[rand() % SZ_NAMES], rand() % (MAX_AGE + 1), c[rand() % SZ_COLORS]);
	trip.insert(temp);
	cout << "Added Goat: " << temp.get_name() << " (" << temp.get_age()
	     << ", " << temp.get_color() << ")\n";
}

void display_trip(set<Goat> trip) {
	cout << "\nDisplaying Goats:\n";
	int count = 1;
	if (trip.empty()) {
		cout << "Set is empty.\n";
		return;
	}
	for (Goat g : trip){
		cout << "[" << count++ << "] "
			 << g.get_name() << " (" << g.get_age()
			 << ", " << g.get_color() << ")\n";
	}
}

int main_menu() {
	int choice;
	cout << "\n*** GOAT MANAGER 3001 ***\n"
		 << "[1] Add a goat\n"
		 << "[2] Delete a goat\n"
		 << "[3] List goats\n"
		 << "[4] Quit\n"
		 << "Choice --> ";
	cin >> choice;
	//input validation
	while (choice < 1 || choice > 4) {
		cout << "Invalid input, enter a number 1-4: ";
		cin >> choice;
	}
	return choice;
}
