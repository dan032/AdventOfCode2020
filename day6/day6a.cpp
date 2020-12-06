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

    unordered_set<char> m;
    while(file.good())
    {
        getline(file, line);
        if (line == "\r")
        {
            total += m.size();
            m.clear();
        }

        for (char c : line)
        {
            if (c == '\r') continue;
            if (m.find(c) == m.end())
            {
                m.insert(c);
            }
        }
    }

    total += m.size();
    cout << total << endl;
    file.close();
    return EXIT_SUCCESS;
}