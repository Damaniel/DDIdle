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

//Skill *g_skill_list;
//Mastery *g_mastery_list;

int g_num_masteries;
int g_num_skills;
int g_active_skill;

void process_proc(Skill *s) {
    // If the mastery has procced
    //  - increase the mastery exp
    //  - If mastery exp is enough for the next level 
    //    - Increase mastery level
    //  - Increase the skill exp by the amount from the particular mastery
    //  - If skill exp is enough for the next level
    //    - Increase skill level
    //  - reset the proc counter
    Mastery *m = get_active_mastery(s);;

    if (!s->is_currently_active) {
        printf("Current skill is inactive!\n");
        return;
    }

    if (g_skill_timer >= m->next_proc) {
        m->current_exp++;
        printf("%s mastery proc count - %d\n", m->name, m->current_exp);
        if(m->current_level < 100 && m->current_exp >= g_mastery_exp_table[m->current_level]) {
                m->current_level++;
                printf("Mastery %s level increased to %d\n", m->name, m->current_level);
        }
        s->current_exp += m->skill_exp;
        if(s->current_level < 100 && s->current_exp >= g_skill_exp_table[s->current_level]) {
                s->current_level++;
                printf("%s skill level increased to %d\n", s->name, s->current_level);
        }
        set_next_proc(m);
    }
}

Skill *get_active_skill(void) {
    return &(g_skill_list[g_active_skill]);
}

Mastery *get_active_mastery(Skill *s) {
    return &(g_mastery_list[g_skill_list[g_active_skill].active_mastery]);
}

void set_next_proc(Mastery *m) {
    m->next_proc = g_skill_timer + m->execution_time;
}

void debug_skill(Skill *s) {
    int i;

    for(i=0; i<s->num_masteries; i++) {
        printf("Mastery %d\n", (i+1));
        if(s->active_mastery == i) {
            printf("  * This mastery is the active one! *\n");
        }

        printf("  - Current level: %d\n", g_mastery_list[s->masteries[i]].current_level);
        printf("  - current exp: %d\n", g_mastery_list[s->masteries[i]].current_exp);
        printf("  - time per action: %d\n", g_mastery_list[s->masteries[i]].execution_time);
    }

    if(s->is_currently_active) {
        printf("This skill is currently being worked on!\n");
    }
    else {
        printf("This skill is NOT currently being worked on!\n");
    }
}

// Deallocate memory used by the skill (mainly just the mastery list)
void destroy_skills(Skill *s) {
    if (s != NULL) {
        free(s);
    }
}

void destroy_masteries(Mastery *m) {
    if (m != NULL) {
        free(m);
    }
}