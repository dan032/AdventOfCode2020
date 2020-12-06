#include <iostream>
#include <fstream>
#include <unordered_set>

using namespace std;

int main()
{
    string line;
    string filename = R"(C:\Users\Dan\Desktop\AOC2020\day6\input.txt)";
    ifstream file(filename);
    int total = 0;

    if (!file.is_open())
    {
        perror("File not found");
        return EXIT_FAILURE;
    }

    unordered_set<char> s;
    while(file.good())
    {
        getline(file, line);
        if (line == "\r")
        {
            total += s.size();
            s.clear();
        }

        for (char c : line)
        {
            if (c == '\r') continue;
            if (s.find(c) == s.end())
            {
                s.insert(c);
            }
        }
    }

    total += s.size();
    cout << total << endl;
    file.close();
    return EXIT_SUCCESS;
}