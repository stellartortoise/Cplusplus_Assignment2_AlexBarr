//cpp C++_Assignment2_AlexBarr\Student.h
#pragma once

#include <string>
#include <ostream>

class Student
{
private:
    std::string name;
    int numCourses;
    std::string* courseList;

public:
    // Big three + constructors
    Student();
    Student(const std::string& studentName); // string ctor
    Student(const std::string& studentName, int courses);
    Student(const std::string& studentName, int size, const std::string* coursesList);
    Student(const Student& other);           // copy ctor
    Student& operator=(const Student& other);// assignment
    ~Student();                              // destructor

    // Functionality
    void addCourse(const std::string& course);
    void print() const;
    void resetCourses();

    // streaming
    friend std::ostream& operator<<(std::ostream& os, const Student& student);

    // small friend helper kept for compatibility with existing code
    friend void changeName(Student& student, const std::string& newName);
};