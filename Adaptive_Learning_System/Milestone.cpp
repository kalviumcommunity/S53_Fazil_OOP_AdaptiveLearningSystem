#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <algorithm>
#include <chrono>

using namespace std;

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
    Student(string studentName, int studentAge, string studentLearningStyle)
        : name(studentName), age(studentAge), learningStyle(studentLearningStyle), initialLearningPath("Basic Math, Basic Geography, Introduction to Science")
    {
    }

    Student &setName(string studentName)
    {
        this->name = studentName;
        return *this;
    }

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

class MultipleChoiceQuiz : public Quiz
{
private:
    vector<string> questions;
    vector<string> correctAnswers;

public:
    void generateQuestions() override
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

int main()
{
    // Creating dynamic array of Student objects using 'new'
    Student *students[3];
    students[0] = new Student("John Doe", 15, "Visual");
    students[1] = new Student("Jane Doe", 16, "Auditory");
    students[2] = new Student("Alice Smith", 14, "Kinesthetic");

    for (int i = 0; i < 3; ++i)
    {
        cout << "\nHi, I'm " << students[i]->getName() << ", a " << students[i]->getAge()
             << "-year-old student who prefers " << students[i]->getLearningStyle() << " learning." << endl;
        cout << "My initial learning path is: " << students[i]->getInitialLearningPath() << endl;

        cout << endl;
    }

    // Iterate over each student and generate quiz questions for each student
    for (int i = 0; i < 3; ++i)
    {
        // Dynamically allocate quiz object and generate new set of questions
        MultipleChoiceQuiz *quiz = new MultipleChoiceQuiz();
        quiz->generateQuestions(); // Generate different questions for each student

        cout << "\n-----------------------------------\n";
        cout << "Evaluating quiz for " << students[i]->getName() << ":\n";
        int score = quiz->evaluateAnswers();
        students[i]->addQuizScore(score);

        LearningPath *learningPath = new LearningPath();
        learningPath->generateLearningPath(students[i]->getAverageScore());
        learningPath->displayLearningPath();

        Feedback *feedback = new Feedback();
        feedback->provideFeedback(students[i]->getAverageScore());

        delete learningPath;
        delete feedback;
        delete quiz;

        cout << "\n-----------------------------------\n";
    }

    // Clean up dynamic memory for students
    for (int i = 0; i < 3; ++i)
    {
        delete students[i];
    }

    return 0;
}

