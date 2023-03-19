
#include "../INCLUDE/DDUNIDLE.H"
#include "../INCLUDE/INVENTRY.H"

InventorySlot g_inventory[INVENTORY_SIZE];

void init_inventory() {
    int i;
    for (i=0; i < INVENTORY_SIZE; i++) { 
        init_inventory_item(i);
    }
}

void init_inventory_item(int index) {
    g_inventory[index].item_id = EMPTY_SLOT;
    g_inventory[index].quantity = 0;
}

int add_item_to_inventory(int item_id) {
    int item_index;

    printf("  - Request to add item (%s)\n", get_item_name(item_id));
    item_index = get_inventory_slot_of_item(item_id);
    if (item_index == -1) {
        item_index = get_first_free_inventory_spot();
        if (item_index == -1) {
            // Inventory is full - we can't add another item
            printf("    Can't add the item - inventory is full!\n");
            return -1;
        }
        printf("    Item doesn't yet exist in the inventory!  Adding to slot %d\n", item_index);
    }
    return add_item(item_id, item_index);
}

int add_item(int item_id, int item_index) {
    printf("  - Add item %s to inventory at slot %d...\n", get_item_name(item_id), item_index);
    if (item_id < 0 || item_id >= INVENTORY_SIZE) {
        printf("     Inventory slot is out of range!\n");
        return -1;
    }
    g_inventory[item_index].item_id = item_id;
    ++(g_inventory[item_index].quantity);
    printf("    There are now %d items in that slot\n", g_inventory[item_index].quantity);
    return 0;
}

// Gets the slot in the inventory containing the specified item, or -1 if there
// are no items of that type in the inventory
int get_inventory_slot_of_item(int item_id) {
    int i;

    for(i=0; i < INVENTORY_SIZE; i++) {
        if (g_inventory[i].item_id == item_id) {
            return i;
        }
    }
    return -1;
}

// Returns the number of free spaces in the inventory
int get_inventory_free_space(void) {
    int free_count = 0;
    int i;

    for (i=0; i < INVENTORY_SIZE; i++) {
        if (g_inventory[i].item_id == EMPTY_SLOT ) {
            free_count++;
        }
    }
    printf("  - Number of free slots is %d\n", free_count);
    return free_count;
}

// Returns the lowest index in the inventory that has nothing in it, or -1
// if the inventory is full.
int get_first_free_inventory_spot(void) {
    int i;
    
    for(i=0; i < INVENTORY_SIZE; i++ ) {
        if (g_inventory[i].item_id == EMPTY_SLOT) { 
            printf("  - First free inventory slot is %d\n", i);
            return i;
        }
    }
    printf("  - No free inventory slots!\n");
    return -1;
}
