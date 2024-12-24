#include "cs.h"
#include "logs.h"
#include "line.h"

#include <iostream>
#include <fstream>

using namespace std;

class Line;
class Pipeline;

int Line::MaxIDCS = 0;

CS::CS()
{
    CSID = Line::MaxIDCS++;
}

istream& operator >> (istream& in, unordered_map<int, CS>& css) {
    CS cs;

    cs.CSName = read_input<string>("Enter name CS: ");
    cs.NumberOfWorkshops = read_input<int>("Enter number of workshops: ", 0);
    cs.WorkshopsInWork = read_input<int>("Enter workshops in work: ", 0, cs.NumberOfWorkshops);
    cs.Efficiency = read_input<int>("Enter efficiency (0-100): ", 0, 100);

    css.insert({ cs.GetID(), cs });
    return in;
}

ostream& operator << (ostream& out, const unordered_map<int, CS>& css)
{
    if (css.size() == 0) { cout << "you have not cs\n"; return out; }
    for (const auto& cs : css) {
        out << cs.second;
    }
    return out;
};

ostream& operator << (ostream& out, const CS& cs)
{
    out << "\nID: " << cs.CSID
        << "\nCS name: " << cs.CSName
        << "\nCS number of workshops: " << cs.NumberOfWorkshops
        << "\nCS workshops in work: " << cs.WorkshopsInWork
        << "\nThe CS attribute: " << cs.Efficiency << endl;
    return out;
};

void change_workshops_in_work(CS& cs, int& new_WorkshopsInWork)
{
    if (new_WorkshopsInWork <= cs.NumberOfWorkshops)
    {
        cs.WorkshopsInWork = new_WorkshopsInWork;
        return;
    }
    else
    {
        cout << "Error CS id=" << cs.CSID << " have " << cs.NumberOfWorkshops << " workshops";
        return;
    }
}
ofstream& operator << (ofstream& out, const unordered_map<int, CS>& css)
{
    for (const auto& cs : css) {
        out << cs.second;
    }
    return out;
}

ofstream& operator << (ofstream& out, const CS& cs)
{
    out << "@cs@" << "\n"
        << cs.CSName << "\n"
        << cs.NumberOfWorkshops << "\n"
        << cs.WorkshopsInWork << "\n"
        << cs.Efficiency << "\n";
    return out;
};


ifstream& operator >> (ifstream& in, unordered_map<int, CS>& css) {
    string line;
    while (getline(in, line)) {
        if (line == "@cs@") {
            CS cs;

            if (!getline(in, cs.CSName) || cs.CSName.empty()) {
                cout << "Error pipe in file\n";
                continue;
            }

            if (!(in >> cs.NumberOfWorkshops) || cs.NumberOfWorkshops <= 0) {
                cout << "Error pipe in file\n";
                in.clear(); in.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            if (!(in >> cs.WorkshopsInWork) || cs.WorkshopsInWork < 0 || cs.WorkshopsInWork > cs.NumberOfWorkshops) {
                cout << "Error pipe in file\n";
                in.clear(); in.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            if (!(in >> cs.Efficiency) || cs.Efficiency < 0 || cs.Efficiency > 100) {
                cout << "Error pipe in file\n";
                in.clear(); in.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            css.insert({ cs.GetID(), cs });
            //cerr << "2\n" << cs.CSName << endl << cs.NumberOfWorkshops << endl << cs.WorkshopsInWork << endl << cs.Efficiency << endl;
        }
    }
    return in;
}

void filter_cs_by_name(unordered_map<int, CS>& cs)
{
    string name = read_input<string>("Enter the name of the cs to filter: ");
    vector<int> ids;
    bool flag = false;


    for (const auto& p : cs) {
        if (p.second.CSName.find(name) != string::npos) {
            cout << p.second;
            ids.push_back(p.second.CSID);
            flag = true;
        }
    }

    if (!flag) { cout << "You don't have cs with name: " << name << endl; return; }

    int ch = read_input<int>("0 - menu:\n1 - chenge cs\n", 0, 1);

    if (ch == 0) { return; }
    ch = read_input<int>("Enter number of workshops in work ", 0);

    for (const auto& id : ids)
    {
        change_workshops_in_work(cs[id], ch);
    }
}

void filter_cs_by_work_percentage(unordered_map<int, CS>& cs)
{
    int percentage = read_input<int>("Enter the work percentage to filter (0-100): ", 0, 100);
    int choice = read_input<int>("Choose option: 1 - More, 2 - Less, 3 - =", 1, 3);
    bool flag = false;

    vector<int> ids;
    for (const auto& p : cs) {
        int current_percentage = (p.second.WorkshopsInWork * 100) / p.second.NumberOfWorkshops;
        if ((choice == 1 && current_percentage > percentage) ||
            (choice == 2 && current_percentage < percentage) ||
            (choice == 3 && current_percentage == percentage))
        {
            cout << p.second;
            ids.push_back(p.second.CSID);
        }
    }

    if (!flag)
    {
        if (choice == 1) { cout << "You don't have cs with % of working > then: " << percentage << endl; }
        else if (choice == 2) { cout << "You don't have cs with % of working < then: " << percentage << endl; }
        else { cout << "You don't have cs with % of working = " << percentage << endl; }
        return;
    }


    int ch = read_input<int>("0 - menu\n1 - edit CS\n", 0, 1);

    if (ch == 0) return;

    ch = read_input<int>("Enter number of workshops in work ", 0);

    for (const auto& id : ids)
    {
        change_workshops_in_work(cs[id], ch);
    }
}