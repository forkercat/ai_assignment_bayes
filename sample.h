#ifndef SAMPLE_H
#define SAMPLE_H

#include <string>
#include <vector>

class Sample
{
public:
    Sample(
        const std::string &label,
        const std::vector<double> feature) : classLabel(label), features(feature) {}
    ~Sample() {}
    void display();     // 显示数据
    std::string getClassLabel() { return classLabel; }      // 获得样本类别
    double getFeature(int index) { return features[index]; }    // 获得样本第i个属性
    void setFeature(int index, double val) { features[index] = val; }   // 设置样本第i个属性
    unsigned int getFeatureNum() { return features.size(); }    // 获得特征个数

private:
    std::string classLabel;     // 样本类别
    std::vector<double> features;   // 特征集
};

#endif // SAMPLE_H
