#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <unordered_map>

using namespace std;
void checkMap(unordered_map<string, unordered_map<string, int>>, const unordered_map<string, int>&);
int total = 0;

int main()
{
    string line;
    string filename = R"(C:\Users\Dan\Desktop\AOC2020\day7\input.txt)";
    unordered_map<string, unordered_map<string, int>> m;

    ifstream file(filename);

    if (!file.is_open())
    {
        perror("File not found");
        return EXIT_FAILURE;
    }

    while(file.good())
    {
        getline(file, line);

        // Extract the key (the bag that the line describes). The remainder is the rest of the line minus the key
        string key = line.substr(0, line.find("bag") - 1);
        string remainder = line.substr(line.find(key) + key.length() + 5);

        // Each entry in the map will contain the key, and another map that will hold the bags it holds, and their amounts
        m[key] = unordered_map<string,int>();

        for (int i = 0; i < remainder.length(); i++)
        {
            if (isdigit(remainder[i]))
            {
                int value = (int) remainder[i] - '0';
                int endIndex = remainder.find("bag", i);
                string bag = remainder.substr(i + 2, endIndex - i - 3);
                m[key][bag] = value;
            }
        }
    }

    // Recursively go through the map, starting with shiny gold.
    unordered_map<string, int> sg = m["shiny gold"];
    checkMap(m, sg);

    file.close();
    cout << "Total " << total << endl;
    return EXIT_SUCCESS;
}

void checkMap(unordered_map<string, unordered_map<string, int>> m, const unordered_map<string, int>& current)
{
    for (auto& e : current)
    {
        for (int i = 0; i < e.second; i++)
        {
            total++;
            checkMap(m, m[e.first]);
        }
    }
}
