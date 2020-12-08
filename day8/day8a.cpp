#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>

using namespace std;
void findAccumulatorValue(vector<pair<string, int>>);

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

    findAccumulatorValue(v);

    cout << acc << endl;
    file.close();
    return EXIT_SUCCESS;
}

void findAccumulatorValue(vector<pair<string, int>> v)
{
    unordered_set<int> m;
    for (int i = 0; i < v.size(); i++)
    {
        if (v[i].first == "acc")
        {
            if (m.find(i) != m.end())
            {
                break;
            }
            m.insert(i);
            acc += v[i].second;
        }
        else if (v[i].first == "jmp")
        {
            if (m.find(i) != m.end())
            {
                break;
            }
            m.insert(i);

            i += v[i].second - 1;
        }

        else if (v[i].first == "nop")
        {
            if (m.find(i) != m.end())
            {
                break;
            }
            m.insert(i);
        }
    }
}