#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <regex>
#include <cmath>

using namespace std;


int main()
{
    string line;
    string filename = R"(C:\Users\Dan\Desktop\AOC2020\day13\input.txt)";
    vector<int> ids;
    int num = 0;
    ifstream file(filename);
    regex e("^-?\\d+");
    if (!file.is_open())
    {
        perror("File not found");
        return EXIT_FAILURE;
    }
    getline(file, line);
    num = stoi(line);
    getline(file, line);


    stringstream ss(line);

    while (ss.good())
    {
        string substr;
        getline(ss, substr, ',');

        if (regex_match(substr, e)){
            ids.push_back(stoi(substr));
        }
    }

    vector<int> v;

    for (int id : ids)
    {
        v.push_back((ceil(num/id) * id) + id);
    }

    int diff = INT32_MAX;
    int id = 0;

    for (int i = 0; i < v.size(); i++)
    {
        if ((v[i] - num) < diff)
        {
            diff = v[i] - num;
            id = ids[i];
        }
    }

    cout <<  (id * diff) << endl;

    cout << endl;

    file.close();
    return EXIT_SUCCESS;
}
