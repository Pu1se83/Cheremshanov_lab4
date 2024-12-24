#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>

#include "cs.h"
#include "pipeline.h"
#include "logs.h"
#include "line.h"

using namespace std;

class Line;

int main()
{
    ofstream logfile("log1.txt");
    redirect_output_wrapper redirector(cerr);
    redirector.redirect(logfile);


    unordered_map<int, Pipeline> pipes;
    unordered_map<int, CS> css;
    Line line;

    short int menu_choice = -1;

    while (true)
    {
        cout << "Menu\n" << "Select menu item\n";
        cout << "1 - add pipeline\n";
        cout << "2 - add CS\n";
        cout << "3 - all objects\n";
        cout << "4 - save in file\n";
        cout << "5 - download from file\n";
        cout << "6 - filter pipes by name\n";
        cout << "7 - filter pipes by repair indicator\n";
        cout << "8 - filter cs by name\n";
        cout << "9 - filter cs by % of working\n";
        cout << "10 - delete pipe\n";
        cout << "11 - delete cs\n";
        cout << "12 - check connections\n";
        cout << "13 - create connection\n";
        cout << "14 - topolog sort\n";
        cout << "0 - exit\n";
        cout << "--------------------------------------------------------------------\n";

        menu_choice = read_input<short int>("Select menu item: ", 0, 16);
        switch (menu_choice)
        {
        case 1: cin >> pipes; break;
        case 2: cin >> css; break;
        case 3: cout << pipes; cout << css; break;
        case 4: {
            if (css.size() != 0 || pipes.size() != 0)
            {
                ofstream outfile(read_input<string>("Enter file name: ")); outfile << css; outfile << pipes; line.save_connections(outfile); outfile.close(); cout << "saved in file\n";
            }
            else { cout << "you don't have pipes and cs\n"; } break;
        }
        case 5: {
            ifstream outfile(read_input<string>("Enter file name: ")); outfile >> css;
            outfile.clear(); outfile.seekg(0, ios::beg); outfile >> pipes; outfile.clear(); outfile.seekg(0, ios::beg); line.load_connections(outfile, pipes, css);  outfile.close(); break;
        }
        case 6: filter_pipes_by_name(pipes); break;
        case 7: filter_pipes_by_repair(pipes); break;
        case 8: filter_cs_by_name(css); break;
        case 9: filter_cs_by_work_percentage(css); break;
        case 10: { cout << pipes; int ch = read_input<int>("Enter ID of pipe: ", 0, pipes.size() - 1); line.delete_pipe(ch, pipes); pipes.erase(ch); break; }
        case 11: { cout << css; int ch = read_input<int>("Enter ID of cs: ", 0, css.size() - 1); line.delete_cs(ch, css, pipes); css.erase(ch); break; }
        case 12: { line.check_connection(pipes, css); break; }
        case 13: { line.create_connection(pipes, css); break; }
        case 14: { line.topologicalSort(pipes, css); break; }
        case 15: { line.mydikstra(css); break; }
        case 16: { line.fordFulkersonMaxFlow(); break; }
        case 0: logfile.close(); return 0;
        }
    }

    return 0;
}