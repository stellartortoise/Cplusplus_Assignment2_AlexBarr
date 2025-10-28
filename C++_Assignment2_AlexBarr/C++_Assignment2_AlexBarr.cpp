// C++_Assignment2_AlexBarr.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <utility>
#include "Header.h"

using namespace std;

class Student
{
private:
    string name;
    int numCourses;
    string* courseList;

public:
    // Default constructor
    Student()
        : name(""), numCourses(0), courseList(nullptr)
    {
    }

    // String Constructor
    Student(const string& studentName)
        : name(studentName), numCourses(0), courseList(nullptr)
    {
    }

    // Parameterized constructor (count only)
    Student(const string& studentName, int courses)
        : name(studentName), numCourses(courses), courseList(nullptr)
    {
        if (numCourses > 0)
            courseList = new string[numCourses];
    }

    // Parameterized constructor with course list (pointer + size)
    // Caller provides a C-style dynamic array (string*) and its size.
    Student(const string& studentName, int size, const string* coursesList)
        : name(studentName), numCourses(size), courseList(nullptr)
    {
        if (numCourses > 0 && coursesList != nullptr)
        {
            courseList = new string[numCourses];
            for (int i = 0; i < numCourses; ++i)
                courseList[i] = coursesList[i]; // deep copy from provided array
        }
    }

    // Copy constructor
    Student(const Student& other)
        : name(other.name), numCourses(other.numCourses), courseList(nullptr)
    {
        if (numCourses > 0)
        {
            courseList = new string[numCourses];
            for (int i = 0; i < numCourses; i++)
            {
                courseList[i] = other.courseList[i];
            }
        }
    }

    // Assignment operator (deep copy, exception-safe)
    Student& operator=(const Student& other)
    {
        if (this == &other) return *this;

        // Allocate and copy first (may throw) so we don't modify 'this' on failure
        string* newList = nullptr;
        if (other.numCourses > 0) {
            newList = new string[other.numCourses];
            for (int i = 0; i < other.numCourses; ++i)
                newList[i] = other.courseList[i];
        }

        // Copy name into a local so name assignment won't leave object partially updated
        string newName = other.name;

        // Commit changes
        delete[] courseList;
        courseList = newList;
        numCourses = other.numCourses;
        name = std::move(newName);

        return *this;
    }

    // Destructor
    ~Student()
    {
        delete[] courseList;
    }

    // Functions

    // Add a course
    void addCourse(const string& course)
    {
        string* newList = new string[numCourses + 1];

        for (int i = 0; i < numCourses; i++)
        {
            newList[i] = courseList[i];
        }

        newList[numCourses] = course;
        delete[] courseList;
        courseList = newList;
        ++numCourses;
    }

    void print() const
    {
        cout << "Student Name: " << name << endl;
        cout << "Number of Courses: " << numCourses << endl;
        cout << "Courses: \n";
        for (int i = 0; i < numCourses; i++)
        {
            if (i == numCourses - 1)
                cout << "\t" << courseList[i] << " ";
            else
                cout << "\t" << courseList[i] << ",\n";
        }
        cout << endl;
    }

    // Overloaded << operator 
    friend ostream& operator<<(ostream& os, const Student& student)
    {
        os << "Student Name: " << student.name << "\n";
        os << "Number of Courses: " << student.numCourses << "\n";
        os << "Courses: \n";
        for (int i = 0; i < student.numCourses; i++)
        {
            if (i == student.numCourses - 1)
                os << "\t" << student.courseList[i] << " ";
            else
                os << "\t" << student.courseList[i] << ",\n";
        }
        return os;
    }

    //Friend operator to change name
    friend void changeName(Student& student, const string& newName);

    void resetCourses()
    {
        delete[] courseList;
        courseList = nullptr;
        numCourses = 0;
    }
};

void changeName(Student& student, const string& newName)
{
    student.name = newName;
}

void resetCourses(Student& student)
{
    student.resetCourses();
}

Student AskForSecondStudent(int& numCourses,Student& s1)
{
    string name = enterName();
    Student s2 = s1;
	changeName(s2, name);

	return s2;
}

void displayStudent(const Student& s)
{
    s.print();
}

Student testStudentClass(int &numCourses)
{
    string name = enterName();
    // enterCourses returns a dynamically allocated array and sets numCourses
    string* courses = enterCourses(numCourses);
    Student s1(name, numCourses, courses);

    // Student made a deep copy; free the temporary array
    delete[] courses;

    // Show result
	return s1;
}

void Begin()
{
    cout << "Sequence of Events:\n\n";
    cout << "1. Register 1st Student\n";
    cout << "2. Display 1st Student's Data\n";
    cout << "3. Register 2nd Student\n";
    cout << "4. Reset 1st Student's Courses\n";
    cout << "5. Display 2nd Student's Data\n";

    cout << "4. Exit\n";
}

string enterName()
{
    string name;
    while (true)
    {
        try {
            cout << "Enter new student name: ";
            getline(cin, name);
            break;
        }
        catch (const exception& e) {
            cerr << "Incorrect Input: " << e.what() << endl;
        }
    }
    return name;
}

string enterCourse()
{
    // Get course name from user
    string course;
    while (true)
    {
        try {
            cout << "Enter course name: ";
            getline(cin, course);
            break;
        }
        catch (const exception& e) {
            cerr << "Incorrect Input: " << e.what() << endl;
        }
    }
    return course;
}

string* enterCourses(int& numCourses) {
    numCourses = 0;
    string* courses = nullptr;
    string course;
    char choice;

    while (true) {
        cout << "Enter another course? (Y or N): ";
        cin >> choice;
        cin.ignore();

        if (choice == 'y' || choice == 'Y') {
            cout << "Enter course name: ";
            getline(cin, course);

            // Allocate new array
            string* newCourses = new string[numCourses + 1];

            // Copy old data
            for (int i = 0; i < numCourses; ++i) {
                newCourses[i] = courses[i];
            }

            // Add new course
            newCourses[numCourses] = course;

            // Clean up old array
            delete[] courses;
            courses = newCourses;
            numCourses++;
        }
        else if (choice == 'n' || choice == 'N') {
            break;
        }
        else {
            cout << "Invalid input. Please enter 'y' or 'n'." << endl;
        }
    }

    return courses;
}

int main()
{
	Begin();
	cout << "-----------------------\n\n";

    int numCourses = 0;
    cout << "Input first Student info \n";
    cout << "-----------------------\n";
    Student firstStudent = testStudentClass(numCourses);
    cout << "\n Display first Student info \n";
    cout << "-----------------------\n\n";
    displayStudent(firstStudent);
    cout << "\n Create Second Student\n";
    cout << "-----------------------\n\n";
	Student secondStudent = AskForSecondStudent(numCourses, firstStudent);
    cout << "\n Display Second Student\n";
    cout << "-----------------------\n\n";
	displayStudent(secondStudent);
    cout << "\n Reset Courses and Display First Student\n";
    cout << "-----------------------\n\n";
	resetCourses(firstStudent);
	displayStudent(firstStudent);
    cout << "\n Show deep copy took place by showing second student's info\n";
    cout << "-----------------------\n\n";
    displayStudent(secondStudent);

    Student thirdStudent = secondStudent;

    thirdStudent << secondStudent;

   
    return 0;
}
