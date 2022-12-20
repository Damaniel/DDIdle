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
    char buf[80];
    int i, j;

    fp = fopen(SKILLS_DATA_FILE, "rb");
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

    g_skill_list = malloc(g_num_skills * sizeof(Skill));
    if(g_skill_list == NULL) {
        printf("Unable to allocate skill memory!\n");
        return -1;
    }
    
    g_mastery_list = malloc(g_num_masteries * sizeof(Mastery));
    if (g_mastery_list == NULL) {
        printf("Unable to allocate mastery memory!\n");
        return -1;
    }

    // Read skill info
    printf("Processing skills...\n");
    for(i=0;i<g_num_skills; i++) {
        fread(buf, sizeof(char), 2, fp);        
        fread(&(g_skill_list[i].name), sizeof(char), 32, fp);
        fread(&(g_skill_list[i].num_masteries), sizeof(short), 1, fp);
        fread(buf, sizeof(char), 16, fp);
        for(j=0; j<g_skill_list[i].num_masteries; j++) {
            fread(&(g_skill_list[i].masteries[j]), sizeof(short), 1, fp);
        }
        // Init the rest of the skill data (it will eventually be loaded from
        // a progress file)
        g_skill_list[i].active_mastery = 0;
        g_skill_list[i].current_exp = 0;
        g_skill_list[i].current_level = 1;
        g_skill_list[i].speed_multiplier = 1.0;
    }

    // Read mastery info
    printf("Processing masteries...\n");
    for(i=0; i<g_num_masteries; i++) {
        fread(buf, sizeof(char), 2, fp);
        fread(&(g_mastery_list[i].name), sizeof(char), 32, fp);
        fread(&(g_mastery_list[i].minimum_skill_level), sizeof(char), 1, fp);
        fread(&(g_mastery_list[i].execution_time), sizeof(short), 1, fp);
        fread(&(g_mastery_list[i].skill_exp), sizeof(short), 1, fp);
        fread(&(g_mastery_list[i].num_prerequisites), sizeof(short), 1, fp);
        for (j=0; j < g_mastery_list[i].num_prerequisites; j++) {
            fread(&(g_mastery_list[i].prerequisites[j]), sizeof(short), 1, fp);
            fread(&(g_mastery_list[i].prerequisite_quantities[j]), sizeof(char), 1, fp);
        }
        fread(buf, sizeof(char), 32, fp);
        // Init the rest of ths skill data (it will eventually be loaded from
        // a progress file)
        g_mastery_list[i].current_level = 1;
        g_mastery_list[i].current_exp = 0;
        g_mastery_list[i].speed_multiplier = 1.0;
    }
    return 0;
}

