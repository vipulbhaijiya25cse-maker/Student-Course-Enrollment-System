#include "Entities.h"
#include <iostream>

void Student::display() const {
    std::cout << "Student " << id << " | " << name << '\n';
}
void Faculty::display() const {
    std::cout << "Faculty " << id << " | " << name << '\n';
}
void Course::display() const {
    std::cout << "Course " << id << " | " << title
              << " | Faculty " << facultyId << " | Seats " << capacity << '\n';
}
