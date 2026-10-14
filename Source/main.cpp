#include "EducationSystem.h"
#include <exception>
#include <iostream>

int main(int argc, char* argv[]) {
    try {
        EducationSystem system(argc > 1 ? argv[1] : "Data");
        system.run();
    } catch (const std::exception& ex) {
        std::cerr << "Startup error: " << ex.what() << '\n';
        return 1;
    }
    return 0;
}
