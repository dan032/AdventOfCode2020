#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <map>
#include <forward_list>

using namespace std;

bool testInfinite(vector<pair<string,int>> v);
void findLoop(map<int, pair<string, int>> &m, vector<int> &jmps, vector<int> &nops, vector<pair<string, int>> v);

int acc = 0;
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


    while(file.good())
    {
        getline(file, line);
        string op = line.substr(0, line.find(' '));
        int num = stoi(line.substr((line.find(' '))));
        pair<string, int> p =  make_pair(op, num);
        v.push_back(p);
    }

    map<int, pair<string, int>> m;
    vector<int> jmps;
    vector<int> nops;

    findLoop(m, jmps, nops, v);

    bool pass = false;
    for (int jmp : jmps)
    {
        v[jmp].first = "nop";
        acc = 0;
        bool infinite = testInfinite(v);
        if (!infinite){
            pass = true;
            break;
        }
        v[jmp].first ="jmp";
    }

    if (!pass)
    {
        for (int nop : nops)
        {
            acc = 0;
            v[nop].first = "jmp";
            bool infinite = testInfinite(v);
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

void findLoop(map<int, pair<string, int>> &m, vector<int> &jmps, vector<int> &nops, vector<pair<string, int>> v)
{
    for (int i = 0; i < v.size(); i++)
    {
        if (v[i].first == "acc")
        {
            if (m.find(i) != m.end())
            {
                break;
            }
            m[i] = v[i];
        }
        else if (v[i].first == "jmp")
        {
            if (m.find(i) != m.end())
            {
                break;
            }
            m[i] = v[i];
            jmps.push_back(i);
            i += v[i].second - 1;
        }

        else if (v[i].first == "nop")
        {
            if (m.find(i) != m.end())
            {
                break;
            }
            m[i] = v[i];
            nops.push_back(i);
        }
    }
}

bool testInfinite(vector<pair<string,int>> v)
{
    map<int, pair<string, int>> m;
    for (int i = 0; i < v.size(); i++)
    {
        if (v[i].first == "acc")
        {
            if (m.find(i) != m.end())
            {
                return true;
            }
            acc += v[i].second;
        }
        else if (v[i].first == "jmp")
        {
            if (m.find(i) != m.end())
            {
                return true;
            }
            m[i] = v[i];

            i += v[i].second - 1;
        }

        else if (v[i].first == "nop")
        {
            if (m.find(i) != m.end())
            {
                return true;
            }
            m[i] = v[i];
        }
    }
    return false;
}