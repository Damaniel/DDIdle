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
#ifndef __DDUNIDLE_H__
#define __DDUNIDLE_H__

#include <stdio.h>
#include <string.h>
#include <allegro.h>

#include "STRUCTS.H"
#include "INVENTRY.H"
#include "SKILLS.H"
#include "FILEUTIL.H"

#define SKILLS_DATA_FILE   "SKILLS.DAT"
#define NUM_MASTERIES   2

// Levels in the game are 1 to 100.  While the array checks generally 
// keep this in mind, some checks might try to index out of range if the
// mastery level is 100.  There's 
extern unsigned int g_skill_exp_table[100];
extern unsigned int g_mastery_exp_table[100];
extern unsigned int g_mastery_exp_to_level_table[100];

extern volatile unsigned int g_skill_timer;
extern volatile unsigned int g_game_timer;

#endif