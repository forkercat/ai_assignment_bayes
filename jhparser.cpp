#include "jhparser.h"

#include <vector>
#include <string>
#include <sstream>
#include <set>

#include <iostream>

using namespace std;

void JHParser::clearData()
{
    samples.clear();
    classLabels.clear();
}

bool JHParser::parse()
{
    // 清空
    clearData();

    if (inputText.length() == 0) return false;

    // split samples
    vector<string> strResult;
    replace_and_split(inputText, strResult);

    // display and see see if ok?
    cout << "Parsing:" << endl;
    for (unsigned int i = 0; i < (strResult.size() > 5 ? 5 : strResult.size()); ++i) {
        cout << strResult[i] << endl;
    }
    cout << endl;

    if (strResult.size() < 2)  return false;

    // string -> double, split each sample
    // vector<Sample> result;
    // set<string> labels;
    for (unsigned int i = 0; i < strResult.size(); ++i) {
        string sampleStr = strResult[i];
        
        vector<string> sample_split;
        sample_split = split_string(sampleStr, " ");
        
        if (sample_split.size() <= 1) return false;

        string classStr = sample_split[0];

        // add to classLabels

        vector<double> features;
        for (unsigned int j = 1; j < sample_split.size(); ++j) {
            string temp = sample_split[j];
            features.push_back(atof(temp.c_str()));     // to double
        }
        
        // add to samples
        Sample sample(classStr, features);
        samples.push_back(sample);
        // add to classLabels
        classLabels.insert(classStr);
    }

    return true;
}

void JHParser::replace_and_split(string &str, std::vector<std::string> &result)
{
    // 想了半天只能这样了, 效果亲测可以.
    // this can format the text well, with no more blanks and lines.
    string str1 = replace_distinct(str, "\r", "#");
    string str2 = replace_distinct(str1, "\n", "#");
    string str3 = replace_distinct(str2, "# ", "#");
    string str4 = replace_distinct(str3, " #", "#");
    string str5 = replace_sucessive(str4, "  ", " ");
    result = split_string(str5, "#");
}

string & JHParser::replace_sucessive(string &str, const string &old_value, const string &new_value)
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

string & JHParser::replace_distinct(string &str, const string &old_value, const string &new_value)
{
    for (string::size_type pos(0); pos != string::npos; pos += new_value.length()) {
        if ((pos = str.find(old_value, pos)) != string::npos)
            str.replace(pos, old_value.length(), new_value);
        else
            break;
    }
    return str;
}

vector<string> JHParser::split_string(string str, string pattern)
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