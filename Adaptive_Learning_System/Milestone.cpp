#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random> // For random number generation

using namespace std;

// Utility function to convert a string to lowercase
string toLowerCase(const string &str)
{
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

// Class representing a Student
class Student
{
private:
    string name;
    int age;
    string learningStyle;
    vector<int> quizScores;
    string initialLearningPath;

public:
    // Constructor
    Student(string studentName, int studentAge, string studentLearningStyle)
        : name(studentName), age(studentAge), learningStyle(studentLearningStyle), initialLearningPath("Basic Math, Basic Geography, Introduction to Science")
    {
    }

    // Setter using 'this' pointer
    Student &setName(string studentName)
    {
        this->name = studentName;
        return *this; // For method chaining
    }

    // Another setter using 'this' pointer
    Student &setAge(int studentAge)
    {
        this->age = studentAge;
        return *this;
    }

    void setLearningStyle(string studentLearningStyle) { learningStyle = studentLearningStyle; }
    void addQuizScore(int score) { quizScores.push_back(score); }

    // Getters
    string getName() const { return name; }
    int getAge() const { return age; }
    string getLearningStyle() const { return learningStyle; }
    vector<int> getQuizScores() const { return quizScores; }
    string getInitialLearningPath() const { return initialLearningPath; }

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
};

// Base class for Quiz
class Quiz
{
public:
    virtual void generateQuestions() = 0;
    virtual int evaluateAnswers() = 0;
};

// Derived class for MultipleChoiceQuiz
class MultipleChoiceQuiz : public Quiz
{
private:
    vector<string> questions;
    vector<string> correctAnswers;

public:
    void generateQuestions() override
    {
        // Larger pool of questions and answers
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
        random_device rd;                                     // Random number generator
        mt19937 g(rd());                                      // Mersenne Twister engine
        shuffle(questionPool.begin(), questionPool.end(), g); // Shuffle questions

        // Select the first 10 questions and their correct answers
        for (size_t i = 0; i < 5 && i < questionPool.size(); ++i)
        {
            questions.push_back(questionPool[i].first);
            correctAnswers.push_back(questionPool[i].second);
        }
    }

    int evaluateAnswers() override
    {
        int score = 0;
        string answer;

        for (size_t i = 0; i < questions.size(); ++i)
        {
            cout << "\n"
                 << questions[i] << endl;
            cout << "Your answer: ";
            getline(cin, answer);
            if (toLowerCase(answer) == toLowerCase(correctAnswers[i]))
            {
                score++;
            }
        }

        int finalScore = score * 10;
        cout << "\nYour final score is: " << finalScore << "/100" << endl;
        return finalScore;
    }
};

// Class for managing Learning Paths
class LearningPath
{
private:
    vector<string> topics;

public:
    void generateLearningPath(float averageScore)
    {
        if (averageScore < 50)
        {
            topics = {"Basic Math", "Basic Geography", "Introduction to Science"};
        }
        else if (averageScore < 75)
        {
            topics = {"Intermediate Math", "World Geography", "Introduction to Physics"};
        }
        else
        {
            topics = {"Advanced Math", "Advanced Geography", "Advanced Physics"};
        }
    }

    void displayLearningPath() const
    {
        cout << "\nYour learning path is:" << endl;
        for (const string &topic : topics)
        {
            cout << "- " << topic << endl;
        }
    }
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
            cout << "\nFeedback: Good progress, but there's room for improvement." << endl;
        }
        else
        {
            cout << "\nFeedback: Excellent work! Ready for advanced challenges!" << endl;
        }
    }
};

// Main function to run the simulation with array of objects
int main()
{
    // Creating an array of Student objects
    Student students[3] = {
        Student("John Doe", 15, "Visual"),
        Student("Jane Doe", 16, "Auditory"),
        Student("Alice Smith", 14, "Kinesthetic")};

    // Introduce the students
    for (Student &student : students)
    {
        cout << "\nHi, I'm " << student.getName() << ", a " << student.getAge()
             << "-year-old student who prefers " << student.getLearningStyle() << " learning." << endl;
        cout << "My initial learning path is: " << student.getInitialLearningPath() << endl;

        cout << endl; // Leaving a line gap
    }

    // Generate and evaluate a quiz for each student
    MultipleChoiceQuiz quiz;
    quiz.generateQuestions();

    for (Student &student : students)
    {
        cout << "\n-----------------------------------\n";
        cout << "Evaluating quiz for " << student.getName() << ":\n";
        int score = quiz.evaluateAnswers();
        student.addQuizScore(score);

        // Generate and display learning path
        LearningPath learningPath;
        learningPath.generateLearningPath(student.getAverageScore());
        learningPath.displayLearningPath();

        // Provide feedback
        Feedback feedback;
        feedback.provideFeedback(student.getAverageScore());

        cout << "\n-----------------------------------\n";
    }

    return 0;
}
