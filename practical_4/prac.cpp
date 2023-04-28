/*
Group B 4 Consider telephone book database of N clients. Make use of a hash table
implementation to quickly look up client‘s telephone number. Make use of two collision 
 handling  techniques  and  compare  them  using  number  of  comparisons required  to  find  a  set  of  telephone  numbers 
 (Note:  Use  linear  probing  with replacement and without replacement)
*/
#include<iostream>
using namespace std;

class Pair{
private:
    int key;
    int value;
public:
    Pair(){
        key = -1;
        value = -1;
    }

    Pair(int key, int value){
        this->key = key;
        this->value = value;
    }

    friend class HashTable;
};

class HashTable{
private:
    int size = 10;

    Pair* arr[10];

    int hash(int n){
        return n%size;
    }

    void place_at_proper_position(Pair* pair, int index){
        for (int i = 0; i < size; i++)
        {
            int curr_index = (index + i) % size;

            if (arr[curr_index]->key == -1)
            {
                arr[curr_index] = pair;
               
                return;
            }
        }

        cout << "Overflow" << endl;
    }

public:
    HashTable(){
        for(int i=0; i<size; i++){
           arr[i] = new Pair();
        }
    }
    void print(){
        for(int i=0; i<size; i++){
           cout << arr[i]->key << " " << arr[i]->value << endl;
        }
    }

    void insert_without_replacement(int key, int value){
        int index = hash(key);

        for(int i=0; i<size; i++){
            int curr_index = (index+i)%size;

            if(arr[curr_index]->key == -1){
                arr[curr_index]->key = key;
                arr[curr_index]->value = value;
                return;
            }
           
        }

        cout << "Overflow" << endl;
    }

    void insert_with_replacement(int key, int value){
        int index = hash(key);

        //if current index is free
        if(arr[index]->key == -1){
            arr[index]->key = key;
            arr[index]->value = value;
            return;
        }else{

            //cond 1: num present at current position is not expected to be present
            //cond 2: num present at current position is correct ahe need to find next free space to place it
            Pair* prev = NULL;
            //cond 1:
            if(arr[index]->key%size != key%size){
                prev = arr[index];
                arr[index] = new Pair(key, value);
            }

            if(prev == NULL) prev = new Pair(key, value);

            place_at_proper_position(prev, index+1);
        } 
    }

    int get(int key){

        int index = hash(key);

        for (int i = 0; i < size; i++)
        {
            int curr_index = (index + i) % size;

            if (arr[curr_index]->key == key)
            {
                return arr[curr_index]->value;
            }
        }

        cout << "Data not found" << endl;
    }
};

int main(){
    HashTable hashTable;
  
    hashTable.insert_with_replacement(57, 1000);
    hashTable.insert_with_replacement(67, 1000);
    hashTable.insert_with_replacement(68, 1000);
  
    hashTable.print();

    return 0;
}