#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>

using namespace std;
void findAccumulatorValue(vector<pair<string, int>>, int&);

int main()
{
    string filename = R"(C:\Users\Dan\Desktop\AOC2020\day8\input.txt)";
    ifstream file(filename);

    string line, operation;
    int value = 0, acc = 0;
    vector<pair<string, int>> v;
    pair<string, int> opPair;

    if (!file.is_open())
    {
        perror("File not found");
        return EXIT_FAILURE;
    }

    while(file.good())                  // Populate vector with all op codes and their values
    {
        getline(file, line);
        operation = line.substr(0, line.find(' '));
        value = stoi(line.substr((line.find(' '))));
        opPair = make_pair(operation, value);
        v.push_back(opPair);
    }

    findAccumulatorValue(v, acc);

    cout << acc << endl;
    file.close();
    return EXIT_SUCCESS;
}

void findAccumulatorValue(vector<pair<string, int>> v, int &acc)
{
    unordered_set<int> m;      // Will store index to check if op code has already been called
    for (int i = 0; i < v.size(); i++)
    {
        if (m.find(i) != m.end()) return;

        m.insert(i);
        if (v[i].first == "acc")
        {
            acc += v[i].second;
        }
        else if (v[i].first == "jmp")
        {
            i += v[i].second - 1;
        }
    }
}