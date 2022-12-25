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
#ifndef __STRUCTS_H__
#define __STRUCTS_H__

#include "DDUNIDLE.H"

// Notes on cumulative memory usage
//
// inventory - 128 x 8 = 1k
// Drop table - 50 * ((8 * 20) + 12) = 8.6k;
// item list - ~1000 * 64 = 64k
// Skill list - 20 * 140 = 2.8k
// Mastery list - (<skills>*<skills/mastery> * 85)
//   Roughly (20 * 15(avg) * 85) = 25.5k
//
// Estimated list size (so far): ~102k
// The goal is to keep all lists below 512k in combined size.

#define INVENTORY_SIZE 128          // up to 128 items in the player's inventory

// Information about the skills and masteries data.
#define SKILLS_DATA_FILE   "SKILLS.DAT"
#define MAX_SKILLS    20
#define MAX_MASTERIES_PER_SKILL   40
#define MAX_DROP_TABLE_ITEMS     20
#define MAX_DROP_TABLES          50

typedef enum {
    NONE,
    MATERIAL,
    FOOD,
    ARTIFACT_CONTAINER,
    ARTIFACT,
    JUNK,
    MELEE_WEAPON,
    RANGED_WEAPON,
    HEAD_ARMOR,
    CHEST_ARMOR,
    HAND_ARMOR,
    LEG_ARMOR,
    FOOT_ARMOR,
    OTHER
} ItemType;

typedef struct {
    int item_id;
    int odds;
} DropTableItem;

typedef struct {
    int item_id;
    int cumulative_odds;
    int num_drop_table_items;
    DropTableItem items[MAX_DROP_TABLE_ITEMS];
} DropTable;

typedef struct {
    int id;
    char name[32];
    int buy_value;
    int sell_value;
    ItemType it;
    int damage;
    int defense;
    int bitmap_offset; 
    int artifact_table_id;   // for artifacts, which table to reference
} Item;

typedef struct {
    short id;
    char name[32];
    int current_level;
    unsigned int current_exp;
    unsigned char minimum_skill_level;
    short execution_time;
    unsigned int skill_exp;
    short num_prerequisites;
    short prerequisites[8];
    unsigned char prerequisite_quantities[8];
    // each mastery produces either a normal item or a special item
    int product_item_id;
    int special_item_id;
    unsigned int next_proc;
    float speed_multiplier;
} Mastery;


typedef struct {
    short id;
    char name[32];
    short num_masteries;
    short masteries[MAX_MASTERIES_PER_SKILL];
    int current_level;
    unsigned int current_exp;
    int active_mastery;
    int is_currently_active;
    float speed_multiplier;
} Skill;


typedef struct {
    int item_id;
    int quantity;
} InventorySlot;

#endif

