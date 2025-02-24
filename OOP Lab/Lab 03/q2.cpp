#include <iostream>
using namespace std;

class FitnessTracker {
private:
    string userName;
    int dailyStepGoal;
    int stepsTaken;
    double caloriesBurned;

public:
    FitnessTracker(string name, int goal) : userName(name), dailyStepGoal(goal), stepsTaken(0), caloriesBurned(0) {
        cout << "Fitness Tracker initialized for " << userName << " with a daily step goal of " << dailyStepGoal << " steps.\n";
    }

    void logSteps(int steps) {
        if (steps <= 0) {
            cout << "Invalid step count! Enter a positive number.\n";
            return;
        }
        stepsTaken += steps;
        calculateCaloriesBurned();
        cout << steps << " steps logged. Total steps today: " << stepsTaken << endl;
    }

    void calculateCaloriesBurned() {
        // Assume 1 step burns 0.04 calories
        caloriesBurned = stepsTaken * 0.04;
    }

    void displayProgress() {
        cout << "\nFitness Progress for " << userName << ":\n";
        cout << "Steps Taken: " << stepsTaken << "/" << dailyStepGoal << endl;
        cout << "Calories Burned: " << caloriesBurned << " kcal\n";

        if (stepsTaken >= dailyStepGoal) {
            cout << "Congratulations! You've reached your step goal for today! Keep it up!\n";
        } else {
            cout << "Keep going! You need " << (dailyStepGoal - stepsTaken) << " more steps to reach your goal!\n";
        }
    }
};

int main() {

    FitnessTracker laibaTracker("Laiba", 10000);

    laibaTracker.logSteps(3000);
    laibaTracker.logSteps(4500);
    laibaTracker.logSteps(3000);  

    laibaTracker.displayProgress();

    return 0;
}
