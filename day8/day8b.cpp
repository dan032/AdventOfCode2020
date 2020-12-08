#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>

using namespace std;
bool checkIntcode(vector<pair<string, int>> v, bool initializeOpsVectors, int&);

vector<int> opsVector;

int main()
{
    string filename = R"(C:\Users\Dan\Desktop\AOC2020\day8\input.txt)";
    ifstream file(filename);

    string line, operation;
    int acc = 0, value = 0;
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
    file.close();
    checkIntcode(v, true, acc);     // Initializes vector that will be used for brute forcing

    bool infinite = true;
    for (int op : opsVector)         // Brute force to see if changing ops removes infinite loop
    {
        acc = 0;
        if (v[op].first == "jmp")
        {
            v[op].first = "nop";
            infinite = checkIntcode(v, false, acc);
            v[op].first ="jmp";
        }
        else if (v[op].first == "nop")
        {
            v[op].first = "jmp";
            infinite = checkIntcode(v, false, acc);
            v[op].first ="nop";
        }

        if (!infinite) break;
    }
    cout << acc << endl;
    return EXIT_SUCCESS;
}

bool checkIntcode(vector<pair<string, int>> v, bool initializeOpsVectors, int &acc)
{
    unordered_set<int> m;      // Will store index to check if op code has already been called
    for (int i = 0; i < v.size(); i++)
    {
        if (m.find(i) != m.end()) return true;

        m.insert(i);
        if (v[i].first == "acc")
        {
            acc += v[i].second;
        }
        else if (v[i].first == "jmp")
        {
            if (initializeOpsVectors)
            {
                opsVector.push_back(i);
            }
            i += v[i].second - 1;
        }
        else if (v[i].first == "nop")
        {
            if (initializeOpsVectors)
            {
                opsVector.push_back(i);
            }
        }
    }
    return false;
}
