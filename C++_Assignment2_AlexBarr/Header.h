#ifndef HEADER_H
#define HEADER_H

#include <string>
using namespace std;

class Student
{
private:
	string name;
	int numCourses;
	string* courseList;
public:
	Student();
	Student(string studentName, int courses);
	Student(const Student& other);
	Student& operator=(const Student& other);
	Student(string studentName, std::string* courses);
	~Student();
	friend void swap(Student& a, Student& b) noexcept;
};

#endif // HEADER_H