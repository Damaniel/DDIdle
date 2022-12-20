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

// This table represents the number of *actions* performed to increase the
// mastery level of any skill to a particular level.
// Note - the table goes from 0 to 99, but represents the experience required
// to go from level 1 to level 100.  These are also absolute values, not
// relative ones - i.e. it acutally takes 38 actions to get from level 10
// to 11, not 166.

unsigned int g_mastery_exp_table[100] = {
      0,     1,     4,     9,    18,    30,    47,    69,    96,   128,
    166,   211,   262,   321,   387,   461,   543,   633,   732,   839,
    956,  1082,  1218,  1364,  1520,  1687,  1864,  2052,  2251,  2462,
   2685,  2920,  3167,  3426,  3698,  3983,  4281,  4592,  4916,  5254,
   5606,  5972,  6353,  6748,  7158,  7583,  8023,  8478,  8949,  9435,
   9937, 10455, 10990, 11541, 12109, 12694, 13296, 13915, 14551, 15205,
  15876, 16565, 17272, 17998, 18742, 19505, 20286, 21086, 21905, 22744,
  23602, 24480, 25377, 26294, 27231, 28188, 29166, 30164, 31183, 32223,
  33284, 34366, 35469, 36594, 37741, 38909, 40099, 41311, 42546, 43803,
  45083, 46385, 47710, 49058, 50429, 51824, 53242, 54684, 56149, 57638
};

// unsigned int g_mastery_exp_table[100] = {
//       0, 1, 1, 1, 1, 1, 1, 1, 1, 1,
//       1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
//       1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
//       1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
//       1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
//       1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
//       1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
//       1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
//       1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
//       1, 1, 1, 1, 1, 1, 1, 1, 1, 1   
// };

// This table repesents mastery exp as well, but lists the number of actions
// to progress from the previous level to this one.  Note that this table
// goes from 0 to 99, but represents the actions required to go from 1-100.
// For example, entry 9 represents the actions required to go from level 9 
// to 10.
unsigned int g_mastery_exp_to_level_table[100] = {
     0,    1,    3,    5,    9,   12,   17,   22,   27,   32,
    38,   45,   51,   59,   66,   74,   82,   90,   99,  107,
   117,  126,  136,  146,  156,  167,  177,  188,  199,  211,
   223,  235,  247,  259,  272,  285,  298,  311,  324,  338,
   352,  366,  381,  395,  410,  425,  440,  455,  471,  486,
   502,  518,  535,  551,  568,  585,  602,  619,  636,  654,
   671,  689,  707,  726,  744,  763,  781,  800,  819,  839,
   858,  878,  897,  917,  937,  957,  978,  998, 1019, 1040,
  1061, 1082, 1103, 1125, 1147, 1168, 1190, 1212, 1235, 1257,
  1280, 1302, 1325, 1348, 1371, 1395, 1418, 1442, 1465, 1489
};


unsigned int g_skill_exp_table[100] = {
          0,        10,         31,         56,         85,        119,        159,        206,        262,        329,
        408,       502,        614,        747,        905,       1090,       1315,       1580,       1895,       2275, 
       2720,      3250,       3880,       4630,       5520,       6585,       7845,       9345,      11130,      13250,
      15780,     18790,      22370,      26630,      31710,      37760,      44970,      53650,      63800,      76000,
      90560,    107920,     128640,     153360,     182870,     218100,     260170,     310440,     370490,     442270,
     528080,    630680,     753410,     900240,    1075950,    1286280,    1538110,    1839710,    2201010,    2633940,
    3152830,   3774910,    4520890,    5415680,    6489240,    7777600,    9324130,   11181000,   13411200,   16090300,
   19309400,  23178600,   27830000,   33423300,   40150900,   48244700,   57984500,   69708000,   83822500,  100819800,
  121293500, 145960600,  175686800,  211528200,  254718900,  306816400,  369657700,  445475700,  536971100,  647410800,
  780747300, 941764000, 1136250000, 1371217000, 1655152000, 1998335000, 2413222000, 2914903000, 3521666000, 4255682000
};

unsigned int g_skill_exp_to_level_table[100] = {
  0, 10, 21, 25, 29, 34, 40, 47, 56, 67,
  
};

