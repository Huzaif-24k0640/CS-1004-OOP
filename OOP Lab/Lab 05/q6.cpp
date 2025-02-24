#include <iostream>
using namespace std;

class Level {
private:
    int levelNumber;
    string description;
public:
    Level(int num, string desc) : levelNumber(num), description(desc) {}

    void displayDetails() {
        cout << "Level " << levelNumber << ": " << description << endl;
    }
};

class VideoGame {
private:
    string title;
    string genre;
    Level* levels[10];
    int levelCount;
public:
    VideoGame(string t, string g) : title(t), genre(g), levelCount(0) {}

    ~VideoGame() {
        // Destroy all levels when game is destroyed
        for (int i = 0; i < levelCount; i++) {
            delete levels[i];
        }
        cout << "Game '" << title << "' and its levels destroyed.\n";
    }

    void addLevel(int num, string desc) {
        if (levelCount < 10) {
            levels[levelCount++] = new Level(num, desc);
            cout << "Level " << num << " added to " << title << endl;
        } else {
            cout << "Maximum levels reached!\n";
        }
    }

    void displayDetails() {
        cout << "\nGame Title: " << title << "\nGenre: " << genre << "\nLevels:\n";
        if (levelCount == 0) {
            cout << "No levels added yet.\n";
        } else {
            for (int i = 0; i < levelCount; i++) {
                levels[i]->displayDetails();
            }
        }
    }
};

int main() {

    VideoGame game("Fantasy Adventure", "Action");

    game.addLevel(1, "Introduction to the fantasy Journey");
    game.addLevel(2, "Fighting monsters");
    game.addLevel(3, "Exploring the Dark Forest of Death");

    game.displayDetails();

    return 0;
}
