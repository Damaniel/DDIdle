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
#ifndef __SKILLS_H__
#define __SKILLS_H__

#include "DDUNIDLE.H"

/* process_proc
 *
 * Processes a single mastery action.  This also affects the skill in that
 * mastery actions give the skill experience. 
 * */
void process_proc(Skill *s);

/* destroy_skills
 *
 * Frees up the skill list. 
 */
void destroy_skills(Skill *s);

/* destroy_masteries
 *
 * Frees up the mastery list. 
 */
void destroy_masteries(Mastery *m);

/* get_active_mastery 
 *
 * a helper function that returns the active mastery for the selected skill.
 */
Mastery *get_active_mastery(Skill *s);

/* get_active_skill
 *
 * a helper function that returns the active skill.
 */
Skill *get_active_skill(void);

/* set_next_proc
 *
 * Determine when the mastery should trigger again and sets it.
 */
void set_next_proc(Mastery *m);

/* debug_skill 
 *
 * Prints out information about the provided skill 
 */
void debug_skill(Skill *s);

/* The global skill and mastery lists */
extern int g_num_skills;
extern int g_num_masteries;
extern Skill *g_skill_list;
extern Mastery *g_mastery_list;

/* The ID of the currently active skill */
extern int g_active_skill;

#endif
