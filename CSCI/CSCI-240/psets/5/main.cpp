/***************************************************************
CSCI 240         Program 5     Fall 2023

Programmer: Nathan Warner
 
Section: 001

Date Due: 10-13-23

Purpose: Write a program that will simulate a battle between a Dungeon & Dragons character and a
random type of monster.
***************************************************************/
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using std::cout;
using std::cin;
using std::cerr;
using std::endl;

// Global Space

// Constants
const int SEED{14}, CRITICAL_ROLL{20}, FAILURE_ROLL{1};
const char* PLAYER_FAILURE_MESSAGE = "The attack hits! Critical failure! The player swings wildly, loses balances, and bumps their head on a wall. -1 HP. Monster's current HP: ";
const char* PLAYER_CRITICAL_MESSAGE = "The attack hits! Natural 20! The player experts attacks the monster's exposed weaknesses, dealing -25 HP to it!. Monster's current HP: ";
const char* MONSTER_FAILURE_MESSAGE = "The attack hits! Critical failure! The monster recklessly attacks, slips and bumps their head on the floor. -1 HP. Players current HP: ";
const char* MONSTER_CRITICAL_MESSAGE = "The attack hits! Natural 20! The monster's combat prowess becomes the stuff of nightmares, savagely rending the player, dealing -25 HP them!. Players current HP: ";
const char* MONSTER_DEFEATED = "The monster has been slain! The adrenaline rush from the victory restores their HP to full!";
const char* PLAYER_DEFEATED = "Gasping for breath and realizing their mother wasn't wrong when they suggested they just stay on the farm and live a quiet life, the player passes away!";
const char* MONSTER_ATTACK_FAIL = "The monster's attack fails to deal damage to the player. Player's current HP: ";
const char* PLAYER_ATTACK_FAIL = "The player's attack fails to deal damage to the player. Monster's current HP: "; 

// Entry
int main(int argc, const char *argv[]) {
    // Seed Random
    srand(SEED);

    // Player Information
    int player_health{0}, armor_class{0}, player_health_info{0};

    // Monster Information
    int monster_type{0}, monster_hp{0}, monster_ac{0};
    const char* monster_name = "";
    const char* encounter_message = "";


    // Game Variables
    int pc_attack_roll{0}, pc_attack_damage{0},
        monster_attack_roll{0}, monster_attack_damage{0},
        kill_streak{0};
    bool display_info = true, gameover = false;

    // Begin Game

    // Generate random values
    player_health = 50 + (rand() % (150 - 50 +1));
    player_health_info = player_health;
    armor_class = 1 + (rand() % (4 - 1 +1));

    // Output Health and AC For Player
    cout << "The player's maximum HP is " << player_health << endl
        << "The player's armor class is " << armor_class << endl;

    // Game loop, looping until player has  been defeated
    while (!gameover) {

        // Make sure the info is displayed at the start of each monster instance
        if (display_info) {
            //  Generate information about the monster
            monster_type = rand() % 3;
            switch (monster_type) {
                case 0:
                    monster_name = "Goblin";
                    encounter_message = "You encounter a meager goblin. This should be easy enough!";
                    monster_hp = 30 + (rand() % (45-30 + 1));
                    monster_ac = 1 + (rand() % (2));
                    break;
                case 1:
                    monster_name = "Ogre";
                    encounter_message = "You encounter a towering ogre. Hope you brought health potions!";
                    monster_hp = 75 + (rand() % (100-75 + 1));
                    monster_ac = 2 + (rand() % (4-2 +1));
                    break;
                case 2:
                    monster_name = "Dragon";
                    encounter_message = "You encounter a dragon the size of a modest castle. Ruination has come!";
                    monster_hp = 345 + (rand() % (500-345 + 1));
                    monster_ac = 5 + (rand() % (6-5 + 1));
                    break;
                }

                // Output monster information
                cout  << endl << encounter_message << endl
                << "The monster's maximum HP is " << monster_hp << endl
                << "The monster's armor class is " << monster_ac << endl << endl;

            display_info = false;
        }

        // Dice Roll I (Player attack)
        pc_attack_roll = 1 + (rand() % 8);
        if (pc_attack_roll > monster_ac) {
            // Dice Roll II (Damage)
            pc_attack_damage = 1 + (rand() % 20);

            // Cases for damage
            switch (pc_attack_damage) {
                case FAILURE_ROLL:
                    player_health-=1;
                    if (player_health < 0) {
                        player_health = 0;
                        gameover = true;
                    }
                    cout << PLAYER_FAILURE_MESSAGE << monster_hp << endl;
                    break;
                case CRITICAL_ROLL:
                    monster_hp-=25;
                    if (monster_hp < 0) {
                        monster_hp = 0;
                    }
                    cout << PLAYER_CRITICAL_MESSAGE << monster_hp << endl;
                    break;
                default:
                    monster_hp-=pc_attack_damage;
                    if (monster_hp < 0) {
                        monster_hp = 0;
                    }
                    cout << "The attack hits! The player damages for -" 
                        << pc_attack_damage 
                        << "HP to the monster. Monster's current HP: " 
                        << monster_hp << endl;
            }
        // Failed Attack
        } else {
            cout << PLAYER_ATTACK_FAIL << monster_hp << endl;
        }
        // Check if the monster is dead
        if (monster_hp <= 0) {
            cout << MONSTER_DEFEATED << endl;
            player_health = player_health_info;
            display_info = true;
            ++kill_streak;
            cout << endl << endl << "-----------------------------------------------------------";
            continue;
        }

        // Dice Roll I (Monster attack)
        monster_attack_roll = 1 + (rand() % 8);
        if (monster_attack_roll > armor_class) {
            // Dice Roll II (Damage)
            monster_attack_damage = 1 + (rand() % 20);

            // Cases for damage
            switch (monster_attack_damage) {
                case FAILURE_ROLL:
                    monster_hp-=1;
                    if (monster_hp < 0) {
                        monster_hp = 0;
                    }
                    cout << MONSTER_FAILURE_MESSAGE << player_health << endl;
                    break;
                case CRITICAL_ROLL:
                    player_health-=25;
                    if (player_health < 0) {
                        player_health = 0; 
                        gameover = true;
                    }
                    cout << MONSTER_CRITICAL_MESSAGE << player_health << endl;
                    break;
                default:
                    player_health-=monster_attack_damage;
                    if (player_health < 0) {
                        player_health = 0; 
                        gameover = true;
                    }
                    cout << "The attack hits! The monster damages for -" 
                        << monster_attack_damage 
                        << "HP to the monster. Playres's current HP: " 
                        << player_health << endl;
            }
        // Failed attack
        } else {
            cout << MONSTER_ATTACK_FAIL << player_health << endl;
        }
        cout << endl;
    }

    // Check if the player is dead, output kill streak
    if (player_health <= 0) {
        cout << PLAYER_DEFEATED << endl << endl;
        cout << "Monster kill streak: " << kill_streak << endl;
    }

    // Program Exit
    return EXIT_SUCCESS;
}
