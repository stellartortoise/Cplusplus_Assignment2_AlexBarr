// C++_Assignment2_AlexBarr.cpp : Main entry point for Student class demonstration.
// This program allows user input for student names and courses, demonstrates deep copy, and supports looping.

#include <iostream>
#include <string>
#include <utility>
#include "Header.h"

using namespace std;

/**
 * @class Student
 * @brief Manages student name and dynamic list of courses.
 *        Supports deep copy, assignment, and course management.
 */
class Student
{
private:
    string name;         ///< Student's name
    int numCourses;      ///< Number of courses
    string* courseList;  ///< Dynamic array of course names

public:
    /// Default constructor
    Student()
        : name(""), numCourses(0), courseList(nullptr)
    {
    }

    /// Constructor with name
    Student(const string& studentName)
        : name(studentName), numCourses(0), courseList(nullptr)
    {
        printf("\x1B[93m[String constructor] Created student with name='%s'\033[0m\t\t\n",name.c_str());
    }

    /// Constructor with name and course count
    Student(const string& studentName, int courses)
        : name(studentName), numCourses(courses), courseList(nullptr)
    {
        if (numCourses > 0)
            courseList = new string[numCourses];
    }

    /// Constructor with name, course count, and course list
    Student(const string& studentName, int size, const string* courseList)
        : name(studentName), numCourses(size), courseList(nullptr)
    {
        if (numCourses > 0 && courseList != nullptr)
        {
            this->courseList = new string[numCourses];
            for (int i = 0; i < numCourses; ++i)
                this->courseList[i] = courseList[i]; // deep copy
        }
    }

    /// Copy constructor
    Student(const Student& other)
        : name(other.name), numCourses(other.numCourses), courseList(nullptr)
    {
        printf("\x1B[93m[Copy constructor] Copying student '%s' (%i courses) \033[0m\t\t\n", other.name.c_str(), other.numCourses);
        if (numCourses > 0)
        {
            courseList = new string[numCourses];
            for (int i = 0; i < numCourses; i++)
            {
                courseList[i] = other.courseList[i];
            }
        }
    }

    /// Assignment operator (deep copy, exception-safe)
    Student& operator=(const Student& other)
    {
        if (this == &other) {
            printf("\x1B[93m[Assign operator] Self-assignment detected for '%s'\033[0m\t\t\n", name.c_str());
            return *this;
        }

        // Allocate and copy first (may throw) so we don't modify 'this' on failure
        string* newList = nullptr;
        if (other.numCourses > 0) {
            newList = new string[other.numCourses];
            for (int i = 0; i < other.numCourses; ++i)
                newList[i] = other.courseList[i];
        }

        string newName = other.name;

        // Commit changes
        delete[] courseList;
        courseList = newList;
        numCourses = other.numCourses;
        name = std::move(newName);

        //cout << "[Assign op] Assigned from '" << other.name << "' (" << other.numCourses << " courses) to '" << name << "'\n";
        printf("\x1B[93m[Assign operator] Assigned from '%s' (%i courses) to '%s'\033[0m\t\t\n", other.name.c_str(), other.numCourses, name.c_str());
        return *this;
    }

    /// Destructor
    ~Student()
    {
        //cout << "[Destructor] Destroying student '" << name << "'\n";
        printf("\x1B[91m[Destructor] Destroying student '%s'\033[0m\t\t\n", name.c_str());
        delete[] courseList;
        courseList = nullptr;
    }

    /// Add a course to the student's list
    void addCourse(const string& course)
    {
        printf("\x1B[93m[addCourse] Adding course '%s' to student '%s'\033[0m\t\t\n", course.c_str(), name.c_str());
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

    /// Print student details
    void print() const
    {
        printf("\x1B[93m[print] Called for student '%s'\033[0m\t\t\n", name.c_str());
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

    /// Overloaded << operator for Student
    friend ostream& operator<<(ostream& os, const Student& student)
    {
        printf("\x1B[93m[operator<<] stream operator called for student '%s'\033[0m\t\t\n", student.name.c_str());
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

	/// Overloaded << operator to assign one Student to another... I understand this is probably bad practice, but I want to show this works
 //   friend Student& operator<<(Student& student1, Student& student2)
 //   {
 //       student1 = student2;
 //       return student1;
	//}

    /// Friend function to change student name
    friend void changeName(Student& student, const string& newName);

    /// Reset all courses for the student
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
    Student s2(s1);
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

string enterName()
{
    string name;
    while (true)
    {
        try {
            cout << "Enter new student name: ";
            getline(cin, name);
            cout << "\n" << endl;
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
            cout << "\n" << endl;
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
    string choice;

    while (true) {
        cout << "Enter a new course? (Y or N): ";
        getline(cin, choice);

        // Accept only a single 'y' or 'Y'
        if (choice == "y" || choice == "Y") {
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
        // Accept only a single 'n' or 'N'
        else if (choice == "n" || choice == "N") {
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
    char restart = 'N';
    do
    {
        int numCourses = 0;
        printf("\x1B[94mInput first Student info \n-----------------------\n\n\033[0m");
        Student firstStudent = testStudentClass(numCourses);

        printf("\x1B[94m\n Display first Student info \n-----------------------\n\n\033[0m");
        displayStudent(firstStudent);

        printf("\x1B[94m\n Create Second Student\n-----------------------\n\n\033[0m");
        Student secondStudent = AskForSecondStudent(numCourses, firstStudent);

        printf("\x1B[94m\n Display Second Student\n-----------------------\n\n\033[0m");
        displayStudent(secondStudent);

        printf("\x1B[94m\n Reset Courses and Display First Student\n-----------------------\n\n\033[0m");
        resetCourses(firstStudent);
        displayStudent(firstStudent);

        printf("\x1B[94m\n Show deep copy took place by showing second student's info\n-----------------------\n\n\033[0m");
        displayStudent(secondStudent);

        Student thirdStudent;
        thirdStudent = secondStudent; // Using overloaded << operator to assign secondStudent to thirdStudent

        printf("\x1B[94m\nThird student after assignment (third = second):\n------------------------------------------------\n\033[0m");
        //displayStudent(thirdStudent);
        cout << "\n" << thirdStudent; // Using overloaded << operator to print thirdStudent

        string restartInput;
        cout << "\nWould you like to restart the sequence? (Y to restart, any other key to exit): ";
        getline(cin, restartInput);

        if (restartInput == "y" || restartInput == "Y")
            restart = 'Y';
        else
            restart = 'N';
    } while (restart == 'y' || restart == 'Y');

    cout << "Program exiting.\n";

    return 0;
}

//References:
// https://stackoverflow.com/questions/4053837/colorizing-text-in-the-console-with-c
