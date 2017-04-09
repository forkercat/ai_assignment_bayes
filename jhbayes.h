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

    std::vector<Sample> getSamples() { return samples; }
    std::set<std::string> getClassLabels() { return classLabels; }
    unsigned int getFeatureNum() { return featureNum; }
    unsigned int getSampleNum() { return sampleNum; }

    std::vector<double> get_all_means() { return all_means; }
    std::vector<double> get_all_variances() { return all_variances; }
    std::vector<double> get_all_maxVals() { return all_maxVals; }
    std::vector<double> get_all_minVals() { return all_minVals; }
    std::map< std::string, std::vector<double> > get_class_means() { return class_means; }
    std::map< std::string, std::vector<double> > get_class_variances() { return class_variances; }

    void goTraining();
    void predict(std::vector<double> predVec, std::map< std::string, double > &result);


private:
    std::vector<Sample> samples;
    std::set<std::string> classLabels;
    unsigned int featureNum;
    unsigned int sampleNum;
    std::vector<double> all_means;
    std::vector<double> all_variances;
    std::vector<double> all_maxVals;
    std::vector<double> all_minVals;

    // 用来计算高斯分布概率密度, 这里是与类有关, classated_*
    std::map< std::string, std::vector<double> > class_means;
    std::map< std::string, std::vector<double> > class_variances;
    std::map< std::string, int > classNum;

    void calcPreData();
    void calcClassMeansAndVariancesData();
    void featureScaling();
    double probGaussian(double val, double mean, double variance);
};

#endif // JHBAYES_H