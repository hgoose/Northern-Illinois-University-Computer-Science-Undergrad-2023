#include <iostream>
#include <cstdlib>

const int SEED = 14, CRITICAL_ROLL = 20, FAILURE_ROLL = 1;

int main() {
    srand(SEED);

    int player_health = 50 + rand() % 101, armor_class = 1 + rand() % 4, kill_streak = 0;
    bool gameover = false;

    std::cout << "The player's maximum HP is " << player_health << "\nThe player's armor class is " << armor_class << std::endl;

    while (!gameover) {
        const char* monster_names[] = {"Goblin", "Ogre", "Dragon"};
        const char* encounter_messages[] = {
            "You encounter a meager goblin. This should be easy enough!",
            "You encounter a towering ogre. Hope you brought health potions!",
            "You encounter a dragon the size of a modest castle. Ruination has come!"
        };
        int monster_hp_limits[][2] = {{30, 45}, {75, 100}, {345, 500}};
        int monster_ac_limits[][2] = {{1, 2}, {2, 4}, {5, 6}};

        int monster_type = rand() % 3;
        int monster_hp = monster_hp_limits[monster_type][0] + rand() % (monster_hp_limits[monster_type][1] - monster_hp_limits[monster_type][0] + 1);
        int monster_ac = monster_ac_limits[monster_type][0] + rand() % (monster_ac_limits[monster_type][1] - monster_ac_limits[monster_type][0] + 1);

        std::cout << "\n" << encounter_messages[monster_type] << "\nThe monster's maximum HP is " << monster_hp << "\nThe monster's armor class is " << monster_ac << std::endl;

        while (monster_hp > 0 && player_health > 0) {
            int pc_attack_roll = 1 + rand() % 8, pc_attack_damage = 1 + rand() % 20;
            if (pc_attack_roll > monster_ac) {
                if (pc_attack_damage == FAILURE_ROLL) {
                    player_health--;
                    std::cout << "Critical failure! Player loses 1 HP. Monster's current HP: " << monster_hp << std::endl;
                } else if (pc_attack_damage == CRITICAL_ROLL) {
                    monster_hp -= 25;
                    std::cout << "Natural 20! Player deals 25 damage. Monster's current HP: " << monster_hp << std::endl;
                } else {
                    monster_hp -= pc_attack_damage;
                    std::cout << "Player damages for " << pc_attack_damage << " HP. Monster's current HP: " << monster_hp << std::endl;
                }
            } else {
                std::cout << "Player's attack fails. Monster's current HP: " << monster_hp << std::endl;
            }

            if (monster_hp <= 0) break;

            int monster_attack_roll = 1 + rand() % 8, monster_attack_damage = 1 + rand() % 20;
            if (monster_attack_roll > armor_class) {
                if (monster_attack_damage == FAILURE_ROLL) {
                    monster_hp--;
                    std::cout << "Monster's critical failure! Monster loses 1 HP. Player's current HP: " << player_health << std::endl;
                } else if (monster_attack_damage == CRITICAL_ROLL) {
                    player_health -= 25;
                    std::cout << "Monster's natural 20! Player loses 25 HP. Player's current HP: " << player_health << std::endl;
                } else {
                    player_health -= monster_attack_damage;
                    std::cout << "Monster damages for " << monster_attack_damage << " HP. Player's current HP: " << player_health << std::endl;
                }
            } else {
                std::cout << "Monster's attack fails. Player's current HP: " << player_health << std::endl;
            }
        }

        if (player_health <= 0) {
            gameover = true;
            std::cout << "Player is defeated. Monster kill streak: " << kill_streak << std::endl;
        } else {
            kill_streak++;
            player_health = 50 + rand() % 101;
            std::cout << "Monster is defeated. Player's HP restored to " << player_health << std::endl;
        }
    }

   return 0;
}
