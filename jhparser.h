#ifndef JHPARSER_H
#define JHPARSER_H

#include <string>
#include <vector>
#include <set>

#include "sample.h"

class JHParser
{
public:
    JHParser() {}
    ~JHParser() {}
    
    bool parseSamples(); // if error occurs, return false.
    bool parsePrediction(std::vector<double> &result);
    std::vector<Sample> getSamples() { return samples; }
    std::set<std::string> getClassLabels() { return classLabels; }
    void setInputText(std::string text) { inputText = text; }

private:
    std::string inputText;
    std::vector<Sample> samples;
    std::set<std::string> classLabels;

    void clearData();

    void replace_and_split(std::string &str, std::vector<std::string> &result);

    // e.g., 21121  21 -> 12 = 12121 = 11221 = 11212
    std::string & replace_sucessive(std::string &str, const std::string &old_value, const std::string &new_value);
    // e.g., 21121  21 -> 12 = 12112
    std::string & replace_distinct(std::string &str, const std::string &old_value, const std::string &new_value);
    // split text, e.g., "^*" can split ^^^^, ****, ^, *, etc.
    std::vector<std::string> split_string(std::string str, std::string pattern);
};

#endif // JHPARSER_H
