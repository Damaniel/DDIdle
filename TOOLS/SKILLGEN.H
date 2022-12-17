#ifndef __SKILLGEN_H__
#define __SKILLGEN_H__

typedef struct {
    int id;
    char name[20];
    int current_level;
    int current_exp;
    int minimum_skill_level;
    int execution_time;
    int num_prerequisites;
    int prerequisites[8];
    int prerequisite_quantities[8];
    unsigned int next_proc;
    float speed_multiplier;
} Mastery;

typedef struct {
    int id;
    char name[20];
    Mastery *masteries;
    int current_level;
    int current_exp;
    int active_mastery;
    int is_currently_active;
    float speed_multiplier;
} Skill;

#endif