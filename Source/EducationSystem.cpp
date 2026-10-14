#include "EducationSystem.h"
#include <algorithm>
#include <iostream>
#include <limits>
#include <memory>
#include <stdexcept>

EducationSystem::EducationSystem(const std::string& directory) : dataFolder(directory) {
    FileManager::load(dataFolder, students, faculty, courses, enrollments);
}
EducationSystem::~EducationSystem() = default;

int EducationSystem::readInt(const std::string& prompt) {
    std::cout << prompt;
    int number;
    if (!(std::cin >> number)) {
        if (std::cin.eof()) throw std::runtime_error("Input ended");
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw std::invalid_argument("Please enter an integer");
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return number;
}

std::string EducationSystem::readText(const std::string& prompt) {
    std::cout << prompt;
    std::string value;
    std::getline(std::cin, value);
    if (value.empty() || value.find('|') != std::string::npos)
        throw std::invalid_argument("Text cannot be empty or contain '|'");
    return value;
}

void EducationSystem::addRecord() {
    int type = readInt("1 Student  2 Faculty  3 Course: ");
    if (type < 1 || type > 3) throw std::invalid_argument("Invalid record type");
    int id = readInt("ID: ");
    if (id <= 0) throw std::invalid_argument("ID must be positive");
    if (type == 1) {
        for (const auto& x : students)
            if (x.getId() == id) throw std::runtime_error("Duplicate student ID");
        students.emplace_back(id, readText("Student name: "));
    } else if (type == 2) {
        for (const auto& x : faculty)
            if (x.getId() == id) throw std::runtime_error("Duplicate faculty ID");
        faculty.emplace_back(id, readText("Faculty name: "));
    } else {
        for (const auto& x : courses)
            if (x.getId() == id) throw std::runtime_error("Duplicate course ID");
        const std::string title = readText("Course title: ");
        const int facultyId = readInt("Faculty ID: ");
        if (std::none_of(faculty.begin(), faculty.end(),
                         [facultyId](const Faculty& x) { return x.getId() == facultyId; }))
            throw std::runtime_error("Faculty not found");
        const int capacity = readInt("Seat capacity: ");
        if (capacity <= 0) throw std::invalid_argument("Capacity must be positive");
        courses.emplace_back(id, title, facultyId, capacity);
    }
    std::cout << "Record added successfully\n";
}

void EducationSystem::displayRecords() const {
    std::cout << "\nSTUDENTS\n";
    for (const auto& x : students) x.display();
    std::cout << "FACULTY\n";
    for (const auto& x : faculty) x.display();
    std::cout << "COURSES\n";
    for (const auto& x : courses) x.display();
    std::cout << "ENROLLMENTS\n";
    for (const auto& x : enrollments)
        std::cout << "Student " << x.getStudentId()
                  << " -> Course " << x.getCourseId() << '\n';
}

void EducationSystem::searchRecord() {
    int type = readInt("1 Student  2 Faculty  3 Course: ");
    int id = readInt("ID: ");
    bool found = false;
    if (type == 1) {
        for (const auto& x : students)
            if (x.getId() == id) { x.display(); found = true; }
    } else if (type == 2) {
        for (const auto& x : faculty)
            if (x.getId() == id) { x.display(); found = true; }
    } else if (type == 3) {
        for (const auto& x : courses)
            if (x.getId() == id) { x.display(); found = true; }
    } else throw std::invalid_argument("Invalid type");
    if (!found) std::cout << "Record not found\n";
}

void EducationSystem::updateRecord() {
    int type = readInt("1 Student  2 Faculty  3 Course: ");
    int id = readInt("ID: ");
    if (type == 1) {
        for (auto& x : students)
            if (x.getId() == id) { x.setName(readText("New name: ")); std::cout << "Updated\n"; return; }
    } else if (type == 2) {
        for (auto& x : faculty)
            if (x.getId() == id) { x.setName(readText("New name: ")); std::cout << "Updated\n"; return; }
    } else if (type == 3) {
        for (auto& x : courses)
            if (x.getId() == id) { x.setTitle(readText("New course title: ")); std::cout << "Updated\n"; return; }
    } else throw std::invalid_argument("Invalid type");
    std::cout << "Record not found\n";
}

void EducationSystem::deleteRecord() {
    int type = readInt("1 Student  2 Faculty  3 Course: ");
    int id = readInt("ID: ");
    bool removed = false;
    if (type == 1) {
        auto size = students.size();
        students.erase(std::remove_if(students.begin(), students.end(),
                       [id](const Student& x) { return x.getId() == id; }), students.end());
        removed = students.size() != size;
        if (removed)
            enrollments.erase(std::remove_if(enrollments.begin(), enrollments.end(),
                             [id](const Enrollment& x) { return x.getStudentId() == id; }), enrollments.end());
    } else if (type == 2) {
        for (const auto& x : courses)
            if (x.getFacultyId() == id)
                throw std::runtime_error("Faculty assigned to a course; cannot delete");
        auto size = faculty.size();
        faculty.erase(std::remove_if(faculty.begin(), faculty.end(),
                      [id](const Faculty& x) { return x.getId() == id; }), faculty.end());
        removed = faculty.size() != size;
    } else if (type == 3) {
        auto size = courses.size();
        courses.erase(std::remove_if(courses.begin(), courses.end(),
                      [id](const Course& x) { return x.getId() == id; }), courses.end());
        removed = courses.size() != size;
        if (removed)
            enrollments.erase(std::remove_if(enrollments.begin(), enrollments.end(),
                             [id](const Enrollment& x) { return x.getCourseId() == id; }), enrollments.end());
    } else throw std::invalid_argument("Invalid type");
    std::cout << (removed ? "Record deleted\n" : "Record not found\n");
}

void EducationSystem::enrollOrDrop() {
    int action = readInt("1 Enroll  2 Drop enrollment: ");
    if (action != 1 && action != 2) throw std::invalid_argument("Invalid action");
    int studentId = readInt("Student ID: ");
    int courseId = readInt("Course ID: ");
    if (action == 2) {
        auto old = enrollments.size();
        enrollments.erase(std::remove_if(enrollments.begin(), enrollments.end(),
                          [studentId, courseId](const Enrollment& x) {
                              return x.getStudentId() == studentId && x.getCourseId() == courseId;
                          }), enrollments.end());
        std::cout << (enrollments.size() < old ? "Enrollment dropped\n" : "Enrollment not found\n");
        return;
    }
    if (std::none_of(students.begin(), students.end(),
                     [studentId](const Student& x) { return x.getId() == studentId; }))
        throw std::runtime_error("Student not found");
    auto course = std::find_if(courses.begin(), courses.end(),
                               [courseId](const Course& x) { return x.getId() == courseId; });
    if (course == courses.end()) throw std::runtime_error("Course not found");
    int filled = 0;
    for (const auto& x : enrollments) {
        if (x.getStudentId() == studentId && x.getCourseId() == courseId)
            throw std::runtime_error("Already enrolled");
        if (x.getCourseId() == courseId) ++filled;
    }
    if (filled >= course->getCapacity()) throw std::runtime_error("Course is full");
    enrollments.emplace_back(studentId, courseId);
    std::cout << "Enrollment successful\n";
}

void EducationSystem::showReport() const {
    std::cout << "\nREPORT Students: " << students.size()
              << " Faculty: " << faculty.size()
              << " Courses: " << courses.size()
              << " Enrollments: " << enrollments.size() << '\n';
    // Dynamic array is managed safely by unique_ptr (automatically delete[]).
    std::unique_ptr<int[]> filled(new int[courses.size()]{});
    for (std::size_t i = 0; i < courses.size(); ++i) {
        for (const auto& x : enrollments)
            if (x.getCourseId() == courses[i].getId()) ++filled[i];
        std::cout << courses[i].getTitle() << ": " << filled[i]
                  << '/' << courses[i].getCapacity() << " seats filled\n";
    }
    std::cout << "PEOPLE (runtime polymorphism)\n";
    for (const auto& x : students) { const Person* p = &x; p->display(); }
    for (const auto& x : faculty) { const Person* p = &x; p->display(); }
}

void EducationSystem::saveOrLoad() {
    int action = readInt("1 Save  2 Load: ");
    if (action == 1) {
        FileManager::save(dataFolder, students, faculty, courses, enrollments);
        std::cout << "Saved\n";
    } else if (action == 2) {
        FileManager::load(dataFolder, students, faculty, courses, enrollments);
        std::cout << "Loaded\n";
    } else throw std::invalid_argument("Invalid action");
}

void EducationSystem::run() {
    while (true) {
        std::cout << "\n=== STUDENT COURSE ENROLLMENT SYSTEM ===\n"
                  << "1 Add Record\n2 Display Records\n3 Search Record\n"
                  << "4 Update Record\n5 Delete Record\n6 Enroll/Drop\n"
                  << "7 Report\n8 Save/Load\n9 Exit\n";
        try {
            int choice = readInt("Choice: ");
            switch (choice) {
                case 1: addRecord(); break;
                case 2: displayRecords(); break;
                case 3: searchRecord(); break;
                case 4: updateRecord(); break;
                case 5: deleteRecord(); break;
                case 6: enrollOrDrop(); break;
                case 7: showReport(); break;
                case 8: saveOrLoad(); break;
                case 9:
                    FileManager::save(dataFolder, students, faculty, courses, enrollments);
                    std::cout << "Saved. Goodbye!\n";
                    return;
                default: std::cout << "Invalid menu choice\n";
            }
        } catch (const std::exception& ex) {
            if (std::string(ex.what()) == "Input ended") {
                FileManager::save(dataFolder, students, faculty, courses, enrollments);
                return;
            }
            std::cout << "Error: " << ex.what() << '\n';
        }
    }
}
