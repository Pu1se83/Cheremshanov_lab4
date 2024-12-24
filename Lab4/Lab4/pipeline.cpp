#include "pipeline.h"
#include "logs.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


int Line::MaxIDPipe = 0;

Pipeline::Pipeline()
{
    PipeID = Line::MaxIDPipe++;
}


istream& operator >> (istream& in, unordered_map<int, Pipeline>& pipes) {
    Pipeline pipe;

    pipe.PipeName = read_input<string>("Enter name pipe: ");
    pipe.LengthOfPipe = read_input<int>("Enter length: ", 0);
    pipe.Diameter = read_input<int>("Enter diameter: ", 0);
    pipe.RepairIndicator = read_input<int>("Enter repair (0 - working, 1 - on repairing): ", 0, 1);

    pipes.insert({ pipe.GetID(), pipe });
    return in;
}


ostream& operator << (ostream& out, const unordered_map<int, Pipeline>& pipes)
{
    if (pipes.size() == 0) { cout << "you have not pipes\n"; return out; }
    for (const auto& pipe : pipes) {
        out << pipe.second;
    }
    return out;
};

ostream& operator << (ostream& out, const Pipeline& pipe)
{
    out << "\nID: " << pipe.PipeID
        << "\nPipe name: " << pipe.PipeName
        << "\nPipe length: " << pipe.LengthOfPipe
        << "\nPipe diameter: " << pipe.Diameter
        << "\nThe pipe attribute: " << pipe.RepairIndicator << endl;
    return out;
};

ofstream& operator << (ofstream& out, const unordered_map<int, Pipeline>& pipes)
{
    for (const auto& pipe : pipes) {
        out << pipe.second;
    }
    return out;
}

ofstream& operator << (ofstream& out, const Pipeline& pipe)
{
    out << "@pipeline@" << '\n'
        << pipe.PipeName << '\n'
        << pipe.LengthOfPipe << '\n'
        << pipe.Diameter << '\n'
        << pipe.RepairIndicator << '\n';
    return out;
};


ifstream& operator >> (ifstream& in, unordered_map<int, Pipeline>& pipes) {
    string line;
    while (getline(in, line)) {
        if (line == "@pipeline@") {
            Pipeline pipe;

            if (!getline(in, pipe.PipeName) || pipe.PipeName.empty()) {
                cout << "Error pipe in file\n";
                continue;
            }

            if (!(in >> pipe.LengthOfPipe) || pipe.LengthOfPipe < 0) {
                in.clear(); in.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Error pipe in file\n";
                continue;
            }

            if (!(in >> pipe.Diameter) || pipe.Diameter <= 0) {
                in.clear(); in.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Error pipe in file\n";
                continue;
            }

            if (!(in >> pipe.RepairIndicator) || (pipe.RepairIndicator != 0 && pipe.RepairIndicator != 1)) {
                in.clear(); in.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Error pipe in file\n";
                continue;
            }

            pipes.insert({ pipe.GetID(), pipe });
            //cerr << "1\n" << pipe.PipeName << endl << pipe.LengthOfPipe << endl << pipe.Diameter << endl << pipe.RepairIndicator << endl;
        }
    }
    return in;
}

void ChangeRepair(Pipeline& pipe, bool repair)
{
    pipe.RepairIndicator = repair;
}

void filter_pipes_by_name(unordered_map<int, Pipeline>& pipes)
{
    string name = read_input<string>("Enter the name or part of the name of the pipe to filter: ");
    vector<int> ids;
    bool flag = false;

    for (const auto& p : pipes) {
        if (p.second.PipeName.find(name) != string::npos) {
            cout << p.second;
            ids.push_back(p.second.PipeID);
            flag = true;
        }
    }

    if (!flag) { cout << "You don't have pipe with name: " << name << endl; return; }

    int ch = read_input<int>("0 - menu:\n1 - chenge pipes\n", 0, 1);

    if (ch == 0) { return; }
    ch = read_input<int>("Enter repair", 0, 1);

    for (const auto& id : ids)
    {
        ChangeRepair(pipes[id], ch);
    }
}

void filter_pipes_by_repair(unordered_map<int, Pipeline>& pipes)
{
    bool repair_status = read_input<bool>("Enter repair status (0 - working, 1 - on repairing): ");
    vector<int> ids;
    bool flag = false;

    for (const auto& p : pipes) {
        if (p.second.RepairIndicator == repair_status) {
            cout << p.second;
            ids.push_back(p.second.PipeID);
            flag = true;
        }
    }

    if (!flag) { cout << "You don't have pipe with repair: " << repair_status << endl; return; }

    int ch = read_input<int>("0 - menu:\n1 - chenge pipes\n", 0, 1);

    if (ch == 0) { return; }
    ch = read_input<int>("Enter repair", 0, 1);

    for (const auto& id : ids)
    {
        ChangeRepair(pipes[id], ch);
    }
}