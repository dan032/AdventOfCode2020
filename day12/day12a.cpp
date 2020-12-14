#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <cmath>

#define PI 3.141592653589793238462643383279502884
using namespace std;

pair<double, double> findVectorComponent(double angle, double distance);
pair<double, double> rotateAroundShip(double x, double y, double angle);
int main()
{
    string line;
    string filename = R"(C:\Users\Dan\Desktop\AOC2020\day12\input.txt)";
    vector<pair<char, double>> v;
    ifstream file(filename);

    if (!file.is_open())
    {
        perror("File not found");
        return EXIT_FAILURE;
    }

    while(file.good())
    {
        getline(file, line);
        char c = line[0];
        double val = stod(line.substr(1));
        v.emplace_back(c, val);
    }

    double x = 0;
    double y = 0;
    double angle = 0;

    double wayX = 10;
    double wayY = 1;

    for (auto & i : v)
    {
        if (i.first == 'N')
        {
            wayY +=  i.second;
        }
        if (i.first == 'S')
        {
            wayY -=  i.second;
        }
        if (i.first == 'W')
        {
            wayX -=  i.second;
        }
        if (i.first == 'E')
        {
            wayX +=  i.second;
        }
        if (i.first == 'L')
        {
            angle -= i.second;
            pair<double, double> vec = rotateAroundShip(wayX, wayY, angle);
            angle = 0;
            wayX = vec.first;
            wayY = vec.second;
        }
        if (i.first == 'R')
        {
            angle += i.second;
            pair<double, double> vec = rotateAroundShip(wayX, wayY, -angle);
            angle = 0;
            wayX = vec.first;
            wayY = vec.second;
        }
        if (i.first == 'F') {
            x += (wayX * i.second);
            y += (wayY * i.second);
        }

        cout << "ShipX: " << x << " ShipY: " << y << endl;
        cout << "WPX: " << wayX << " WPY: " << wayY << endl;
        cout << "-------------------------------------------" << endl;
    }

    cout << abs(x) + abs(y) << endl;

    file.close();
    return EXIT_SUCCESS;
}

pair<double, double> rotateAroundShip(double x, double y, double angle)
{
    double xComp = (y * cos(angle * PI / 180.0)) - (x*sin(angle * PI / 180.0));
    double yComp = (y * sin(angle * PI / 180.0)) + (x*cos(angle * PI / 180.0));
    return make_pair(xComp, yComp);
}

pair<double, double> findVectorComponent(double angle, double distance)
{
    double x = distance * cos(angle * PI / 180.0);
    double y = distance * sin(angle * PI / 180.0);
    return make_pair(x, y);
}

