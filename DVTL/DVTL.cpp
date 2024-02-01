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
    DVTL::Vector<int> vecint(DVTL::Initializer_list<int>({ 1, 1, 77, 8, 42, 76, 61, 9, 86, 41, 70, 1 }));

    coutVec(vecint);
    DVTL::Stable_partition(vecint.Begin(), vecint.End(), [](int a) {return a % 2 == 0; });
    coutVec(vecint);
    DVTL::Next_permutation(vecint.Begin(), vecint.End());
    coutVec(vecint);
    DVTL::Prev_permutation(vecint.Begin(), vecint.End());
    coutVec(vecint);

    
    

    return 0;
}
