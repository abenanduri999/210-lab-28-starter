#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include <vector>
#include <algorithm>
#include <numeric>
#include <random>
#include "Goat.h"
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25;

int select_goat(list<Goat> trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string [], string []);
void display_trip(list<Goat> trip);
void reverse_goat(list<Goat> &trip); 
void clear_goat(list<Goat> &trip); 
void shuffle_goat(list<Goat> &trip); 
void sumAge_goat(list<Goat> trip); 
void merge_goat(list<Goat> &trip);
int main_menu();

int main() {
    srand(time(0));
    bool again;

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

    // create & populate a trip of Goats using std::list of random size 8-15
    int tripSize = rand() % 8 + 8;
    list<Goat> trip;
    int age;
    string name, color;
    for (int i = 0; i < tripSize; i++) {
        age = rand() % MAX_AGE;  // defined in Goat.h
        name = names[rand() % SZ_NAMES];
        color = colors[rand() % SZ_COLORS];
        Goat tmp(name, age, color);
        trip.push_back(tmp);
    }
    
    // Goat Manager 3001 Engine
    int sel = main_menu();
    while (sel != 12) {
        switch (sel) {
            case 1:
                cout << "Adding a goat.\n";
                add_goat(trip, names, colors);
                break;
            case 2:    
                cout << "Removing a goat.\n";
                delete_goat(trip);
                break;
            case 3:    
                cout << "Displaying goat data.\n";
                display_trip(trip);
                break;
            case 4: 
                cout<< "List of goats have been reversed.\n"; 
                reverse_goat(trip); 
                break;
            case 5: 
                cout <<"Goats list has been cleared.\n";
                clear_goat(trip); 
                break;
            case 6: 
                cout<<"Goats have been shuffled.\n"; 
                shuffle_goat(trip);
                break;
            case 7: 
                sumAge_goat(trip); 
                break;
            case 8: 
                cout<<"The new merged list is:\n";
                merge_goat(trip); 
                break; 
            default:
                cout << "Invalid selection.\n";
                break;
        }
        sel = main_menu();
    }
    

    return 0;
}

int main_menu() {
    cout << "*** GOAT MANAGER 3001 ***\n";
    cout << "[1] Add a goat\n";
    cout << "[2] Delete a goat\n";
    cout << "[3] List goats\n";
    cout << "[4] Reverse goats\n"; 
    cout << "[5] Clear goats\n"; 
    cout << "[6] Shuffle goats\n";
    cout << "[7] Sum of all the ages\n";
    cout << "[8] Merge list with another.\n";
    cout << "[9] ";
    cout << "[10] ";
    cout << "[11] ";
    cout << "[12] Quit\n";
    cout << "Choice --> ";
    int choice;
    cin >> choice;
    while (choice < 1 || choice > 12) {
        cout << "Invalid, again --> ";
        cin >> choice;
    }
    return choice;
}

void delete_goat(list<Goat> &trip) {
    cout << "DELETE A GOAT\n";
    int index = select_goat(trip);
    auto it = trip.begin();
    advance(it, index-1);
    trip.erase(it);
    cout << "Goat deleted. New trip size: " << trip.size() << endl;
}

void add_goat(list<Goat> &trip, string nms[], string cls[]) {
    cout << "ADD A GOAT\n";
    int age = rand() % MAX_AGE;
    string nm = nms[rand() % SZ_NAMES];
    string cl = cls[rand() % SZ_COLORS];
    Goat tmp(nm, age, cl);
    trip.push_back(tmp);
    cout << "Goat added. New trip size: " << trip.size() << endl;
}

void display_trip(list<Goat> trp) {
    int i = 1;
    for (auto gt: trp)
        cout << "\t" 
             << "[" << i++ << "] "
             << gt.get_name() 
             << " (" << gt.get_age() 
             << ", " << gt.get_color() << ")\n";
}

int select_goat(list<Goat> trp) {
    int input;
    cout << "Make a selection:\n";
    display_trip(trp);
    cout << "Choice --> ";
    cin >> input;
    while (input < 1 || input > trp.size()) {
        cout << "Invalid choice, again --> ";
        cin >> input;
    }
    return input;
}

void reverse_goat(list<Goat> &trip)
{
    reverse(trip.begin(), trip.end()); 
    display_trip(trip); 
}

void clear_goat(list<Goat> &trip)
{
    trip.clear(); 
}

void shuffle_goat(list<Goat> &trip)
{
    vector<Goat> temp;          //couldnt shuffle a list so copied list into vector
    for(auto element : trip) //shuffled vector and copied it back to list
    {
        temp.push_back(element); 
    }
    shuffle(temp.begin(), temp.end(), default_random_engine()); 

    clear_goat(trip);
    
    for(auto tmp : temp)
    {
        trip.push_back(tmp);
    }
    display_trip(trip); 
   
}

void sumAge_goat(list<Goat> trip)
{
    vector<int> temp; 
    for (auto tmp : trip)
    {
        temp.push_back(tmp.get_age());
    }
    int sum = accumulate(temp.begin(), temp.end(), 0); 
    cout<<"The sum of all ages is: "<<sum<<endl; 
    
}

void merge_goat(list<Goat> &trip)
{
    Goat goat1("Bob", 5, "cyan"); 
    Goat goat2("Pavel", 8, "viridian"); 
    list<Goat> newTrip; 
    newTrip.push_back(goat1); 
    newTrip.push_back(goat2); 

    list<Goat> mergedList(trip.size() + newTrip.size());
    merge(trip.begin(), trip.end(), newTrip.begin(), newTrip.end(), mergedList.begin()); 
    display_trip(mergedList); 
}