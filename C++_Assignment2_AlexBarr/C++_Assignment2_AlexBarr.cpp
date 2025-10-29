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
        cout << "[String ctor] Created student with name='" << name << "'\n";
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
        cout << "[Copy ctor] Copying student '" << other.name << "' (" << other.numCourses << " courses)\n";
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
        if (this == &other) {
            cout << "[Assign op] Self-assignment detected for '" << name << "'\n";
            return *this;
        }

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

        cout << "[Assign op] Assigned from '" << other.name << "' (" << other.numCourses << " courses) to '" << name << "'\n";
        return *this;
    }

    // Destructor
    ~Student()
    {
        cout << "[Destructor] Destroying student '" << name << "'\n";
        if (courseList != nullptr) {
            delete[] courseList;
            courseList = nullptr;
        }
    }

    // Functions Test Version Control

    // Add a course
    void addCourse(const string& course)
    {
        cout << "[addCourse] Adding course '" << course << "' to student '" << name << "'\n";
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
        cout << "[print] Called for student '" << name << "'\n";
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
        cout << "[operator<<] stream operator called for student '" << student.name << "'\n";
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

void demoStudentCapabilities()
{
    cout << "===== Student class capability demo =====\n\n";

    // Default ctor
    cout << "-- Default constructor --\n";
    {
        Student sDefault;
        cout << "sDefault.print():\n";
        sDefault.print(); // should show empty student
    } // sDefault destroyed here

    // String ctor
    cout << "\n-- String constructor --\n";
    {
        Student sName("Alice");
        cout << "Demonstrate print() and operator<< for same object:\n";
        sName.print();
        cout << sName << '\n'; // operator<< demonstration
    } // sName destroyed here

    // Count ctor and addCourse
    cout << "\n-- Count constructor + addCourse --\n";
    {
        Student sCount("Bob", 1); // allocate room for 1 course
        sCount.addCourse("CS101"); // demonstration of addCourse
        sCount.addCourse("MATH200"); // resizing behavior
        cout << "sCount via print():\n";
        sCount.print();
        cout << "sCount via operator<<:\n";
        cout << sCount << '\n';
    } // sCount destroyed here

    // Pointer+size ctor, copy ctor, assignment operator, deep-copy test
    cout << "\n-- Pointer+size ctor, copy ctor and assignment operator (deep copy test) --\n";
    {
        string coursesArr[] = { "Physics", "Chemistry", "English" };
        Student sFromArray("Carol", 3, coursesArr);
        cout << "sFromArray initial:\n";
        sFromArray.print();

        cout << "\nCopy-construct sCopy from sFromArray:\n";
        Student sCopy = sFromArray; // copy ctor

        cout << "\nDefault-construct sAssigned and assign sFromArray to it:\n";
        Student sAssigned;
        sAssigned = sFromArray; // assignment operator

        cout << "\nModify original (sFromArray.addCourse(\"Biology\")) and show deep copy preserved:\n";
        sFromArray.addCourse("Biology");

        cout << "\nAfter modification:\nOriginal (sFromArray):\n";
        sFromArray.print();

        cout << "\nCopy (sCopy) should be unchanged:\n";
        sCopy.print();

        cout << "\nAssigned (sAssigned) should be unchanged:\n";
        sAssigned.print();

        cout << "\nDemonstrate operator<< on assigned:\n";
        cout << sAssigned << '\n';

        cout << "\nReset courses in original (sFromArray.resetCourses()) and show others unaffected:\n";
        sFromArray.resetCourses();
        cout << "Original after reset:\n"; sFromArray.print();
        cout << "Copy after original reset (should still have courses):\n"; sCopy.print();
    } // sFromArray, sCopy, sAssigned destroyed here (destructor messages appear)

    cout << "\n===== Demo complete. Destructors for demo objects ran as they left scope. =====\n\n";
}

int main()
{
    char restart = 'N';
    do
    {
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

        cout << "\nThird student after assignment (third = second):\n";
        cout << "------------------------------------------------\n";
        displayStudent(thirdStudent);

        cout << "\nWould you like to restart the sequence? (Y to restart, any other key to exit): ";
        if (!(cin >> restart))
            restart = 'N';
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Used AI for input cleanup
        cout << "\n";
    } while (restart == 'y' || restart == 'Y');

    cout << "Program exiting.\n";

    return 0;
}
