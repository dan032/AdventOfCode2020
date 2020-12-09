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

    while(r < v.size())
    {
        unordered_set<long> s;

        for (int i = 0; i < q.size(); i++)
        {
            for (int j = i + 1; j < q.size(); j++)
            {
                s.insert(q[i] + q[j]);
            }
        }

        if (s.find(v[r]) == s.end())
        {
            cout << v[r] << endl;
            break;
        }

        q.push_back(v[r++]);
        q.pop_front();
    }

    file.close();
    return EXIT_SUCCESS;
}