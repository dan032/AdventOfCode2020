#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>

using namespace std;

bool checkIntcode(vector<pair<string, int>> v, bool initializeVectors);

int acc = 0;                        // Accumulator for final result
vector<int> jmps;                   // Will be used to brute force all jump op codes
vector<int> nops;                   // Will be used to brute force all nop op codes

int main()
{
    string line;
    string filename = R"(C:\Users\Dan\Desktop\AOC2020\day8\input.txt)";
    vector<pair<string, int>> v;
    ifstream file(filename);

    if (!file.is_open())
    {
        perror("File not found");
        return EXIT_FAILURE;
    }

    while(file.good())          // Populate vector with all op codes and their values
    {
        getline(file, line);
        string op = line.substr(0, line.find(' '));
        int num = stoi(line.substr((line.find(' '))));
        pair<string, int> p =  make_pair(op, num);
        v.push_back(p);
    }

    checkIntcode(v, true);     // Initializes vectors that will be used for brute forcing

    bool pass = false;
    for (int jmp : jmps)         // Brute force to see if changing jump ops removes infinite loop
    {
        v[jmp].first = "nop";
        acc = 0;
        bool infinite = checkIntcode(v, false);
        if (!infinite){
            pass = true;
            break;
        }
        v[jmp].first ="jmp";
    }

    if (!pass)
    {
        for (int nop : nops)     // Brute force to see if changing nop ops removes infinite loop
        {
            acc = 0;
            v[nop].first = "jmp";
            bool infinite = checkIntcode(v, false);
            if (!infinite){
                break;
            }
            v[nop].first ="nop";
        }
    }

    cout << acc << endl;
    file.close();
    return EXIT_SUCCESS;
}

bool checkIntcode(vector<pair<string, int>> v, bool initializeVectors)
{
    unordered_set<int> m;      // Will be stored to check if op code has already been called

    for (int i = 0; i < v.size(); i++)
    {
        if (v[i].first == "acc")
        {
            if (m.find(i) != m.end())
            {
                return true;
            }
            m.insert(i);
            acc += v[i].second;
        }
        else if (v[i].first == "jmp")
        {
            if (m.find(i) != m.end())
            {
                return true;
            }
            if (initializeVectors)
            {
                jmps.push_back(i);
            }

            m.insert(i);
            i += v[i].second - 1;
        }

        else if (v[i].first == "nop")
        {
            if (m.find(i) != m.end())
            {
                return true;
            }
            if (initializeVectors)
            {
                nops.push_back(i);
            }
            m.insert(i);
        }
    }
    return false;
}
