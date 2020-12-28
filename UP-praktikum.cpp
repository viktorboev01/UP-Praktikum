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
    for (int i = 1; i < strlen(regex); i++)
    {
        if (regex[i] == '^' && regex[i - 1] != '\\')
        {
            return -1;
        }
    }
    for (int i = 0; i < strlen(regex); i++)
    {
        if (regex[i] == '\\')
        {
            if (regex[i + 1] != '\\' && regex[i + 1] != '.' && regex[i + 1] != '*' && regex[i + 1] != '?' && regex[i + 1] != '+' && regex[i + 1] != '^')
            {
                return -1;
            }
            i++;
        }
        else if (regex[i] == '.' || regex[i] == '*' || regex[i] == '?' || regex[i] == '+')
        {
            counter_for_spec_char++;
            if (regex[i] == '.')
            {
                counter_for_spec_char--;
            }
            if (counter_for_spec_char > 1)
            {
                return -1;
            }
            else if (regex[i + 1] == '.' || regex[i + 1] == '*' || regex[i + 1] == '?' || regex[i + 1] == '+')
            {
                return -1;
            }
        }
    }
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
    }
    file.close(); // close massage.txt 
    return 0;
}
