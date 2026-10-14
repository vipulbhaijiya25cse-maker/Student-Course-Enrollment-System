STUDENT COURSE ENROLLMENT SYSTEM
Enrollment Number: IU2541230421 | Project Code: CPP11
Source-code package | C++17

CONTENTS:
  Source/       Five modular source/header files plus main.cpp
  Data/         Sample persistent text files
  Tests/        Demonstration test steps
  README.txt    These instructions

HOW TO BUILD (Linux/macOS, with g++):
  g++ -std=c++17 -Wall -Wextra Source/*.cpp -o student_course_enrollment

HOW TO BUILD (Windows, with MinGW g++ in Command Prompt):
  g++ -std=c++17 -Wall -Wextra Source\*.cpp -o student_course_enrollment.exe

HOW TO RUN (from this project folder):
  Linux/macOS: ./student_course_enrollment Data
  Windows:     student_course_enrollment.exe Data

FEATURES:
  1. Add Record (student, faculty, course)
  2. Display Records
  3. Search Record
  4. Update Record
  5. Delete Record
  6. Enroll / Drop Enrollment
  7. Report (including seat occupancy)
  8. Save / Load
  9. Exit (automatic save)

SAMPLE DATA:
  Students: 101 Aarav Shah, 102 Diya Patel, 103 Karan Singh
  Faculty: 501 Dr Mehta
  Courses: 201 Object Oriented Programming (2 seats), 202 Data Structures (3 seats)
  Initial enrollment: Student 101 in Course 201

TEST IDEAS:
  1. Enroll Student 102 into Course 201 -> succeeds (course now full).
  2. Enroll Student 103 into Course 201 -> Error: Course is full.
  3. Enroll Student 101 into Course 201 -> Error: Already enrolled.
  4. Search for Student 101 -> displays Aarav Shah.
  5. Save, exit, rerun -> data persists.

OOP CONCEPTS:
  Classes, encapsulation, constructors, destructor, inheritance,
  runtime polymorphism, dynamic memory (unique_ptr<int[]>),
  STL vectors, file handling, exception handling, modular classes.

NOTE: These source files match the previously discussed Student Course
Enrollment System project. Compile the code on your own computer, and
keep a backup of Data/ before running tests that change it.
