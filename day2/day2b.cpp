#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>

using namespace std;

int main()
{
    string line;
    string filename = R"(C:\Users\Dan\Desktop\AOC2020\day2\input.txt)";
    vector<int> v;
    ifstream file(filename);

    if (!file.is_open())
    {
        perror("File not found");
        return EXIT_FAILURE;
    }

    int total = 0;
    while(file.good())
    {
        getline(file, line);

        int dashIdx = line.find('-');
        int min = stoi(line.substr(0, dashIdx ));
        int max = stoi(line.substr(dashIdx + 1, line.find(' ')));
        char c = line.at(line.find(' ') + 1);
        string s = line.substr(line.find(' ') + 4);

        if ((s[min - 1] == c) ^ (s[max - 1] == c))
        {
            total++;
        }
    }

    cout << total << endl;
    file.close();

    return EXIT_SUCCESS;
}