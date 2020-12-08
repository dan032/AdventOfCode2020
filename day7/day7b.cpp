#include <iostream>
#include <fstream>
#include <unordered_map>

using namespace std;

typedef struct {
    unordered_map<string, int> subBags;
} Bag;


void checkBag(unordered_map<string,Bag> m, const Bag &current);

int total = 0;

int main()
{
    string line;
    string filename = R"(C:\Users\Dan\Desktop\AOC2020\day7\input.txt)";
    ifstream file(filename);

    unordered_map<string, Bag> m;

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

        m[key] = Bag();

        for (int i = 0; i < remainder.length(); i++)
        {
            if (isdigit(remainder[i]))
            {
                int value = (int) remainder[i] - '0';
                int endIndex = remainder.find("bag", i);
                string bag = remainder.substr(i + 2, endIndex - i - 3);
                m[key].subBags[bag] = value;
            }
        }
    }

    // Recursively go through the map, starting with shiny gold.
    Bag sg = m["shiny gold"];
    checkBag(m, sg);

    file.close();
    cout << "Total " << total << endl;
    return EXIT_SUCCESS;
}

void checkBag(unordered_map<string, Bag> m, const Bag &current)
{
    for (auto& e : current.subBags)
    {
        for (int i = 0; i < e.second; i++)
        {
            total++;
            checkBag(m, m[e.first]);
        }
    }
}
