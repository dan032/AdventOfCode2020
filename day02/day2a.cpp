#include <iostream>
#include <fstream>

using namespace std;

void parseLine(string, int*);

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
        getline(file, line);
        parseLine(line, &total);
    }

    cout << total << endl;
    file.close();
    return EXIT_SUCCESS;
}

void parseLine(string line, int* total) {
    int count = 0;
    int dashIdx = line.find('-');
    int min = stoi(line.substr(0, dashIdx));
    int max = stoi(line.substr(dashIdx + 1, line.find(' ')));
    char c = line.at(line.find(' ') + 1);
    string s = line.substr(line.find(' ') + 4);

    for (char i : s) {
        if (i == c)
            count++;
    }

    if (count <= max && count >= min)
        (*total)++;
}