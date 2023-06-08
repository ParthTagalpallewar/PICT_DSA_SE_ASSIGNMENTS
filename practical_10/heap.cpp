#include<iostream>
using namespace std;

class Student{
    string name;
    int roll;

public:
    Student()
    {
        this->name = "";
        this->roll = -1;
    }

    Student(string name, int roll){
        this->name = name;
        this->roll = roll;
    }

    void display(){
        cout << "Student( " << name + ", " << roll << ") " << endl;
    }

    friend class Heap;

};

class Heap{

    int size, capacity;
    Student **heap;

    int parent(int i){
        return ((i-1)/2);
    }

    int left(int i){
        return (i*2 + 1);
    }

    int right(int i){
        return (i*2 + 2);
    }

    void swap(Student* &s1, Student* &s2){
        Student* temp = s1;
        s1 = s2;
        s2 = temp;
    }

    public:
        Heap(int capacity){
            this->capacity=capacity;
            size = 0;
            heap = new Student*[capacity];
        }

        void insert(Student* stud){
            if(size >= capacity){
                cout << "Heap is full" << endl;
                return;
            }

            int i = size;
            heap[size] = stud;
            size += 1;

            while(i>=0 && heap[i]->roll > heap[parent(i)]->roll){
                swap(heap[i], heap[parent(i)]);
                i = parent(i);
            }

        }

        void heapify(int i){

            int lc = left(i);
            int rc = right(i);
            int largest = i;

            if(lc <= size && heap[lc] > heap[largest]){
                largest = lc;
            }

            if(rc <= size && heap[rc] > heap[largest]){
                largest = rc;
            }

            if(largest != i){
                swap(heap[i], heap[largest]);
                heapify(largest);
            }
        }

        Student* getMax(){
            return heap[0];
        }

        Student* extractMax(){
            Student* max = heap[0];
            heap[0] = heap[size-1];
            size = size-1;

            heapify(0);
            return max;
        }

        void print(){
            for(int i=0; i<size; i++){
                 heap[i]->display();
            }
        }


};

int main(){
    
    int n;
    cin >> n;

    Heap heap(n);

    for(int i=0; i<n; i++){
        string name;
        int roll;

        cin >> name;
        cin >> roll;

        heap.insert(new Student(name, roll));
    }

    heap.print();

    return 0;
}