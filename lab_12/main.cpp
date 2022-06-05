#include <iostream>
#include <memory> 
#include <string>
#include <vector>
#define MY_DEBUG
using namespace std;

class Teacher;
class Student
{
public:
	Student(const string& name)
	{
		m_student = name;
#ifdef MY_DEBUG
		cout << "Constructor: Student" << endl;
#endif
	}
	~Student()
	{
#ifdef MY_DEBUG
		cout << "Destructor: Student " << endl;
#endif
	}

	string NameStudent() { return m_student; }
	shared_ptr<Teacher> GetTeacher() { m_teacher; }

	void AddTeacher(shared_ptr<Teacher>& teacher)
	{
		m_teacher = teacher;
	}

private:
	string m_student;
	weak_ptr<Teacher> m_teacher;
};


class Teacher
{
public:
	Teacher(const string& name)
	{
		m_teachers = name;
#ifdef MY_DEBUG
		cout << "Constructor: Teacher" << endl;
#endif
	}
	~Teacher()
	{
#ifdef MY_DEBUG
		cout << "Destructor: Teacher " << endl;
#endif
	}

	friend void Student_Teacher(shared_ptr<Teacher>& T, shared_ptr<Student>& S)
	{
		T->AddStudent(S);
		S->AddTeacher(T);
	}
	string NameTeacher() { return m_teachers; }

	void AddStudent(shared_ptr<Student>& student)
	{
		m_students.push_back(student);
	}

	void AllStudents()
	{
		if (!m_students.empty())
		{
			cout << m_teachers << " students: " << endl;
			for (const auto& Student : m_students)
			{
				cout << Student->NameStudent() << endl;
			}
		}
	}
private:
	string m_teachers;
	vector<shared_ptr<Student>> m_students;
};


int main()
{
	auto teacher0{ make_shared<Teacher>("Ivan Vladimirovich") };
	auto student1{ make_shared<Student>("Petr") };
	auto student2{ make_shared<Student>("Alexandr") };
	auto student3{ make_shared<Student>("Samuil") };

	Student_Teacher(teacher0, student1);
	Student_Teacher(teacher0, student2);
	Student_Teacher(teacher0, student3);

	teacher0->AllStudents();
}
