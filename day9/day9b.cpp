#include <iostream>
#include <fstream>
#include <vector>
#include <deque>


using namespace std;
int main()
{
    string line;
    string filename = R"(C:\Users\Dan\Desktop\AOC2020\day9\input.txt)";
    vector<long> v;
    deque<long> q;

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

    int r = 25;

    for (int i = 0; i < r; i++)
    {
        q.push_back(v[i]);
    }

    long goal = 1492208709;

    while(r < v.size())
    {
        long total = 0;

        for (long i : q)
        {
            total += i;
        }

        if (total == goal)
        {
            long min = q[0];
            long max = q[0];

            for (long j : q)
            {
                if (j < min)
                {
                    min = j;
                }
                if (j > max)
                {
                    max = j;
                }
            }

            cout << min + max << endl;
            break;
        }

        if (total < goal)
        {
            q.push_back(v[r++]);
        }

        else{
            q.pop_front();
        }
    }

    file.close();
    return EXIT_SUCCESS;
}