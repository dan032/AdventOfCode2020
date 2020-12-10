#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

using namespace std;

int main()
{
    string line;
    string filename = R"(C:\Users\Dan\Desktop\AOC2020\day10\input.txt)";
    vector<uintmax_t> v;
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

    v.push_back(0);
    v.push_back(*max_element(v.begin(), v.end()) + 3);
    sort(v.begin(), v.end());

    unordered_map<uintmax_t, uintmax_t> m{{0,1}};

    for (auto& e : v)
    {
        m[e] += m[e - 1] + m[e - 2] + m[e - 3];
    }

    cout << m[v.back()] << endl;

    return EXIT_SUCCESS;
}