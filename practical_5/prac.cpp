
#include <iostream>
using namespace std;

class Pair{
private:
	int key;
	int value;
	Pair* next;
public:
	Pair(){
		this->key = -1;
		this->value = -1;
		next = NULL;
	}

	Pair(int key, int value){
		this->key = key;
		this->value = value;
	}

	void add_next(Pair* next){
		this->next = next;
	}

	bool has_next(){
		return this->next != NULL;
	}

	Pair* get_next(){
		return this->next;
	}

	friend class HashMap;
};



class HashMap{
private:
	Pair *arr[10];

	int hash(int key){
		return key % 10;
	}
public:
	HashMap(){
		for(int i=0; i < 10; i++){
			arr[i] = NULL;
		}
	}

	void insert(int key, int value){
		int hashcode = hash(key);

		Pair* curr = new Pair(key, value);

		if(arr[hashcode] == NULL){
			arr[hashcode] = curr;
		}else{

			Pair* temp = arr[hashcode];

			while(temp->has_next()){
				temp = temp->get_next();
			}

			temp->add_next(curr);
			cout << "Data Inserted Successfully" << endl;
		}
	}

	void find(int key){

		int hashcode = hash(key);

		if(arr[hashcode] == NULL){
			cout << "No key Found" << endl;
			return;
		}

		Pair* temp = arr[hashcode];

		while(temp != NULL && temp->key != key){
			temp = temp->get_next();
		}

		if(temp == NULL){
			cout << "No key Found" << endl;
			return;
		}

		cout << "Data at key " << key << " is " << temp->value << endl;
	}

	void delete_pair(int key){
		int hashcode = hash(key);

		if(arr[hashcode] == NULL){
			cout << "No key found to delete" << endl;
			return;
		}
		Pair* prev = NULL;
		Pair* temp = arr[hashcode];

		while(temp != NULL && temp->key != key){
			prev = temp;
			temp = temp->get_next();
		}

		if(temp == NULL){
			cout << "No key found to delete" << endl;
			return;
		}

		Pair* deleted = temp;
		prev->next = temp->next;


		cout << "Successfully Deleted key " << deleted->key << " value " << deleted->value << endl;
	}

	void print(){

		for(int i=0; i<10; i++){
			if(arr[i] == NULL){
				continue;
			}

			Pair* curr = arr[i];

			while(curr->has_next()){
				cout<<" (" << curr->key << ", " << curr->value << ") ";
				curr = curr->get_next();
			}

			cout<<" (" << curr->key << ", " << curr->value << ") ";

			cout << endl;
		}

	}
};

int main() {
	HashMap hashmap;


    int choice;
    int key, value;


    while(true)
    {
    	cout << endl;
        cout<<"Choose one of the following\nThe choices are: "<<endl;
        cout<<"1) Insert Data into HashMap"<<endl;
        cout<<"2) Find Data form HashMap"<<endl;
        cout<<"3) Delete Data form HashMap"<<endl;
        cout<<"4) Print All Data form HashMap"<<endl;
        cout<<"5) END"<<endl;
        cout << endl;
        cin>>choice;

        if(choice == 5){
        	break;
        }

		switch(choice){
			  case 1:
			  {
				  cout<<"Enter the key and value you wanted to insert in hashmap"<<endl;
				  cout<<"key to insert ";
				  cin>>key;
				  cout<<"value to insert ";
				  cin>>value;

				  hashmap.insert(key, value);
				  break;
			  }

			  case 2:
			  {

				  cout<<"key to insert " << endl;
				  cin>>key;

				  hashmap.find(key);

				  break;
			  }

			  case 3:
			  {

				  cout<<"key to delete " << endl;
				  cin>>key;

				  hashmap.delete_pair(key);

				  break;
			  }

			  case 4:
			  {

				  cout<<"Printing All Data " << endl;


				  hashmap.print();

				  cout << "All Data printed Successfully" << endl;

				  break;
			  }

			  default :
			  {
				  cout<<"You have entered an invalid choice";
				  break;
			  }

			 }
        }

	return 0;
}