#include "headers/Map.h"
#include <iostream>
#include <iomanip>

void printHelper(DVTL::Map<int, float>::Node* node, int indent) {
    if (node != nullptr) {
        printHelper(node->right, indent + 8);

        if (node->parent == nullptr) {
            std::cout << std::setw(indent) << "X/" << node->data.First << std::endl;
        }
        else {
            std::cout << std::setw(indent) << node->parent->data.First<<"/" << node->data.First << std::endl;
        }

        printHelper(node->left, indent + 8);
    }
}

int main() {   
        DVTL::Map<int, float> mapIF;
        for (int i = 0; i < 15; i++) {
            mapIF.Insert(i, 0.f);
        }

        printHelper(mapIF.getroot(), 0);

        for (int i = 0; i < 5; i++) {
            int a;
            std::cin >> a;
            mapIF.Erase(a);
            printHelper(mapIF.getroot(), 0);
        }
    
    return 0;
}
