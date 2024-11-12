#include <iostream>
#include <string>
#include <typeinfo>
#include <map>

int main() {
    int i;
    if ((i = 1) && i <= 5)
        std::cout << "Success! i: " << i << std::endl;
    else
        std::cout << "Fail! i: " << i << std::endl;
    std::cout << "out of scope, i: " << i << '\n';
    
}
