#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>

using namespace std;

int main()
{
    string line;
    string filename = R"(C:\Users\Dan\Desktop\AOC2020\day5\input.txt)";
    ifstream file(filename);

    if (!file.is_open())
    {
        perror("File not found");
        return EXIT_FAILURE;
    }

    int res = 0;
    while(file.good())
    {
        getline(file, line);

        int l = 0, r = 127;
        for (int i = 0; i < 6; i++)
        {
            if (line[i] == 'F')
            {
                r -= (r - l + 1) / 2;
            }
            else if (line[i] == 'B')
            {
                l += (r - l + 1) / 2;
            }
        }

        int row = line[6]  == 'F' ? min(l, r) : max(l, r);

        l = 0;
        r = 7;
        for (int i = 6; i < 9; i++)
        {
            if (line[i] == 'R')
            {
                l += (r - l + 1) / 2;
            }
            else if (line[i] == 'L')
            {
                r -= (r - l + 1) / 2;
            }
        }

        int col = line[9] == 'R' ? max(l, r) : min(l, r);
        res = max(res, (row * 8 ) + col);
    }

    cout << res << endl;
    file.close();
    return EXIT_SUCCESS;
}