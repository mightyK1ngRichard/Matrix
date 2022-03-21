#include "Header.h"

int main() {
	matrix<double> arr(2, 2);
	matrix<double> arr1(2, 2);
	matrix<double> arr2(2, 2);
	for (size_t i = 0; i < 2; i++) {
		for (size_t j = 0; j < 2; j++) {
			arr1[i][j] = i;
			arr2[i][j] = i;
		}
	}
	arr = arr1 + arr2;

	return 0;
}
