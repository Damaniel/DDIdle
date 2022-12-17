#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SKILLGEN.H"

#define MAX_SKILLS 100
#define MAX_MASTERIES 1500

int g_num_skills;
int g_num_masteries;

typedef struct {
    Skill s;
    int is_set;
} SkillListItem;

typedef struct {
    Mastery m;
    int is_set;
} MasteryListItem;

typedef enum {
    MAIN_MENU,
    SKILL_MENU,
    ASSIGN_TO_SKILL,
    SAVE_FILE,
    MASTERY_MENU,
    LIST_SKILLS,
    ADD_SKILL,
    REMOVE_SKILL,
    LIST_MASTERIES,
    ADD_MASTERY,
    REMOVE_MASTERY
} OptionState;

int g_exit;
OptionState g_cur_state;
SkillListItem g_skill_list[MAX_SKILLS];
MasteryListItem g_mastery_list[MAX_MASTERIES];

int load_skill_file(char *filename) {
    return 0;
}

int save_skill_file(char *filename) {

}

int get_first_free_skill() {
    int i;
    for(i=0; i<MAX_SKILLS;i++) {
        if (!g_skill_list[i].is_set) {
            return i;
        }
    }
    printf("Skill list is full!\n");
    return -1;
}

int get_first_free_mastery() {
    int i;
    for(i=0; i<MAX_MASTERIES;i++) {
        if (!g_mastery_list[i].is_set) {
            return i;
        }
    }
    printf("Mastery list is full!\n");
    return -1;
}

void list_skills(void) {
    int i, counter;

    counter = 1;
    printf("\n");
    for(i=0; i<MAX_SKILLS;i++) {
        if (g_skill_list[i].is_set) {
            printf("%d) %s\n", counter, g_skill_list[i].s.name);
            counter++;
        }
    }
    if(counter == 1) {
        printf("-- no skills defined yet --\n");
    }
    g_cur_state = SKILL_MENU;
    return;
}

void remove_skill(void) {
    int i, counter, id;
    char buf[80];
    int valid_skill_ids[MAX_SKILLS];

    counter = 1;
    for(i=0; i<MAX_SKILLS;i++) {
        if (g_skill_list[i].is_set) {
            printf("%d) %s\n", counter, g_skill_list[i].s.name);            
            valid_skill_ids[counter-1] = g_skill_list[i].s.id;
            counter++;
        }
    }
    if(counter == 1) {
        printf("\nNothing to remove.\n");
    } 
    else {
        printf("\nEnter the number of the skill to remove:");
        fgets(buf, 80, stdin);
        id = atoi(buf);
        if(id == 0) {
            printf("\nThat's not a number!\n");
        }
        else {
            if(id >= counter) {
                printf("Invalid skill index!\n");
            }
            else {
                g_skill_list[valid_skill_ids[id-1]].is_set = 0;
                printf("\nSkill removed.\n");
            }
        }

    }
    g_cur_state = SKILL_MENU;
}

void add_skill(void) {
    int first_free, i;
    Skill s;

    first_free = get_first_free_skill();
    if (first_free == -1) {
        printf("Can't add new skill!\n");
        return;
    }

    printf("Enter skill name:");
    fgets(s.name, 20, stdin);
    for(i=0; i<20; i++) {
        if(s.name[i] == '\n') {
            s.name[i] = '\0';
        }
    }
    s.current_exp = 0;
    s.current_level = 1;
    s.speed_multiplier = 1.0;
    s.id = first_free;
    g_skill_list[first_free].s = s;
    g_skill_list[first_free].is_set = 1;

    printf("Skill added.\n");
    g_cur_state = SKILL_MENU;
    return;
}

void main_menu(void) {
    char buf[80];

    printf("\nMain menu:\n");
    printf("---------\n");
    printf("1) Skill mode\n");
    printf("2) Mastery mode\n");
    printf("3) Assign masteries to skill\n");
    printf("4) Save file\n");
    printf("------------------\n");
    printf("q) Quit\n");
    printf("Choose an option and press Enter: ");

    fgets(buf, 80, stdin);
    switch (buf[0]) {
        case '1':
            g_cur_state = SKILL_MENU;
            break;
        case '2':
            g_cur_state = MASTERY_MENU;
            break;
        case '3':
            g_cur_state = ASSIGN_TO_SKILL;
            break;
        case '4':
            g_cur_state = SAVE_FILE;
            break;
        case 'q':
        case 'Q':
            g_exit = 1;
            break;
        default:
            printf("Choose an option and press Enter: ");
            fgets(buf, 80, stdin);
            break;
    }
}

void skill_menu() {
    char buf[80];

    printf("\nSkill menu:\n");
    printf("---------\n");
    printf("1) List skills\n");
    printf("2) Add skill\n");
    printf("3) Remove skill\n");
    printf("------------------\n");
    printf("b) Back to main menu\n");
    printf("Choose an option and press Enter: ");

    fgets(buf, 80, stdin);
    switch (buf[0]) {
        case '1':
            g_cur_state = LIST_SKILLS;
            break;
        case '2':
            g_cur_state = ADD_SKILL;
            break;
        case '3':
            g_cur_state = REMOVE_SKILL;
            break;
        case 'b':
        case 'B':
            g_cur_state = MAIN_MENU;
            break;
        default:
            printf("Choose an option and press Enter: ");
            fgets(buf, 80, stdin);
            break;
    }
}

int mastery_menu() {
    char buf[80];
    printf("\nMastery menu:\n");
    printf("---------\n");
    printf("1) List masteries\n");
    printf("2) Add mastery\n");
    printf("3) Remove mastery\n");
    printf("------------------\n");
    printf("b) Back to main menu\n");
    printf("Choose an option and press Enter: ");

    fgets(buf, 80, stdin);
    switch (buf[0]) {
        case '1':
            g_cur_state = LIST_MASTERIES;
            break;
        case '2':
            g_cur_state = ADD_MASTERY;
            break;
        case '3':
            g_cur_state = REMOVE_MASTERY;
            break;
        case 'b':
        case 'B':
            g_cur_state = MAIN_MENU;
            break;
        default:
            printf("Choose an option and press Enter: ");
            fgets(buf, 80, stdin);
            break;
    }
}

int main(int argc, char **argv) {
    char *filename;
    int result, create_new = 0;
    char buf[80];
    FILE *fp;

    if(argc != 2) {
        printf("Usage: skillgen <name of skill file>\n");
        return 0;
    }

    filename = argv[1];

    // Attempt to open file.  If open fails, ask if the user wants to make
    // the file
    fp = fopen(filename, "rb");

    if (fp == NULL) {
        printf("File doesn't exist.  Create this file? (y/n)");
        fgets(buf, 80, stdin);
        if (buf[0] == 'n' || buf[0] == 'N') {
            printf("Exiting...\n");
            exit(1);
        }
        create_new = 1;
    }

    // If the file exists, attempt to load it
    if (!create_new) {
        result = load_skill_file(filename);
        if (result != 0) {
            printf("The file couldn't be opened.  Is it valid?\n");
            return 1;
        }
    }

    g_exit = 0;
    while (!g_exit) {
        switch (g_cur_state) {
            case MAIN_MENU:
                main_menu();
                break;
            case SKILL_MENU:
                skill_menu();
                break;
            case MASTERY_MENU:
                printf("To do\n");
                g_cur_state = MAIN_MENU;
                break;
            case SAVE_FILE:
                printf("To do\n");
                g_cur_state = MAIN_MENU;
                break;
            case LIST_SKILLS:
                list_skills();
                break;
            case ADD_SKILL:
                add_skill();
                break;
            case REMOVE_SKILL:
                remove_skill();
                break;
        }
    }

    return 0;
}