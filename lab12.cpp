#include <iostream>
#include <string>
using namespace std;

// Base Class: Employee
class employee {
protected:
    string name;
    int id;

public:
    employee() : name("Default"), id(0) {
        cout << "Employee Constructor called" << endl;
    }

    employee(string n, int i) : name(n), id(i) {
        cout << "Employee Parameterized Constructor called" << endl;
    }

    virtual ~employee() {
        cout << "Employee Destructor called" << endl;
    }

    virtual void displayInfo() {
        cout << "Employee Name: " << name << ", ID: " << id << endl;
    }

    virtual double calculateSalary(double base_salary) {
        return base_salary;
    }

    void staticBindingExample() {
        cout << "Static Binding in Employee" << endl;
    }
};

// Derived Class: Manager
class manager : public employee {
protected:
    int num_teams;

public:
    manager() : employee(), num_teams(0) {
        cout << "Manager Constructor called" << endl;
    }

    manager(int t, string n, int i) : employee(n, i), num_teams(t) {
        cout << "Manager Parameterized Constructor called" << endl;
    }

    ~manager() override {
        cout << "Manager Destructor called" << endl;
    }

    void displayInfo() override {
        cout << "Manager Name: " << name << ", ID: " << id
            << ", Teams: " << num_teams << endl;
    }

    double calculateSalary(double salary_per_team) override {
        return salary_per_team * num_teams;
    }
};

// Derived Class: Engineer
class engineer : public employee {
protected:
    int num_projects;

public:
    engineer() : employee(), num_projects(0) {
        cout << "Engineer Constructor called" << endl;
    }

    engineer(int p, string n, int i) : employee(n, i), num_projects(p) {
        cout << "Engineer Parameterized Constructor called" << endl;
    }

    ~engineer() override {
        cout << "Engineer Destructor called" << endl;
    }

    void displayInfo() override {
        cout << "Engineer Name: " << name << ", ID: " << id
            << ", Projects: " << num_projects << endl;
    }

    double calculateSalary(double salary_per_project) override {
        return salary_per_project * num_projects;
    }
};

// Class to Demonstrate Diamond Problem
class senior_employee : public virtual employee {
public:
    senior_employee() {
        cout << "Senior Employee Constructor called" << endl;
    }

    ~senior_employee() {
        cout << "Senior Employee Destructor called" << endl;
    }

    void seniorInfo() {
        cout << "Senior Employee Specific Info" << endl;
    }
};

class senior_manager : public senior_employee, public manager {
public:
    senior_manager() : senior_employee(), manager() {
        cout << "Senior Manager Constructor called" << endl;
    }

    ~senior_manager() {
        cout << "Senior Manager Destructor called" << endl;
    }

    void displayInfo() override {
        cout << "Senior Manager Name: " << name << ", ID: " << id << endl;
    }
};

// Main Function
int main() {
    // 1. Constructor Call Sequence
    cout << "\n--- Constructor Call Sequence ---\n";
    manager m1(3, "Alice", 101);
    engineer e1(5, "Bob", 102);

    // 2. Polymorphism with Virtual Functions
    cout << "\n--- Polymorphism with Virtual Functions ---\n";
    employee* emp_ptr = &m1; // Base class pointer to Manager object
    emp_ptr->displayInfo();
    cout << "Salary: " << emp_ptr->calculateSalary(1000) << endl;

    emp_ptr = &e1; // Base class pointer to Engineer object
    emp_ptr->displayInfo();
    cout << "Salary: " << emp_ptr->calculateSalary(500) << endl;

    // 3. Static and Dynamic Binding
    cout << "\n--- Static and Dynamic Binding ---\n";
    e1.staticBindingExample();        // Static binding
    emp_ptr->displayInfo();           // Dynamic binding (resolved at runtime)

    // 4. Type Casting
    cout << "\n--- Type Casting ---\n";
    manager* mgr_ptr = static_cast<manager*>(&m1); // Upcasting
    mgr_ptr->displayInfo();

    emp_ptr = static_cast<employee*>(&m1);        // Upcasting
    manager* downcast_mgr = dynamic_cast<manager*>(emp_ptr); // Downcasting
    if (downcast_mgr) {
        downcast_mgr->displayInfo();
    }

    // 5. Diamond Problem in Multiple Inheritance
    cout << "\n--- Diamond Problem in Multiple Inheritance ---\n";
    senior_manager sm;
    sm.displayInfo(); // Ambiguity resolved using virtual inheritance

    return 0;
}
