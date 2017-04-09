#include "sample.h"

#include <iostream>

// 显示数据, 调试
void Sample::display()
{
    std::cout << "ClassLabel:" << classLabel << std::endl;
    for(unsigned int i = 0; i < features.size(); ++i) {
        std::cout << "feature:" << features[i] << " ";
    }
    std::cout << std::endl;
}
