#include "../INCLUDE/DDUNIDLE.H"

// This table represents the number of *actions* performed to increase the
// mastery level of any skill to a particular level.
// Note - the table goes from 0 to 99, but represents the experience required
// to go from level 1 to level 100.  These are also absolute values, not
// relative ones - i.e. it acutally takes 16 actions to get from level 10
// to 11, not 117.
unsigned int g_mastery_exp_table[100] = {
        0,     5,    12,    23,    35,    48,    61,    74,    87,   102,
      117,   134,   151,   170,   189,   210,   232,   256,   281,   308,
      336,   366,   398,   432,   469,   507,   548,   592,   639,   688,
      741,   796,   856,   919,   986,  1058,  1134,  1214,  1300,  1391,
     1487,  1591,  1700,  1817,  1940,  2072,  2211,  2359,  2517,  2684,
     2862,  3050,  3251,  3464,  3690,  3930,  4185,  4456,  4744,  5049,
     5374,  5718,  6084,  6473,  6886,  7324,  7789,  8283,  8807,  9364,
     9955, 10583, 11249, 11957, 12708, 13505, 14352, 15251, 16205, 17218,
    18294, 19436, 20648, 21935, 23302, 24752, 26292, 27927, 29663, 31505,
    33461, 35538, 37743, 40084, 42569, 45207, 48008, 50981, 54138, 57490

};

unsigned int g_skill_exp_table[100] = {

};
