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
    
    // 解析样本
    bool parseSamples(); // 解析出错返回false

    // 解析预测输入
    bool parsePrediction(std::vector<double> &result);

    // 获得样本集
    std::vector<Sample> getSamples() { return samples; }

    // 获得类别集
    std::set<std::string> getClassLabels() { return classLabels; }

    // 设置原始文本
    void setInputText(std::string text) { inputText = text; }

private:
    std::string inputText;
    std::vector<Sample> samples;
    std::set<std::string> classLabels;

    // 清空成员数据
    void clearData();

    // 替换且分割字符
    void replace_and_split(std::string &str, std::vector<std::string> &result);

    // 替换和分割的详细方法
    // e.g., 21121  21 -> 12 = 12121 = 11221 = 11212
    std::string & replace_sucessive(std::string &str, const std::string &old_value, const std::string &new_value);
    // e.g., 21121  21 -> 12 = 12112
    std::string & replace_distinct(std::string &str, const std::string &old_value, const std::string &new_value);
    // split text, e.g., "^*" can split ^^^^, ****, ^, *, etc.
    std::vector<std::string> split_string(std::string str, std::string pattern);
};

#endif // JHPARSER_H
