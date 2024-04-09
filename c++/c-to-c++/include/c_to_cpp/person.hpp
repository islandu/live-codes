#ifndef _CTOCPP_PERSON_HPP
#define _CTOCPP_PERSON_HPP

#include <string>

// using std::string;

namespace c_to_cpp {

class Person {
public:
    // Constructor
    Person(const std::string& name, unsigned int age);

    // Default destructor (virtual)
    // I have to declare this virtual for polymorphism to work
    virtual ~Person(void);

    // Getters (encapsulation)
    const std::string& name(void) const;
    unsigned int age(void) const;

    // to_string method (const)
    // `virtual` means I can override it in a derived class
    virtual std::string to_string(void) const;

    // birthday method (non-const)
    void birthday(void);

private:
    // Private members
    std::string name_;
    unsigned int age_;
};

class Employee : public Person {
public:
    Employee(const std::string& name, unsigned int age,
             unsigned int employee_id);

    std::string to_string(void) const override;

private:
    unsigned int employee_id_;
};

} // namespace c_to_cpp

#endif // _CTOCPP_PERSON_HPP
