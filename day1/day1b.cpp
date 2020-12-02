#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>

using namespace std;

int findProduct(const vector<int>&);

int main()
{
    string line;
    string filename = R"(C:\Users\Dan\Desktop\AOC2020\input.txt)";
    vector<int> v;
    ifstream file(filename);

    if (!file.is_open())
    {
        perror("File not found");
        return EXIT_FAILURE;
    }

    while(file.good())
    {
        getline(file, line);
        v.push_back(stoi(line));
    }

    file.close();
    cout << findProduct(v) << endl;
    return EXIT_SUCCESS;
}

int findProduct(const vector<int>& v)
{
    for (int i = 0; i < v.size() - 2; i++)
    {
        unordered_set<int> s;
        int curr_sum = 2020 - v[i];
        for (int j = i + 1; j < v.size(); j++)
        {
            if (s.find(curr_sum - v[j]) != s.end())
            {
                return  v[i] * v[j] * (curr_sum - v[j]);
            }
            s.insert(v[j]);
        }
    }
    return -1;
}