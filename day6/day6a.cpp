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
        if (line == "\r")       // Means I have hit a new group, add the current group count to total and clear
        {
            total += s.size();
            s.clear();
        }

        for (char c : line)     // Iterate over each line and count the number of unique letters in the group.
        {                       // Set is only cleared when a new group is started
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