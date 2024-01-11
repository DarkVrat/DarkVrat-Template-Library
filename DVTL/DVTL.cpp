#include "headers/vector.h"

int main() {
	DVTL::vector<int> vec(5, 90);
	for (size_t i = 0; i < vec.size(); i++)
		int a = vec[i];

	DVTL::vector<int> hop;

	hop = vec;
}
