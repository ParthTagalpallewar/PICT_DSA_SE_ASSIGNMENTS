#include <iostream>
using namespace std;

class Student {
public:
  string name;
  int rank;

  Student(const string &name, int rank) {
    this->name = name;
    this->rank = rank;
  }
};

class MaxHeap {
private:
  Student **heap;
  int capacity; // MAX number of data that can be stored
  int size;     // Current no. of data present

  int parent(int i) { return (i / 2); }

  int leftChild(int i) { return 2 * i + 1; }

  int rightChild(int i) { return 2 * i + 2; }

  void swap(Student *&a, Student *&b) {
    Student *temp = a;
    a = b;
    b = temp;
  }

  void maxHeapify(int i) {
    int left = leftChild(i);
    int right = rightChild(i);
    int largest = i;

    if (left < size && heap[left]->rank > heap[largest]->rank)
      largest = left;

    if (right < size && heap[right]->rank > heap[largest]->rank)
      largest = right;

    if (largest != i) {
      swap(heap[i], heap[largest]);
      maxHeapify(largest);
    }
  }

public:
  MaxHeap(int capacity) {
    this->capacity = capacity;
    heap = new Student *[capacity];
    size = 0;
  }

  void insert(Student *student) {
    if (size == capacity)
      return;

    size++;
    int currentIndex = size - 1;
    heap[currentIndex] = student;

    while (currentIndex > 0 &&
           heap[currentIndex]->rank > heap[parent(currentIndex)]->rank) {
      swap(heap[currentIndex], heap[parent(currentIndex)]);
      currentIndex = parent(currentIndex);
    }
  }

  Student *extractMax() {
    if (size == 0)
      return nullptr;

    Student *maxStudent = heap[0];
    heap[0] = heap[size - 1]; // last element of heap array
    size--;
    maxHeapify(0);

    return maxStudent;
  }
};


// Getting the pointer of the student array
void heapSort(Student *arr[], int n) {
  MaxHeap maxHeap(n);

  // Build max heap
  for (int i = 0; i < n; i++)
    maxHeap.insert(arr[i]);

  // Extract max elements and place them at the end of the array
  for (int i = n - 1; i >= 0; i--)
    arr[i] = maxHeap.extractMax(); // It changes the sequence of student array as it is a pointer
}

int main() {
  const int numStudents = 5;

  // Student data (name, rank)
  Student *students[numStudents] = {
      new Student("Alice", 5), new Student("Bob", 2), new Student("Charlie", 9),
      new Student("David", 1), new Student("Eve", 3)};

  heapSort(students, numStudents);

  cout << "Sorted student data (ascending order of ranks):" << endl;
  for (int i = 0; i < numStudents; i++)
    cout << students[i]->name << ": Rank " << students[i]->rank << endl;

  return 0;
}
