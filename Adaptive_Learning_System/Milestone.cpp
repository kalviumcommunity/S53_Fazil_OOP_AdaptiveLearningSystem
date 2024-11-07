#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

string toLowerCase(const string &str)
{
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

class Course
{
private:
    string courseName;
    int courseDuration; 
    string courseLevel;

public:
    Course(string name, int duration, string level)
        : courseName(name), courseDuration(duration), courseLevel(level) {}

    ~Course() // Destructor for Course class
    {
        
    }

    string getCourseName() const { return courseName; }
    int getCourseDuration() const { return courseDuration; }
    string getCourseLevel() const { return courseLevel; }

    void setCourseName(const string &name) { courseName = name; }
    void setCourseDuration(int duration) { courseDuration = duration; }
    void setCourseLevel(const string &level) { courseLevel = level; }

    void displayCourseDetails() const
    {
        cout << "Course: " << courseName << ", Duration: " << courseDuration
             << " weeks, Level: " << courseLevel << endl;
    }
};

class Student
{
private:
    string name;
    int age;
    string learningStyle;
    vector<int> quizScores;
    vector<Course *> enrolledCourses; 

    static int totalStudents;
    static int totalQuizScores;

public:
    Student() : age(0) {} 

    Student(string studentName, int studentAge, string studentLearningStyle)
    {
        setName(studentName);
        setAge(studentAge);
        setLearningStyle(studentLearningStyle);
        totalStudents++;
    }

    ~Student() // Destructor for Student class
    {
        for (Course* course : enrolledCourses)
        {
            delete course; 
        }
        enrolledCourses.clear();
    }

    Student &addQuizScore(int score)
    {
        quizScores.push_back(score);
        totalQuizScores += score;
        return *this;
    }

    Student &enrollInCourse(Course *course)
    {
        enrolledCourses.push_back(course);
        return *this;
    }

    string getName() const { return name; }
    int getAge() const { return age; }
    string getLearningStyle() const { return learningStyle; }
    vector<int> getQuizScores() const { return quizScores; }
    vector<Course *> getEnrolledCourses() const { return enrolledCourses; }

    void setName(const string &studentName) { name = studentName; }
    void setAge(int studentAge) { age = studentAge; }
    void setLearningStyle(const string &studentLearningStyle) { learningStyle = studentLearningStyle; }

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

    static int getTotalStudents() { return totalStudents; }
    static int getTotalQuizScores() { return totalQuizScores; }
};

int Student::totalStudents = 0;
int Student::totalQuizScores = 0;

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

        unsigned seed = chrono::system_clock::now().time_since_epoch().count(); 
        mt19937 g(seed);
        shuffle(questionPool.begin(), questionPool.end(), g); 

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
        cout << "\nYou scored " << score << " out of " << questions.size() << " (" << (score * 10) << "%)." << endl;
    }

    int getScore() const { return score * 10; }
};

class LearningPath
{
private:
    vector<Course *> courses;

public:
    ~LearningPath() // Destructor for LearningPath class
    {
        for (Course *course : courses)
        {
            delete course;
        }
        courses.clear();
    }

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

    for (Course *course : learningPath.getCourses())
    {
        student.enrollInCourse(new Course(*course));
    }

    student.displayEnrolledCourses();

    cout << "\nTotal Students: " << Student::getTotalStudents() << endl;

    return 0;
}
