#include <climits>
#include <iostream>
#include <stdexcept>
#include <vector>
#include "c_to_cpp/person.hpp"

using c_to_cpp::Person;
using c_to_cpp::Employee;

int main(void)
{
    Person *person = new Person("Sam Sepiol", UINT_MAX);
    Person *employee = new Employee("Elliot Alderson", 28, 42);
    std::vector<Person *> people;

    people.push_back(person);
    people.push_back(employee);

    for (const Person *p : people) {
        std::cout << p->to_string() << std::endl;
    }

    // Delete Persons allocated on the heap with `new`
    delete person;
    delete employee;

    // std::cout << person.to_string() << std::endl;
    // std::cout << person.name() << std::endl;
    // std::cout << person.age() << std::endl;

    // try {
    //     person.birthday();
    // }
    // catch (const std::exception& e) {
    //     std::cout << "Error caught: " << e.what() << std::endl;
    // }

    return 0;
}

