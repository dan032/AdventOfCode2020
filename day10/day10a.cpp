#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

int main()
{
    string line;
    string filename = R"(C:\Users\Dan\Desktop\AOC2020\day10\input.txt)";
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
    cout << endl;

    v.push_back(0);
    v.push_back(*max_element(v.begin(), v.end()) + 3);
    sort(v.begin(), v.end());

    int ones = 0;
    int threes=  0;

    for (int i = 0; i < v.size() - 1; i++)
    {
        if (v[i + 1] - v[i] == 1) ones++;
        if (v[i + 1] - v[i] == 3) threes++;
    }
    cout << ones*threes <<endl;

    file.close();
    return EXIT_SUCCESS;
}

