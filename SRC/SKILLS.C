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

void process_proc(Skill *s) {
    // If the mastery has procced
    //  - increase the mastery exp
    //  - If mastery exp is enough for the next level 
    //    - Increase mastery level
    //  - Increase the skill exp by the amount from the particular mastery
    //  - If skill exp is enough for the next level
    //    - Increase skill level
    //  - reset the proc counter
    Mastery *m = &(s->masteries[s->active_mastery]);

    if (!s->is_currently_active) {
        printf("Current skill is inactive!\n");
        return;
    }

    if (g_skill_timer >= m->next_proc) {
        m->current_exp++;
        printf("Mastery proc count - %d\n", m->current_exp);
        if(m->current_level < 100 && m->current_exp >= g_mastery_exp_table[m->current_level]) {
                m->current_level++;
                printf("Level increase to %d\n", m->current_level);
        }
        m->next_proc = g_skill_timer + m->execution_time;
    }
}

void initialize_skill(Skill *s) {
    Mastery m;

    // Set up the skill with the test mastery
    s->masteries = malloc(NUM_MASTERIES * sizeof(Mastery));

    // Create a test mastery
    m.current_level = 1;
    m.current_exp = 0;
    m.execution_time = 15;  
    s->masteries[0] = m;

    // Create another test mastery
    m.current_level = 3;
    m.current_exp = 3;
    m.execution_time = 25;
    s->masteries[1] = m;

    // Set some metadata for the skill
    s->current_exp = 0;
    s->current_level = 1;
    s->active_mastery = 0;
    s->is_currently_active = 1;
}

void debug_skill(Skill *s) {
    int i;

    for(i=0; i<NUM_MASTERIES; i++) {
        printf("Mastery %d\n", i+i);
        if(s->active_mastery == i) {
            printf("  * This mastery is the active one! *\n");
        }
        printf("  - Current level: %d\n", s->masteries[i].current_level);
        printf("  - current exp: %d\n", s->masteries[i].current_exp);
        printf("  - time per action: %d\n", s->masteries[i].execution_time);
    }

    if(s->is_currently_active) {
        printf("This skill is currently being worked on!\n");
    }
    else {
        printf("This skill is NOT currently being worked on!\n");
    }
}

// Deallocate memory used by the skill (mainly just the mastery list)
void destroy_skill(Skill *s) {
    free(s->masteries);
}