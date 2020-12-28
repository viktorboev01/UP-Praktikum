#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    const int array_size = 101;
    char massage[array_size] = { "" };
    cin.getline(massage, array_size);
    char regex[array_size] = { "" };
    cin.getline(regex, array_size);
    ifstream file(massage); 
    if (!file.is_open())    // when the program cannot find or open the file
    {
        cout << -1 << endl;
        return -1;
    }
    else
    {
        while (!file.eof())    // works while reaching the end of the file
        {
            
        }
        file.close(); // close massage.txt 
    }
    return 0;
}