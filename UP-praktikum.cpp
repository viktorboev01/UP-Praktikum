#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    const int array_size = 100;
    int counter_for_spec_char = 0, position_spec_char = -1, k = 0, counter_reps_char_before_spec_char = 0; // k is iterator for later
    bool possible_coincidence = true, is_line_printed = false;
    char* massage, * regex, * row, * new_regex, spec_char, char_before_spec_char;
    massage = new char[array_size];
    new_regex = new char[array_size];
    regex = new char[array_size];
    row = new char[array_size];
    cin.getline(massage, array_size);
    cin.getline(regex, array_size);
    if (regex[0] == '*' || regex[0] == '?' || regex[0] == '+') // for cases when regex begin with spec char from 3-5
    {
        return -1;
    }
    for (int i = 1; i < strlen(regex); i++) // for cases when regex have '^' on illegal position
    {
        if (regex[i] == '^' && regex[i - 1] != '\\')
        {
            return -1;
        }
    }
    for (int i = 0; i < strlen(regex); i++) // Check whether there is something else illegal in the regex
    {
        if (regex[i] == '\\')
        {
            if (regex[i + 1] != '\\' && regex[i + 1] != '.' && regex[i + 1] != '*' && regex[i + 1] != '?' && regex[i + 1] != '+' && regex[i + 1] != '^')
            {
                return -1;
            }
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
            k = 0;
            for (int j = 0; j < strlen(new_regex); j++)
            {
                regex[j] = new_regex[j];
            }
            regex[strlen(new_regex)] = '\0';
        }
        else if (regex[i] == '.' || regex[i] == '*' || regex[i] == '?' || regex[i] == '+') 
        {	
            if (regex[i] == '*') 
            {
                position_spec_char = i;
                spec_char = regex[i];
            }
            if (regex[i] == '+')
            {
                position_spec_char = i;
                spec_char = regex[i];
            }
            if (regex[i] == '?')
            {
                position_spec_char = i;
                spec_char = regex[i];
            }
            counter_for_spec_char++;
            if (regex[i] == '.')
            {
                counter_for_spec_char--;
            }
            if (counter_for_spec_char > 1) // check whether there is two special chars form 3-5 in regex
            {
                return -1;
            }
	    // check whether there is two adjacent special chars form 2-5 in regex
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
            is_line_printed = false;
            counter_reps_char_before_spec_char = 0;
            file.getline(row, array_size);
            if (regex[0] == '^' && regex[1] == '\0') // if regex is '^'
            {
                cout << row << endl;
            }
            else if (regex[0] == '^' && regex[1] != '\0') //if regex is from type '^abcd'
            {
                for (int j = 1; j < strlen(regex); j++)
                {
                    if (row[j - 1] != regex[j])
                    {
                        if (regex[j] == '.')
                        {
                            continue;
                        }
                        possible_coincidence = false;
                        break;
                    }
                }
                if (possible_coincidence == true)
                {
                    cout << row << endl;
                    break;
                }
                else
                {
                    possible_coincidence = true;
                }
            }
            else if (position_spec_char == -1) //if regex is from type 'abcd' 
            {
                for (int i = 0; i < strlen(row) - strlen(regex) + 1; i++)
                {
                    for (int j = i; j < strlen(regex) + i; j++)
                    {
                        if (row[j] != regex[j - i])
                        {
                            if (regex[j - i] == '.')
                            {
                                continue;
                            }
                            possible_coincidence = false;
                            break;
                        }
                    }
                    if (possible_coincidence == true)
                    {
                        cout << row << endl;
                        break;
                    }
                    else
                    {
                        possible_coincidence = true;
                    }
                }
            }
            else if (position_spec_char == 1) //if regex is from type 'ab?cd', 'ab*cd', 'ab+cd'
            {
                for (int i = 0; i < strlen(row) - position_spec_char + 2; i++)
                {
                    if (row[i] == regex[2])
                    {
                        while (regex[position_spec_char - 1] == row[i - counter_reps_char_before_spec_char - 1])
                        {
                            counter_reps_char_before_spec_char++;
                        }
                        int j = 0;
                        while (j + 2 != strlen(regex))
                        {
                            if (row[i + j] != regex[2 + j])
                            {
                                break;
                            }
                            j++;
                        }
                        if (j + 2 == strlen(regex))
                        {
                            if (spec_char == '*')
                            {
                                is_line_printed = true;
                            }
                            if (spec_char == '?' && counter_reps_char_before_spec_char < 2)
                            {
                                is_line_printed = true;
                            }
                            if (spec_char == '+' && counter_reps_char_before_spec_char > 0)
                            {
                                is_line_printed = true;
                            }
                        }
                    }
                    if (is_line_printed == true)
                    {
                        cout << row << endl;
                        is_line_printed = false;
                        break;
                    }
                }
            }
            else
            {
                for (int i = 0; i < strlen(row) - position_spec_char + 2; i++)
                {
                    if (row[i] == regex[0])
                    {
                        int j = i;
                        while (j != position_spec_char - 1 + i)
                        {
                            if (row[j] != regex[j - i] && regex[j - i] != '.')
                            {
                                break;
                            }
                            j++;
                        }
                        if (j - i == position_spec_char - 1)
                        {
                            while (regex[position_spec_char - 1] == row[j + counter_reps_char_before_spec_char])
                            {
                                counter_reps_char_before_spec_char++;
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
                                if (spec_char == '*')
                                {
                                    is_line_printed = true;
                                }
                                if (spec_char == '?' && counter_reps_char_before_spec_char < 2)
                                {
                                    is_line_printed = true;
                                }
                                if (spec_char == '+' && counter_reps_char_before_spec_char > 0)
                                {
                                    is_line_printed = true;
                                }
                            }
                        }
                    }
                    if (is_line_printed == true)
                    {
                        cout << row << endl;
                        is_line_printed = false;
                        break;
                    }
                }
            }
        }
    }
    file.close(); // close massage.txt
    delete[] massage;
    delete[] regex;
    delete[] row;
    return 0;
}
