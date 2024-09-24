#include <iostream>
using namespace std;

// Class representing a Student
class Student
{
private:
    string name;
    int age;

public:
    // Constructor
    Student(string studentName, int studentAge)
        : name(studentName), age(studentAge) {}

    // Setter for student name
    void setName(string studentName)
    {
        name = studentName;
    }

    // Getter for student name
    string getName()
    {
        return name;
    }

    // Setter for student age
    void setAge(int studentAge)
    {
        age = studentAge;
    }

    // Getter for student age
    int getAge()
    {
        return age;
    }

    // Display student info
    void displayInfo()
    {
        cout << "Student Name: " << name << endl;
        cout << "Age: " << age << endl;
    }
};

// Class for providing Feedback
class Feedback
{
public:
    // Provide feedback based on age
    void provideFeedback(int age)
    {
        if (age < 18)
        {
            cout << "You are a young learner. Keep up the good work!" << endl;
        }
        else
        {
            cout << "Great effort! Continue learning and growing." << endl;
        }
    }
};

// Main function
int main()
{
    // Creating a student object
    Student student("John Doe", 15);

    // Display student information
    student.displayInfo();

    // Providing feedback based on age
    Feedback feedback;
    feedback.provideFeedback(student.getAge());

    return 0;
}
