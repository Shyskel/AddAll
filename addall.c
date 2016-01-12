// Name: Tyler Gauntlett
// NID: ty340586
// Date: 11/17/2015
// Course: Fall COP 3502


#include <stdio.h>
#include <stdlib.h>

struct heapStruct {

	int* heapArray;
	int size;
	int cost;
};


struct heapStruct* initHeap(int capacity);
void insert(struct heapStruct *h, int value);
void percolateUp(struct heapStruct *h, int index);
void percolateDown(struct heapStruct *h, int index);
void findSum(struct heapStruct *heap);
int removeMin(struct heapStruct *h);
int minimum(int a, int indexa, int b, int indexb);
void swap(struct heapStruct *h, int index1, int index2);


int main(){

	// Initialize variables.
	struct heapStruct *minHeap;
	int caseNumber, numOfInput;

	// Loop based on number of test cases.
	scanf("%i", &caseNumber);
	while (caseNumber > 0){

		scanf("%d", &numOfInput);

		// Initilize heap using minimum number of 
		// memory required.
		minHeap = initHeap(numOfInput);

		// Loop based on number of integers to be used
		// as input.
		while (numOfInput > 0){

			int input;
			scanf("%d", &input);

			// Inserts each element into the minHeap.
			insert(minHeap, input);

			numOfInput--;
		}

		// Function that will alter minHeap->cost to represent
		// the total cost for adding the numbers together.
		findSum(minHeap);

		// Print the cost.
		printf("%d\n", minHeap->cost);

		// Decrement count and free array/struct before 
		// processing the next case.
		caseNumber--;
		free(minHeap->heapArray);
		free(minHeap);
	}

	return 0;
}


// Allocates space for the heap/heap->heapArray,
// set the size/cost to 0, and set capacity to input value.
struct heapStruct* initHeap(int capacity) {

	struct heapStruct* minHeap;
	minHeap = (struct heapStruct*)(malloc(sizeof(struct heapStruct)));
	minHeap->heapArray = (int*)malloc(sizeof(int)*(capacity + 1));
	minHeap->cost = 0;
	minHeap->size = 0;
	return minHeap;
}


// Inserts the value into the next avaible spot in the heapArray.
void insert(struct heapStruct *heap, int value) {
	
	heap->size++;
	heap->heapArray[heap->size] = value;
	percolateUp(heap, heap->size);
	
}


// Moves the value into a higher slot in the array
// based on its maginitued.
void percolateUp(struct heapStruct *heap, int index) {

	// Can only percolate up if the node isn't the root.
	if (index > 1) {

		// See if our current node is smaller in value than its parent.        
		if (heap->heapArray[index / 2] > heap->heapArray[index]) {

			// Move our node up one level.
			swap(heap, index, index / 2);

			// See if it needs to be done again.
			percolateUp(heap, index / 2);
		}
	}
}

// Moves the value into a lower slot in the array
// based on its maginitued.
void percolateDown(struct heapStruct *h, int index) {

	int min;

	// Only try to percolate down internal nodes.
	if ((2 * index + 1) <= h->size) {

		// Find the minimum value of the two children of this node.            
		min = minimum(h->heapArray[2 * index], 2 * index, h->heapArray[2 * index + 1], 2 * index + 1);

		// If this value is less than the current value, then we need to move
		// our current value down the heap.  
		if (h->heapArray[index] > h->heapArray[min]) {
			swap(h, index, min);

			// This part is recursive and allows us to continue percolating
			// down the element in question.
			percolateDown(h, min);
		}
	}

	// Case where our current element has exactly one child, a left child.
	else if (h->size == 2 * index) {

		// Here we only compare the current item to its only child.
		// Clearly, no recursive call is needed since the child of this node
		// is a leaf. 
		if (h->heapArray[index] > h->heapArray[2 * index])
			swap(h, index, 2 * index);
	}
}


// Function that finds the lowest cost required.
void findSum(struct heapStruct *heap){

	int sum;

	// Loop that starts/stops when there are more than 2 integers
	// in the heap.
	while(heap->size > 1){

		// Stores the minimum value in the heap in two variables.
		int min1 = removeMin(heap);
		int min2 = removeMin(heap);
		
		// Both vairables must contain valid heap integers.
		if (min1 != -1 && min2 != -1){

			// Add them together.
			sum = min1 + min2;

			// Insert the new sum between two integers back into the heap.
			insert(heap, sum);

			// Keep a running total cost required for all the addition.
			heap->cost = heap->cost + sum;
		}
			
		// When a value is stored in the first variable, but the heap runs
		// out of values to store into the second variable.
		else if (min1 != -1 && min2 == -1){

			// Keep a running total cost required for all the addition.
			heap->cost = heap->cost + min1;
		}

		// Loop should always break before getting here, but in case
		// both variables contain -1, then the heap is completely
		// empty.
		else break;

	}

}


// Removes the lowest values (the root) in the heap.
int removeMin(struct heapStruct *heap) {

	int retval;

	// Only remove an element if they heap contains at least
	// one element.
	if (heap->size > 0) {

		// Minimum value is always stored at the root.
		retval = heap->heapArray[1];

		// Copy the last value into this top slot.
		heap->heapArray[1] = heap->heapArray[heap->size];

		// Decrese size after removing the value.
		heap->size--;

		// Need to let this value move down to its rightful spot in the heap.
		percolateDown(heap, 1);

		// Now we can return our value.
		return retval;
	}

	// No value to return, indicate failure with a -1.
	else
		return -1;
}


// Returns the smaller of two values.
int minimum(int a, int indexa, int b, int indexb) {

	// Return the value associated with a.    
	if (a < b)
		return indexa;

	// Return the value associated with b.
	else
		return indexb;
}


// Swaps the values stored in the heap pointed to by h in index1 and index2.
void swap(struct heapStruct *heap, int index1, int index2) {
	int temp = heap->heapArray[index1];
	heap->heapArray[index1] = heap->heapArray[index2];
	heap->heapArray[index2] = temp;
}