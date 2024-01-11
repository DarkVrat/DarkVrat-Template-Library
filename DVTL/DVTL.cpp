#include "headers/allocator.h"

int main() {
	int* arr = DVTL::allocator<int>::allocate(5);
	DVTL::allocator<int>::construct(arr, 0, 5);
	DVTL::allocator<int>::destroy(arr, 0);
	DVTL::allocator<int>::deallocate(arr);
}
