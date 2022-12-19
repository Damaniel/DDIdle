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

/* Skillgen - create a DDunIdle skill/masteries file.  Note that there's 
   very little error checking/validation of any kind, so it's easily possible to
   create invalid files.  This tool is mainly just an interactive way for me
   to create a file that's in an easy-to-parse format.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SKILLGEN.H"

#define MAX_SKILLS 100
#define MAX_MASTERIES 1500
#define MAX_ASSIGNED_MASTERIES 100

short g_num_skills;
short g_num_masteries;

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
short g_num_assigned_masteries[MAX_SKILLS];
short g_assigned_mastery_ids[MAX_SKILLS][MAX_ASSIGNED_MASTERIES];

void init_assigned_mastery_ids(void) {
    int i, j;

    for(i=0;i<MAX_SKILLS;i++) {
        for(j=0;j<MAX_ASSIGNED_MASTERIES;j++) {
            g_assigned_mastery_ids[i][j] = 0;
        }
    }
}

int load_skill_file(char *filename) {
    FILE *fp;
    char buf[80];
    int i, j;

    fp = fopen(filename, "rb");
    if (fp == NULL) {
        printf("Unable to open file!\n");
        return -1;
    }

    // Read header
    buf[0]= fgetc(fp);
    buf[1] = fgetc(fp);
    if(buf[0] != 'D' || buf[1] != 'D') {
        printf("Not a valid data file!\n");
        return -2;
    }
    
    // Skip version info for now - there's only one version at the moment
    fgetc(fp);
    fgetc(fp);

    // Get skill count, mastery count, and pull in the padding just to advance
    // the file pointer
    fread(&g_num_skills, sizeof(short), 1, fp);
    fread(&g_num_masteries, sizeof(short), 1, fp);
    fread(buf, sizeof(char), 58, fp);

    printf("Number of skills: %d\n", g_num_skills);
    printf("Number of masteries: %d\n", g_num_masteries);

    // Read skill info
    for(i=0;i<g_num_skills; i++) {
        fread(&buf, sizeof(char), 2, fp);        
        fread(&(g_skill_list[i].s.name), sizeof(char), 32, fp);
        fread(&(g_num_assigned_masteries[i]), sizeof(short), 1, fp);
        fread(buf, sizeof(char), 16, fp);
        for(j=0; j<g_num_assigned_masteries[i]; j++) {
            fread(&g_assigned_mastery_ids[i][j], sizeof(short), 1, fp);
        }
        g_skill_list[i].is_set = 1;
    }

    // Read mastery info
    for(i=0; i<g_num_masteries; i++) {
        fread(&buf, sizeof(char), 2, fp);
        fread(&(g_mastery_list[i].m.name), sizeof(char), 32, fp);
        fread(&(g_mastery_list[i].m.minimum_skill_level), sizeof(char), 1, fp);
        fread(&(g_mastery_list[i].m.execution_time), sizeof(short), 1, fp);
        fread(&(g_mastery_list[i].m.skill_exp), sizeof(short), 1, fp);
        fread(&(g_mastery_list[i].m.num_prerequisites), sizeof(short), 1, fp);
        printf("Number of prerequisites: %d\n", g_mastery_list[i].m.num_prerequisites);
        for (j=0; j < g_mastery_list[i].m.num_prerequisites; j++) {
            fread(&(g_mastery_list[i].m.prerequisites[j]), sizeof(short), 1, fp);
            fread(&(g_mastery_list[i].m.prerequisite_quantities[j]), sizeof(char), 1, fp);
            //printf("%d  %d\n", g_mastery_list[i].m.prerequisites[j], g_mastery_list[i].m.prerequisite_quantities[j]);
        }
        fread(buf, sizeof(char), 32, fp);
        g_mastery_list[i].is_set = 1;
    }

    printf("\nFile loaded.\n");
    return 0;
}

int save_skill_file(char *filename) {
    FILE *fp;
    int i,j; 
    unsigned short cur_skill_id, cur_mastery_id;
    int name_len;

    // Write header
    fp = fopen(filename, "wb");
    if (fp == NULL) {
        printf("Unable to save file!\n");
        return -1;
    }

    fprintf(fp, "DD");
    fputc(0x00, fp);
    fputc(0x01, fp);
    fwrite(&g_num_skills, sizeof(short), 1, fp);
    fwrite(&g_num_masteries, sizeof(short), 1, fp);
    for(i=0;i<58;i++) {
        fputc(0, fp);
    }
    
    cur_skill_id = 0;
    cur_mastery_id = 0;
    // For each skill
    //  - Write skill header
    for (i=0; i< MAX_SKILLS; i++) {
        if(g_skill_list[i].is_set) { 
            // Skill ID
            fwrite(&cur_skill_id, sizeof(short), 1, fp);
            cur_skill_id++;
            // Name
            fwrite(&(g_skill_list[i].s.name), sizeof(char), 32, fp);
            // Number of masteries
            fwrite(&(g_num_assigned_masteries[i]), sizeof(short), 1, fp);
            // Padding
            for(j=0;j<16;j++) {
                fputc(0, fp);
            }
            // Mastery IDs
            for (j=0; j< g_num_assigned_masteries[i]; j++) {
                fwrite(&(g_assigned_mastery_ids[i][j]), sizeof(short), 1, fp); 
            }
        }
    }

    // Write out the masteries
    for (i=0; i < MAX_MASTERIES; i++ ) {
        if (g_mastery_list[i].is_set) { 
            // mastery ID
            fwrite(&cur_mastery_id, sizeof(short), 1, fp);
            cur_mastery_id++;
            // name
            fwrite(&(g_mastery_list[i].m.name), sizeof(char), 32, fp);
            // minimum skill level
            fwrite(&(g_mastery_list[i].m.minimum_skill_level), sizeof(char), 1, fp);
            // execution time
            fwrite(&(g_mastery_list[i].m.execution_time), sizeof(short), 1, fp);
            // Skill exp gained
            fwrite(&(g_mastery_list[i].m.skill_exp), sizeof(short), 1, fp);
            // prerequisite count
            fwrite(&(g_mastery_list[i].m.num_prerequisites), sizeof(short), 1, fp);
            // Prerequisite details (item IDs, counts)
            for(j=0; j< g_mastery_list[i].m.num_prerequisites; j++) {
                printf("%d %d\n", g_mastery_list[i].m.prerequisites[j], g_mastery_list[i].m.prerequisite_quantities[j]);
                fwrite(&(g_mastery_list[i].m.prerequisites[j]), sizeof(short), 1, fp);
                fwrite(&(g_mastery_list[i].m.prerequisite_quantities[j]), sizeof(char), 1, fp);
            }
            // Padding
            for(j=0; j<32; j++) {
                fputc(0, fp);
            }
        }
    }

    fclose(fp);
    printf("File saved.\n");
    g_cur_state = MAIN_MENU;
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
        if (counter % 15 == 0) {
            printf("\nPress ENTER for next page: ");
            getc(stdin);
            printf("\n");
        }        
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
        if (counter % 15 == 0) {
            printf("\nPress ENTER for next page: ");
            fgets(buf, 10, stdin);
            printf("\n");
        }        
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
                g_num_skills--;
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

    // Clear string
    for(i=0;i<32;i++) {
        s.name[i] = 0;
    }

    printf("Enter skill name:");
    fgets(s.name, 32, stdin);
    for(i=0; i<32; i++) {
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
    g_num_skills++;
    g_cur_state = SKILL_MENU;
    return;
}

void list_masteries(void) {
    int i, j, counter;

    counter = 1;
    printf("\n");
    for(i=0; i<MAX_MASTERIES;i++) {
        if (counter % 15 == 0) {
            printf("\nPress ENTER for next page: ");
            getc(stdin);
            printf("\n");
        }
        if (g_mastery_list[i].is_set) {
            printf("%d) %s  ", counter, g_mastery_list[i].m.name);
            printf("ML: %d  ", g_mastery_list[i].m.minimum_skill_level);
            printf("ET: %d  ", g_mastery_list[i].m.execution_time);
            if (g_mastery_list[i].m.num_prerequisites > 0) {
                printf("P: Y, %d", g_mastery_list[i].m.num_prerequisites);
            }
            else {
                printf("P: N");
            }
            printf("\n");            
            counter++;
        }
    }
    if(counter == 1) {
        printf("\n-- no masteries defined yet --\n");
    }
    g_cur_state = MASTERY_MENU;
}

void add_mastery(void) {
    int first_free, i, num_masteries;
    char buf[80];
    Mastery m;

    first_free = get_first_free_mastery();
    if (first_free == -1) {
        printf("Can't add new mastery!\n");
        return;
    }

    // Clear string
    for(i=0;i<32;i++) {
        m.name[i] = 0;
    }
    printf("Enter mastery name: ");
    fgets(m.name, 32, stdin);
    for(i=0; i<32; i++) {
        if(m.name[i] == '\n') {
            m.name[i] = '\0';
        }
    }

    printf("What is the minimum skill level required to perform this (1-100)? ");
    fgets(buf, 80, stdin);
    m.minimum_skill_level = atoi(buf);

    printf("How long does one execution take (in tenths of a second)? ");
    fgets(buf, 80, stdin);
    m.execution_time = atoi(buf);

    printf("How much skill experience does this action generate? ");
    fgets(buf, 80, stdin);
    m.skill_exp = atoi(buf);

    printf("Does this mastery require any prerequisites (Y/N)?");
    fgets(buf, 80, stdin);
    if(buf[0] == 'Y' || buf[0] == 'y') {
        printf("How many (1-8)? ");
        fgets(buf, 80, stdin);
        m.num_prerequisites = atoi(buf);
        for(i=0; i< m.num_prerequisites; i++) {
            printf("Enter the item ID for prerequisite %d: ", i+1);
            fgets(buf, 80, stdin);
            m.prerequisites[i] = atoi(buf);
            printf("Enter the number of that item required: ");
            fgets(buf, 80, stdin);
            m.prerequisite_quantities[i] = atoi(buf);
        }
    }
    else {
        m.num_prerequisites = 0;
        for(i=0;i<8;i++) {
            m.prerequisites[i] = 0;
        }
    }

    m.current_exp = 0;
    m.current_level = 1;
    m.speed_multiplier = 1.0;
    m.id = first_free;
    g_mastery_list[first_free].m = m;
    g_mastery_list[first_free].is_set = 1;

    printf("Mastery added.\n");
    g_num_masteries++;
    g_cur_state = MASTERY_MENU;
    return;
}

void remove_mastery(void) {
    int i, counter, id;
    char buf[80];
    int valid_mastery_ids[MAX_MASTERIES];

    counter = 1;
    for(i=0; i<MAX_MASTERIES;i++) {
        if (counter % 15 == 0) {
            printf("\nPress ENTER for next page: ");
            getc(stdin);
            printf("\n");
        }        
        if (g_mastery_list[i].is_set) {
            printf("%d) %s\n", counter, g_mastery_list[i].m.name);
            valid_mastery_ids[counter-1] = g_mastery_list[i].m.id;
            counter++;
        }
    }
    if(counter == 1) {
        printf("\nNothing to remove.\n");
    } 
    else {
        printf("\nEnter the number of the mastery to remove:");
        fgets(buf, 80, stdin);
        id = atoi(buf);
        if(id == 0) {
            printf("\nThat's not a number!\n");
        }
        else {
            if(id >= counter) {
                printf("Invalid mastery index!\n");
            }
            else {
                g_mastery_list[valid_mastery_ids[id-1]].is_set = 0;
                g_num_masteries--;
                printf("\nMastery removed.\n");
            }
        }

    }
    g_cur_state = MASTERY_MENU;    
}

void assign_to_skill(void) {
    char buf[10];
    int i, done = 0, skill_id, mastery_id, counter;

    while(!done) {
        list_skills();
        printf("\nEnter the number of the skill to assign to: ");
        fgets(buf, 10, stdin);
        skill_id = atoi(buf);
        if(skill_id < 1 || skill_id >= MAX_SKILLS) {
            printf("Enter a valid index!\n");
        } else {
            done = 1;
        }
    }

    done = 0;
    counter = 0;
    g_num_assigned_masteries[skill_id-1] = 0;
    while(!done) {
        list_masteries();
        printf("Enter the number of the mastery to add, or 'q' to quit: ");
        fgets(buf, 10, stdin);
        if(buf[0] == 'q' || buf[0] == 'Q') {
            done = 1;
        }
        else {
            mastery_id = atoi(buf);
            if(mastery_id < 1 || mastery_id >= MAX_MASTERIES) {
                printf("Enter a valid index!\n");
            }
            else {
                g_assigned_mastery_ids[skill_id-1][counter] = mastery_id - 1;
                counter++;
            }
        }
    }

    g_num_assigned_masteries[skill_id-1] = counter;
    printf("\nMasteries: ");
    for(i=0; i< g_num_assigned_masteries[skill_id-1]; i++ ) {
        printf("%d  ", g_assigned_mastery_ids[skill_id-1][i]);
    }

    g_cur_state = MAIN_MENU;
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

    g_num_masteries = 0;
    g_num_skills = 0;

    init_assigned_mastery_ids();

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
                mastery_menu();
                break;
            case ASSIGN_TO_SKILL:
                assign_to_skill();
                break;
            case SAVE_FILE:
                save_skill_file(filename);
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
            case LIST_MASTERIES:
                list_masteries();
                break;
            case ADD_MASTERY:
                add_mastery();
                break;
            case REMOVE_MASTERY:
                remove_mastery();
                break;
        }
    }

    return 0;
}