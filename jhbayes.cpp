#include "jhbayes.h"

#include <vector>
#include <set>
#include <map>
#include <iostream>
#include <math.h>

using namespace std;

JHBayes::JHBayes(const vector<Sample> temps, const set<string> labels) : samples(temps), classLabels(labels)
{
    featureNum = samples[0].getFeatureNum();
    sampleNum = samples.size();
    all_means = vector<double>(featureNum, 0);
    all_variances = vector<double>(featureNum, 0);
    all_minVals = vector<double>(featureNum, 0);
    all_maxVals = vector<double>(featureNum, 0);

    // rel
    set<string>::iterator it;
    for (it = classLabels.begin(); it != classLabels.end(); ++it) {
        rel_means[*it] = vector<double>(featureNum, 0);
        rel_variances[*it] = vector<double>(featureNum, 0);
        classNum[*it] = 0;
    }
}

void JHBayes::goTraining()
{
    // 计算均值和方差
    calcPreData();
    // 特征缩放
    // featureScaling();
    // 再计算一次
    // calcPreData();

    calcRelData();

}

void JHBayes::calcPreData()
{
    // all
    // 平均数 和 最大/小值
    for (unsigned int i = 0; i < featureNum; ++i) {
        for (unsigned int j = 0; j < sampleNum; ++j) {
            double val = samples[j].getFeature(i);
            all_means[i] += val;

            // 求最大/小值
            if (j == 0) {
                all_minVals[i] = all_maxVals[i] = val;
            } else {
                if (val < all_minVals[i]) {
                    all_minVals[i] = val;
                }
                if (val > all_maxVals[i]) {
                    all_maxVals[i] = val;
                }
            }
        }
        // 到最后一个求平均数
        all_means[i] /= (double)sampleNum;
    }

    // 求方差
    for (unsigned int i = 0; i < featureNum; ++i) {
        for (unsigned int j = 0; j < sampleNum; ++j) {
            double val = samples[j].getFeature(i);
            all_variances[i] += pow(val - all_means[i], 2);
        }
        // 到最后一个求平均数
        all_variances[i] /= (double)sampleNum;
    }
}

void JHBayes::calcRelData()
{
    // classNum
    for (unsigned int i = 0; i < sampleNum; ++i) {
        classNum[samples[i].getClassLabel()] += 1;
    }

    // iterate set
    set<string>::iterator it;
    for (it = classLabels.begin(); it != classLabels.end(); ++it) {

        // rel_means
        for (unsigned int i = 0; i < featureNum; ++i) {
            for (unsigned int j = 0; j < sampleNum; ++j) {
                string label = samples[j].getClassLabel();
                if (label.compare(*it) == 0) {
                    double val = samples[j].getFeature(i);
                    rel_means[*it][i] += val;
                }
            }
            // 到最后一个求平均数
            rel_means[*it][i] /= (double)classNum[*it];
        }

        // rel_variances
        for (unsigned int i = 0; i < featureNum; ++i) {
            for (unsigned int j = 0; j < sampleNum; ++j) {
                string label = samples[j].getClassLabel();
                if (label.compare(*it)) {
                    double val = samples[j].getFeature(i);
                    rel_variances[*it][i] += pow(val - rel_means[*it][i], 2);
                }
            }
            // 到最后一个求平均数
            rel_variances[*it][i] /= (double)classNum[*it];
        }
    }
}



void JHBayes::featureScaling()
{
    for (unsigned int i = 0; i < sampleNum; ++i) {
        for (unsigned int j = 0; j < featureNum; ++j) {
            double val = samples[i].getFeature(j);
            val = (val - all_means[j]) / (all_maxVals[j] - all_minVals[j]);
            samples[i].setFeature(j, val);
        }
    }
}

double JHBayes::probGaussian(double val, double mean, double variance)
{
    return 1 / sqrt(2 * M_PI * variance) * exp(-pow(val - mean, 2) / (2 * variance));
}