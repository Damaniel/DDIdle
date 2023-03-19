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

unsigned int g_mastery_exp_table[100] = {
           0,          1,          4,          7,         11,         16,         22,         29,         36,         45,
          55,         66,         78,         91,        106,        121,        138,        156,        175,        196,
         219,        244,        270,        298,        328,        360,        394,        430,        469,        510,
         554,        601,        650,        703,        759,        818,        881,        948,       1019,       1095,
        1176,       1262,       1353,       1450,       1553,       1663,       1780,       1904,       2036,       2177,
        2327,       2486,       2656,       2837,       3030,       3235,       3454,       3687,       3936,       4201,
        4484,       4785,       5107,       5450,       5817,       6208,       6626,       7072,       7549,       8058,
        8602,       9183,       9804,      10467,      11176,      11935,      12746,      13613,      14540,      15531,
       16592,      17727,      18941,      20240,      21630,      23117,      24709,      26412,      28235,      30187,
       32277,      34514,      36909,      39474,      42220,      45161,      48310,      51682,      55293,      59161
};

unsigned int g_mastery_exp_to_level_table[100] = {
           0,          1,          3,          3,          4,          5,          6,          7,          7,          9,
          10,         11,         12,         13,         15,         15,         17,         18,         19,         21,
          23,         25,         26,         28,         30,         32,         34,         36,         39,         41,
          44,         47,         49,         53,         56,         59,         63,         67,         71,         76,
          81,         86,         91,         97,        103,        110,        117,        124,        132,        141,
         150,        159,        170,        181,        193,        205,        219,        233,        249,        265,
         283,        301,        322,        343,        367,        391,        418,        446,        477,        509,
         544,        581,        621,        663,        709,        759,        811,        867,        927,        991,
        1061,       1135,       1214,       1299,       1390,       1487,       1592,       1703,       1823,       1952,
        2090,       2237,       2395,       2565,       2746,       2941,       3149,       3372,       3611,       3868
};

unsigned int g_skill_exp_table[100] = {
           0,         10,         23,         39,         59,         84,        114,        151,        195,        248,
         312,        389,        481,        591,        723,        881,       1069,       1294,       1562,       1881,
        2261,       2714,       3254,       3896,       4661,       5571,       6654,       7942,       9475,      11298,
       13467,      16047,      19116,      22766,      27107,      32270,      38411,      45714,      54400,      64730,
       77015,      91625,     109000,     129663,     154236,     183459,     218212,     259541,     308690,     367139,
      436648,     519309,     617610,     734511,     873531,    1038855,    1235460,    1469265,    1747308,    2077959,
     2471173,    2938786,    3494875,    4156180,    4942610,    5877838,    6990018,    8312631,    9885493,   11755952,
    13980315,   16625544,   19771270,   23512190,   27960919,   33251380,   39542834,   47024676,   55922136,   66503060,
    79085970,   94049656,  111844579,  133006428,  158172250,  188099625,  223689473,  266013174,  316344820,  376199572,
   447379269,  532026672,  632689966,  752399472,  894758869, 1064053677, 1265380267, 1504799281, 1789518076, 2128107693
};

unsigned int g_skill_exp_to_level_table[100] = {
           0,         10,         13,         16,         20,         25,         30,         37,         44,         53,
          64,         77,         92,        110,        132,        158,        188,        225,        268,        319,
         380,        453,        540,        642,        765,        910,       1083,       1288,       1533,       1823,
        2169,       2580,       3069,       3650,       4341,       5163,       6141,       7303,       8686,      10330,
       12285,      14610,      17375,      20663,      24573,      29223,      34753,      41329,      49149,      58449,
       69509,      82661,      98301,     116901,     139020,     165324,     196605,     233805,     278043,     330651,
      393214,     467613,     556089,     661305,     786430,     935228,    1112180,    1322613,    1572862,    1870459,
     2224363,    2645229,    3145726,    3740920,    4448729,    5290461,    6291454,    7481842,    8897460,   10580924,
    12582910,   14963686,   17794923,   21161849,   25165822,   29927375,   35589848,   42323701,   50331646,   59854752,
    71179697,   84647403,  100663294,  119709506,  142359397,  169294808,  201326590,  239419014,  284718795,  338589617
};