
#include<iostream>
#include<fstream>

using namespace std;
class Student {

public:
    string name;
    int roll_no;
    int div;
    string address;

    Student() {
        name = "";
        roll_no = 0;
        div = 0;
        address = "";
    }

void read_data() {
    cout << "Enter the name : ";
    cin >> name;
    cout << "Enter roll no. :";
    cin >> roll_no;
    cout << "Division : ";
    cin >> div;
    cout << "Address : ";
    cin >> address;
}

void printData() {
    cout << "Name : " << name << endl;
    cout << "Roll no. : " << roll_no << endl;
    cout << "Division : " << div << endl;
    cout << "Address : " << address << endl;
}

friend class StudDatabase;

};

class StudDatabase {

Student st;
fstream file;

public:

void add_data() {
    file.open("new.txt", ios::app);
    cout << "Enter the name : ";
    cin >> st.name;
    cout << "Enter roll no. :";
    cin >> st.roll_no;
    cout << "Division : ";
    cin >> st.div;
    cout << "Address : ";
    cin >> st.address;

    file << endl << "Name : " << st.name << endl;
    file << "Roll no : " << st.roll_no << endl;
    file << "Division : " << st.div << endl;
    file << "Address : " << st.address << endl;

    file.close();
}

void print_data() {

    file.open("new.txt", ios::in);
    string tp;
    while (getline(file, tp)) { //read data from file object and put it into string.
        cout << tp << "\n";   //print the data of the string
    }
    file.close();
}

void search() {
cout << "Search" << endl;
}

};

int main() {

StudDatabase s;

int choice;
bool flag = true;

while (flag) {
cout << "---STUDENT DATABASE---" << endl;
cout << "1. Add a Student." << endl;
cout << "2. Display all Students" << endl;
cout << "3. Search a Student" << endl;
cout << "4. Exit" << endl;

cout << "Enter your Choice : ";
cin >> choice;

if (choice == 1) {
s.add_data();
} else if (choice == 2) {
s.print_data();
} else if (choice == 3) {
s.search();
} else if (choice == 4) {
flag = false;
cout << "Exited..." << endl;
} else {
cout << "Invalid Input!" << endl;
cout << "Enter valid Input..." << endl;
}
}

return 0;

}