#include<iostream>
#include<string.h>
#include<fstream>
using namespace std;

class Student{
    int roll;
    char name[20];
   

    public:
    Student()
    {
        this->roll = -1;
        strcpy(name, "");
        
    }

    void take_input(){
        cout << "Enter Roll No :- ";
        cin >> roll;
        cout << "Enter Name:  " ;
        cin.getline(name, 19);
        cin >> name;
        cout << endl;
    }

    void show(){
        cout << "Student(" << name << ", " << roll << ") " << endl; 
    }

    friend class DB;
};

class DB{

    public:

        void insert(){
            Student stud;
            stud.take_input();
            stud.show();

            fstream fs;

            fs.open("stud.dat", ios::app | ios::binary);

            fs.write((char *)&stud, sizeof(stud));

            fs.close();

            cout << "Student Inserted successfully" << endl;
        }

        void print_all(){

            Student s;

            fstream fs;
            fs.open("stud.dat", ios::in | ios::binary);

            if (!fs.is_open())
            {
                cout << "File Not Found!!" << endl;
                return;
            }

            fs.read((char *)&s, sizeof(s));
            while (!fs.eof())
            {
                s.show();
                fs.read((char *)&s, sizeof(s));
            }

            cout << endl;
            cout << endl;

            fs.close();

        }
        
        void search(){
            cout << "Enter student you wanted to search ";
            string stud;
            cin >> stud;

            fstream fin;
            fin.open("stud.dat", ios::in | ios::binary);
            Student s;
            fin.read((char *)&s, sizeof(s));
            while(!fin.eof()){

                if(s.name == stud){
                    s.show();
                }

                fin.read((char *)&s, sizeof(s));
            }

            fin.close();
        }

        void del(){
            string name;
            cout << "Enter Name of student to remove " << endl;
            cin >> name;

            fstream fs("stud.dat", ios::in | ios::binary);
            fstream fout("temp.dat", ios::app | ios::binary);

            Student st;
            fs.read((char *)&st, sizeof(st));
            while(!fs.eof()){

                if(st.name == name){
                    st.show();
                }else{
                    fout.write((char *)&st, sizeof(st));
                }


                fs.read((char *)&st, sizeof(st));
            }

            remove("stud.dat");
            rename("temp.dat", "stud.dat");


        }
};

int main()
{
        cout << "Sequential Files in CPP" << endl; // prints Hashing

        DB s1;

        bool flag = true;
        string data;

        while (flag)
        {
            cout << endl << endl;
            cout << "1. Add new Student (save)" << endl;
            cout << "2. Display All Students" << endl;
            cout << "3. Search Student" << endl;
            cout << "4. Delete Student" << endl;
            cout << "5. Exit..." << endl;
            int ch;
            cout << "\nEnter Your Choise: ";
            cin >> ch;

            switch (ch)
            {
            case 1:
                s1.insert();
                break;
            case 2:
                s1.print_all();
                break;

            case 3:
                s1.search();
                break;
            case 4:
                s1.del();
                break;
            case 5:
                cout << "Exiting...";
                flag = false;
                break;
            default:
                cout << "Invalid Entry" << endl;
                break;
            }
        }
        return 0;
}