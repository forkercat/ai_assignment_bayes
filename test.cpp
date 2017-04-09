#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include <math.h>

using namespace std;

string &replace_all(string &str, const string &old_value, const string &new_value)
{
    while (true) {
        string::size_type pos(0);
        if ((pos = str.find(old_value)) != string::npos)
            str.replace(pos, old_value.length(), new_value);
        else
            break;
    }
    return str;
}

string &replace_all_distinct(string &str, const string &old_value, const string &new_value)
{
    for (string::size_type pos(0); pos != string::npos; pos += new_value.length()) {
        if ((pos = str.find(old_value, pos)) != string::npos)
            str.replace(pos, old_value.length(), new_value);
        else
            break;
    }
    return str;
}

vector<string> split_string(string str, string pattern)
{
    vector<string> result;
    if (pattern.empty())
        return result;
    size_t start = 0, index = str.find_first_of(pattern, 0);
    while (index != str.npos) {
        if (start != index)
            result.push_back(str.substr(start, index - start));
        start = index + 1;
        index = str.find_first_of(pattern, start);
    }
    if (!str.substr(start).empty())
        result.push_back(str.substr(start));
    return result;
}

int main(int argc, char **argv)
{
    stringstream stream;
    string str = "123123   321312 3232 3 3232 \n\r2323 sfa 32fd  fadfa   fdfd\n\r\n\r\n\r fafa  fadf afdaf   323";

    string str1 = replace_all_distinct(str, "\r", "#");
    string str2 = replace_all_distinct(str1, "\n", "#");
    string str3 = replace_all_distinct(str2, "# ", "#");
    string str4 = replace_all_distinct(str3, " #", "#");
    string str5 = replace_all(str4, "  ", " ");

    string pattern = "#";
    vector<string> result = split_string(str5, pattern);

    cout << "The result:" << endl;
    for (int i = 0; i < result.size(); i++) {
        cout << result[i] << endl << endl;
    }

    
    cout << 1 / sqrt(2 * M_PI * 0.035) * exp(-pow(6 - 5.855, 2) / (2 * 0.035)) << endl;
    
    return 0;
}
