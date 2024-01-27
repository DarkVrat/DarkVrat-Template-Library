#include "headers/Map.h"
#include <iostream>
#include <iomanip>
#include <map>

void printHelper(DVTL::Map<int, float>::Node* node, int indent) {
    if (node != nullptr) {
        printHelper(node->right, indent + 2);

        if(node->parent==nullptr)
            std::cout << std::setw(indent) << node->data.First << std::endl;
        else if(node==node->parent->left)
            std::cout << std::setw(indent) << "\\" << node->data.First << std::endl;
        else
            std::cout << std::setw(indent) << "/" << node->data.First << std::endl;

        printHelper(node->left, indent + 2);
    }
}

int main() {   
        DVTL::Map<int, float> mapIF;
        for (int i = 0; i < 31; i++) {
            mapIF.Insert(i, 0.f);
        }

        auto it = mapIF.Begin();

        std::cout << it->First << std::endl;

        for (int i = 0; i < 15; i++) {
            it++;
            std::cout << it->First << std::endl;
        }
        for (int i = 0; i < 12; i++) {
            it--;
            std::cout << it->First << std::endl;
        }
    
    return 0;
}
