#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    const int array_size = 101;
    int counter_for_spec_char = 0, position_dot = -1, position_qmark = -1, position_plus = -1, position_star = -1, k = 0;
    char massage[array_size] = { "" }, row[array_size] = { "" }, answer[array_size] = { "" };
    cin.getline(massage, array_size);
    char regex[array_size] = { "" }, new_regex[array_size];
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
            while (regex[k] != '\\')
            {
                new_regex[k] = regex[k];
                k++;
            }
            while (regex[k] != '\0')
            {
                new_regex[k] = regex[k + 1];
                k++;
            }
            new_regex[k + 1] = '\0';
            k = 0;
            for (int j = 0; j < strlen(new_regex); j++)
            {
                regex[j] = new_regex[j];
            }
            regex[strlen(new_regex)] = '\0';
        }
        else if (regex[i] == '.' || regex[i] == '*' || regex[i] == '?' || regex[i] == '+')
        {
            if (regex[i] == '.')
            {
                position_dot = i;
            }
            if (regex[i] == '*')
            {
                position_star = i;
            }
            if (regex[i] == '+')
            {
                position_plus = i;
            }
            if (regex[i] == '?')
            {
                position_qmark = i;
            }
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
            file.getline(row, array_size);
            if (regex[0] == '^' && regex[1] == '\0')
            {
                for (int i = 0; i < strlen(row); i++)
                {
                    answer[i] = row[i];
                    cout << answer[i];
                }
                cout << endl;
            }
            else
            {
                ;
            }
        }
    }
    file.close(); // close massage.txt
    return 0;
}
