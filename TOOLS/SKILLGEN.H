#ifndef __SKILLGEN_H__
#define __SKILLGEN_H__

typedef struct {
    short id;
    char name[32];
    int current_level;
    int current_exp;
    unsigned char minimum_skill_level;
    short execution_time;
    short skill_exp;
    short num_prerequisites;
    short prerequisites[8];
    unsigned char prerequisite_quantities[8];
    unsigned int next_proc;
    float speed_multiplier;
} Mastery;

typedef struct {
    short id;
    char name[32];
    short max_masteries_per_skill[50];
    int current_level;
    int current_exp;
    int active_mastery;
    int is_currently_active;
    float speed_multiplier;
} Skill;

#endif