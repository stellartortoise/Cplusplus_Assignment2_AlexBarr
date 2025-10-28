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

	//String Constructor
    Student(const string& studentName)
        : name(studentName), numCourses(0), courseList(nullptr)
    {
    }

    // Parameterized constructor
    Student(const string& studentName, int courses)
        : name(studentName), numCourses(courses), courseList(nullptr)
    {
        if (numCourses > 0)
            courseList = new string[numCourses];
    }

	// Parameterized constructor with course list
    //template <size_t N> //I had to use AI for this one; it seems this is the only way I can figure out how to dynamically
	//change the num courses based on the size of the input array.
    Student(string studentName, int size, const string &coursesList)
        : name(studentName), numCourses(size), courseList(coursesList)
    {
        //if (numCourses > 0)
        //{
        //    courseList = new string[numCourses];
        //    for (int i = 0; i < numCourses; ++i)
        //        courseList[i] = coursesList[i]; // deep copy from provided array
        //}
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

    // Assignment operator (copy-and-swap for strong exception safety)
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

        // Copy name into a local so name construction can't leave object in a partially updated state
        string newName = other.name;

        // All allocations/copies succeeded -> commit changes
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

    void print()
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
                cout << "\t" << student.courseList[i] << " ";
            else
                cout << "\t" << student.courseList[i] << ",\n";
        }
        return os;
	}

    void resetCourses()
    {
        numCourses = 0;
        delete[] courseList;
        courseList = nullptr;
	}


};

void testStudentClass(int &numCourses)
{
	string name = enterName();
	string courses[] = enterCourses(numCourses);
    Student s1(name, numCourses, courses);
}

string enterName()
{
    string name;
    while (true)
    {
        try {
            cout << "Enter student name: ";
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
	//Get course name from user
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
	int numCourses = 0;
    cout << "Hello World!\n";
}
