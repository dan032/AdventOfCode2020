#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <regex>

using namespace std;

unordered_map<string, string> loadVectorIntoMap(const vector<string>&);

int main()
{
    string line;
    string filename = R"(C:\Users\Dan\Desktop\AOC2020\day4\input.txt)";
    ifstream file(filename);
    string keyValues[] = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid", "cid"};

    if (!file.is_open()) {
        perror("File not found");
        return EXIT_FAILURE;
    }

    int count = 0;
    while (file.good())
    {
        vector<string> v;
        bool firstEnter = true;

        // Loop through file until an entry is completed
        while (firstEnter || ((line != "\r") && file.good()))
        {
            getline(file, line);
            if (line != "\r")
            {
                v.push_back(line);
            }
            firstEnter = false;
        }

        // Separate entry into key value pairs and insert into map
        unordered_map<string, string> m = loadVectorIntoMap(v);

        bool invalid = false;
        for (const string& key : keyValues)
        {
            if (m.find(key) == m.end())
            {
                if (key != "cid")
                {
                    invalid = true;
                    break;
                }
            }
        }

        if (!invalid)
        {
            count++;
        }
        m.clear();
    }

    cout << count << endl;
    file.close();
    return EXIT_SUCCESS;
}

unordered_map<string, string> loadVectorIntoMap(const vector<string>& v)
{
    unordered_map<string, string> m;
    for (const string& s : v)
    {
        istringstream iss(s);
        vector<string> entries{
                istream_iterator<string>(iss), {}
        };
        for (const string& entry : entries){
            m[entry.substr(0, s.find(':'))] = entry.substr(s.find(':') + 1);
        }
    }
    return m;
}