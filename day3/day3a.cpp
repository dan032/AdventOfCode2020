#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main()
{
    string line;
    string filename = R"(C:\Users\Dan\Desktop\AOC2020\day3\input.txt)";
    ifstream file(filename);
    vector<string> v;

    if (!file.is_open())
    {
        perror("File not found");
        return EXIT_FAILURE;
    }

    while(file.good())
    {
        getline(file, line);
        v.push_back(line);
    }

    int xIdx = 0, yIdx = 0, count = 0;
    int width = v[0].size() - 1;

    while(yIdx < v.size())
    {
        if (v[yIdx][xIdx] == '#')
            count++;

        yIdx += 1;
        xIdx += 3;
        if (xIdx >= width) xIdx -= width;
    }

    cout << count << endl;
    file.close();
    return EXIT_SUCCESS;
}
