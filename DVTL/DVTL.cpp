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
    DVTL::Vector<int> vecint(DVTL::Initializer_list<int>({ 4, 5,1, 6, 1, -4, 7,1, 3,1, 7, 43, -14}));

    coutVec(vecint);
    DVTL::Make_heap(vecint.Begin(), vecint.End());
    coutVec(vecint);
   
    DVTL::Remove(vecint.Begin(), vecint.End(), 1);
    coutVec(vecint);

    return 0;
}
