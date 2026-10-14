#include "FileManager.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

void FileManager::save(const std::string& folder,
                       const std::vector<Student>& students,
                       const std::vector<Faculty>& faculty,
                       const std::vector<Course>& courses,
                       const std::vector<Enrollment>& enrollments) {
    std::ofstream s(folder + "/students.txt");
    std::ofstream f(folder + "/faculty.txt");
    std::ofstream c(folder + "/courses.txt");
    std::ofstream e(folder + "/enrollments.txt");
    if (!s || !f || !c || !e)
        throw std::runtime_error("Cannot write to Data folder");
    for (const auto& x : students) s << x.getId() << '|' << x.getName() << '\n';
    for (const auto& x : faculty) f << x.getId() << '|' << x.getName() << '\n';
    for (const auto& x : courses)
        c << x.getId() << '|' << x.getTitle() << '|'
          << x.getFacultyId() << '|' << x.getCapacity() << '\n';
    for (const auto& x : enrollments)
        e << x.getStudentId() << '|' << x.getCourseId() << '\n';
    if (!s || !f || !c || !e)
        throw std::runtime_error("Error while writing records");
}

void FileManager::load(const std::string& folder,
                       std::vector<Student>& students,
                       std::vector<Faculty>& faculty,
                       std::vector<Course>& courses,
                       std::vector<Enrollment>& enrollments) {
    std::vector<Student> s;
    std::vector<Faculty> f;
    std::vector<Course> c;
    std::vector<Enrollment> e;
    std::string line, a, b, d, g;
    std::ifstream studentFile(folder + "/students.txt");
    std::ifstream facultyFile(folder + "/faculty.txt");
    std::ifstream courseFile(folder + "/courses.txt");
    std::ifstream enrollmentFile(folder + "/enrollments.txt");

    while (std::getline(studentFile, line)) {
        std::istringstream input(line);
        if (std::getline(input, a, '|') && std::getline(input, b))
            s.emplace_back(std::stoi(a), b);
    }
    while (std::getline(facultyFile, line)) {
        std::istringstream input(line);
        if (std::getline(input, a, '|') && std::getline(input, b))
            f.emplace_back(std::stoi(a), b);
    }
    while (std::getline(courseFile, line)) {
        std::istringstream input(line);
        if (std::getline(input, a, '|') && std::getline(input, b, '|') &&
            std::getline(input, d, '|') && std::getline(input, g))
            c.emplace_back(std::stoi(a), b, std::stoi(d), std::stoi(g));
    }
    while (std::getline(enrollmentFile, line)) {
        std::istringstream input(line);
        if (std::getline(input, a, '|') && std::getline(input, b))
            e.emplace_back(std::stoi(a), std::stoi(b));
    }
    students = std::move(s);
    faculty = std::move(f);
    courses = std::move(c);
    enrollments = std::move(e);
}
