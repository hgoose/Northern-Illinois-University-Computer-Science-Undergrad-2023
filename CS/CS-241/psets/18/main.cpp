//
//  main.cpp
//  
//
//  Created by Kurt McMahon on 11/4/23.
//

#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "player.h"
#include "hitter.h"
#include "pitcher.h"

using std::cout;
using std::endl;
using std::getline;
using std::ifstream;
using std::left;
using std::right;
using std::setw;
using std::sort;
using std::stoi;
using std::string;
using std::vector;

void read_hitters(const string&, vector<player*>&);
void read_pitchers(const string&, vector<player*>&);
void print_hitters(const vector<player*>&);
void print_pitchers(const vector<player*>&);

int main()
{
    vector<player*> roster;
    
    read_hitters("hitters.txt", roster);
    read_pitchers("pitchers.txt", roster);
    
    sort(roster.begin(), roster.end(), [](player* a, player* b) {
        return a->get_number() < b->get_number();
    });
    
    cout << "2023 White Sox Roster\n\n";
    
    cout << left << setw(6) << '#' << setw(24) << "NAME"
         << right << setw(3) << 'H' << setw(7) << "AB"
         << setw(11) << "AVG\n\n";
    
    print_hitters(roster);

    cout << endl;

    cout << left << setw(6) << '#' << setw(24) << "NAME"
         << right << setw(3) << "ER" << setw(7) << "IP"
         << setw(11) << "ERA\n\n";

    print_pitchers(roster);
    
    for (size_t i = 0; i < roster.size(); i++)
    {
        delete roster[i];
    }

    return 0;
}

void read_hitters(const string& file_name, vector<player*>& roster)
{
    string name, str_number, str_hits, str_at_bats;
    int number, hits, at_bats;
    
    ifstream in_file(file_name);
    if (!in_file)
    {
        cout << "Unable to open " << file_name << endl;
        exit(1);
    }
    
    while (getline(in_file, name, ','))
    {
        getline(in_file, str_number, ',');
        getline(in_file, str_hits, ',');
        getline(in_file, str_at_bats);
        
        number = stoi(str_number);
        hits = stoi(str_hits);
        at_bats = stoi(str_at_bats);

        roster.push_back(new hitter(name, number, hits, at_bats));
    }
    
    in_file.close();
}

void read_pitchers(const string& file_name, vector<player*>& roster)
{
    string name, str_number, str_earned_runs, str_innings_pitched;
    int number, earned_runs, innings_pitched;
    
    ifstream in_file(file_name);
    if (!in_file)
    {
        cout << "Unable to open " << file_name << endl;
        exit(1);
    }
    
    while (getline(in_file, name, ','))
    {
        getline(in_file, str_number, ',');
        getline(in_file, str_earned_runs, ',');
        getline(in_file, str_innings_pitched);
        
        number = stoi(str_number);
        earned_runs = stoi(str_earned_runs);
        innings_pitched = stoi(str_innings_pitched);

        roster.push_back(new pitcher(name, number, earned_runs, innings_pitched));
    }
    
    in_file.close();
}
