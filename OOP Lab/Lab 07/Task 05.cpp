#include <iostream>
using namespace std;

class Character {
protected:
    int characterID;
    string name;
    int level;
    int healthPoints;
    string weaponType;

public:
    Character(int id, string n, int lvl, int hp, string weapon) : characterID(id), name(n), level(lvl), healthPoints(hp), weaponType(weapon) {}
    virtual void attack() {
        cout << name << " attacks with " << weaponType << "!" << endl;
    }
    virtual void defend() {
        cout << name << " defends!" << endl;
    }
    virtual void displayStats() {
        cout << "ID: " << characterID << "\nName: " << name << "\nLevel: " << level << "\nHealth: " << healthPoints << "\nWeapon: " << weaponType << endl;
    }
};

class Warrior : public Character {
private:
    int armorStrength;
    int meleeDamage;

public:
    Warrior(int id, string n, int lvl, int hp, string weapon, int armor, int damage) :
        Character(id, n, lvl, hp, weapon), armorStrength(armor), meleeDamage(damage) {}
    void attack() override {
        cout << name << " performs a melee attack dealing " << meleeDamage << " damage!" << endl;
    }
};

class Mage : public Character {
private:
    int manaPoints;
    int spellPower;

public:
    Mage(int id, string n, int lvl, int hp, string weapon, int mana, int spell) :
        Character(id, n, lvl, hp, weapon), manaPoints(mana), spellPower(spell) {}
    void defend() override {
        cout << name << " casts a magical barrier!" << endl;
    }
};

class Archer : public Character {
private:
    int arrowCount;
    int rangedAccuracy;

public:
    Archer(int id, string n, int lvl, int hp, string weapon, int arrows, int accuracy) :
        Character(id, n, lvl, hp, weapon), arrowCount(arrows), rangedAccuracy(accuracy) {}
    void attack() override {
        cout << name << " fires an arrow with " << rangedAccuracy << "% accuracy!" << endl;
    }
};

class Rogue : public Character {
private:
    int stealthLevel;
    int agility;

public:
    Rogue(int id, string n, int lvl, int hp, string weapon, int stealth, int agi) :
        Character(id, n, lvl, hp, weapon), stealthLevel(stealth), agility(agi) {}
    void displayStats() override {
        Character::displayStats();
        cout << "Stealth Level: " << stealthLevel << "\nAgility: " << agility << endl;
    }
};

int main() {
    Warrior w1(1, "Thor", 10, 100, "Hammer", 50, 30);
    Mage m1(2, "Merlin", 12, 80, "Staff", 100, 40);
    Archer a1(3, "Robinhood", 15, 90, "Bow", 20, 85);
    Rogue r1(4, "Assassin", 18, 85, "Dagger", 90, 95);

    cout << "\n--- Warrior Info ---\n";
    w1.displayStats();
    w1.attack();
    
    cout << "\n--- Mage Info ---\n";
    m1.displayStats();
    m1.defend();
    
    cout << "\n--- Archer Info ---\n";
    a1.displayStats();
    a1.attack();
    
    cout << "\n--- Rogue Info ---\n";
    r1.displayStats();
    
    return 0;
}
