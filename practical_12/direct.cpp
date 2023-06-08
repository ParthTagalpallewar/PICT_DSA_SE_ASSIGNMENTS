#include<iostream>
#include<fstream>
#include<string.h>

using namespace std;

class Student{
    int roll;
    char name[20];

    public:
    Student(){
        this->roll = -1;
        strcpy(name, "");
    }

    void take_input(){
        cout << "Enter roll no of student: ";
        cin >> roll;

        cout << "Enter name of student: ";
        cin.getline(name, 20);
        cin >> name;
    }

    void show(){
        cout << "Student(" << name << ", " << roll << endl << ")";
    }

    friend class DB;
};

class DB{

    string fname = "stud.dat";

public:
    void init(){

        ifstream ifs;
        ifs.open(fname, ios::binary);

        if(!ifs){
            //creating new file 
            ofstream of;
            of.open(fname, ios::out | ios::binary);

            //put dummy data
            Student dummy;
            for(int i=0; i<10; i++){
                of.write((char *)&dummy, sizeof(Student));
            }
            
            of.close();
        }

        ifs.close();

    }

    int get_hash(int roll){
        return roll%10;
    }

    void insert(){

        Student st;
        st.take_input();

        fstream fs;
        fs.open(fname, ios::binary | ios::in | ios::out);

        int hash = get_hash(st.roll);

        fs.seekp(hash*sizeof(Student), ios::beg);

        fs.write((char *)&st, sizeof(Student));

        cout << "Student saved successfully" << endl;

        fs.close();

    }

    void read_all(){

        fstream fs;
        fs.open(fname, ios::in | ios::out | ios::binary);

        Student st;

        fs.read((char *)&st, sizeof(Student));
        for(int i=0; i<10; i++){

            fs.seekg(i*sizeof(Student), ios::beg);


            if(st.roll != -1){
                st.show();
            }

            fs.read((char *)&st, sizeof(Student));
        }

        fs.close();

    }

    void del(){
        int roll;
        cout << "Enter roll number of user you want to delete " << endl;
        cin >> roll;

        int hash = get_hash(roll);

        fstream fs;
        fs.open(fname, ios::in | ios::out | ios::binary);

        fs.seekg(hash*sizeof(Student), ios::beg);

        Student st;

        fs.read((char*)&st, sizeof(st));

        if(st.roll == -1){
            cout << "Data does not exist" << endl;
            fs.close();
            return;
        }

        fs.seekp(hash * sizeof(Student), ios::beg);
        Student dummy;

        fs.write((char *)&dummy, sizeof(Student));

        cout << "Student Deleted Successfully!" << endl;

        fs.close();
    }
};

int main()
{

    // Object to do
    DB d;
    d.init();

    // driver program
    bool flag = true;

    int ch;

    while (true)
    {
        cout << "\nDIRECT ACCESS FILE" << endl;
        cout << "1. Save Data" << endl;
        cout << "2. Read Data" << endl;
        cout << "3. Delete Data" << endl;
        cout << "4. Exit..." << endl;

        cout << "Enter Your choice: ";
        cin >> ch;

        switch (ch)
        {
        case 1:
            d.insert();
            break;
        case 2:
            d.read_all();
            break;
        case 3:
            d.del();
            break;
        case 4:
            cout << "Exiting..." << endl;
            flag = false;
            break;
        }
    }

    return 0;
}