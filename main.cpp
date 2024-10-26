/***************************************************

COMSC 210 | Lab 23 | Skylar Robinson | IDE Used: Eclipse

*****************************************************/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include "Goat.h"
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25, MAX_AGE = 20;

int select_goat(list<Goat>);
void delete_goat(list<Goat> &);
void add_goat(list<Goat>&, string [], string []);
void display_trip(list<Goat>);
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

    list<Goat> trip;
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

int select_goat(list<Goat> trip) {
	int choice;
	cout << "Select a goat by number:\n";
	display_trip(trip);
	cin >> choice;
	return choice;
}

void delete_goat(list<Goat> &trip) {
	int toDel = select_goat(trip);
	auto current = trip.begin();
	for (int i = 1; i < toDel; i++)
		current++;
	trip.erase(current);
}

void add_goat(list<Goat> &trip, string n[] , string c[]) {
	Goat temp;
	temp.set_name(n[rand() % SZ_NAMES]);
	temp.set_color(c[rand() % SZ_COLORS]);
	temp.set_age(rand() % (MAX_AGE + 1));
	trip.push_back(temp);
}

void display_trip(list<Goat> trip) {
	int count = 1;
	if (trip.empty()) {
		cout << "List is empty.\n";
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
		cout << "Invalid choice, input a number 1-4: ";
		cin >> choice;
	}
	return choice;
}
