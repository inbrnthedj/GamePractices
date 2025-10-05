#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
// #include <windows.h> // this is only for sleep()

#define MAX_NAME_LENGTH 50
#define MIN_NAME_LENGTH 3

typedef struct {
    char name[MAX_NAME_LENGTH + 1];
    int level;
    int strength;
    int intelligence;
    int health;
    int stamina;
    int magicka;
} Character;

// Function prototypes
int physical_attack(Character* character);
int magical_attack(Character* character);
bool is_alive(const Character* character);
void print_character(const Character* character);
bool validate_character(const Character* character);

int main() {
    // Initialize random seed
    srand((unsigned int)time(NULL));

    // Create characters
    Character mage = {
        .name = "Merlin",
        .level = 1,
        .strength = 20,
        .intelligence = 110,
        .health = 1000,
        .stamina = 80,
        .magicka = 200
    };

    Character knight = {
        .name = "Pendragon",
        .level = 1,
        .strength = 90,
        .intelligence = 70,
        .health = 1500,
        .stamina = 150,
        .magicka = 1
    };

    // Validate characters
    if (!validate_character(&mage) || !validate_character(&knight)) {
        printf("Error: Invalid character attributes!\n");
        return 1;
    }
    
    // Fight simulation
    
    printf("Mage or Knight? (M/K) ");
    char role;
    role=getchar();
    if (role=='M' || role=='m'){
        printf("Playing as %s\n", mage.name);
    } else{
        printf("Playing as %s\n\n", knight.name);
    }
    // Start battle
    printf("Battle starts between Mage and Knight!\n\n");

    while (is_alive(&mage) && is_alive(&knight)) {
        int toss = rand() % 2 + 1;  // 1 or 2

        if (toss == 1) {
            //for buffer
                getchar();
            // Mage turn
            if (rand() % 2 == 0) {  // Random choice between magic and physical
                int damage = magical_attack(&mage);
                knight.health -= damage;
                printf("%s casts a spell! Deals %d damage. %s HP = %d\n", 
                       mage.name, damage, knight.name, knight.health);

            } else {
                int damage = physical_attack(&mage);
                knight.health -= damage;
                printf("%s strikes physically! Deals %d damage. %s HP = %d\n", 
                       mage.name, damage, knight.name, knight.health);

            }

        } else {
            //for buffer
            getchar();
            // Knight turn
            if (rand() % 2 == 0) {  // Random choice between magic and physical
                int damage = physical_attack(&knight);
                mage.health -= damage;
                printf("%s strikes physically! Deals %d damage. %s HP = %d\n", 
                       knight.name, damage, mage.name, mage.health);

            } else {
                int damage = magical_attack(&knight);
                mage.health -= damage;
                printf("%s casts a spell! Deals %d damage. %s HP = %d\n", 
                       knight.name, damage, mage.name, mage.health);

            }

        }

    }

    // Winner
    printf("\nThe winner is:\n");
    if (is_alive(&mage)) {
        print_character(&mage);
    } else {
        print_character(&knight);
    }

    return 0;
}

int physical_attack(Character* character) {
    if (character->stamina <= 0) {
        printf("%s is too exhausted to perform a physical attack!\n", character->name);
        return 0;
    }
    
    int stamina_cost = 20 / character->strength;
    if (stamina_cost < 1) stamina_cost = 1;
    character->stamina -= stamina_cost;
    
    return character->strength * (rand() % 6 + 1);  // rand() % 6 + 1 gives 1-6
}

int magical_attack(Character* character) {
    if (character->magicka <= 0) {
        printf("%s is out of magicka!\n", character->name);
        return 0;
    }
    
    int magicka_cost = 20 / character->magicka;
    if (magicka_cost < 1) magicka_cost = 1;
    character->magicka -= magicka_cost;
    
    return character->intelligence * (rand() % 6 + 1);  // rand() % 6 + 1 gives 1-6
}

bool is_alive(const Character* character) {
    return character->health > 0;
}

void print_character(const Character* character) {
    printf("<Character name=%s, level=%d, hp=%d, sta=%d, int=%d, mag=%d>\n",
           character->name, character->level, character->health, 
           character->stamina, character->intelligence, character->magicka);
}

bool validate_character(const Character* character) {
    if (strlen(character->name) < MIN_NAME_LENGTH || strlen(character->name) > MAX_NAME_LENGTH) {
        return false;
    }
    if (character->level <= 0 || character->strength <= 0 || character->intelligence <= 0 ||
        character->health <= 0 || character->stamina <= 0 || character->magicka <= 0) {
        return false;
    }
    return true;
}

