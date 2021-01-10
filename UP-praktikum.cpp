/**
*
* Solution to course project # 7
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2020/2021
*
* @author Viktor Boev
* @idnumber 62564
* @compiler VC
*
* <main file>
*
*/

#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

char* remove_backslash(char* regex)
{
    const int array_size = 5000;
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
    const int array_size = 5000;
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
    int counter_dashes = 0;
    for (int i = 1; i < strlen(regex); i++)
    {
        if (regex[i - 1] == '\\')
        {
            counter_dashes++;
        }
        else
        {
            if (regex[i] == '*' || regex[i] == '?' || regex[i] == '+')
            {
                return i - counter_dashes;
            }
        }
    }
    return -1;
}
char what_is_spec_char(char* regex, int position_spec_char)
{
    return regex[position_spec_char];
}
bool is_there_dot_spec(int number, int* pos_spec_dots)
{
    int k = 0;
    while (pos_spec_dots[k] >= 0)
    {
        if (number == pos_spec_dots[k])
        {
            return true;
        }
        k++;
    }
    return false;
}
bool is_regex_valid(char* regex, int* pos_spec_dots)
{
    int counter_for_array = 0; 
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
            if (strlen(regex) - i == 1)
            {
                break;
            }
        }
        else if (regex[i] == '.' || regex[i] == '*' || regex[i] == '?' || regex[i] == '+')
        {
            counter_for_spec_char++;
            if (regex[i] == '.')
            {
                pos_spec_dots[counter_for_array] = i;
                counter_for_array++;
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
bool coinc_without_spec_chars(char* row, char* regex, bool is_there_arrow, int* pos_spec_dots)
{
    if (strlen(row) - strlen(regex) < 0 || strlen(row) == 0) 
    {
        return false;
    }
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
        while (row[j] == regex[j - i] || is_there_dot_spec(j - i, pos_spec_dots) == true)
        {
            if (j == strlen(row) || j - i == strlen(regex))
            {
                break;
            }
            j++;
        }
        if (j - i == strlen(regex))
        {
            return true;
        }
    }
    return false;
}
bool coinc_with_spec_char_beginning(char* row, char* regex, bool is_there_arrow, int* pos_spec_dots)
{
    int a = strlen(regex); // strlen is unsigned int, we need int
    int b = strlen(row);
    if (a - b > 2 || strlen(row) == 0)
    {
        return false;
    }
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
            while (regex[0] == row[i - counter_reps_char_before_spec_char - 1] && i - counter_reps_char_before_spec_char - 1 >= 0)
            {
                counter_reps_char_before_spec_char++;
            }
            int j = 0;
            while (row[i + j + 1] == regex[j + 3] || is_there_dot_spec(3 + j, pos_spec_dots) == true)
            {
                j++;
                if (row[i + j + 1] == '\0')
                {
                    break;
                }
            }
            if (j + 3 == strlen(regex))
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
bool coinc_with_spec_char_not_beginning(char* row, char* regex, bool is_there_arrow, int* pos_spec_dots, int place_spec_char)
{
    int a = strlen(regex); 
    int b = strlen(row);
    if (a - b > 2 || strlen(row) == 0) 
    {
        return false;
    }
    int counter_reps_char_before_spec_char = 0;
    int spec_counter = 0;
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
            while (j != place_spec_char - 1 + i)
            {
                if (row[j] != regex[j - i] && is_there_dot_spec(j - i, pos_spec_dots) == false)
                { 
                    break;
                }
                j++;
            }
            if (j - i == place_spec_char - 1)
            {
                while (regex[place_spec_char - 1] == row[j + counter_reps_char_before_spec_char])
                {
                    counter_reps_char_before_spec_char++;
                }
                while (regex[place_spec_char - 1] == regex[place_spec_char + 1 + spec_counter]) // for cases abcd*d
                {
                    counter_reps_char_before_spec_char--;
                    spec_counter++;
                }
                while (j - i + 2 != strlen(regex))
                {
                    if (row[counter_reps_char_before_spec_char + j] != regex[j - i + 2] && is_there_dot_spec(j - i + 2, pos_spec_dots) == false)
                    {
                        break;
                    }
                    j++;
                }
                if (j - i + 2 == strlen(regex))
                {
                    if (what_is_spec_char(regex, place_spec_char) == '*')
                    {
                        return true;
                    }
                    if (what_is_spec_char(regex, place_spec_char) == '?' && (counter_reps_char_before_spec_char < 2 || i == 0))
                    {
                        return true;
                    }
                    if (what_is_spec_char(regex, place_spec_char) == '+' && counter_reps_char_before_spec_char > 0)
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
    const int array_size = 5000;
    int* pos_spec_dots;
    pos_spec_dots = new int[array_size];
    bool is_there_arrow = false;
    char* massage, * regex, * row;
    massage = new char[array_size];
    regex = new char[array_size];
    row = new char[array_size];
    cin.getline(massage, array_size);
    cin.getline(regex, array_size);
    int place_spec_char = where_is_spec_char(regex);
    if (regex[0] == '^' && regex[1] != '\0') //if regex is from type '^abcd'
    {
        is_there_arrow = true;
        remove_arrow(regex);
    }
    if (is_regex_valid(regex, pos_spec_dots) == true)
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
                if (place_spec_char == -1) //if regex is from type 'abcd' 
                {
                    if (coinc_without_spec_chars(row, regex, is_there_arrow, pos_spec_dots) == true)
                    {
                        cout << row << endl;
                        continue;
                    }
                }
                else if (place_spec_char == 1) //if regex is from type 'b?cd', 'b*cd', 'b+cd'
                {
                    if (coinc_with_spec_char_beginning(row, regex, is_there_arrow, pos_spec_dots) == true)
                    {
                        cout << row << endl;
                        continue;
                    }
                }
                else //if regex is from type 'ab?cd', 'ab*cd', 'ab+cd'
                {
                    if (coinc_with_spec_char_not_beginning(row, regex, is_there_arrow, pos_spec_dots, place_spec_char) == true)
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
    delete[] pos_spec_dots;
    return 0;
}
