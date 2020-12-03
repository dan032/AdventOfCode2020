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

    int values[5][2] = {{1,1},{3,1},{5,1},{7,1},{1,2}};

    long total = 1;
    int width = v[0].size() - 1;
    int xIdx = 0, yIdx = 0, count = 0;

    for (auto & value : values)
    {
        xIdx = 0;
        yIdx = 0;
        count = 0;

        while(yIdx < v.size())
        {
            if (v[yIdx][xIdx] == '#')
                count++;

            yIdx += value[1];
            xIdx += value[0];
            if (xIdx >= width) xIdx -= width;
        }
        total *= count;
    }

    cout << total << endl;
    file.close();
    return EXIT_SUCCESS;
}
