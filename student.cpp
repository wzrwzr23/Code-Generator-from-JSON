#include <iostream>
#include "student.h"
using namespace std;
Student::Student(string n, int i, string e, float g)
{
    name = n;
    id = i;
    email = e;
    gpa = g;
}
string Student::get_name()
{
    return this->name;
}
void Professor::set_name(string n)
{
    this->name = n;
}
float Student::average_gpa(Student s)
{
    cout << "Averaging 2 GPAs" << endl;
    return (this->gpa + s.gpa) / 2;
}
int main(int argc, char *argv[])
{
    Student s1 = Student("John Tan", 1001234,
                         "johntan@sutd.edu.sg", 4.25f);
    return 0;
}
