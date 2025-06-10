#include <iostream>

// Empty class 
class Empty {
};

// Class with methods
class OnlyMethods {
    int sum(int a, int b) {
        return a + b;
}
};

// Class with member fields
struct Fields {
    int a;
    bool b;
    double c;
    char d;
};

// Class with class member field (static)
struct StaticFields {
    int a;
    bool b;
    double c;
    char d;
    static int e;
    static bool f;
    static double g;
    static char h;
};

int StaticFields::e = 35'000;
bool StaticFields::f = false;
double StaticFields::g = 4.639876;
char StaticFields::h = 'i';

int main (int argc, char *argv[]) {

    std::cout << "Empty class size: " << sizeof(Empty) << '\n';
    std::cout << "Class with methods class size: " << sizeof(OnlyMethods) << '\n';
    std::cout << "Class with member fields class size: " << sizeof(Fields) << '\n';
    std::cout << "Class with class member fields (static) class size: " << sizeof(StaticFields) << '\n';

    // Check layout in debugger
    Empty empty[]{{},{},{}};
    for (auto obj : empty) {
        std::cout << std::hex << &obj << '\n';
    }

    OnlyMethods onlyMethods{};
    Fields fields{34'000, true, 6.439876, 'h'};
    StaticFields staticFields{34'000, true, 6.439876, 'h'};

    return 0;
}
