#include<iostream>
#include<fstream>

using namespace std;
const string filename = "data.bin";

class Student{
    public:
        string name;
        int id;

        Student(){
            name = "";
            id = -1;
        }

        Student(string name, int id){
            this->name = name;
            this->id = id;
        }
};

int main(){

    Student s1("Student One", 5);
    Student s2("Student two", 6);

    //writing 10 entries
    fstream fs1(filename, ios::app | ios::binary);

    for(int i=0; i<10; i++){
        Student s("", -1);

        fs1.seekp(s1.id * sizeof(s), ios::beg);
        fs1.write(reinterpret_cast<const char *>(&s), sizeof(s));
    }

    fs1.close();
    //completed

    fstream fs(filename, ios::app | ios::binary);
    
    fs.seekp(s1.id*sizeof(s1), ios::beg);
    fs.write(reinterpret_cast<const char*>(&s1), sizeof(s1));

    fs.seekp(s2.id*sizeof(s2), ios::beg);
    fs.write(reinterpret_cast<const char*>(&s2), sizeof(s2));
    
    fs.close();

    cout << "Write operation completed" << endl;

    fstream fss(filename, ios::in | ios::binary);
    Student ss1;

    fss.seekg((s1.id*sizeof(s1))-sizeof(s1), ios::beg);

    fss.read(reinterpret_cast<char*>(&ss1), sizeof(s1));

    cout << "Read Completed" << endl;
    cout << "Student( " << ss1.name << ", " << ss1.id <<" )" << endl;

    fss.close();


    return 0;
}