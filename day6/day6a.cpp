#include <iostream>
#include <fstream>
#include <unordered_set>

using namespace std;

int main()
{
    string line;
    string filename = R"(C:\Users\Dan\Desktop\AOC2020\day6\input.txt)";
    ifstream file(filename);

    if (!file.is_open())
    {
        perror("File not found");
        return EXIT_FAILURE;
    }

    int total = 0;
    while(file.good())
    {
        bool firstEnter = true;
        unordered_set<char> m;

        while (firstEnter || ((line != "\r") && file.good()))
        {
            getline(file, line);
            for (char c : line)
            {
                if (c == '\r') continue;
                if (m.find(c) == m.end())
                {
                    m.insert(c);
                    total++;
                }
            }
            firstEnter = false;
        }
    }

    cout << total << endl;
    file.close();
    return EXIT_SUCCESS;
}