#include<iostream>
#include<fstream>
#include<string>
#include<vector>

int main(int argc, char** argv) {
    // reading .mpb file
    using namespace std;
    cout << "[in] reading .mpb file" << endl;
    string filein = argv[1];
    string fileout = argv[2];
    ifstream in(filein);
    string strin;
    getline(in, strin);
    const int num_vertices = stoi(strin);
    getline(in, strin);
    const int source_index = stoi(strin);
    int V[num_vertices];
    for (int i = 0; i < num_vertices; i++) {
        getline(in, strin);
        V[i] = stoi(strin);
    }
    int E[num_vertices][num_vertices];
    for (int i = 0; i < num_vertices; i++) {
        for (int j = 0; j < num_vertices; j++) {
            in >> strin;
            E[i][j] = stoi(strin);
        }
    }
    int H[num_vertices][num_vertices];
    for (int i = 0; i < num_vertices; i++) {
        for (int j = 0; j < num_vertices; j++) {
            in >> strin;
            H[i][j] = stoi(strin);
        }
    }
    in.close();

    //const int bothsquared = pm_size * pm_size * vm_size * vm_size;
    //const int sum = bothsquared + (pm_size * vm_size);

    vector<string> assignments(num_vertices);
    string bounds = "";
    string coverage_constraint = "";
    string obj = "";

    cout << "[info] writing objective and generating constraints and variable bounds" << endl;

    for(int i = 0; i < num_vertices; i++) {
        string varname = "a" + to_string(i);
        assignments[i] = varname;
        bounds += "0 <= " + varname + " <= 1\n";
    }
    
    int objcounter = 0;
    int counter = 0;

    for (int i = 0; i < num_vertices; i++) {
        string var_i = assignments[i];
        for (int j = 0; j < num_vertices; j++) {
            string var_j = assignments[j];
            if (H[i][j] >= 0) {
                if (objcounter > 0) {
                    obj += " + " + to_string(H[i][j]) + " " + var_i;
                } else {
                    obj += to_string(H[i][j]) + " " + var_i;
                }
                objcounter++;
            }
        }
    }
    obj += "\n";

    for (int j = 0; j < num_vertices; j++) {
        string constraint = "c" + to_string(counter) + ": ";
        int term_count = 0;
        for (int i = 0; i < num_vertices; i++) {
            if (H[i][j] > 0) {
                if (term_count > 0) {
                    constraint += " + " + to_string(H[i][j]) + " " + assignments[i];
                } else {
                    constraint += to_string(H[i][j]) + " " + assignments[i];
                }
                term_count++;
            }
        }
        constraint += " >= 1\n";
        coverage_constraint += constraint;
        counter++;
    }
    coverage_constraint += "c" + to_string(counter) + ": " + assignments[source_index] + " = 1\n";

    cout << "[out] printing .lp file" << endl;

    ofstream out(fileout);

    out << "Minimize" << endl;
    out << "obj: ";
    out << obj << endl;
    out << "Subject To" << endl;
    out << coverage_constraint;
    out << "Bounds" << endl;
    out << bounds;
    out << "Binaries" << endl;
    for (int i = 0; i < num_vertices; i++) {
        out << assignments[i] << endl;
    }
    out << "End" << endl;
    out.close();
}
