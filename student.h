#ifndef STUDENT_H
#define STUDENT_H
using namespace std;
class Student
{
private:
    string name;
    int id;
    string email;
    float gpa;
public:
string get_name();
    Student(string n, int i, string e, float g);
protected:
float average_gpa(Student s);
};
class Professor
{
    private:
    public:
    protected:
};
#endif
