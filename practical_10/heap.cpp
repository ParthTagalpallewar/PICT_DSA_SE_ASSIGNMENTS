#include<iostream>
using namespace std;

class Student{
    string name;
    int roll;

    public:
        Student(){
            this->name = "";
            this->roll = -1;
        }

        Student(string name, int roll){
            this->name = name;
            this->roll = roll;
        }
        
        void display(){
            cout << "Name: - " << name << " roll " << roll << endl;
        }

        friend class Heap;
};

class Heap{

    int capacity;
    int size;
    Student **heap;

    int parent(int i){return (i/2);}
    int left_child(int i) {
        return (2*i + 1);
    }
    int right_child(int i){
        return (2*i + 2);
    }

    void swap(Student* &s1, Student* &s2){
        Student* temp = s1;
        s1 = s2;
        s2 = temp;
    }

    void heapify(int i){
        int left = left_child(i);
        int right = right_child(i);
        int largest = i;

        if(left < size && heap[left]->roll > heap[largest]->roll){
            largest = left;
        }

        if(right < size && heap[right]->roll > heap[largest]->roll){
            largest = right;
        }

        if(largest != i){
            swap(heap[largest], heap[i]);
            heapify(largest);
        }
    }

    public:
    Heap(int capacity){
        capacity = capacity;
        size = 0;
        heap = new Student*[capacity];
    }

    void insert(Student *student){
        if(size == capacity)
            return;

        int curr = size;
        heap[size] = student;
        size += 1;

        while(curr > 0 && heap[curr]->roll > heap[parent(curr)]->roll){
            swap(heap[curr], heap[parent(curr)]);
            curr = parent(curr);
        }


    }
    
    Student* get_max(){

        if(size == 0) return NULL;

        Student* max = heap[0];

        heap[0] = heap[size-1];

        size -= 1;

        heapify(0);
        return max;
    }
};

// Getting the pointer of the student array
void heapSort(Student *arr[], int n)
{
    Heap maxHeap(n);

    // Build max heap
    for (int i = 0; i < n; i++)
        maxHeap.insert(arr[i]);

    // Extract max elements and place them at the end of the array
    for (int i = n - 1; i >= 0; i--)
        arr[i] = maxHeap.get_max(); // It changes the sequence of student array as it is a pointer
}

int main()
{
    const int numStudents = 5;

    // Student data (name, rank)
    Student *students[numStudents] = {
        new Student("Alice", 5), new Student("Bob", 2), new Student("Charlie", 9),
        new Student("David", 1), new Student("Eve", 3)};

    heapSort(students, numStudents);

    cout << "Sorted student data (ascending order of ranks):" << endl;
    for (int i = 0; i < numStudents; i++)
        students[i]->display();

    return 0;
}