/* Copyright 2022 Shaun Brandt

   Permission is hereby granted, free of charge, to any person obtaining a
   copy of this software and associated documentation files (the "Software"),
   to deal in the Software without restriction, including without limitation
   the rights to use, copy, modify, merge, publish, distribute, sublicense,
   and/or sell copies of the Software, and to permit persons to whom the
   Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included
   in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
   FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
   DEALINGS IN THE SOFTWARE.
 */
#include "../INCLUDE/DDUNIDLE.H"

/* The master item table.  The item IDs in here are referenced by skills and 
   materies, so it needs to be kept in sync with the SKILLS.DAT file */

// typedef enum {
//     NONE
//     MATERIAL,
//     FOOD,
//     ARTIFACT,
//     JUNK,
//     MELEE_WEAPON,
//     RANGED_WEAPON,
//     HEAD_ARMOR,
//     CHEST_ARMOR,
//     HAND_ARMOR,
//     LEG_ARMOR,
//     FOOT_ARMOR,
//     OTHER
// } ItemType;

// typedef struct {
//     int id;
//     char name[20];
//     int buy_value;
//     int sell_value;
//     ItemType it;
//     int damage;
//     int defense;
//     int bitmap_offset;    
// } Item;

// typedef struct {
//     short id;
//     char name[32];
//     int current_level;
//     unsigned int current_exp;
//     unsigned char minimum_skill_level;
//     short execution_time;
//     short skill_exp;
//     short num_prerequisites;
//     short prerequisites[8];
//     unsigned char prerequisite_quantities[8];
//     // To add (each mastery produces either a normal item or a special item)
//     // int product_item_id
//     // int special_item_id
//     unsigned int next_proc;
//     float speed_multiplier;
// } Mastery;

// typedef struct {
//     short id;
//     char name[32];
//     short num_masteries;
//     short masteries[MAX_MASTERIES_PER_SKILL];
//     int current_level;
//     unsigned int current_exp;
//     int active_mastery;
//     int is_currently_active;
//     float speed_multiplier;
// } Skill;


Mastery g_mastery_list[] = {
    {0,  "Tin",        1, 0, 1,   15,      1, 0, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, 0, 0, 0, 1.0},
    {1,  "Coal",       1, 0, 1,   18,      2, 0, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, 0, 0, 0, 1.0},
    {2,  "Zinc",       1, 0, 5,   22,      3, 0, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, 0, 0, 0, 1.0},
    {3,  "Copper",     1, 0, 10,  30,      8, 0, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, 0, 0, 0, 1.0},
    {4,  "Iron",       1, 0, 20,  45,     37, 0, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, 0, 0, 0, 1.0},
    {5,  "Marble",     1, 0, 25,  50,     54, 0, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, 0, 0, 0, 1.0},
    {6,  "Mercury",    1, 0, 25,  51,     55, 0, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, 0, 0, 0, 1.0},
    {7,  "Silver",     1, 0, 35,  68,    283, 0, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, 0, 0, 0, 1.0},
    {8,  "Gold",       1, 0, 50,  85,   1857, 0, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, 0, 0, 0, 1.0},
    {9,  "Granite",    1, 0, 60,  95,   7915, 0, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, 0, 0, 0, 1.0},
    {10, "Platinum",   1, 0, 70, 110,  14678, 0, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, 0, 0, 0, 1.0},
    {11, "Rhodium",    1, 0, 70, 112,  15307, 0, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, 0, 0, 0, 1.0},
    {12, "Indium",     1, 0, 90, 145, 145258, 0, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, 0, 0, 0, 1.0},
    {13, "Orichalcum", 1, 0, 90, 150, 165000, 0, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, 0, 0, 0, 1.0}
};

Skill g_skill_list[] = {
    {0, "Mining", 14, 
        { 0,  1,  2,  3, 4, 5, 6, 7, 8, 9, 
         10, 11, 12, 13, 0, 0, 0, 0, 0, 0,
          0 , 0,  0,  0, 0, 0, 0, 0, 0, 0,
          0,  0,  0,  0, 0, 0, 0, 0, 0, 0},
     1, 0, 0, 0, 1.0}
};

DropTable g_drop_table[] = {

};

Item g_item_list[] = {
    {0, "Empty item", 0, 0, NONE, 0, 0, 0, 0},
    // ****** Standard mastery drops ****** 
    // Logs
    {1, "Balsa log", 6, 3, MATERIAL, 0, 0, 1, 0},
    {2, "Cedar log", 16, 8, MATERIAL, 0, 0, 2, 0},
    {3, "Fir log", 32, 16, MATERIAL, 0, 0, 3, 0},
    {4, "Pine log", 60, 30, MATERIAL, 0, 0, 4, 0}, 
    {5, "Ash log", 150, 75, MATERIAL, 0, 0, 5, 0}, 
    {6, "Beech log", 400, 200, MATERIAL, 0, 0, 6, 0},
    {7, "Birch log", 1200, 600, MATERIAL, 0, 0, 7, 0},
    {8, "Oak log", 3000, 1500, MATERIAL, 0, 0, 8, 0},
    {9, "Maple log", 9000, 4500, MATERIAL, 0, 0, 9, 0},
    {10, "Ebony log", 20000, 10000, MATERIAL, 0, 0, 10, 0},
    {11, "Ancient log", 50000, 25000, MATERIAL, 0, 0, 11, 0},
    // Ores
    {12, "Tin ore", 6, 3, MATERIAL, 0, 0, 12, 0},
    {13, "Coal chunk", 16, 8, MATERIAL, 0, 0, 13, 0},
    {14, "Zinc ore", 32, 16, MATERIAL, 0, 0, 14, 0},
    {15, "Copper ore", 60, 30, MATERIAL, 0, 0, 15, 0},
    {16, "Iron ore", 150, 75, MATERIAL, 0, 0, 16, 0},
    {17, "Marble chunk", 200, 100, MATERIAL, 0, 0, 17, 0},
    {18, "Cinnabar", 350, 175, MATERIAL, 0, 0, 18, 0}, 
    {19, "Silver ore", 800, 400, MATERIAL, 0, 0, 19, 0},
    {20, "Gold ore", 2000, 1000, MATERIAL, 0, 0, 20, 0},
    {21, "Granite chunk", 4000, 2000, MATERIAL, 0, 0, 21, 0},
    {22, "Platinum ore", 8000, 4000, MATERIAL, 0, 0, 22, 0},
    {23, "Rhodium ore", 10000, 5000, MATERIAL, 0, 0, 23, 0},
    {24, "Indium ore", 20000, 10000, MATERIAL, 0, 0, 24, 0},
    {25, "Orichalcum ore", 50000, 25000, MATERIAL, 0, 0, 25, 0},
    // Fishing
    {26, "Minnow", 6, 3, MATERIAL, 0, 0, 26, 0},
    {27, "Sardine", 16, 8, MATERIAL, 0, 0, 27, 0},
    {28, "Starfish", 32, 16, MATERIAL, 0, 0, 28, 0},
    {29, "Perch", 60, 30, MATERIAL, 0, 0, 29, 0},
    {30, "Trout", 120, 60, MATERIAL, 0, 0, 30, 0},
    {31, "Salmon", 200, 100, MATERIAL, 0, 0, 31, 0},
    {32, "Bass", 500, 250, MATERIAL, 0, 0, 32, 0}, 
    {33, "Swordfish", 1200, 600, MATERIAL, 0, 0, 33, 0},
    {34, "Tuna", 2200, 1100, MATERIAL, 0, 0, 34, 0}, 
    {35, "Octopus", 3200, 1600, MATERIAL, 0, 0, 35, 0}, 
    {36, "Shark", 4800, 2400, MATERIAL, 0, 0, 36, 0}, 
    {37, "Silverfish", 7000, 3500, MATERIAL, 0, 0, 37, 0}, 
    {38, "Rockfish", 7800, 3900, MATERIAL, 0, 0, 38, 0}, 
    {39, "Goldfish", 15000, 7500, MATERIAL, 0, 0, 39, 0},
    {40, "Whale", 10000, 5000, MATERIAL, 0, 0, 40, 0},
    {41, "Sea Monster", 25000, 12500, MATERIAL, 0, 0, 41, 0},
    {42, "Ancient Bass", 50000, 25000, MATERIAL, 0, 0, 42, 0},
    // Hunting
    {43, "Squirrel meat", 6, 3, MATERIAL, 0, 0, 43, 0},
    {44, "Duck meat", 0, 0, MATERIAL, 0, 0, 44, 0}, 
    {45, "Rabbit meat", 0, 0, MATERIAL, 0, 0, 45, 0}, 
    {46, "Turkey", 0, 0, MATERIAL, 0, 0, 46, 0}, 
    {47, "Pig meat", 0, 0, MATERIAL, 0, 0, 47, 0},
    {48, "Wolf meat", 0, 0, MATERIAL, 0, 0, 48, 0}, 
    {49, "Venison", 0, 0, MATERIAL, 0, 0, 49, 0}, 
    {50, "Elk meat", 0, 0, MATERIAL, 0, 0, 50, 0}, 
    {51, "Tiger meat", 0, 0, MATERIAL, 0, 0, 51, 0}, 
    {52, "Cave lion meat", 0, 0, MATERIAL, 0, 0, 52, 0},
    {53, "Sabertooth meat", 0, 0, MATERIAL, 0, 0, 53, 0}, 
    {54, "Yeti meat", 0, 0, MATERIAL, 0, 0, 54, 0},
    {55, "Elephant meat", 0, 0, MATERIAL, 0, 0, 55, 0},
    {56, "Beast meat", 0, 0, MATERIAL, 0, 0, 56, 0},
    // Gathering
    {57, "Raspberry", 0, 0, MATERIAL, 0, 0, 57, 0},
    {58, "Blueberry", 0, 0, MATERIAL, 0, 0, 58, 0},
    {59, "Milk", 0, 0, MATERIAL, 0, 0, 59, 0},
    {60, "Huckleberry", 0, 0, MATERIAL, 0, 0, 60, 0},
    {61, "Strawberry", 0, 0, MATERIAL, 0, 0, 61, 0}, 
    {62, "Honey", 0, 0, MATERIAL, 0, 0, 62, 0}, 
    {63, "Apple", 0, 0, MATERIAL, 0, 0, 63, 0},
    {64, "Orange", 0, 0, MATERIAL, 0, 0, 64, 0}, 
    {65, "Banana", 0, 0, MATERIAL, 0, 0, 65, 0}, 
    {66, "Starfruit", 0, 0, MATERIAL, 0, 0, 66, 0},
    {67, "Dungeonberry", 0, 0, MATERIAL, 0, 0, 67, 0},
    {68, "Dragonfruit", 0, 0, MATERIAL, 0, 0, 68, 0},
    {69, "Truffle", 0, 0, MATERIAL, 0, 0, 69, 0},
    {70, "Ancient nectar", 0, 0, MATERIAL, 0, 0, 70, 0},
    // Herbalism
    {71, "Spearmint", 0, 0, MATERIAL, 0, 0, 71, 0},
    {72, "Thyme", 0, 0, MATERIAL, 0, 0, 72, 0},
    {73, "Chamomile", 0, 0, MATERIAL, 0, 0, 73, 0},
    {74, "Lavender", 0, 0, MATERIAL, 0, 0, 74, 0},
    {75, "Rose", 0, 0, MATERIAL, 0, 0, 75, 0},
    {76, "Lemongrass", 0, 0, MATERIAL, 0, 0, 76, 0},
    {77, "Sage", 0, 0, MATERIAL, 0, 0, 77, 0},
    {78, "Rosemary", 0, 0, MATERIAL, 0, 0, 78, 0},
    {79, "Catnip", 0, 0, MATERIAL, 0, 0 , 79, 0},
    {80, "Dewleaf", 0, 0, MATERIAL, 0, 0, 80, 0},
    {81, "Nettle", 0, 0, MATERIAL, 0, 0, 81, 0},
    {82, "Cavemint", 0, 0, MATERIAL, 0, 0, 82, 0},
    {83, "Silphium", 0, 0, MATERIAL, 0, 0, 83, 0},
    // Smelting
    {84, "Tin bar", 0, 0, MATERIAL, 0, 0, 84, 0},
    {85, "Zinc bar", 0, 0, MATERIAL, 0, 0, 85, 0},
    {86, "Copper bar", 0, 0, MATERIAL, 0, 0, 86, 0},
    {87, "Brass bar", 0, 0, MATERIAL, 0, 0, 87, 0},
    {88, "Bronze bar", 0, 0, MATERIAL, 0, 0, 88, 0},
    {89, "Iron bar", 0, 0, MATERIAL, 0, 0, 89, 0},
    {90, "Marble block", 0, 0, MATERIAL, 0, 0, 90, 0},
    {91, "Silver bar", 0, 0, MATERIAL, 0, 0, 91, 0}, 
    {92, "Gold bar", 0, 0, MATERIAL, 0, 0, 92, 0},
    {93, "Amalgam", 0, 0, MATERIAL, 0, 0, 93, 0},
    {94, "Steel bar", 0, 0, MATERIAL, 0, 0, 94, 0},
    {95, "Granite block", 0, 0, MATERIAL, 0, 0, 95, 0},
    {96, "Electrum bar", 0, 0, MATERIAL, 0, 0, 96, 0},
    {97, "Platinum bar", 0, 0, MATERIAL, 0, 0, 97, 0},
    {98, "Rhodium bar", 0, 0, MATERIAL, 0, 0, 98, 0},
    {99, "Indium bar", 0, 0, MATERIAL, 0, 0, 99, 0},
    {100, "Orichalcum bar", 0, 0, MATERIAL, 0, 0, 100, 0},
    {101, "Mystic metal bar", 0, 0, MATERIAL, 0, 0, 101, 0},
    // Woodworking
    {102, "Balsa inlay", 0, 0, MATERIAL, 0, 0, 102, 0},
    {103, "Balsa statue", 0, 0, OTHER, 0, 0, 103, 0},
    {104, "Cedar inlay", 0, 0, MATERIAL, 0, 0, 104, 0},
    {105, "Cedar sword", 0, 0, MELEE_WEAPON, 0, 0, 105, 0},
    {106, "Cedar bow", 0, 0, RANGED_WEAPON, 0, 0, 106, 0},
    {107, "Cedar helmet", 0, 0, HEAD_ARMOR, 0, 0, 107, 0},
    {108, "Cedar armor", 0, 0, CHEST_ARMOR, 0, 0, 108, 0},
    {109, "Cedar gauntlets", 0, 0, HAND_ARMOR, 0, 0, 109, 0},
    {110, "Cedar legguards", 0, 0, LEG_ARMOR, 0, 0, 110, 0},
    {111, "Cedar boots", 0, 0, FOOT_ARMOR, 0, 0, 111, 0},
    {112, "Fir inlay", 0, 0, MATERIAL, 0, 0, 112, 0},
    {113, "Fir sword", 0, 0, MELEE_WEAPON, 0, 0, 113, 0},
    {114, "Fir bow", 0, 0, RANGED_WEAPON, 0, 0, 114, 0},
    {115, "Fir helmet", 0, 0, HEAD_ARMOR, 0, 0, 115, 0},
    {116, "Fir armor", 0, 0, CHEST_ARMOR, 0, 0, 116, 0},
    {117, "Fir gauntlets", 0, 0, HAND_ARMOR, 0, 0, 117, 0},
    {118, "Fir legguards", 0, 0, LEG_ARMOR, 0, 0, 118, 0},
    {119, "Fir boots", 0, 0, FOOT_ARMOR, 0, 0, 119, 0},

};