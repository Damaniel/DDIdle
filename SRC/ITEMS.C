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

Item g_item_list[] = {
    {0, "Empty item", 0, 0, NONE, 0, 0, 0},
    // ****** Standard mastery drops ****** 
    // Logs
    {1, "Balsa log", 6, 3, MATERIAL, 0, 0, 1},
    {2, "Cedar log", 16, 8, MATERIAL, 0, 0, 2},
    {3, "Fir log", 32, 16, MATERIAL, 0, 0, 3},
    {4, "Pine log", 60, 30, MATERIAL, 0, 0, 4}, 
    {5, "Ash log", 150, 75, MATERIAL, 0, 0, 5}, 
    {6, "Beech log", 400, 200, MATERIAL, 0, 0, 6},
    {7, "Birch log", 1200, 600, MATERIAL, 0, 0, 7},
    {8, "Oak log", 3000, 1500, MATERIAL, 0, 0, 8},
    {9, "Maple log", 9000, 4500, MATERIAL, 0, 0, 9},
    {10, "Ebony log", 20000, 10000, MATERIAL, 0, 0, 10},
    {11, "Ancient log", 50000, 25000, MATERIAL, 0, 0, 11},
    // Ores
    {12, "Tin ore", 6, 3, MATERIAL, 0, 0, 12},
    {13, "Coal chunk", 16, 8, MATERIAL, 0, 0, 13},
    {14, "Zinc ore", 32, 16, MATERIAL, 0, 0, 14},
    {15, "Copper ore", 60, 30, MATERIAL, 0, 0, 15},
    {16, "Iron ore", 150, 75, MATERIAL, 0, 0, 16},
    {17, "Marble chunk", 200, 100, MATERIAL, 0, 0, 17},
    {18, "Cinnabar", 350, 175, MATERIAL, 0, 0, 18}, 
    {19, "Silver ore", 800, 400, MATERIAL, 0, 0, 19},
    {20, "Gold ore", 2000, 1000, MATERIAL, 0, 0, 20},
    {21, "Granite chunk", 4000, 2000, MATERIAL, 0, 0, 21},
    {22, "Platinum ore", 8000, 4000, MATERIAL, 0, 0, 22},
    {23, "Rhodium ore", 10000, 5000, MATERIAL, 0, 0, 23},
    {24, "Indium ore", 20000, 10000, MATERIAL, 0, 0, 24},
    {25, "Orichalcum ore", 50000, 25000, MATERIAL, 0, 0, 25},
    // Fishing
    {26, "Minnow", 6, 3, MATERIAL, 0, 0, 26},
    {27, "Sardine", 16, 8, MATERIAL, 0, 0, 27},
    {28, "Starfish", 32, 16, MATERIAL, 0, 0, 28},
    {29, "Perch", 60, 30, MATERIAL, 0, 0, 29},
    {30, "Trout", 120, 60, MATERIAL, 0, 0, 30},
    {31, "Salmon", 200, 100, MATERIAL, 0, 0, 31},
    {32, "Bass", 500, 250, MATERIAL, 0, 0, 32}, 
    {33, "Swordfish", 1200, 600, MATERIAL, 0, 0, 33},
    {34, "Tuna", 2200, 1100, MATERIAL, 0, 0, 34}, 
    {35, "Octopus", 3200, 1600, MATERIAL, 0, 0, 35}, 
    {36, "Shark", 4800, 2400, MATERIAL, 0, 0, 36}, 
    {37, "Silverfish", 7000, 3500, MATERIAL, 0, 0, 37}, 
    {38, "Rockfish", 7800, 3900, MATERIAL, 0, 0, 38}, 
    {39, "Goldfish", 15000, 7500, MATERIAL, 0, 0, 39},
    {40, "Whale", 10000, 5000, MATERIAL, 0, 0, 40},
    {41, "Sea Monster", 25000, 12500, MATERIAL, 0, 0, 41},
    {42, "Ancient Bass", 50000, 25000, MATERIAL, 0, 0, 42},
    // Hunting
    {43, "Squirrel meat", 6, 3, MATERIAL, 0, 0, 43},
    {44, "Duck meat", 0, 0, MATERIAL, 0, 0, 44}, 
    {45, "Rabbit meat", 0, 0, MATERIAL, 0, 0, 45}, 
    {46, "Turkey", 0, 0, MATERIAL, 0, 0, 46}, 
    {47, "Pig meat", 0, 0, MATERIAL, 0, 0, 47},
    {48, "Wolf meat", 0, 0, MATERIAL, 0, 0, 48}, 
    {49, "Venison", 0, 0, MATERIAL, 0, 0, 49}, 
    {50, "Elk meat", 0, 0, MATERIAL, 0, 0, 50}, 
    {51, "Tiger meat", 0, 0, MATERIAL, 0, 0, 51}, 
    {52, "Cave lion meat", 0, 0, MATERIAL, 0, 0, 52},
    {53, "Sabertooth meat", 0, 0, MATERIAL, 0, 0, 53}, 
    {54, "Yeti meat", 0, 0, MATERIAL, 0, 0, 54},
    {55, "Elephant meat", 0, 0, MATERIAL, 0, 0, 55},
    {56, "Beast meat", 0, 0, MATERIAL, 0, 0, 56},
    // Gathering
    {57, "Raspberry", 0, 0, MATERIAL, 0, 0, 57},
    {58, "Blueberry", 0, 0, MATERIAL, 0, 0, 58},
    {59, "Milk", 0, 0, MATERIAL, 0, 0, 59},
    {60, "Huckleberry", 0, 0, MATERIAL, 0, 0, 60},
    {61, "Strawberry", 0, 0, MATERIAL, 0, 0, 61}, 
    {62, "Honey", 0, 0, MATERIAL, 0, 0, 62}, 
    {63, "Apple", 0, 0, MATERIAL, 0, 0, 63},
    {64, "Orange", 0, 0, MATERIAL, 0, 0, 64}, 
    {65, "Banana", 0, 0, MATERIAL, 0, 0, 65}, 
    {66, "Starfruit", 0, 0, MATERIAL, 0, 0, 66},
    {67, "Dungeonberry", 0, 0, MATERIAL, 0, 0, 67},
    {68, "Dragonfruit", 0, 0, MATERIAL, 0, 0, 68},
    {69, "Truffle", 0, 0, MATERIAL, 0, 0, 69},
    {70, "Ancient nectar", 0, 0, MATERIAL, 0, 0, 70},
    // Herbalism
    {71, "Spearmint", 0, 0, MATERIAL, 0, 0, 71},
    {72, "Thyme", 0, 0, MATERIAL, 0, 0, 72},
    {73, "Chamomile", 0, 0, MATERIAL, 0, 0, 73},
    {74, "Lavender", 0, 0, MATERIAL, 0, 0, 74},
    {75, "Rose", 0, 0, MATERIAL, 0, 0, 75},
    {76, "Lemongrass", 0, 0, MATERIAL, 0, 0, 76},
    {77, "Sage", 0, 0, MATERIAL, 0, 0, 77},
    {78, "Rosemary", 0, 0, MATERIAL, 0, 0, 78},
    {79, "Catnip", 0, 0, MATERIAL, 0, 0 , 79},
    {80, "Dewleaf", 0, 0, MATERIAL, 0, 0, 80},
    {81, "Nettle", 0, 0, MATERIAL, 0, 0, 81},
    {82, "Cavemint", 0, 0, MATERIAL, 0, 0, 82},
    {83, "Silphium", 0, 0, MATERIAL, 0, 0, 83}
    // ****** Special mastery drops ******

};