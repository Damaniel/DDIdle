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

int load_skills_datafile(void) {

    FILE *fp;
    int skill_count, mastery_count, char_count;
    int i, j, k;
    char buf[80];

    fp = fopen("skills.dat", "r");
    if (fp == NULL) {
        return -1;
    }

    fscanf(fp, "%d\n", &skill_count);

    g_skill_list = malloc(skill_count * sizeof(Skill));
    if (g_skill_list == NULL) {
        printf("No memory to allocate skills!\n");
        fclose(fp);
        return -1;
    }

    for(i=0; i<skill_count; i++) {
        // Set skill defaults
        g_skill_list[i].current_exp = 0;
        g_skill_list[i].current_level = 1;
        g_skill_list[i].is_currently_active = 0;
        g_skill_list[i].speed_multiplier = 1.0;
        g_skill_list[i].active_mastery = 0;
        // read in the rest
        fscanf(fp, "%d\n", &char_count);
        fgets(buf, 80, fp);
        strncpy(g_skill_list[i].name, buf, char_count);
        g_skill_list[i].name[char_count] = '\0';
        fscanf(fp, "%d\n", &mastery_count);
        g_skill_list[i].masteries = malloc(mastery_count * sizeof(Mastery));
        printf("Skill: %s\n", g_skill_list[i].name);
        printf("-----------------------\n");
        if (g_skill_list[i].masteries == NULL) {
            printf("No memory to allocate masteries!\n");
            fclose(fp);
            return -1;
        } 
        for(j=0; j<mastery_count; j++) {
            // Set mastery defaults
            g_skill_list[i].masteries[j].current_exp = 0;
            g_skill_list[i].masteries[j].current_level = 1;
            g_skill_list[i].masteries[j].speed_multiplier = 1.0;
            // read in the rest
            fscanf(fp, "%d\n", &char_count);
            fgets(buf, 80, fp);
            strncpy(g_skill_list[i].masteries[j].name, buf, char_count);
            g_skill_list[i].masteries[j].name[char_count] = '\0';            
            fscanf(fp, "%d\n", &(g_skill_list[i].masteries[j].minimum_skill_level));
            fscanf(fp, "%d\n", &(g_skill_list[i].masteries[j].execution_time));
            fscanf(fp, "%d\n", &(g_skill_list[i].masteries[j].num_prerequisites));
            if(g_skill_list[i].masteries[j].num_prerequisites > 0) {
                for(k=0; k < g_skill_list[i].masteries[j].num_prerequisites; k++) {
                    fscanf(fp, "%d\n", &(g_skill_list[i].masteries[j].prerequisites[k]));
                }
            }
            printf("Mastery name: %s\n", g_skill_list[i].masteries[j].name);
            printf(" - Minimum skill level: %d\n", g_skill_list[i].masteries[j].minimum_skill_level);
            printf(" - Execution time: %d ticks\n", g_skill_list[i].masteries[j].execution_time);
            printf(" - Number of item prerequisites: %d\n", g_skill_list[i].masteries[j].num_prerequisites);
            if( g_skill_list[i].masteries[j].num_prerequisites > 0) {
                printf( " - Item IDs of prerequisites: ");
                for (k = 0; k < g_skill_list[i].masteries[j].num_prerequisites; k++) {
                    printf("%d ", g_skill_list[i].masteries[j].prerequisites[k]);
                }
                printf("\n");
            }
        }

    }
    fclose(fp);
    return 0;
}

