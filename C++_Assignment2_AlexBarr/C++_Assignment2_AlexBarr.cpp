// C++_Assignment2_AlexBarr.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

using namespace std;

int main()
{
    std::cout << "Hello World!\n";
}

class Student
{
    public:
        Student(string studentName, int courses)
        {
            name = studentName;
            numCourses = courses;
		}
    private:
        string name;
        int numCourses;
		string* courseList[];

};