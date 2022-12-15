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

volatile unsigned int g_skill_timer;
volatile unsigned int g_game_timer;

void skill_handler(void) {
    g_skill_timer++;
}
END_OF_FUNCTION(skill_handler);

void game_handler(void) {
    g_game_timer++;
}
END_OF_FUNCTION(game_handler);

int main(void) {
    Skill s;
    unsigned int next_frame;

    LOCK_VARIABLE(g_game_timer);
    LOCK_VARIABLE(g_skill_timer);
    LOCK_FUNCTION(game_handler);
    LOCK_FUNCTION(skill_handler);

    initialize_skill(&s);
    debug_skill(&s);

    g_skill_timer = 0;
    g_game_timer = 0;

    allegro_init();
    install_timer();
    install_int(skill_handler, 100);
    install_int(game_handler, 33);

    s.masteries[s.active_mastery].next_proc = g_skill_timer + s.masteries[s.active_mastery].execution_time;

    next_frame = g_game_timer + 1;
    while(g_game_timer < 600) {
        // Update all active skill processing
        process_proc(&s);
        // Update graphics

        // Wait until the next frame flips over
        while(g_game_timer < next_frame) {
            rest(1);
        }
        next_frame = g_game_timer + 1;
    }

    destroy_skill(&s);
    return 0;
}