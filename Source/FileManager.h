#pragma once
#include "Entities.h"
#include <string>
#include <vector>

class FileManager {
public:
    static void save(const std::string& folder,
                     const std::vector<Student>& students,
                     const std::vector<Faculty>& faculty,
                     const std::vector<Course>& courses,
                     const std::vector<Enrollment>& enrollments);
    static void load(const std::string& folder,
                     std::vector<Student>& students,
                     std::vector<Faculty>& faculty,
                     std::vector<Course>& courses,
                     std::vector<Enrollment>& enrollments);
};
