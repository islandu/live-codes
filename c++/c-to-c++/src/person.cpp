#include <climits>
#include <cstdio>
#include <stdexcept>
#include "c_to_cpp/person.hpp"

namespace c_to_cpp {

// ClassName::method_name()
Person::Person(const std::string& name, unsigned int age)
    : name_(name), age_(age) { }

Person::~Person(void) { }

// Getters (encapsulation)

const std::string&
Person::name(void) const
{
    return this->name_;
}

unsigned int
Person::age(void) const
{
    return this->age_;
}

// to_string method (const)
std::string
Person::to_string(void) const
{
    std::string result;

    result.resize(255);
    std::snprintf(result.data(), 255,
                  "Person { name: '%s', age: %u }",
                  this->name_.c_str(), this->age_);

    result.shrink_to_fit();
    return result;
}

// birthday method (non-const)
void
Person::birthday(void)
{
    if (this->age_ == UINT_MAX)
    {
        throw std::overflow_error(
            "Person's age will overflow if incremented");
    }

    ++this->age_;
}

Employee::Employee(const std::string& name, unsigned int age,
                   unsigned int employee_id)
                   : Person(name, age), employee_id_(employee_id)
{
}

std::string
Employee::to_string(void) const
{
    std::string result;

    result.resize(255);
    std::snprintf(result.data(), 255,
                  "Employee { name: '%s', age: %u, employee_id: %u }",
                  this->name().c_str(), this->age(), this->employee_id_);

    result.shrink_to_fit();
    return result;
}

} // namespace c_to_cpp
