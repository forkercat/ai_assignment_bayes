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
    void display();
    std::string getClassLabel() { return classLabel; }
    double getFeature(int index) { return features[index]; }

private:
    std::string classLabel;
    std::vector<double> features;
};

#endif // SAMPLE_H
