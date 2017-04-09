#ifndef JHBAYES_H
#define JHBAYES_H

#include <string>
#include <vector>
#include <map>
#include <set>

#include "sample.h"

class JHBayes
{
public:
    JHBayes(const std::vector<Sample> temps, const std::set<std::string> labels);
    ~JHBayes() {}

    void goTraining();

private:
    std::vector<Sample> samples;
    std::set<std::string> classLabels;
    unsigned int featureNum;
    unsigned int sampleNum;
    std::vector<double> all_means;
    std::vector<double> all_variances;
    std::vector<double> all_maxVals;
    std::vector<double> all_minVals;

    // 用来计算高斯分布概率密度, 这里是与类有关, related_*
    std::map< std::string, std::vector<double> > rel_means;
    std::map< std::string, std::vector<double> > rel_variances;
    std::map< std::string, int > classNum;

    void calcPreData();
    void calcRelData();
    void featureScaling();
    double probGaussian(double val, double mean, double variance);
};

#endif // JHBAYES_H