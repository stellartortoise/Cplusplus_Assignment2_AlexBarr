//cpp C++_Assignment2_AlexBarr\Student.cpp
#include "Student.h"
#include <iostream>
#include <utility>

// Default ctor
Student::Student()
    : name(""), numCourses(0), courseList(nullptr)
{
    // quiet default ctor (no extra output requested)
}

// String ctor
Student::Student(const std::string& studentName)
    : name(studentName), numCourses(0), courseList(nullptr)
{
    std::cout << "[String ctor] Created student with name='" << name << "'\n";
}

// Parameterized (count only)
Student::Student(const std::string& studentName, int courses)
    : name(studentName), numCourses(courses), courseList(nullptr)
{
    if (numCourses > 0)
        courseList = new std::string[numCourses];
}

// Parameterized (pointer + size)
Student::Student(const std::string& studentName, int size, const std::string* coursesList)
    : name(studentName), numCourses(size), courseList(nullptr)
{
    if (numCourses > 0 && coursesList != nullptr)
    {
        courseList = new std::string[numCourses];
        for (int i = 0; i < numCourses; ++i)
            courseList[i] = coursesList[i]; // deep copy
    }
}

// Copy ctor
Student::Student(const Student& other)
    : name(other.name), numCourses(other.numCourses), courseList(nullptr)
{
    std::cout << "[Copy ctor] Copying student '" << other.name << "' (" << other.numCourses << " courses)\n";
    if (numCourses > 0)
    {
        courseList = new std::string[numCourses];
        for (int i = 0; i < numCourses; ++i)
            courseList[i] = other.courseList[i];
    }
}

// Assignment (exception-safe deep copy)
Student& Student::operator=(const Student& other)
{
    if (this == &other) {
        std::cout << "[Assign op] Self-assignment detected for '" << name << "'\n";
        return *this;
    }

    std::string* newList = nullptr;
    if (other.numCourses > 0) {
        newList = new std::string[other.numCourses];
        for (int i = 0; i < other.numCourses; ++i)
            newList[i] = other.courseList[i];
    }

    std::string newName = other.name;

    // commit
    delete[] courseList;
    courseList = newList;
    numCourses = other.numCourses;
    name = std::move(newName);

    std::cout << "[Assign op] Assigned from '" << other.name << "' (" << other.numCourses << " courses) to '" << name << "'\n";
    return *this;
}

// Destructor
Student::~Student()
{
    std::cout << "[Destructor] Destroying student '" << name << "'\n";
    if (courseList != nullptr) {
        delete[] courseList;
        courseList = nullptr;
    }
}

// addCourse
void Student::addCourse(const std::string& course)
{
    std::cout << "[addCourse] Adding course '" << course << "' to student '" << name << "'\n";
    std::string* newList = new std::string[numCourses + 1];
    for (int i = 0; i < numCourses; ++i)
        newList[i] = courseList[i];
    newList[numCourses] = course;
    delete[] courseList;
    courseList = newList;
    ++numCourses;
}

// print
void Student::print() const
{
    std::cout << "[print] Called for student '" << name << "'\n";
    std::cout << "Student Name: " << name << '\n';
    std::cout << "Number of Courses: " << numCourses << '\n';
    std::cout << "Courses:\n";
    for (int i = 0; i < numCourses; ++i)
    {
        if (i == numCourses - 1)
            std::cout << '\t' << courseList[i] << ' ';
        else
            std::cout << '\t' << courseList[i] << ",\n";
    }
    std::cout << '\n';
}

// resetCourses
void Student::resetCourses()
{
    delete[] courseList;
    courseList = nullptr;
    numCourses = 0;
}

// operator<<
std::ostream& operator<<(std::ostream& os, const Student& student)
{
    std::cout << "[operator<<] stream operator called for student '" << student.name << "'\n";
    os << "Student Name: " << student.name << "\n";
    os << "Number of Courses: " << student.numCourses << "\n";
    os << "Courses: \n";
    for (int i = 0; i < student.numCourses; ++i)
    {
        if (i == student.numCourses - 1)
            os << "\t" << student.courseList[i] << " ";
        else
            os << "\t" << student.courseList[i] << ",\n";
    }
    return os;
}

// small friend helper
void changeName(Student& student, const std::string& newName)
{
    student.name = newName;
}