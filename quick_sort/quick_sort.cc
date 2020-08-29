namespace sorting {

namespace {

void swap(int arr[], int i, int j) {
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

int partition(int arr[], int l, int r) {
	int ref = arr[r];
	int i = l - 1;

	for (int j = l; j < r; j++) {
		if (arr[j] < ref) {
			i++;
			swap(arr, i, j);		
		}
	}

	swap(arr, i + 1, r);
	return i + 1;
}

void quick_sort(int arr[], int l, int r) {
	if (l >= r) 
		return;
    int pivot = partition(arr, l, r);
    quick_sort(arr, l, pivot - 1);
    quick_sort(arr, pivot + 1, r);
}	

}

void quick_sort(int arr[], int len) {
	quick_sort(arr, 0, len - 1);
}

}