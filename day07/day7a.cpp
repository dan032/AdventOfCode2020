#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include <string>

using namespace std;
void searchForBag(const string& s);

vector<string> res;

int main()
{
    searchForBag("shiny gold");

    cout << res.size() << endl;
    return EXIT_SUCCESS;
}

void searchForBag(const string& s)
{
    string line;
    string filename = R"(C:\Users\Dan\Desktop\AOC2020\day7\input.txt)";
    ifstream file(filename);

    while(file.good())
    {
        getline(file, line);
        if (line.find(s) != string::npos && line.rfind(s) != 0)
        {
            string key = line.substr(0, line.find("bag") - 1);
            if (find(res.begin(), res.end(), key) == res.end())
            {
                res.push_back(key);
                searchForBag(key);
            }
        }
    }
}
