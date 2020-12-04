#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <regex>

using namespace std;

map<string, string> loadVectorIntoMap(const vector<string> &v);
bool isValid(map<string, string>, const string&);

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
        map<string, string> m = loadVectorIntoMap(v);

        // Loop through keys and validate entry
        bool valid = true;
        for (const string& key : keyValues)
        {
            bool isEntryValid = isValid(m, key);
            if (!isEntryValid)
            {
                valid = false;
            }
        }

        if (valid)
        {
            count++;
        }
    }

    cout << count << endl;
    file.close();
    return EXIT_SUCCESS;
}

map<string, string> loadVectorIntoMap(const vector<string>& v)
{
    map<string, string> m;
    for (const string& s : v)
    {
        istringstream iss(s);
        vector<string> entries{
                istream_iterator<string>(iss), {}
        };

        for (const string& entry : entries)
        {
            m[entry.substr(0, s.find(':'))] = entry.substr(s.find(':') + 1);
        }
    }
    return m;
}

bool isValid(map<string, string> m, const string& key)
{
    if (m.find(key) == m.end())
    {
        if (key != "cid")
        {
            return false;
        }
    }

    if (key == "byr")
    {
        int byr = stoi(m[key]);
        if (byr < 1920 || byr > 2002)
        {
            return false;
        }
    }

    if (key == "iyr")
    {
        int iyr = stoi(m[key]);
        if (iyr < 2010 || iyr > 2020)
        {
            return false;
        }
    }

    if (key == "eyr")
    {
        int eyr = stoi(m[key]);
        if (eyr < 2020 || eyr > 2030)
        {
            return false;
        }
    }

    if (key == "hgt")
    {
        if (m[key].length() < 3)
        {
            return false;
        }

        string unit = m[key].substr(m[key].length() - 2);
        int hgt = stoi(m[key].substr(0, m[key].length() - 2));

        if (unit == "cm")
        {
            if (hgt < 150 || hgt > 193)
            {
                return false;
            }

        }

        else if (unit == "in")
        {
            if (hgt < 59 || hgt > 79)
            {
                return false;
            }
        }
        else{
            return false;
        }
    }

    if (key == "hcl")
    {
        if (!regex_match(m[key], regex("#[0-9|a-f]{6}")))
        {
            return false;
        }
    }

    if (key == "ecl")
    {
        string eyeColors[7] = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
        bool validEye = false;
        for (const string& color : eyeColors)
        {
            if (m[key] == color)
            {
                validEye = true;
                break;
            }
        }

        if (!validEye)
        {
            return false;
        }
    }

    if (key == "pid")
    {
        if (!regex_match(m[key], regex("[0-9]{9}")))
        {
            return false;
        }
    }
    return true;
}