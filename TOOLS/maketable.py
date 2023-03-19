import math

def next_skill_level_exp(cur_level):
    return round(0.25 * math.floor((cur_level - 1) + (300 * pow(2, (cur_level - 1) / 7))))
    return 

def next_mastery_level_exp(cur_level):
    return round(0.25 * math.floor((cur_level - 1) + (300 * pow(2, (cur_level - 1) / 7))))

def create_skill_table(max_level):
    # These arrays start from level 0, but a level one character has 0 total exp, so we populate the 
    # first two values with 0 (the former is a dummy value which will be cut off when we make
    # the arrays since the C code will adjust array index to character level accordingly)
    skill_table = [0, 0]
    for level in range(2, max_level + 1):
        skill_table.append(next_skill_level_exp(level))
    return skill_table

def create_mastery_table(max_level):
    mastery_table = [0, 0]
    for level in range(2, max_level + 1):
        mastery_table.append(next_mastery_level_exp(level))
    return mastery_table

def pretty_print_table(table):
    cumulative_exp = 0
    print("Level\t\tExperience\tCumulative experience")
    for i in range(1, len(table)):
        cumulative_exp = cumulative_exp + table[i]
        print(f"{i}\t\t{table[i]}\t\t{cumulative_exp}")

def export_table_as_c_arrays(table_base, table, item_count):
    exp_table_name = table_base + "_exp"
    exp_diff_table_name = table_base + "_diff_exp"
    cumulative_exp = 0
    cumulative_table = []

    print(f"unsigned int {exp_table_name}[{item_count}] = \u007b\n  ", end="")
    for i in range(1, len(table) - 1):
        if i > 1 and i % 10 == 1:
            print("\n  ", end="")
        cumulative_exp = cumulative_exp + table[i]
        cumulative_table.append(cumulative_exp)
        print(f"{str(cumulative_table[i-1]):>8}", end=", ")
    cumulative_exp = cumulative_exp + table[len(table) - 1]
    cumulative_table.append(cumulative_exp)
    print(f"{str(cumulative_table[len(cumulative_table)-1]):>8}")
    print("};")
    print()

    print(f"unsigned int {exp_diff_table_name}[{item_count}] = \u007b\n  ", end="")
    for i in range(1, len(table) - 1):
        if i > 1 and i % 10 == 1:
            print("\n  ", end="")
        print(f"{str(table[i]):>8}", end=", ")
    print(f"{str(table[len(table)-1]):>8}")
    print("};")


skill_table = create_skill_table(100)
mastery_table = create_mastery_table(100)

export_table_as_c_arrays("mastery", mastery_table, 100)
export_table_as_c_arrays("skill", skill_table, 100)
