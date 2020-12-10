#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>

using namespace std;

int findProduct(const vector<int>&);

int main()
{
    string line;
    string filename = R"(C:\Users\Dan\Desktop\AOC2020\day1\input.txt)";
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
    unordered_set<int> s;
    for(int num : v)
    {
        int diff = 2020 - num;

        if (s.find(diff) != s.end())
        {
            return diff * num;
        }
        s.insert(num);
    }
}
