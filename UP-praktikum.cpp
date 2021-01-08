#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

char* remove_backslash(char* regex)
{
    const int array_size = 100;
    char* new_regex;
    new_regex = new char[array_size];
    int k = 0;
    while (regex[k] != '\\') // here I remove '\' from the regex
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
    for (int j = 0; j < strlen(new_regex); j++)
    {
        regex[j] = new_regex[j];
    }
    regex[strlen(new_regex)] = '\0';
    delete[] new_regex;
    return regex;
}
char* remove_arrow(char* regex)
{
    const int array_size = 100;
    char* new_regex;
    new_regex = new char[array_size];
    int k = 0;
    while (regex[k] != '\0')
    {
        new_regex[k] = regex[k + 1];
        k++;
    }
    new_regex[k + 1] = '\0';
    for (int j = 0; j < strlen(new_regex); j++)
    {
        regex[j] = new_regex[j];
    }
    regex[strlen(new_regex)] = '\0';
    delete[] new_regex;
    return regex;
}
int where_is_spec_char(char* regex)
{
    for (int i = 0; i < strlen(regex); i++)
    {
        if ((regex[i] == '*' || regex[i] == '?' || regex[i] == '+') && regex[i - 1] != '\\')
        {
            if (regex[i] == '*')
            {
                return i;
            }
            if (regex[i] == '+')
            {
                return i;
            }
            if (regex[i] == '?')
            {
                return i;
            }
        }
    }
    return -1;
}
char what_is_spec_char(char* regex, int position_spec_char)
{
    return regex[position_spec_char];
}
bool is_regex_valid(char* regex)
{
    int counter_for_spec_char = 0;
    if (regex[0] == '*' || regex[0] == '?' || regex[0] == '+') // for cases when regex begin with spec char from 3-5
    {
        return false;
    }
    for (int i = 1; i < strlen(regex); i++) // for cases when regex have '^' on illegal position
    {
        if (regex[i] == '^' && regex[i - 1] != '\\')
        {
            return false;
        }
    }
    for (int i = 0; i < strlen(regex); i++)
    {
        if (regex[i] == '\\')
        {
            if (regex[i + 1] != '\\' && regex[i + 1] != '.' && regex[i + 1] != '*' && regex[i + 1] != '?' && regex[i + 1] != '+' && regex[i + 1] != '^')
            {
                return false;
            }
            remove_backslash(regex);
        }
        else if (regex[i] == '.' || regex[i] == '*' || regex[i] == '?' || regex[i] == '+')
        {
            counter_for_spec_char++;
            if (regex[i] == '.')
            {
                counter_for_spec_char--;
            }
            if (counter_for_spec_char > 1) // check whether there is two special chars form 3-5 in regex
            {
                return false;
            }
            // check whether there is two adjacent special chars form 2-5 in regex
            else if (regex[i + 1] == '.' || regex[i + 1] == '*' || regex[i + 1] == '?' || regex[i + 1] == '+')
            {
                return false;
            }
        }
    }
    return true;
}
bool coinc_without_spec_chars(char* row, char* regex, bool is_there_arrow)
{
    for (int i = 0; i < strlen(row) - strlen(regex) + 1; i++)
    {
        if (is_there_arrow == true)
        {
            if (i != 0)
            {
                break;
            }
        }
        int j = i;
        while (row[j] == regex[j - i] || regex[j - i] == '.')
        {
            j++;
        }
        if (j - i == strlen(regex))
        {
            return true;
        }
    }
    return false;
}

bool coinc_with_spec_char_beginning(char* row, char* regex, bool is_there_arrow)
{
    int counter_reps_char_before_spec_char = 0;
    for (int i = 0; i < strlen(row) - 1; i++)
    {
        if (is_there_arrow == true)
        {
            if (i != 0)
            {
                break;
            }
        }
        if (row[i] == regex[2])
        {
            while (regex[0] == row[i - counter_reps_char_before_spec_char - 1])
            {
                counter_reps_char_before_spec_char++;
            }
            int j = 0;
            while (j + 2 != strlen(regex))
            {
                if (row[i + j + counter_reps_char_before_spec_char] != regex[2 + j])
                {
                    break;
                }
                j++;
            }
            if (j + 2 == strlen(regex))
            {
                if (what_is_spec_char(regex, 1) == '*')
                {
                    return true;
                }
                if (what_is_spec_char(regex, 1) == '?' && counter_reps_char_before_spec_char < 2)
                {
                    return true;
                }
                if (what_is_spec_char(regex, 1) == '+' && counter_reps_char_before_spec_char > 0)
                {
                    return true;
                }
            }
        }
        else if (strlen(regex) == 2 && what_is_spec_char(regex, 1) != '+')
        {
            return true;
        }
    }
    return false;
}
bool coinc_with_spec_char_not_beginning(char* row, char* regex, bool is_there_arrow)
{
    int counter_reps_char_before_spec_char = 0;
    for (int i = 0; i < strlen(row) - where_is_spec_char(regex) + 2; i++)
    {
        if (is_there_arrow == true)
        {
            if (i != 0)
            {
                break;
            }
        }
        if (row[i] == regex[0])
        {
            int j = i;
            while (j != where_is_spec_char(regex) - 1 + i)
            {
                if (row[j] != regex[j - i] && regex[j - i] != '.')
                {
                    break;
                }
                j++;
            }
            if (j - i == where_is_spec_char(regex) - 1)
            {
                while (regex[where_is_spec_char(regex) - 1] == row[j + counter_reps_char_before_spec_char])
                {
                    counter_reps_char_before_spec_char++;
                }
                if (regex[where_is_spec_char(regex) - 1] == regex[where_is_spec_char(regex) + 1]) // for cases comp*p
                {
                    counter_reps_char_before_spec_char--;
                }
                while (j - i + 2 != strlen(regex))
                {
                    if (row[counter_reps_char_before_spec_char + j] != regex[j - i + 2])
                    {
                        break;
                    }
                    j++;
                }
                if (j - i + 2 == strlen(regex))
                {
                    if (what_is_spec_char(regex, where_is_spec_char(regex)) == '*')
                    {
                        return true;
                    }
                    if (what_is_spec_char(regex, where_is_spec_char(regex)) == '?' && counter_reps_char_before_spec_char < 2)
                    {
                        return true;
                    }
                    if (what_is_spec_char(regex, where_is_spec_char(regex)) == '+' && counter_reps_char_before_spec_char > 0)
                    {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

int main()
{
    bool is_there_arrow = false;
    const int array_size = 101;
    char* massage, * regex, * row;
    massage = new char[array_size];
    regex = new char[array_size];
    row = new char[array_size];
    cin.getline(massage, array_size);
    cin.getline(regex, array_size);
    if (is_regex_valid(regex) == true)
    {
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
                if (regex[0] == '^' && regex[1] == '\0') // if regex is '^'
                {
                    cout << row << endl;
                }
                else if (regex[0] == '^' && regex[1] != '\0') //if regex is from type '^abcd'
                {
                    is_there_arrow = true;
                    remove_arrow(regex);
                }
                if (where_is_spec_char(regex) == -1) //if regex is from type 'abcd' 
                {
                    if (coinc_without_spec_chars(row, regex, is_there_arrow) == true)
                    {
                        cout << row << endl;
                        continue;
                    }
                }
                else if (where_is_spec_char(regex) == 1) //if regex is from type 'ab?cd', 'ab*cd', 'ab+cd'
                {
                    if (coinc_with_spec_char_beginning(row, regex, is_there_arrow) == true)
                    {
                        cout << row << endl;
                        continue;
                    }
                }
                else
                {
                    if (coinc_with_spec_char_not_beginning(row, regex, is_there_arrow) == true)
                    {
                        cout << row << endl;
                        continue;
                    }
                }
            }
        }
        file.close(); // close massage.txt
    }
    else
    {
        cout << -1 << endl;
        return -1;
    }
    delete[] massage;
    delete[] regex;
    delete[] row;
    return 0;
}
