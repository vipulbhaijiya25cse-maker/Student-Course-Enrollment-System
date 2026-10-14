#pragma once
#include <string>
#include <stdexcept>

// Abstract parent enables inheritance and runtime polymorphism.
class Person {
protected:
    int id;
    std::string name;
public:
    Person(int personId = 0, const std::string& personName = "")
        : id(personId), name(personName) {}
    virtual ~Person() = default;
    int getId() const { return id; }
    std::string getName() const { return name; }
    void setName(const std::string& value) {
        if (value.empty() || value.find('|') != std::string::npos)
            throw std::invalid_argument("Invalid name");
        name = value;
    }
    virtual void display() const = 0;
};

class Student : public Person {
public:
    Student(int i = 0, const std::string& n = "") : Person(i, n) {}
    void display() const override;
};

class Faculty : public Person {
public:
    Faculty(int i = 0, const std::string& n = "") : Person(i, n) {}
    void display() const override;
};

class Course {
private:
    int id, facultyId, capacity;
    std::string title;
public:
    Course(int i = 0, const std::string& t = "", int faculty = 0, int seats = 1)
        : id(i), facultyId(faculty), capacity(seats), title(t) {}
    int getId() const { return id; }
    int getFacultyId() const { return facultyId; }
    int getCapacity() const { return capacity; }
    std::string getTitle() const { return title; }
    void setTitle(const std::string& value) {
        if (value.empty() || value.find('|') != std::string::npos)
            throw std::invalid_argument("Invalid course title");
        title = value;
    }
    void display() const;
};

class Enrollment {
private:
    int studentId, courseId;
public:
    Enrollment(int student = 0, int course = 0)
        : studentId(student), courseId(course) {}
    int getStudentId() const { return studentId; }
    int getCourseId() const { return courseId; }
};
