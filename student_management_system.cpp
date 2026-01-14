#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <limits>
using namespace std;

struct Student
{
    string name;
    string father_name;
    string grade; // Class of study i.e (7,10,Bs,Master)
    int roll_no;
    string contact;
};
vector<Student> students;

void load_data();
void save_data();
void clearScreen();
int getvalidatedchoice(int min, int max);
bool letters_only(string alpha);
string validate(string alpha);
bool digits_only(string digits);
string validate_contact(string digits);
int validaterollno(int x);
bool rollno_exist(int roll_no);
int manage_roll_number();
void addstudent();
void displayallstudents();
string tolowercase();
void search_student();
int access_student();
void update_record();
void delete_record();



void load_data()
{
    ifstream file("student_record.txt");
    Student s;
    students.clear();
    while (getline(file, s.name, '|'))
    {
        getline(file, s.father_name, '|');
        getline(file, s.grade, '|');
        file >> s.roll_no;
        file.ignore();
        getline(file, s.contact);
        students.push_back(s);
    }
    file.close();
}

void save_data()
{
    ofstream file("student_record.txt");
    for (int i = 0; i < students.size(); i++)
    {
        file << students[i].name << "|"
             << students[i].father_name << "|"
             << students[i].grade << "|"
             << students[i].roll_no << "|"
             << students[i].contact << endl;
    }
    file.close();
}
void clearScreen()
{
    cout << "\033[2J\033[H";
}

int getvalidatedchoice(int min, int max) {
    int option;
    while(true) {
        if(!(cin>>option)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter valid option : ";
            continue;
        }
        if(option<min or option>max) {
            cout << "Enter valid option : ";
            continue ;
        }
        break;
    }
    return option;
}
bool letters_only(string alpha) {
    for(int i=0; i<alpha.size(); i++) {
        if(!(isalpha(alpha.at(i))) && alpha.at(i)!=' ') {
            return false;
        }
    }
    return true;
}
string validate(string alpha) {
    while(true) {
        if(!getline(cin, alpha)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input" << endl;
            continue;
        }
        if(alpha.empty()) {
            cout << "Enter something : " ;
            continue;
        }
        if(!letters_only(alpha)) {
            cout << "Enter letters only : ";
            continue;
        }
        break;
    }
    return alpha;
}

bool digits_only(string digits) {
    for(int i=0; i<digits.size(); i++) {
        if(!(isdigit(digits.at(i)))) {
            return false;
        }
    }
    return true;
}
string validate_contact(string digits) {
    while(true) {
        if(!getline(cin, digits)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input" << endl;
            continue;
        }
        if(digits.empty()) {
            cout << "Enter something : " ;
            continue;
        }
        if(!(digits_only(digits))) {
            cout << "Enter digits only : ";
            continue;
        }
        if(digits.size()>12 or digits.size()<11) {
            cout << "Enter valid length : " ;   // ie 03451234567 or 923451234567
            continue ;
        }
        break;
    }
    return digits;
}
int validaterollno(int x) {
    while(true) {
        cin >> x;
        if(cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input : ";
            continue ;
        }
        break;
    }
    return x;
}
bool rollno_exist(int roll_no)
{
    for (int i = 0; i < students.size(); i++)
    {
        if (students[i].roll_no == roll_no)
        {
            return 1;
        }
    }
    return 0;
}

int manage_roll_number() {
    int x=0;
    bool exists = 0;
    do
    {
        if (exists)
        {
            cout << " try other : ";
        }
        else
        {
            cout << "Enter Roll_no : ";
        }
        x= validaterollno(x);
        exists = rollno_exist(x);
        if (exists)
        {
            cout << "Roll_no already exist";
        }
    } while (exists);
    return x;
}

void addstudent()
{
    Student s;
    cout << "Enter Student Name : ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    s.name = validate(s.name);
    cout << "Enter Father Name : ";
    s.father_name = validate(s.father_name);
    cout << "Enter Grade of study : ";
    cin >> s.grade;

    s.roll_no=manage_roll_number();

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter contact no : ";
    s.contact = validate_contact(s.contact);
    students.push_back(s);
    clearScreen();
    cout << "Student added successfully..." << endl
         << endl;
}
void display_this_student(const Student &s)
{
    cout << "Student Name   : " << s.name << endl
         << "Father Name    : " << s.father_name << endl
         << "Grade of Study : " << s.grade << endl
         << "Roll number    : " << s.roll_no << endl
         << "Contact number : " << s.contact << endl;
}
void displayallstudents()
{
    for (int i = 0; i < students.size(); i++)
    {
        cout << "Student Name   : " << students[i].name << endl
             << "Father Name    : " << students[i].father_name << endl
             << "Grade of Study : " << students[i].grade << endl
             << "Roll number    : " << students[i].roll_no << endl
             << "Contact number : " << students[i].contact << endl
             << endl<<endl;
    }
}

string tolowercase(string s)
{
    for (int i = 0; i < s.length(); i++)
    {
        s[i] = tolower(s[i]);
    }
    return s;
}

void search_student()
{
    int choice;
    string str_input;
    int num_input;
    cout << "How you want to search " << endl
         << "1. search by name " << endl
         << "2. search by father name" << endl
         << "3. search by grade " << endl
         << "4. search roll_no " << endl
         << "5. search by contact no " << endl
         << endl
         << "Enter your choice : ";
    choice = getvalidatedchoice(1,5);
    switch (choice)
    {
    case 1:
        cout << "Enter search value : ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, str_input);
        break;
    case 2:
        cout << "Enter search value : ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, str_input);
        break;
    case 3:
        cout << "Enter search value : ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, str_input);
        break;
    case 4:
        cout << "Enter search value : ";
        cin >> num_input;
        break;
    case 5:
        cout << "Enter search value : ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, str_input);
        break;
    default:
        clearScreen();
        cout << "Invalid choice...\n"
             << endl;
        break;
    }
    clearScreen();

    bool found = 0;
    for (int i = 0; i < students.size(); i++)
    {
        if ((choice == 1 && tolowercase(students[i].name) == tolowercase(str_input)) ||
                (choice == 2 && tolowercase(students[i].father_name) == tolowercase(str_input)) ||
                (choice == 3 && tolowercase(students[i].grade) == tolowercase(str_input)) ||
                (choice == 4 && students[i].roll_no == num_input) ||
                (choice == 5 && students[i].contact == str_input))
        {
            found = 1;
            cout << "Student found \n"
                 << endl;
            display_this_student(students[i]);
            cout << endl;
        }
    }
    if (found == 0)
    {
        clearScreen();
        cout << "Student not found..." << endl
             << endl;
    }
}

int access_student()
{
    int roll_no;
    cout << "Enter student roll_no : ";
    cin >> roll_no;
    for (int i = 0; i < students.size(); i++)
    {
        if (roll_no == students[i].roll_no)
        {
            return i;
        }
    }
    return -1;
}

void update_record()
{
    int x;
    x = access_student(); // it return iteration of student to be updated
    if (x < 0)
    {
        cout << "Student not found..." << endl
             << endl;
    }
    else
    {
        int choice;
        string str_input;
        int num_input;
        cout << "What you to update " << endl
             << "1. Name " << endl
             << "2. Father name" << endl
             << "3. Grade " << endl
             << "4. Roll_no " << endl
             << "5. Contact no " << endl
             << endl
             << "Enter your choice : ";
        choice = getvalidatedchoice(1,5);
        switch (choice)
        {
        case 1:
            cout << "Enter updated value : ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            str_input = validate(str_input);
            students[x].name = str_input;
            break;
        case 2:
            cout << "Enter updated value : ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            str_input = validate(str_input);
            students[x].father_name = str_input;
            break;
        case 3:
            cout << "Enter updated value : ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, str_input);
            students[x].grade = str_input;
            break;
        case 4:
            students[x].roll_no =
                manage_roll_number();
            break;
        case 5:
            cout << "Enter updated value : ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            str_input = validate_contact(str_input) ;
            students[x].contact = str_input;
            break;
        }
        clearScreen();
        cout << "Record updated successfully..." << endl
             << endl;
    }
}

void delete_record()
{
    int x, choice;
    clearScreen();
    x = access_student(); // it return iteration of student to be updated
    if (x < 0)
    {
        cout << "Student not found...\n" << endl;
    }
    else
    {
        cout << endl;
        display_this_student(students[x]);
        cout << "\nAre you Sure you want to delete this record" << endl
             << "1. Yes" << endl
             << "2. No" << endl
             << "Enter you choice : ";
        choice = getvalidatedchoice(1,2);
        switch (choice)
        {
        case 1:
            students.erase(students.begin() + x);
            clearScreen();
            cout << "Record deleted successfully..." << endl
                 << endl;
            break;
        case 2:
            clearScreen();
            cout << "Deletion cancelled..." << endl<<endl;
            break;
        }
    }
}

int main()
{
    load_data();
    bool exit = 1;
    while (exit)
    {
        int option;
        cout << "_____Student Management System_____" << endl
             << endl;
        cout << "1. Add student record" << endl;
        cout << "2. View all Students " << endl;
        cout << "3. Search for a student " << endl;
        cout << "4. Update student record" << endl;
        cout << "5. Delete student record" << endl;
        cout << "6. Exit " << endl
             << endl;
        cout << "Select the Option : ";
        option = getvalidatedchoice(1,6);
        clearScreen();
        switch (option)
        {
        case 1:
            addstudent();
            save_data();
            break;
        case 2:
            displayallstudents();
            break;
        case 3:
            search_student();
            break;
        case 4:
            update_record();
            save_data();
            break;
        case 5:
            delete_record();
            save_data();
            break;
        case 6:
            exit = 0;
            break;
        }
    }
    return 0;
}
    