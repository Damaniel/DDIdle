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

#include "ddunidle.h"

#define INVENTORY_SIZE 128          // up to 128 items in the player's inventory

typedef enum {
    MATERIAL,
    MELEE_WEAPON,
    RANGED_WEAPON,
    HEAD_ARMOR,
    CHEST_ARMOR,
    HAND_ARMOR,
    LEG_ARMOR,
    FOOT_ARMOR
} ItemType;

typedef struct {
    char name[20];
    int buy_value;
    int sell_value;
    ItemType it;
    int damage;
    int defense;
    int bitmap_offset;    
} Item;

typedef struct {
    short id;
    char name[32];
    int current_level;
    int current_exp;
    unsigned char minimum_skill_level;
    short execution_time;
    short num_prerequisites;
    short prerequisites[8];
    unsigned char prerequisite_quantities[8];
    unsigned int next_proc;
    float speed_multiplier;
} Mastery;


typedef struct {
    short id;
    char name[32];
    Mastery *masteries;
    int current_level;
    int current_exp;
    int active_mastery;
    int is_currently_active;
    float speed_multiplier;
} Skill;


typedef struct {
    int item_id;
    int quantity;
} InventorySlot;



#endif