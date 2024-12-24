#pragma once

#include <string>
#include <iostream>
#include <unordered_map>

#include "line.h"

using namespace std;

class Line;

class CS
{
private:
    int CSID = 0;
    string CSName = "None";
    int NumberOfWorkshops = -1;
    int WorkshopsInWork = -1;
    short int Efficiency = -1;
public:

    CS();
    int GetID() const { return CSID; };

    void create_cs(unordered_map<int, CS>& css) { cin >> css; };
    friend void change_workshops_in_work(CS& cs, int& new_WorkshopsInWork);
    friend istream& operator >> (istream& in, unordered_map<int, CS>& css);
    friend ostream& operator << (ostream& out, const CS& cs);
    friend ofstream& operator << (ofstream& out, const CS& cs);
    friend ifstream& operator >> (ifstream& in, unordered_map<int, CS>& css);

    friend void filter_cs_by_name(unordered_map<int, CS>& cs);
    friend void filter_cs_by_work_percentage(unordered_map<int, CS>& cs);
    friend class Line;
    friend class Pipeline;
};

ostream& operator << (ostream& out, const unordered_map<int, CS>& css);
ofstream& operator << (ofstream& out, const unordered_map<int, CS>& css);