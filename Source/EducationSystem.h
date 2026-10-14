#pragma once
#include "FileManager.h"
#include <string>
#include <vector>

class EducationSystem {
private:
    std::vector<Student> students;
    std::vector<Faculty> faculty;
    std::vector<Course> courses;
    std::vector<Enrollment> enrollments;
    std::string dataFolder;

    int readInt(const std::string& prompt);
    std::string readText(const std::string& prompt);
    void addRecord();
    void displayRecords() const;
    void searchRecord();
    void updateRecord();
    void deleteRecord();
    void enrollOrDrop();
    void showReport() const;
    void saveOrLoad();
public:
    explicit EducationSystem(const std::string& dataDirectory);
    ~EducationSystem();
    void run();
};
