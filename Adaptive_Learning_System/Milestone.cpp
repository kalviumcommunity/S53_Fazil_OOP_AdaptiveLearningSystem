#include <iostream>
#include <string>

using namespace std;

// Class representing a Student
class Student
{
private:
    string name;
    int age;
    string learningStyle;
    string initialLearningPath;

public:
    // Constructor
    Student(string studentName, int studentAge, string studentLearningStyle)
        : name(studentName), age(studentAge), learningStyle(studentLearningStyle), initialLearningPath("Basic Math, Basic Geography, Introduction to Science")
    {
    }

    // Setters using 'this' pointer
    Student &setName(string studentName)
    {
        this->name = studentName; // Using 'this' pointer to access the current object's member
        return *this;             // Return *this to enable method chaining
    }

    Student &setAge(int studentAge)
    {
        this->age = studentAge; // Using 'this' pointer
        return *this;
    }

    Student &setLearningStyle(string studentLearningStyle)
    {
        this->learningStyle = studentLearningStyle; // Using 'this' pointer
        return *this;
    }

    // Getters
    string getName() const { return name; }
    int getAge() const { return age; }
    string getLearningStyle() const { return learningStyle; }
    string getInitialLearningPath() const { return initialLearningPath; }

    // Display Student Information
    void displayStudentInfo() const
    {
        cout << "Student Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Learning Style: " << learningStyle << endl;
        cout << "Initial Learning Path: " << initialLearningPath << endl;
    }
};

// Class for managing Learning Paths
class LearningPath
{
private:
    string path;

public:
    // Constructor
    LearningPath(string initialPath) : path(initialPath) {}

    // Setter using 'this' pointer
    LearningPath &updateLearningPath(string newPath)
    {
        this->path = newPath; // Using 'this' pointer to update learning path
        return *this;         // Return *this for method chaining
    }

    // Getter
    string getLearningPath() const { return path; }

    // Display Learning Path
    void displayLearningPath() const
    {
        cout << "Learning Path: " << path << endl;
    }
};

// Main function
int main()
{
    // Create a student profile
    Student student("John Doe", 15, "Visual");

    // Display initial student info
    student.displayStudentInfo();
    cout << endl;

    // Update student details using method chaining with 'this' pointer
    student.setName("Jane Doe").setAge(16).setLearningStyle("Kinesthetic");

    // Display updated student info
    cout << "\nUpdated Student Info:\n";
    student.displayStudentInfo();
    cout << endl;

    // Create a learning path object
    LearningPath learningPath("Basic Math, Basic Geography, Introduction to Science");

    // Update the learning path using 'this' pointer and display it
    learningPath.updateLearningPath("Intermediate Math, World Geography, Introduction to Physics").displayLearningPath();

    return 0;
}
