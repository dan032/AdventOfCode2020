#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <deque>


using namespace std;
int main()
{
    string line;
    string filename = R"(C:\Users\Dan\Desktop\AOC2020\day9\input.txt)";
    vector<long long> v;
    deque<long long> q;

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

    for (int i = l; i < r; i++)
    {
        q.push_back(v[i]);
    }

    long long goal = 1492208709;

    while(r < v.size())
    {
        unordered_set<long> s;
        long long total = 0;
        for (long long i : q)
        {
            total += i;
        }

        if (total == goal)
        {

            long long min = q[0];
            long long max = q[0];

            for (long long j : q)
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