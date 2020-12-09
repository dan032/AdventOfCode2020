#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <deque>

using namespace std;
bool checkSum(deque<long>  q, vector<long> v, int r);

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

    bool success;
    while(r < v.size())
    {

        success = checkSum(q, v, r);

        if (!success)
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

bool checkSum(deque<long>  q, vector<long> v, int r)
{
    bool found = false;
    for (int i = 0; i < q.size(); i++)
    {
        for (int j = i + 1; j < q.size(); j++)
        {
            if (q[i] + q[j] == v[r])
            {
                found = true;
            }
        }
    }
    return found;
}