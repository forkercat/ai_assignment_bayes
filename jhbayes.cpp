#include "jhbayes.h"

#include <vector>
#include <set>
#include <map>
#include <iostream>
#include <math.h>

using namespace std;

JHBayes::JHBayes(const vector<Sample> temps, const set<string> labels) : samples(temps), classLabels(labels)
{
    // 成员初始化
    featureNum = samples[0].getFeatureNum();
    sampleNum = samples.size();
    all_means = vector<double>(featureNum, 0);
    all_variances = vector<double>(featureNum, 0);
    all_minVals = vector<double>(featureNum, 0);
    all_maxVals = vector<double>(featureNum, 0);

    // 计算某个类别的样本个数
    set<string>::iterator it;
    for (it = classLabels.begin(); it != classLabels.end(); ++it) {
        class_means[*it] = vector<double>(featureNum, 0);
        class_variances[*it] = vector<double>(featureNum, 0);
        classNum[*it] = 0;
    }
}

void JHBayes::goTraining()
{
    // 计算均值和方差
    calcPreData();
    // 特征缩放, 实际没有使用到.
    // featureScaling();
}

// 数据预处理
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

    // 计算各类均值和方差
    calcClassMeansAndVariancesData();
}

// 数据预处理, 进一步得到平均值和方差
void JHBayes::calcClassMeansAndVariancesData()
{
    // classNum
    for (unsigned int i = 0; i < sampleNum; ++i) {
        classNum[samples[i].getClassLabel()] += 1;
    }

    // iterate set
    set<string>::iterator it;
    for (it = classLabels.begin(); it != classLabels.end(); ++it) {

        // 类别平均值
        for (unsigned int i = 0; i < featureNum; ++i) {
            for (unsigned int j = 0; j < sampleNum; ++j) {
                string label = samples[j].getClassLabel();
                if (label.compare(*it) == 0) {
                    double val = samples[j].getFeature(i);
                    class_means[*it][i] += val;
                }
            }
            // 到最后一个求平均数
            class_means[*it][i] /= (double)classNum[*it];
        }

        // 类别方差
        for (unsigned int i = 0; i < featureNum; ++i) {
            for (unsigned int j = 0; j < sampleNum; ++j) {
                string label = samples[j].getClassLabel();
                if (label.compare(*it) == 0) {
                    double val = samples[j].getFeature(i);
                    class_variances[*it][i] += pow(val - class_means[*it][i], 2);
                }
            }
            // 到最后一个求方差数
            class_variances[*it][i] /= (double)(classNum[*it] - 1);
        }
    }
}


// 特征缩放
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

// 正态分布计算公式
double JHBayes::probGaussian(double val, double mean, double variance)
{
    return 1 / sqrt(2 * M_PI * variance) * exp(-pow(val - mean, 2) / (2 * variance));
}

// 预测
void JHBayes::predict(vector<double> predVec, map< string, double > &result)
{
    set<string>::iterator it;
    for (it = classLabels.begin(); it != classLabels.end(); ++it) {
        string classStr = *it;
        double val = 0.0;

        // 公式: P(f1|C) x P(f2|C) x P(f3|C) x P(C)
        double P_C = (double)classNum[classStr] / (double)samples.size();
        val = P_C;

        for (unsigned int i = 0; i < predVec.size(); ++i) {
            double P_val = 0.0;

            P_val = probGaussian(predVec[i], class_means[classStr][i], class_variances[classStr][i]);
            
            val *= P_val;   // 相当于: P(f1|C)
        }

        result[classStr] = val;
    }
}