#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

// Function to convert a string to lowercase for case-insensitive comparison
string toLowerCase(const string &str)
{
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

// Class representing a Course
class Course
{
private:
    string courseName;
    int courseDuration; // Duration in weeks
    string courseLevel;

public:
    // Constructor
    Course(string name, int duration, string level)
        : courseName(name), courseDuration(duration), courseLevel(level) {}

    // Getters
    string getCourseName() const { return courseName; }
    int getCourseDuration() const { return courseDuration; }
    string getCourseLevel() const { return courseLevel; }

    // Setters
    void setCourseName(const string &name) { courseName = name; }
    void setCourseDuration(int duration) { courseDuration = duration; }
    void setCourseLevel(const string &level) { courseLevel = level; }

    // Display course details
    void displayCourseDetails() const
    {
        cout << "Course: " << courseName << ", Duration: " << courseDuration
             << " weeks, Level: " << courseLevel << endl;
    }
};

// Class representing a Student
class Student
{
private:
    string name;
    int age;
    string learningStyle;
    vector<int> quizScores;
    vector<Course *> enrolledCourses; // Vector of pointers to Course

    // Static variables to track the total number of students and total quiz scores
    static int totalStudents;
    static int totalQuizScores;

public:
    Student() : age(0) {} // Default constructor

    Student(string studentName, int studentAge, string studentLearningStyle)
    {
        setName(studentName);
        setAge(studentAge);
        setLearningStyle(studentLearningStyle);
        totalStudents++; // Increment total students
    }

    // Add quiz score and update total quiz scores
    Student &addQuizScore(int score)
    {
        quizScores.push_back(score);
        totalQuizScores += score;
        return *this;
    }

    // Enroll in a course (using pointers)
    Student &enrollInCourse(Course *course)
    {
        enrolledCourses.push_back(course);
        return *this;
    }

    // Getters (Accessors)
    string getName() const { return name; }
    int getAge() const { return age; }
    string getLearningStyle() const { return learningStyle; }
    vector<int> getQuizScores() const { return quizScores; }
    vector<Course *> getEnrolledCourses() const { return enrolledCourses; }

    // Setters
    void setName(const string &studentName) { name = studentName; }
    void setAge(int studentAge) { age = studentAge; }
    void setLearningStyle(const string &studentLearningStyle) { learningStyle = studentLearningStyle; }

    // Calculate average score
    float getAverageScore() const
    {
        if (quizScores.empty())
            return 0;
        int sum = 0;
        for (int score : quizScores)
        {
            sum += score;
        }
        return static_cast<float>(sum) / quizScores.size();
    }

    // Display enrolled courses
    void displayEnrolledCourses() const
    {
        cout << "\nEnrolled Courses:" << endl;
        if (enrolledCourses.empty())
        {
            cout << "No courses enrolled yet." << endl;
        }
        else
        {
            for (const Course *course : enrolledCourses)
            {
                course->displayCourseDetails();
            }
        }
    }

    // Static function to return total number of students
    static int getTotalStudents() { return totalStudents; }
    static int getTotalQuizScores() { return totalQuizScores; }
};

// Initialize static variables
int Student::totalStudents = 0;
int Student::totalQuizScores = 0;

// Class for Quiz functionality
class Quiz
{
private:
    vector<string> questions;
    vector<string> correctAnswers;
    int score;

public:
    Quiz() : score(0) {}

    void generateQuestions()
    {
        vector<pair<string, string>> questionPool = {
            {"What is the capital of France?", "paris"},
            {"What is 2 + 2?", "4"},
            {"What is the largest planet in our solar system?", "jupiter"},
            {"Who wrote 'Romeo and Juliet'?", "shakespeare"},
            {"What is the chemical symbol for water?", "h2o"},
            {"In which year did the Titanic sink?", "1912"},
            {"What is the square root of 64?", "8"},
            {"Who painted the Mona Lisa?", "da vinci"},
            {"What is the capital city of Japan?", "tokyo"},
            {"How many continents are there on Earth?", "7"},
            {"What is the smallest prime number?", "2"},
            {"Which planet is known as the Red Planet?", "mars"},
            {"What is the main ingredient in guacamole?", "avocado"},
            {"Who discovered penicillin?", "fleming"},
            {"What is the tallest mountain in the world?", "everest"},
            {"What gas do plants absorb from the atmosphere?", "carbon dioxide"},
            {"What is the largest ocean on Earth?", "pacific"},
            {"Who was the first person to walk on the moon?", "neil armstrong"},
            {"What is the hardest natural substance on Earth?", "diamond"},
            {"What is the capital of Australia?", "canberra"},
            {"Which element has the chemical symbol 'O'?", "oxygen"}};

        // Shuffle the question pool
        unsigned seed = chrono::system_clock::now().time_since_epoch().count(); // Use current time as seed
        mt19937 g(seed);
        shuffle(questionPool.begin(), questionPool.end(), g); // Shuffle questions

        // Select the first 10 questions and their correct answers
        for (size_t i = 0; i < 10 && i < questionPool.size(); ++i)
        {
            questions.push_back(questionPool[i].first);
            correctAnswers.push_back(questionPool[i].second);
        }
    }

    void administerQuiz()
    {
        string answer;
        score = 0;

        for (size_t i = 0; i < questions.size(); ++i)
        {
            cout << questions[i] << endl;
            cout << "Your answer: ";
            getline(cin, answer);

            if (toLowerCase(answer) == toLowerCase(correctAnswers[i]))
            {
                score++;
            }
        }
        cout << "\nYou scored " << score << " out of " << questions.size() << " (" << (score * 20) << "%)." << endl;
    }

    int getScore() const { return score * 10; }
};

// Class for Learning Path functionality
class LearningPath
{
private:
    vector<Course *> courses;

public:
    void generateLearningPath(float averageScore)
    {
        courses.clear();
        if (averageScore < 50)
        {
            courses.push_back(new Course("Basic Math", 6, "Basic"));
            courses.push_back(new Course("Basic Geography", 6, "Basic"));
            courses.push_back(new Course("Basic Science", 6, "Basic"));
        }
        else if (averageScore < 75)
        {
            courses.push_back(new Course("Intermediate Math", 8, "Intermediate"));
            courses.push_back(new Course("World Geography", 8, "Intermediate"));
            courses.push_back(new Course("Introduction to Physics", 8, "Intermediate"));
        }
        else
        {
            courses.push_back(new Course("Advanced Math", 10, "Advanced"));
            courses.push_back(new Course("Advanced Geography", 10, "Advanced"));
            courses.push_back(new Course("Advanced Physics", 10, "Advanced"));
        }
    }

    void displayLearningPath() const
    {
        cout << "\nRecommended Learning Path:" << endl;
        for (const Course *course : courses)
        {
            course->displayCourseDetails();
        }
    }

    vector<Course *> getCourses() const { return courses; }
};

// Class for providing Feedback
class Feedback
{
public:
    void provideFeedback(float averageScore) const
    {
        if (averageScore < 50)
        {
            cout << "\nFeedback: Focus on foundational topics for improvement." << endl;
        }
        else if (averageScore < 75)
        {
            cout << "\nFeedback: You're doing well. Work on intermediate skills." << endl;
        }
        else
        {
            cout << "\nFeedback: Excellent performance! Consider advanced topics." << endl;
        }
    }
};

int main()
{
    string studentName;
    int studentAge;
    string studentLearningStyle;

    cout << "Enter student name: ";
    getline(cin, studentName);

    cout << "Enter student age: ";
    cin >> studentAge;
    cin.ignore();

    cout << "Enter student learning style: ";
    getline(cin, studentLearningStyle);

    Student student;
    student.setName(studentName);
    student.setAge(studentAge);
    student.setLearningStyle(studentLearningStyle);

    Quiz quiz;
    quiz.generateQuestions();
    quiz.administerQuiz();
    student.addQuizScore(quiz.getScore());

    cout << "\nStudent Details:" << endl;
    cout << "Name: " << student.getName() << ", Age: " << student.getAge()
         << ", Learning Style: " << student.getLearningStyle() << endl;
    cout << "Average Quiz Score: " << student.getAverageScore() << "%" << endl;

    LearningPath learningPath;
    learningPath.generateLearningPath(student.getAverageScore());
    learningPath.displayLearningPath();

    Feedback feedback;
    feedback.provideFeedback(student.getAverageScore());

    // Enroll student in recommended courses and display enrolled courses
    for (Course *course : learningPath.getCourses())
    {
        student.enrollInCourse(course);
    }

    cout << "\nEnrolled Courses:" << endl;
    for (Course *course : student.getEnrolledCourses())
    {
        cout << "Course Name: " << course->getCourseName() << endl;
        cout << "Course Duration: " << course->getCourseDuration() << " hours" << endl;
        cout << "Course Difficulty: " << course->getCourseLevel() << endl;
        cout << "--------------------------" << endl;
    }

    // Clean up dynamically allocated memory
    for (Course *course : learningPath.getCourses())
    {
        delete course;
    }

    return 0;
}
