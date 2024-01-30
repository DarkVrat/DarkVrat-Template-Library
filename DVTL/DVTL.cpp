#include "headers/Map.h"

#include "headers/Vector.h"
#include "headers/Algorithm.h"

#include <iostream> 
#include <vector>
#include <algorithm>

template<typename T_Vector>
void coutVec(const T_Vector& vec) {
    for (size_t i = 0; i < vec.Size(); i++) {
        std::cout << vec[i] << ", ";
    }
    std::cout << std::endl;
}

int main() {
    DVTL::Vector<int> vecint(DVTL::Initializer_list<int>({ 1, 4, 5, 6, 1, -4, 7, 3, 7, 43, -14}));
    
    return 0;
}
