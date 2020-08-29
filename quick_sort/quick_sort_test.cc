#include "quick_sort.h"
#include <assert.h>
#include <iostream>
#include <string>

using namespace sorting;

// NARGS(...) counts the length of the variadic arguments.
// https://stackoverflow.com/questions/11920577/casting-all-parameters-passed-in-macro-using-va-args
#define NARGS_SEQ(_1,_2,_3,_4,_5,_6,_7,_8, N, ...) N
#define NARGS(...) NARGS_SEQ(__VA_ARGS__, 8, 7, 6, 5, 4, 3, 2, 1, 0)

#define TEST(name, ...) 																	\
	void name() {																			\
		int arr[NARGS(__VA_ARGS__)] = {__VA_ARGS__};										\
		std::cout << "Before sorting: " << print(arr, NARGS(__VA_ARGS__)) << std::endl;		\
		quick_sort(arr, NARGS(__VA_ARGS__));												\
		verify_sorted(arr, NARGS(__VA_ARGS__));												\
	}																						\

std::string print(int arr[], int L) {
	std::string s;
	for (int i = 0; i < L; i++) {
		s.append(std::to_string(arr[i]));
		s.append(",");
	}
	return s;
}

void verify_sorted(int arr[], int L) {
	std::cout << "After sorting: " << print(arr, L) << std::endl;
	for (int i = 1; i < L; i++) {
		assert(arr[i] >= arr[i-1]);
	}
}

TEST(empty);
TEST(single_element, 1);
TEST(sorted, 1, 2, 3, 4, 5);
TEST(reverse_sorted, 6, 10, 8, 6, 4, 2, 0);
TEST(randomized, 100, 400, 19, 20, 300);

int main() {
	empty();	
	single_element();
	sorted();
	reverse_sorted();
	randomized();
}