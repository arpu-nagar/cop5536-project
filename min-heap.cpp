#include <bits/stdc++.h>

class MinHeap {
   private:
    std::vector<int> heap;

    // Helper function to maintain the heap property
    void heapifyUp(int index) {
        while (index > 0) {
            int parentIndex = (index - 1) / 2;
            if (heap[index] < heap[parentIndex]) {
                std::swap(heap[index], heap[parentIndex]);
                index = parentIndex;
            } else {
                break;
            }
        }
    }

    // Helper function to maintain the heap property
    void heapifyDown(int index) {
        int leftChildIndex = 2 * index + 1;
        int rightChildIndex = 2 * index + 2;
        int smallestIndex = index;

        if (leftChildIndex < heap.size() &&
            heap[leftChildIndex] < heap[smallestIndex]) {
            smallestIndex = leftChildIndex;
        }

        if (rightChildIndex < heap.size() &&
            heap[rightChildIndex] < heap[smallestIndex]) {
            smallestIndex = rightChildIndex;
        }

        if (smallestIndex != index) {
            std::swap(heap[index], heap[smallestIndex]);
            heapifyDown(smallestIndex);
        }
    }

   public:
    // Insert a new element into the heap
    void insert(int value) {
        heap.push_back(value);
        heapifyUp(heap.size() - 1);
    }

    // Extract the minimum element from the heap
    int extractMin() {
        if (heap.empty()) {
            std::cerr << "Heap is empty!" << std::endl;
            return -1;  // You may choose to handle this differently based on
            // your requirements
        }

        int minValue = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        heapifyDown(0);

        return minValue;
    }

    int getMin() {
        if (heap.empty()) {
            std::cerr << "Heap is empty!" << std::endl;
            return -1;  // You may choose to handle this differently based on
            // your requirements
        }

        int minValue = heap[0];

        return minValue;
    }

    // Display the elements of the heap
    void display() {
        for (auto value : heap) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    MinHeap minHeap;

    minHeap.insert(5);
    minHeap.insert(3);
    minHeap.insert(8);
    minHeap.insert(1);
    minHeap.insert(7);

    std::cout << "Min Heap: ";
    minHeap.display();

    std::cout << "Extracted Min Value: " << minHeap.extractMin() << std::endl;

    std::cout << "Min Heap after extraction: ";
    minHeap.display();

    return 0;
}
