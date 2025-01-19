#include <utility>

void heapify(int [], int n);
void sift_down(int [], int, int);

void heap_sort(int array[], int n) {
	int end;
	
	heapify(array, n);
	
	end = n - 1;
	
	while(end > 0) {
		std::swap(array[end], array[0]);
		
		end--;
		
		sift_down(array, 0, end);
	}
}

void heapify(int array[], int n) {
	int start = (n - 2)/2;
	
	while(start >= 0) {
		sift_down(array, start, n-1);
		start--;
	}
}

void sift_down(int array[], int start, int end) {
	int root = start;
	int child;
	int largest;
	
	while(2 * root + 1 <= end) {
		child = 2 * root + 1;
		largest = root;
		
		if(array[largest] < array[child]) {
			largest = child;
		}
		
		if(child + 1 <= end && array[largest] < array[child + 1]) {
			largest = child + 1;
		}
		
		if(largest == root) {
			return;
		} else {
			std::swap(array[root], array[largest]);
			root = largest;
		}
	}
}
