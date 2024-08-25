#include <iostream>
#include <string.h>
#include <fstream>
#include <iomanip>
using namespace std;

void addRecord();         // function to write data to file from memory
void showAll();           // function to read data from file to memory
void searchByRollNo();    // function to display data on query from file to memory
void deleteRecord();      // function to delete data from file
void viewDeletedRecord(); // function to display deleted data
void modifyRecord();      // function to modify the data in file

class Student
{
private:
    int rollNo;
    char name[40];
    char gender;
    int age;
    int std;

public:
    // default constructor
    Student()
    {
        rollNo = 0;
        strcpy(name, "NO_NAME");
        gender = '-';
        age = 0;
        std = 0;
    }
    // parameterized constructor
    Student(int rn, char nm[40], char g, int a, int s)
    {
        rollNo = rn;
        strcpy(name, nm);
        gender = g;
        age = a;
        std = s;
    }

    void modifyData()
    {

        cout << "Roll No. : " << rollNo << endl;
        cout << "Enter student details : \n";
        cout << "Name : ";
        cin.get();

        cin.getline(name, 40);
        cout << "Gender : ";
        cin >> gender;
        cout << "Age : ";
        cin >> age;
        cout << "standard : ";
        cin >> std;
    }

    char *getName()
    {
        return name;
    }

    int getRollNo()
    {
        return rollNo;
    }

    void getData()
    {
        cout << "Enter student details : \n";
        cout << "Roll No. : ";
        cin >> rollNo;
        cout << "Name : ";
        cin.get();

        cin.getline(name, 40);
        cout << "Gender : ";
        cin >> gender;
        cout << "Age : ";
        cin >> age;
        cout << "standard : ";
        cin >> std;
    }

    void showData()
    {
        cout << "student details : \n";
        cout << "Roll No. : " << rollNo << endl;
        cout << "Name : " << name << endl;
        cout << "Gender : " << gender << endl;
        cout << "Age : " << age << endl;
        cout << "standard : " << std << endl;
    }

    void listData()
    {
        cout.setf(ios::left);
        cout << setw(10) << rollNo;
        cout << setw(40) << name;
        cout << setw(10) << gender;
        cout << setw(5) << age;
        cout << setw(5) << std;
        cout << endl;
    }
} s;

void heading()
{
    cout.setf(ios::left);
    cout << setw(10) << "Roll No.";
    cout << setw(40) << "Name";
    cout << setw(10) << "Gender";
    cout << setw(5) << "Age";
    cout << setw(5) << "Std";
    cout << endl;
}

void menu()
{
    cout << "STUDENT RECORDS MANAGEMENT SYSTEM \n";
    cout << "================================== \n";
    cout << "This project is all about to know the following features \n";
    cout << "0. EXIT \n";
    cout << "1. Register New Student \n";
    cout << "2. Show All Student \n";
    cout << "3. Search Student By Roll No \n";
    cout << "4. Modify Student Record \n";
    cout << "5. Delete Student Record \n";
    cout << "6. Veiw Deleted Record \n";
    cout << "========================================================= \n";
    cout << "Enter your choice: ";
}

void addRecord()
{
    ofstream fout;
    fout.open("stuData.bin", ios::out | ios::app | ios::binary);
    s.getData();
    fout.write((char *)&s, sizeof(s));
    fout.close();
    cout << "\nData saved to file.. ... \n";
}

void showAll()
{
    ifstream fin;
    fin.open("stuData.bin", ios::in | ios::binary);
    heading();
    while (fin.read((char *)&s, sizeof(s)))
    {
        s.listData();
    }
    fin.close();
}

void searchByRollNo()
{
    ifstream fin;
    fin.open("stuData.bin", ios::in | ios::binary);
    int rn, flag = 0;
    cout << "\nEnter Roll No. to be search: ";
    cin >> rn;

    while (fin.read((char *)&s, sizeof(s)))
    {
        if (rn == s.getRollNo())
        {
            heading();
            s.listData();
            flag = 1;
        }
    }
    fin.close();
    if (flag == 0)
    {
        cout << "\nNo such roll no. found....\n";
    }
}

void modifyRecord()
{
    fstream fio;
    fio.open("stuData.bin", ios::in | ios::out | ios::binary);
    int rn, flag = 0, pos;
    cout << "\nEnter Roll No. to be modified: ";
    cin >> rn;
    while (fio.read((char *)&s, sizeof(s)))
    {
        if (rn == s.getRollNo())
        {
            pos = fio.tellg(); // return current position of cursor
            cout << "Following record found to be modified.... \n";
            heading();
            s.listData();

            cout << "\n Enter new record details \n";
            fio.seekg(pos - sizeof(s)); // shift the cursor to its parameterized position
            s.getData();                // new data to memory
            fio.write((char *)&s, sizeof(s));
            flag = 1;
        }
    }
    fio.close();
    if (flag == 0)
    {
        cout << "\nNo such roll no. found....\n";
    }
}

void deleteRecord()
{
    ifstream fin;
    fin.open("stuData.bin", ios::in | ios::binary);
    ofstream fout1("temp.bin");
    ofstream fout2("trashes.bin", ios::app);
    int rn, flag = 0;
    cout << "\nEnter Roll No. to be deleted: ";
    cin >> rn;

    while (fin.read((char *)&s, sizeof(s)))
    {
        if (rn == s.getRollNo())
        {
            cout << "Following records has been moved to trash.\n";
            heading();
            s.listData();
            flag = 1;
            fout2.write((char *)&s, sizeof(s));
        }
        else
        {
            fout1.write((char *)&s, sizeof(s));
        }
    }
    fin.close();
    fout1.close();
    fout2.close();

    if (flag == 0)
    {
        cout << "\nNo such roll no. found....\n";
    }
    remove("stuData.bin");
    rename("temp.bin", "stuData.bin");
}

void veiwDeletedRecord()
{
    ifstream fin;
    fin.open("trashes.bin", ios::in | ios::binary);
    cout << "TRASH FILE DATA.....\n";
    heading();
    while (fin.read((char *)&s, sizeof(s)))
    {
        s.listData();
    }
    fin.close();
}

int main()
{

    int n = 0, ch, i, rn, flag = 0, pos;
    Student s[100];
    do
    {
        system("cls");
        menu();
        cin >> ch;

        switch (ch)
        {
        case 1:
            addRecord();
            break;

        case 2:
            showAll();
            break;

        case 3:
            searchByRollNo();
            break;

        case 4:
            modifyRecord();
            break;

        case 5:
            deleteRecord();
            break;

        case 6:
            veiwDeletedRecord();
            break;

        default:
            break;
        }
        system("pause");
    } while (ch);
}