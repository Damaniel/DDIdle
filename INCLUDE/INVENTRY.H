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
#ifndef __INVENTRY_H__
#define __INVENTRY_H__

#include "ddunidle.h"

extern InventorySlot g_inventory[INVENTORY_SIZE];

// Adds an item to the inventory (either by stacking it with an existing item of that
// type in an inventory slot, or in an empty slot of no item of the kind exists)
int add_item_to_inventory(int item_id);

// Puts the specified item in the specified slot
int add_item(int item_id, int item_index);

// Clears the entire inventory
void init_inventory(void);

// Clears a single inventory item
void init_inventory_item(int index);

// Gets the slot in the inventory containing the specified item, or -1 if there
// are no items of that type in the inventory
int get_inventory_slot_of_item(int item_id);

// Returns the number of free spaces in the inventory
int get_inventory_free_space(void);

// Returns the lowest index in the inventory that has nothing in it, or -1
// if the inventory is full.
int get_first_free_inventory_spot();

#endif