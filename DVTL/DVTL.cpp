#include "headers/Map.h"
#include <iostream>
#include <iomanip>

void printHelper(DVTL::Map<int, float>::Node* node, int indent) {
    if (node != nullptr) {
        printHelper(node->right, indent + 4);

        std::cout << std::setw(indent) << node->data.First << std::endl;

        printHelper(node->left, indent + 4);
    }
}

int main() {    
    DVTL::Map<int, float> mapIF;
    for (int i = 0; i < 63; i++) {
        mapIF.Insert(i, 0.f);
    }
    printHelper(mapIF.getroot(), 0);
    return 0;
}
