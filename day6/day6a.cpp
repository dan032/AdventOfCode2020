#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

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

        unordered_map<char, int> m;
        for (auto & i : v)
        {
            for (char j : i)
            {
                if (j == '\r') continue;
                if (m.find(j) == m.end())
                {
                    m[j] = 1;
                    total++;
                }
            }
        }
    }

    cout << total << endl;
    file.close();
    return EXIT_SUCCESS;
}