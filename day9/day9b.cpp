#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
int main()
{
    string line;
    string filename = R"(C:\Users\Dan\Desktop\AOC2020\day9\input.txt)";
    vector<long> v;
    ifstream file(filename);

    if (!file.is_open())
    {
        perror("File not found");
        return EXIT_FAILURE;
    }

    while(file.good())
    {
        getline(file, line);
        v.push_back(stol(line));
    }

    int l = 0;
    int r = 25;
    long goal = 1492208709;

    while(r < v.size())
    {
        long total = 0, min = v[l], max = v[l];
        for (int i = l; i < r; i++)
        {
            total += v[i];
            min = v[i] < min ? v[i] : min;
            max = v[i] > max ? v[i] : max;
        }

        if (total == goal)
        {
            cout << min + max << endl;
            break;
        }

        r = total < goal ? ++r : r;
        l = total > goal ? ++l : l;
    }

    file.close();
    return EXIT_SUCCESS;
}