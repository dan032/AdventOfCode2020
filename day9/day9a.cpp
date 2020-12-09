#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
bool checkSum(vector<long> v, int l, int r);

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

    bool found;
    while(r < v.size())
    {

        found = checkSum(v, l, r);

        if (!found)
        {
            cout << v[r] << endl;
            break;
        }

        l++;
        r++;
    }

    file.close();
    return EXIT_SUCCESS;
}

bool checkSum(vector<long> v, int l, int r)
{
    bool found = false;
    for (int i = l; i < r; i++)
    {
        for (int j = i + 1; j < r; j++)
        {
            if (v[i] + v[j] == v[r])
            {
                found = true;
            }
        }
    }
    return found;
}