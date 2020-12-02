#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    string line;
    string filename = R"(C:\Users\Dan\Desktop\AOC2020\day2\input.txt)";
    ifstream file(filename);

    if (!file.is_open())
    {
        perror("File not found");
        return EXIT_FAILURE;
    }

    int total = 0;
    while(file.good())
    {
        int count = 0;

        getline(file, line);

        int dashIdx = line.find('-');
        int min = stoi(line.substr(0, dashIdx ));
        int max = stoi(line.substr(dashIdx + 1, line.find(' ')));
        char c = line.at(line.find(' ') + 1);
        string s = line.substr(line.find(' ') + 3);

        for (char i : s)
        {
            if (i == c)
                count++;
        }

        if (count <= max && count  >= min)
            total++;
    }

    cout << total << endl;
    file.close();

    return EXIT_SUCCESS;
}