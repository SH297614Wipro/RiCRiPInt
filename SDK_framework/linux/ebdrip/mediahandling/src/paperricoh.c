
#include "omstub.h"
#include "gps/penv_var.h"
#include "oil.h"


#define NULL 0
/* #define TRUE 1 */

extern OIL_TyJob *g_pstCurrentJob;


PAPERINFO paper_table_variable_resolution[MAX_TABLE_SIZE];
PAPERINFO System_Paper_table[MAX_TABLE_SIZE]=
{
{{ 2550, 3300}, { 2450, 3200}, { 50, 50}, { 2400, 3300},{ 75, 0}, { 2550, 3180}, { 0, 60}, { 25, -50},{ -50, 10}, 603,  2,  0 ,  0, 0, { 612, 792}, { 2450, 3200}, { 50, 50}, { 300, 300}},
{{ 2550, 3300}, { 3200, 2450}, { 50, 50}, { 2400, 3300},{ 75, 0}, { 2550, 3180}, { 0, 60}, { 25, -50}, {-50, 10}, 602,  2,  0 ,  0, 0, { 612, 792}, { 3200, 2450}, { 50, 50}, { 300, 300}},
{{ 2550, 4200}, { 2450, 4100}, { 50, 50}, { 2400, 4200},{ 75, 0}, { 2550, 4080}, { 0, 60}, { 25, -50},{ -50, 10}, 514,  3,  1 ,  0, 0, { 612, 1008}, { 2450, 4100}, { 50, 50}, { 300, 300}},
{{ 2550, 4200}, { 4100, 2450}, { 50, 50}, { 2400, 4200},{ 75, 0}, { 2550, 4080}, { 0, 60}, { 25, -50},{ -50, 10}, 515,  3,  1 ,  0,0,  { 612, 1008}, { 4100, 2450}, { 50, 50}, { 300, 300}},
{{ 3300, 5100}, { 3200, 5000}, { 50, 50}, { 3150, 5100},{ 75, 0}, { 3300, 4980}, { 0, 60}, { 25, -50},{ -50, 10}, 516,  6,  4 ,  0, 0, { 792, 1224}, { 3200, 5000}, { 50, 50},  { 300, 300}},
{{ 3300, 5100}, { 5000, 3200}, { 50, 50}, { 3150, 5100},{ 75, 0}, { 3300, 4980}, { 0, 60}, { 25, -50},{ -50,10 }, 517,  6,  4 ,  0, 0, { 792, 1224}, { 5000,3200}, { 50, 50}, { 300, 300}},
{{ 2175, 3150}, { 2075, 3050}, { 50, 50}, { 2025, 3150},{ 75, 0}, { 2175, 3030}, { 0, 60}, { 25, -50},{ -50, 10}, 498,  1,  3 ,  0, 0, { 522, 756}, { 2075, 3050}, { 50, 50}, { 300, 300}},
{{ 2175, 3150}, { 3050,  2075}, { 50, 50}, { 2025, 3150},{ 75, 0}, { 2175, 3030}, { 0, 60}, { 25, -50},{ -50, 10}, 499,  1,  3 , 0, 0, { 522, 756}, { 3050, 2075}, { 50, 50}, { 300, 300}},
{{ 1650, 2550}, { 1550, 2450}, { 50, 50}, { 1500, 2550},{ 75, 0}, { 1650, 2430}, { 0, 60}, { 25, -50},{ -50, 10}, 500,  2008,  19 ,  0, 1, { 396, 612}, { 1550, 2450}, { 50, 50}, { 300, 300}},
{{ 1650, 2550}, { 2450, 1550}, { 50, 50}, { 1500, 2550},{ 75, 0}, { 1650, 2430}, { 0, 60}, { 25, -50},{ -50,10}, 501,  2008,  19 ,  0, 1, { 396, 612}, { 2450,1550}, { 50, 50}, { 300, 300}},
{{ 2480, 3507}, { 2380, 3407}, { 50,50}, { 2338, 3507},{ 71, 0}, { 2480, 3389}, { 0, 59}, { 21,-50},{ -50, 9}, 581,  26,  2 ,  0, 0, { 595, 842},{ 2379, 3408}, { 50, 50}, { 300, 300}},
{{ 2480, 3507}, { 3407,2380}, { 50, 50}, { 2338, 3507},{ 71, 0}, { 2480, 3389}, { 0,59}, { 21, -50},{ -50, 9}, 596,  26,  2 ,  0, 0,{ 595, 842}, { 3408, 2379}, { 50, 50}, { 300, 300}},
{{ 3507, 4960}, { 3407, 4860}, { 50, 50}, { 3365, 4960},{ 71, 0}, { 3507,4842}, { 0, 59}, { 21, -50},{ -50, 9}, 582,27,5 ,  0, 0, { 842, 1191}, { 3408, 4862}, { 50, 50},{ 300, 300}},
{{ 3507, 4960}, { 4860, 3407}, { 50, 50}, { 3365, 4960},{ 71, 0}, { 3507, 4842}, { 0, 59}, { 21, -50},{ -50,9}, 597,  27,  5 ,  0, 0, { 842, 1191}, { 4862,3408}, { 50, 50}, { 300, 300}},
{{ 3600, 5400}, { 3500, 5300}, { 50,50}, { 3458, 5400},{ 71, 0}, { 3600, 5080}, { 0, 158},{25, -50},{ -50, 9}, 583,  2043,  205 ,  0, 1,{864, 1296}, { 3500, 5300}, { 50, 50}, { 300, 300}},
{{ 3600, 5400},{ 5300, 3500}, { 50, 50}, { 3458, 5400},{ 71, 0}, { 3600, 5080},{ 0, 158}, { 25, -50},{ -50, 9}, 598,  2043,  205 ,0, 1, { 864, 1296}, { 5300, 3500}, { 50, 50}, { 300,300}},
{{ 1748, 2480}, { 1648, 2380}, { 50, 50}, { 1606, 2480},{ 71,0}, { 1748, 2362}, { 0, 59}, { 21, -50},{ -50, 9}, 580,2000,  15 , 0, 0, { 420, 595}, { 1650, 2379},{ 50, 50}, { 300, 300}},
{{ 1748, 2480}, { 2380, 1648}, { 50, 50},{1606, 2480},{ 71, 0}, { 1748, 2362}, { 0, 59}, { 21, -50},{ -50, 9}, 595,  2000,  15 ,  0, 0, { 420, 595},{ 2379, 1650}, { 50, 50}, { 300, 300}},
{{ 1240, 1748}, { 1140,1648}, { 50, 50}, { 1098, 1748},{ 71, 0}, { 1240, 1630}, { 0,59}, { 21, -50},{ -50, 9}, 579,  2001,  20 ,  0,0, { 297, 420}, { 1137, 1650}, { 50, 50}, { 300, 300}},
{{ 1240, 1748}, { 1648, 1140}, { 50, 50}, { 1098, 1748},{ 71, 0}, {1240, 1630}, { 0, 59}, { 21, -50},{ -50, 9}, 594,  2001,20 , 0, 0, { 297, 420}, { 1650, 1137}, { 50, 50},{ 300, 300}},
{{ 2400, 3900}, { 2300, 3800}, { 50, 50}, { 2250, 3900}, { 75, 0}, { 2400, 3780}, { 0, 60}, { 25, -50},{ -50,10}, 504,  2011,  18 ,  0, 1, { 576, 936}, { 2300,3800}, { 50, 50}, { 300, 300}},
{{ 2400, 3900}, { 3800, 2300}, { 50,50}, { 2250, 3900},{ 75, 0}, { 2400, 3780}, { 0, 60}, { 25,-50},{ -50, 10}, 505,  2011,  18 ,  0, 1, { 576,936}, { 3800, 2300}, { 50, 50}, { 300, 300}},
{{ 2550, 3900}, {2450, 3800}, { 50, 50}, { 2400, 3900},{ 75, 0}, { 2550, 3780},{ 0, 60}, { 25, -50},{ -50, 10}, 512,  2007,  17 , 0,1, { 612, 936}, { 2450, 3800}, { 50, 50}, { 300, 300}},
{{ 2550, 3900},{ 3800, 2450}, { 50, 50}, { 2400, 3900},{ 75, 0},{ 2550, 3780}, { 0, 60}, { 25, -50},{ -50, 10}, 513,  2007,17 ,  0, 1, { 612, 936}, { 3800, 2450}, { 50, 50},{ 300, 300}},
{{ 2475, 3900}, { 2375, 3800}, { 50, 50}, { 2325, 3900},{ 75, 0}, { 2475, 3780}, { 0, 60}, { 25, -50},{ -50,10}, 506,  2012,  16 ,  0, 1, { 595, 935}, { 2379,3795}, { 50, 50}, { 300, 300}},
{{ 2475, 3900}, { 3800, 2375}, { 50,50}, { 2325, 3900},{ 75, 0}, { 2475, 3780}, { 0, 60}, { 25,    -50},{ -50, 10}, 507,  2012,  16 ,  0, 1, { 595,935}, { 3795, 2379}, { 50, 50}, { 300, 300}},
{{ 1237, 2850}, {1137, 2750}, { 50, 50}, { 1087, 2850},{ 75, 0}, { 1237, 2730},{ 0, 60}, { 25, -50},{ -50, 10}, 492,  81,  6 ,1, 1, { 297, 684}, { 1137, 2750}, { 50, 50}, { 300, 300}},
{{ 1237, 2850}, { 2750, 1137}, { 50, 50}, { 1087, 2850},{ 75, 0}, {1237, 2730}, { 0, 60}, { 25, -50},{ -50, 10}, 497,  81,6 ,  0, 1, { 297, 684}, { 2750, 1137}, { 50, 50},{ 300, 300}}, 
{{ 1162, 2250}, { 1062, 2150}, { 50, 50}, { 1012, 2250},{ 75, 0}, { 1162, 2130}, { 0, 60}, { 25, -50},{ -50,10}, 491,  80,  7 , 1, 1, { 279, 540}, { 1062, 2150},{ 50, 50}, { 300, 300}},
{{ 1162, 2250}, { 2150, 1062}, { 50, 50},{ 1012, 2250},{ 75, 0}, { 1162, 2130}, { 0, 60}, { 25, -50}, { -50, 10}, 496,  80,  7 ,  0, 1, { 279, 540},{ 2150, 1062}, { 50, 50}, { 300, 300}},
{{ 1346, 1913}, { 1246,1813}, { 50, 50}, { 1204, 1913},{ 71, 0}, { 1346, 1795}, { 0,59}, { 21, -50},{ -50, 9}, 489,  2022,  202 ,  0,1, { 323, 459}, { 1245, 1812}, { 50, 50}, { 300, 300}}, 
{{ 1346, 1913}, { 1813, 1246}, { 50, 50}, { 1204, 1913},{ 71, 0}, {1346, 1795}, { 0, 59}, { 21, -50},{ -50, 9}, 494,  2022,202 ,  0, 1, { 323, 459}, { 1812, 1245}, { 50, 50},{ 300, 300}},
{{ 1913, 2704}, { 1813, 2604}, { 50, 50}, { 1771, 2704},{ 71, 0}, { 1913, 2586}, { 0, 59}, { 21, -50},{ -50,9}, 488,  91,  8 ,  1, 1, { 459, 649}, { 1812, 2604},{ 50, 50}, { 300, 300}},
{{ 1913, 2704}, { 2604, 1813}, { 50, 50},{ 1771, 2704},{ 71, 0}, { 1913, 2586}, { 0, 59}, { 21, -50},{ -50, 9}, 493,  91,  8 ,  0, 1, { 459, 649},{ 2604, 1812}, { 50, 50}, { 300, 300}},
{{ 1299, 2598}, { 1199,2498}, { 50, 50}, { 1157, 2598},{ 71, 0}, { 1299, 2480}, { 0, 59}, { 21, -50},{ -50, 9}, 490,  90,  9 , 1, 1,{ 311, 623}, { 1195, 2495}, { 50, 50}, { 300, 300}},
{{ 1299,2598}, { 2498, 1199}, { 50, 50}, { 1157, 2598},{ 71, 0}, { 1299,2480}, { 0, 59}, { 21, -50},{ -50, 9}, 495,  90, 9 ,  0, 1, { 311, 623}, { 2495, 1195}, { 50, 50}, { 300, 300}},
{{ 3153, 4606}, { 3053, 4506}, { 50, 50}, { 3011, 4606},{ 71, 0}, { 3153, 4488}, { 0, 59}, { 21, -50},{ -50,9}, 564,  2030,  203 ,  0, 1, { 757, 1106}, { 3054,4508}, { 50, 50}, { 300, 300}},
{{ 3153, 4606}, { 4506, 3053}, { 50,50}, { 3011, 4606},{ 71, 0}, { 3153, 4488}, { 0, 59}, { 21, -50},{ -50, 9}, 565,  2030,  203 ,  0, 1, { 757,1106}, { 4508, 3054}, { 50, 50}, { 300, 300}},
{{ 2303, 3153}, { 2203, 3053}, { 50, 50}, { 2161, 3153},{ 71, 0}, { 2303, 3035}, { 0, 59}, { 21, -50},{ -50, 9}, 562,  2031,  204 ,  0, 1, { 553, 757}, { 2204, 3054}, { 50, 50}, { 300, 300}},
{{ 2303, 3153}, { 3053, 2203}, { 50, 50}, { 2161, 3153},{ 71, 0}, {2303, 3035}, { 0, 59}, { 21, -50},{ -50, 9}, 563,  2031,204 ,  0, 1, { 553, 757}, { 3054, 2204}, { 50, 50},{ 300, 300}},
{{ 3035, 4299}, { 2935, 4199}, { 50, 50}, { 2893, 4299}, { 71, 0}, { 3035, 4181}, { 0, 59}, { 21, -50},{ -50,9}, 575,  46,  10 ,  0, 0, { 729, 1032}, { 2937, 4200},{ 50, 50}, { 300, 300}},
{{ 3035, 4299}, { 4199, 2935}, { 50, 50}, { 2893, 4299},{ 71, 0}, { 3035, 4181}, { 0, 59}, { 21, -50}, { -50, 9}, 590,  46,  10 ,  0, 0, { 729, 1032},{ 4200, 2937}, { 50, 50}, { 300, 300}},
{{ 2149, 3035}, { 2049,2935}, { 50, 50}, { 2007, 3035},{ 71, 0}, { 2149, 2917}, { 0,59}, { 21, -50},{ -50, 9}, 574,  45,  11 ,  0, 1,{ 516, 729}, { 2050, 2937}, { 50, 50}, { 300, 300}},
{{ 2149,3035}, { 2935, 2049}, { 50, 50}, { 2007, 3035},{ 71, 0}, { 2149, 2917}, { 0, 59}, { 21, -50},{ -50, 9}, 589,  45, 11 ,  0, 1, { 516, 729}, { 2937, 2050}, { 50, 50},{ 300, 300}},
{{ 1511, 2149}, { 1411, 2049}, { 50, 50}, { 1369, 2149},{ 71, 0}, { 1511, 2031}, { 0, 59}, { 21, -50},{ -50, 9}, 573,  2020,  201 ,  0, 1, { 363, 516}, { 1412,2050}, { 50, 50}, { 300, 300}},
{{ 1511, 2149}, { 2049, 1411}, { 50,50}, { 1369, 2149},{ 71, 0}, { 1511, 2031}, { 0, 59}, { 21, -50},{ -50, 9}, 588,  2020,  201 ,  0, 1, { 363,516}, { 2050, 1412}, { 50, 50}, { 300, 300}},
{{ 1074, 1511}, { 974, 1411}, { 50, 50}, { 932, 1511},{ 71, 0}, { 1074, 1393}, { 0, 59}, { 21, -50},{ -50, 9}, 572,  2065,  225 ,  0, 1, { 0, 0}, { 0, 0}, { 0, 0}, { 300, 300}},
{{ 1074,1511}, { 1411, 974}, { 50, 50}, { 932, 1511},{ 71, 0}, { 1074,1393}, { 0, 59}, { 21, -50},{ -50, 9}, 587,  2065, 225 ,  0, 1, { 0, 0}, { 0, 0}, { 0, 0}, { 300, 300}},
{{ 2475, 4200}, { 2375, 4100}, { 50, 50}, { 2325, 4200},{ 75, 0}, { 2475, 4080}, { 0, 60}, { 25, -50},{ -50, 10}, 508,  2014,  21 ,  0, 1, { 594, 1008}, { 2375, 4100}, { 50, 50}, { 300, 300}},
{{ 2475, 4200}, { 4100, 2375}, { 50, 50}, { 2325, 4200},{ 75, 0}, { 2475, 4080}, { 0, 60}, { 25, -50},{ -50, 10}, 509,  2014,  21 ,  0, 1, { 594, 1008},{ 4100, 2375}, { 50, 50}, { 300, 300}},
{{ 1181, 1748}, { 1081,1648}, { 50, 50}, { 1039, 1748},{ 71, 0}, { 1181, 1630}, { 0,59}, { 21, -50},{ -50, 9}, 524,  71,  13 ,  0, 1,{ 283, 419}, { 1079, 1645}, { 50, 50}, { 300, 300}},
{{ 1181,1748}, { 1648, 1081}, { 50, 50}, { 1039, 1748},{ 71, 0}, { 1181,1630}, { 0, 59}, { 21, -50},{ -50, 9}, 561,  71,13 ,  0, 1, { 283, 419}, { 1645, 1079}, { 50, 50},{ 300, 300}},
{{ 1748, 2362}, { 1648, 2262}, { 50, 50}, { 1606, 2362},{ 71, 0}, { 1748, 2244}, { 0, 59}, { 21, -50},{ -50,9}, 523,  72,  14 ,  0, 1, { 419, 567}, { 1645,2262}, { 50, 50}, { 300, 300}},
{{ 1748, 2362}, { 2262, 1648}, { 50,50}, { 1606, 2362},{ 71, 0}, { 1748, 2244}, { 0, 59}, { 21, -50},{ -50, 9}, 560,  72,  14 ,  0, 1, { 419,567}, { 2262, 1645}, { 50, 50}, { 300, 300}}, 
{{ 1417, 2775}, { 1317, 2675}, { 50, 50}, { 1275, 2775},{ 71, 0}, { 1417, 2657}, { 0, 59}, { 21, -50},{ -50, 9}, 522,  2051,  211 ,  1,1, { 340, 666}, { 1316, 2675}, { 50, 50}, { 300, 300}},
{{ 1417, 2775}, { 2675, 1317}, { 50, 50}, { 1275, 2775},{ 71, 0}, {1417, 2657}, { 0, 59}, { 21, -50},{ -50, 9}, 559,  2051,211 ,  1, 1, { 340, 666}, { 2675, 1316}, { 50, 50},{ 300, 300}},
{{ 1240, 2775}, { 1140, 2675}, { 50, 50}, { 1098, 2775}, { 71, 0}, { 1240, 2657}, { 0, 59}, { 21,-50},{ -50,9}, 521,  109,  206 ,  1, 1, { 298, 666}, { 1141,2675}, { 50, 50}, { 300, 300}}, 
{{ 1240, 2775}, { 2675, 1140}, { 50,50}, { 1098, 2775},{ 71, 0}, { 1240, 2657}, { 0, 59}, { 21,-50},{ -50, 9}, 558,  109,  206 ,  1, 1, { 298,666}, { 2675, 1141}, { 50, 50}, { 300, 300}},
{{ 1417, 2775}, { 1317, 2675}, { 50, 50}, { 1275, 2775},{ 71, 0}, { 1417, 2657}, { 0, 59}, { 21, -50},{ -50, 9}, 520,  110,  207 ,  1, 1, { 340, 666}, { 1316, 2675}, { 50, 50}, { 300, 300}}, 
{{ 1417, 2775}, { 2675, 1317}, { 50, 50}, { 1275, 2775},{ 71, 0}, {1417, 2657}, { 0, 59}, { 21, -50},{ -50, 9}, 557,  110,207 ,  1, 1, { 340, 666}, { 2675, 1316}, { 50, 50}, { 300, 300}},
{{ 1062, 2421}, { 962, 2321}, { 50, 50},  { 920, 2421},{ 71, 0}, { 1062, 2303}, { 0, 59}, { 21, -50},{ -50,9}, 519,  111,  208 ,  1, 1, { 255, 581}, { 962,2320}, { 50, 50}, { 300, 300}},
{{ 1062, 2421}, { 2321, 962}, { 50,50},   { 920, 2421},{ 71, 0}, { 1062, 2303}, { 0, 59}, { 21,-50},{ -50, 9}, 556,  111,  208 ,  1, 1, { 255,581}, { 2320, 962}, { 50, 50}, { 300, 300}},
{{ 2834, 3921}, { 2734, 3821}, { 50, 50}, { 2692, 3921},{ 71, 0}, { 2834, 3803}, { 0, 59}, { 21, -50},{ -50, 9}, 518,  2050,  210 ,  1,1, { 680, 941}, { 2733, 3820}, { 50, 50}, { 300, 300}},
{{ 2834, 3921}, { 3821, 2734}, { 50, 50}, { 2692, 3921},{ 71, 0}, {2834, 3803}, { 0, 59}, { 21, -50},{ -50, 9}, 555,  2050,210 ,  1, 1, { 680, 941}, { 3820, 2733}, { 50, 50},{ 300, 300}},
{{ 3900, 5760}, { 3800, 5660}, { 50, 50}, { 3750, 5760},{ 75, 0}, { 3900, 5640}, { 0, 60}, { 25, -50},{ -50,10}, 543,  2052,  212 ,  0, 1, { 0, 0}, { 0, 0},{ 0, 0}, { 300, 300}}, 
{{ 3900, 5760}, { 5660, 3800}, { 50, 50}, { 3750, 5760},{ 75, 0}, { 3900, 5640}, { 0, 60}, { 25, -50},{ -50, 10}, 554,  2052,  212 ,  0, 1, { 0, 0},{ 0, 0}, { 0, 0}, { 300, 300}},
{{ 3900, 5700}, { 3800, 5600}, { 50, 50}, { 3750, 5700},{ 75, 0}, { 3900, 5580}, { 0, 60},{ 25, -50},{ -50, 10}, 542,  2053,  213 ,0, 1,{ 0, 0}, { 0, 0}, { 0, 0}, { 300, 300}},
{{ 3900, 5700}, { 5600, 3800}, { 50, 50}, { 3750, 5700},{ 75, 0}, { 3900, 5580},{ 0, 60}, { 25, -50},{ -50, 10}, 553,  2053,  213 ,0, 1, { 0, 0}, { 0, 0}, { 0, 0}, { 300, 300}},
{{ 3780, 5760}, { 3680, 5660}, { 50, 50}, { 3630, 5760},{ 75, 0}, {3780, 5640}, { 0, 60}, { 25, -50},{ -50, 10}, 541,  2054,214 ,  0, 1, { 0, 0}, { 0, 0}, { 0, 0}, { 300, 300}},
{{ 3780, 5760}, { 5660, 3680}, { 50, 50}, { 3630, 5760},{ 75, 0}, { 3780, 5640}, { 0, 60}, { 25, -50},{ -50, 10},552,  2054,  214 ,  0, 1, { 0, 0}, { 0, 0}, {0, 0}, { 300, 300}},
{{ 3780, 5550}, { 3680, 5450}, { 50, 50},{ 3630, 5550},{ 75, 0}, { 3780, 5430}, { 0, 60}, { 25, -50}, { -50, 10}, 540,  2055,  215 ,  0, 1, { 0, 0},{ 0, 0}, { 0, 0}, { 300, 300}},
{{ 3780, 5550}, { 5450, 3680},{ 50, 50}, { 3630, 5550},{ 75, 0}, { 3780, 5430}, { 0, 60},{ 25, -50},{ -50, 10}, 551,  2055,  215 ,  0, 1,{ 0, 0}, { 0, 0}, { 0, 0}, { 300, 300}}, 
{{ 3900, 5400},{ 3800, 5300}, { 50, 50}, { 3750, 5400},{ 75, 0}, { 3900, 5280}, { 0, 60}, { 25, -50},{ -50, 10}, 539,  2056,  216 , 0, 1, { 0, 0}, { 0, 0}, { 0, 0}, { 300, 300}},
{{ 3900, 5400}, { 5300, 3800}, { 50, 50}, { 3750, 5400},{ 75, 0}, {3900, 5280}, { 0, 60}, { 25, -50},{ -50, 10}, 550,  2056,216 ,  0, 1, { 0, 0}, { 0, 0}, { 0, 0}, { 300, 300}},
{{ 3779, 5314}, { 3679, 5214}, { 50, 50},{ 3637, 5314},{ 71, 0}, { 3779, 5196}, { 0, 59}, { 21, -50},{ -50, 9},538,  2057,  217 ,  0, 1, { 0, 0}, { 0, 0}, {0, 0}, { 300, 300}},
{{ 3779, 5314}, { 5214, 3679}, { 50, 50},{ 3637, 5314},{ 71, 0}, { 3779, 5196}, { 0, 59}, { 21, -50},{ -50, 9}, 549,  2057,  217 ,  0, 1, { 0, 0},{ 0, 0}, { 0, 0}, { 300, 300}},
{{ 2657, 3779}, { 2557, 3679},{ 50, 50}, { 2515, 3779},{ 71, 0}, { 2657, 3661}, { 0, 59}, { 21, -50},{ -50, 9}, 537,  2058,  218 ,  0, 1,{ 0, 0}, { 0, 0}, { 0, 0}, { 300, 300}},
{{ 2657, 3779},{ 3679, 2557}, { 50, 50}, { 2515, 3779},{ 71, 0}, { 2657, 3661}, { 0, 59}, { 21, -50},{ -50, 9}, 548,  2058,  218 , 0, 1, { 0, 0}, { 0, 0}, { 0, 0}, { 300, 300}},
{{ 2669, 3661}, { 2569, 3561}, { 50, 50}, { 2527, 3661},{ 71, 0}, {2669, 3543}, { 0, 59}, { 21, -50},{ -50, 9}, 536,  2059, 219 ,  0, 1, { 0, 0}, { 0, 0}, { 0, 0}, { 300, 300}},
{{ 2669, 3661}, { 3561, 2569}, { 50, 50}, { 2527, 3661},{ 71, 0}, { 2669, 3543}, { 0, 59}, { 21, -50},{ -50, 9}, 547,  2059,  219 ,  0, 1, { 0, 0}, { 0, 0}, {0, 0}, { 300, 300}},
{{ 3661, 5102}, { 3561, 5002}, { 50, 50},{ 3519, 5102},{ 71, 0}, { 3661, 4984}, { 0, 59}, { 21, -50},{ -50, 9}, 535,  2060,  220 ,  0, 1, { 0, 0},{ 0, 0}, { 0, 0}, { 300, 300}},
{{ 3661, 5102}, { 5002, 3561},{ 50, 50}, { 3519, 5102},{ 71, 0}, { 3661, 4984}, { 0, 59}, { 21, -50},{ -50, 9}, 546,  2060,  220 ,  0, 1, { 0, 0}, { 0, 0}, { 0, 0}, { 300, 300}},
{{ 2400, 3000}, { 2300, 2900}, { 50, 50}, { 2250, 3000},{ 75, 0}, { 2400, 2880}, { 0, 60}, { 25, -50},{ -50, 10}, 534,  2061,  221 , 0, 1, { 0, 0}, { 0, 0}, { 0, 0}, { 300, 300}},
{{ 2400, 3000}, { 2900, 2300}, { 50, 50}, { 2250, 3000},{ 75, 0}, {2400, 2880}, { 0, 60}, { 25, -50},{ -50, 10}, 545,  2061,221 ,  0, 1, { 0, 0}, { 0, 0}, { 0, 0}, { 300, 300}},
{{ 3300, 4200}, { 3200, 4100}, { 50, 50}, { 3150, 4200},{ 75, 0}, { 3300, 4080}, { 0, 60}, { 25, -50},{ -50, 10},533,  2062,  222 ,  0, 1, { 0, 0}, { 0, 0}, {0, 0}, { 300, 300}},
{{ 3300, 4200}, { 4100, 3200}, { 50, 50},{ 3150, 4200},{ 75, 0}, { 3300, 4080}, { 0, 60}, { 25, -50},{ -50, 10}, 544,  2062,  222 ,  0, 1, { 0, 0},{ 0, 0}, { 0, 0}, { 300, 300}},
{{ 3000, 4200}, { 2900, 4100},{ 50, 50}, { 2850, 4200},{ 75, 0}, { 3000, 4080}, { 0, 60},{ 25, -50},{ -50, 10}, 530,  2064,  224 , 0, 0,{ 0, 0}, { 0, 0}, { 0, 0}, { 300, 300}},
{{ 3000, 4200},{ 4100, 2900}, { 50, 50}, { 2850, 4200},{ 75, 0}, { 3000, 4080},{ 0, 60}, { 25, -50},{ -50, 10}, 532,  2064,  224 ,0, 0, { 0, 0}, { 0, 0}, { 0, 0}, { 300, 300}},
{{ 3300, 4500}, { 3200, 4400}, { 50, 50}, { 3150, 4500},{ 75, 0}, {3300, 4380}, { 0, 60}, { 25, -50},{ -50, 10}, 529,  2063,223 , 0, 0, { 0, 0}, { 0, 0}, { 0, 0}, { 300, 300}},
{{ 3300, 4500}, { 4400, 3200}, { 50, 50}, { 3150, 4500},{ 75, 0}, { 3300, 4380}, { 0, 60}, { 25, -50},{ -50, 10},531,  2063,  223 ,  0, 0, { 0, 0}, { 0, 0}, { 0, 0}, { 300, 300}},
{{ 3510, 5310}, { 3410, 5210}, { 50, 50},{ 3360, 5310},{ 75, 0}, { 3510, 5190}, { 0, 60}, { 25, -50}, { -50, 10}, 487,  101,  255 ,  0, 0, { 792, 1224},{ 3150, 4950}, { 50, 50}, { 300, 300}},
{{ 9933, 14043}, { 9833,13943}, { 50, 50}, { 9791, 14043},{ 71, 0}, { 9933, 13925}, { 0,59}, { 21, -50},{ -50, 9}, 586,  2068,  228 , 0,1, { 2384, 3370}, { 9833, 13941}, { 50, 50}, { 300, 300}},
{{ 9933, 14043}, { 13943, 9833}, { 50, 50}, { 9791, 14043},{ 71, 0}, {9933, 13925}, { 0, 59}, { 21, -50},{ -50, 9}, 601,  2068,228 ,  0, 1, { 2384, 3370}, { 13941, 9833}, { 50, 50},{ 300, 300}},
{{ 7015, 9933}, { 6915, 9833}, { 50, 50}, { 6873, 9933},{ 71, 0}, { 7015, 9815}, { 0, 59}, { 21, -50},{ -50,9}, 585,  2067,  227 ,  0, 1, { 1684, 2384}, { 6916,9833}, { 50, 50}, { 300, 300}},
{{ 7015, 9933}, { 9833, 6915}, { 50,50}, { 6873, 9933},{ 71, 0}, { 7015, 9815}, { 0, 59}, { 21,-50},{ -50, 9}, 600,  2067,  227 ,  0, 1, { 1684,2384}, { 9833, 6916}, { 50, 50}, { 300, 300}}, 
{{ 4960, 7015}, { 4860, 6915}, { 50, 50}, { 4818, 7015},{ 71, 0}, { 4960, 6897}, { 0, 59}, { 21, -50},{ -50, 9}, 584,  2066,  226 ,  0, 1, { 1191, 1684}, { 4862, 6916}, { 50, 50}, { 300, 300}}, 
{{ 4960, 7015}, { 6915, 4860}, { 50, 50}, { 4818, 7015},{ 71, 0}, {4960, 6897}, { 0, 59}, { 21, -50},{ -50, 9}, 599,  2066, 226 ,  0, 1, { 1191, 1684}, { 6916, 4862}, { 50, 50}, { 300, 300}},
{{ 8598, 12165},{ 8498, 12065}, { 50, 50}, { 8456, 12165}, { 71, 0}, { 8598, 12047}, { 0, 59},{ 21,-50},{ -50, 9}, 578,  2071,  231 ,  0, 1, { 2064, 2920}, { 8500, 12066}, { 50, 50}, { 300,300}},
{{ 8598, 12165}, { 12065, 8498}, { 50, 50}, { 8456, 12165},{ 71, 0}, { 8598, 12047}, { 0, 59},{ 21,-50},{ -50, 9},593,2071,  231 ,  0, 1, { 2064, 2920}, { 8500, 12066}, { 50, 50}, { 300, 300}}, 
{{ 6082, 8598}, { 5982, 8498}, { 50, 50}, { 5940, 8598},{ 71, 0}, { 6082,  8480}, { 0, 59}, { 21, -50},{ -50, 9}, 577,  2070, 230 , 0, 1, { 1460, 2064}, { 5983, 8500}, { 50, 50},{ 300, 300}},
{{ 6082, 8598}, { 8498, 5982}, { 50, 50}, { 5940, 8598},{ 71, 0}, { 6082, 8480}, { 0, 59}, { 21, -50},{ -50,9}, 592,  2070,  230 ,  0, 1, { 1460, 2064}, { 8500,5983}, { 50, 50}, { 300, 300}}, 
{{ 4299, 6082}, { 4199, 5982}, { 50,50}, { 4157, 6082},{ 71, 0}, { 4299, 5964}, { 0, 59}, { 21,  -50},{ -50, 9}, 576,  2069,  229 ,  0, 1, { 1032,1460}, { 4200, 5983}, { 50, 50}, { 300, 300}}, 
{{ 4299, 6082}, { 5982, 4199}, { 50, 50}, { 4157, 6082},{ 71, 0}, { 4299, 5964}, { 0, 59}, { 21, -50},{ -50, 9}, 591,  2069,  229 ,  0, 1, { 1032, 1460}, { 5983, 4200}, { 50, 50}, { 300, 300}}, 
{{ 2400, 3150}, { 2300, 3050}, { 50, 50}, { 2250, 3150},{ 75, 0}, {2400, 3030}, { 0, 60}, { 25, -50},{ -50, 10}, 502,  2072, 232 , 0, 1, { 0, 0}, { 0, 0}, { 0, 0}, { 300, 300}},
{{ 2400, 3150}, { 3050, 2300}, { 50, 50}, { 2250, 3150},{ 75, 0}, { 2400, 3030}, { 0, 60}, { 25, -50},{ -50, 10}, 503,  2072,  232 ,  0, 1, { 0, 0}, { 0, 0}, {0, 0}, { 300, 300}},
{{ 3000, 4500}, { 2900, 4400}, { 50, 50},{ 2850, 4500},{ 75, 0}, { 3000, 4380}, { 0, 60}, { 25, -50},{ -50, 10}, 527,  2073,  233 ,  0, 0, { 0, 0},{ 0, 0}, { 0, 0}, { 300, 300}}, 
{{ 3000, 4500}, { 4400, 2900}, { 50, 50}, { 2850, 4500},{ 75, 0}, { 3000, 4380}, { 0, 60},{ 25, -50},{ -50, 10}, 528,  2073,  233 ,  0, 0, { 0, 0}, { 0, 0}, { 0, 0}, { 300, 300}},
{{ 2149, 2480}, { 2049, 2380}, { 50, 50}, { 2007, 2480},{ 71, 0}, { 2149, 2362},{ 0, 59}, { 21, -50},{ -50, 9}, 566,  2074,  234 ,0, 0, { 0, 0}, { 0, 0}, { 0, 0}, { 300, 300}},
{{ 2149, 2480}, { 2380, 2049}, { 50, 50}, { 2007, 2480},{ 71, 0}, {2149, 2362}, { 0, 59}, { 21, -50},{ -50, 9}, 567,  2074,     234 ,  0, 0, { 0, 0}, { 0, 0}, { 0, 0}, { 300, 300}},
{{ 2007, 2480}, { 1907, 2380}, { 50, 50}, { 1865, 2480},{ 71, 0}, { 2007, 2362}, { 0, 59}, { 21, -50},{ -50, 9},570,  2075,  235 ,  0, 0, { 0, 0}, { 0, 0}, {0, 0}, { 300, 300}},
{{ 2007, 2480}, { 2380, 1907}, { 50, 50},{ 1865, 2480},{ 71, 0}, { 2007, 2362}, { 0, 59}, { 21, -50}, { -50, 9}, 571,  2075,  235 ,  0, 0, { 0, 0}, { 0, 0}, { 0, 0}, { 300, 300}}, 
{{ 2480, 4014}, { 2380, 3914}, { 50, 50}, { 2338, 4014},{ 71, 0}, { 2480, 3896}, { 0, 59}, { 21, -50},{ -50, 9}, 568,  2076,  236 , 0, 0,{ 0, 0}, { 0, 0}, { 0, 0}, { 300, 300}},
{{ 2480, 4014}, { 3914, 2380}, { 50, 50}, { 2338, 4014},{ 71, 0}, { 2480, 3896}, { 0, 59}, { 21, -50},{ -50, 9}, 569,  2076,  236 , 0, 0, { 0, 0}, { 0, 0}, { 0, 0}, { 300, 300}},
{{ 2550, 3600}, { 2450, 3500}, { 50, 50}, { 2400, 3600},{ 75, 0}, {2550, 3480}, { 0, 60}, { 25, -50},{ -50, 10}, 525,  2077, 237 , 0, 0, { 0, 0}, { 0, 0}, { 0, 0}, { 300, 300}}, 
{{ 2550, 3600}, { 3500, 2450}, { 50, 50}, { 2400, 3600},{ 75, 0}, { 2550, 3480}, { 0, 60}, { 25, -50},{ -50, 10}, 526,  2077,  237 ,  0, 0, { 0, 0}, { 0, 0}, {0, 0}, { 300, 300}}
};

#define	SIZE_OF_TABLE	(sizeof(PageSize_OMCode)/sizeof(PageSize_OMCode[0]))

static const PAPERINFO * curPaper;
static const PAPERINFO * endPaper;
extern Sint8 ChoosePaperDirectionDone;
extern struct Pagesize_OMCode_t PageSize_OMCode[15];
extern Boolean PrintSysGetPaperInfo(OMenum paper);

#if defined(SUPPORT_EDGE2EDGE) || defined(RXPS_EDGE_TO_EDGE)
static Boolean set_edge2edge = FALSE;
static Boolean set_edge2edge_custom = FALSE;
#ifdef PCL_CUSTOM_EDGE2EDGE
static Boolean pre_enter_lang = FALSE;
static Boolean pre_enter_lang_custom = FALSE;
static int pre_njobid = 0, pre_ujobid = 0;
static Boolean customEdge2Edge = FALSE;
/* Temporary Declarations */
struct PaperDimension offset = {100,100};
struct PaperDimension nomoffset = {150,0};
struct PaperDimension rotnomoffset = {0,120};
struct PaperDimension HPnomoffset = {25,-50};
struct PaperDimension HProtnomoffset = {-50,10};

int cvtx=600;
int cvty=600;
int cvtw=0, cvtl=0;
 
#endif /*PCL_CUSTOM_EDGE2EDGE*/
#endif /* SUPPORT_EDGE2EDGE || RXPS_EDGE_TO_EDGE */

/*	
#define CONVERT_XONE(field)     \
    (op->field.x * xres / 300)

#define CONVERT_YONE(field)     \
    (op->field.y * yres / 300)
    */

OMenum Map_Page_Size(int size, int MapValue)
{
	int i;
	OMenum retval;
	switch(MapValue)
	{
	case 0: /* Get PCL page size for OMcode*/
			for(i=0;i<SIZE_OF_TABLE;i++)
			{
				if(PageSize_OMCode[i].OMCode== size)
					retval= PageSize_OMCode[i].PCL5mediasize;
			}
			break;
	case 1: /*Get the OMCode for papersize*/
		   for(i=0;i<SIZE_OF_TABLE;i++)
			{
				if(PageSize_OMCode[i].PCL5mediasize== size)
					retval= PageSize_OMCode[i].OMCode;
			}  
			break;
		
	case 2: /*Get GPS Page size for OMcode*/
			for(i=0;i<SIZE_OF_TABLE;i++)
			{
				if(PageSize_OMCode[i].OMCode== size)
					retval= PageSize_OMCode[i].GPSmediasize;
			}
			break;
		}
		return retval;
}

void PRpaperPair (PAPERCODE OMsize, int xres, int yres, OMenum *LongEdge, OMenum *ShortEdge )
{
    int nPapers,retval;
    const PAPERINFO *paperInfo, *paperInfo2;
    PAPERINFO  * papers;
    papers = (PAPERINFO*)malloc(115 * sizeof(PAPERINFO));    
	retval = Map_Page_Size(OMsize,GET_OMCODE);
	OMsize=retval;	
    paperInfo = PRpaperinfoOriginal (OMsize, xres, yres);
    /*ASSERT(paperInfo);*/
    nPapers = PRpapertable(papers, xres, yres);
	/*ASSERT(LongEdge && ShortEdge);*/
    *LongEdge = *ShortEdge = 0;

    if( paperInfo != (papers+nPapers) ) {    /* 'paperInfo' is not last table */
        paperInfo2 = paperInfo + 1; /* check next PAPERINFO */
	        if ( paperInfo->PCLpaperID == paperInfo2->PCLpaperID ) {
#ifdef SYS_CHECK_DIRECTION
            if ( PrintSysGetPaperInfo(paperInfo->OMcode) )
#endif
            *ShortEdge = paperInfo->OMcode;
#ifdef SYS_CHECK_DIRECTION
            if ( PrintSysGetPaperInfo(paperInfo2->OMcode) )
#endif
            *LongEdge = paperInfo2->OMcode;
			
			retval = Map_Page_Size(*ShortEdge,GET_PCL_SIZE);
	        *ShortEdge=retval;	
			retval = Map_Page_Size(*LongEdge,GET_PCL_SIZE);
	        *LongEdge=retval;	
			return;
        }
    }

    if( paperInfo != papers ) {  /* 'paperInfo' is not first table*/
        paperInfo2 = paperInfo - 1; /* check previous PAPERINFO */
            if ( paperInfo->PCLpaperID == paperInfo2->PCLpaperID ) {
#ifdef SYS_CHECK_DIRECTION
            if ( PrintSysGetPaperInfo(paperInfo2->OMcode) )
#endif
            *ShortEdge = paperInfo2->OMcode;
#ifdef SYS_CHECK_DIRECTION
            if ( PrintSysGetPaperInfo(paperInfo->OMcode) )
#endif
            *LongEdge = paperInfo->OMcode;
			retval = Map_Page_Size(*ShortEdge,GET_PCL_SIZE);
	        *ShortEdge=retval;	
			retval = Map_Page_Size(*LongEdge,GET_PCL_SIZE);
	        *LongEdge=retval;	
            return;
        }
    }

    *ShortEdge = paperInfo->OMcode; /*Not found pair code*/
	retval = Map_Page_Size(*ShortEdge,GET_PCL_SIZE);
	*ShortEdge=retval;	
}

void PRcustompaperinfo(int pwidth, int plength, int xres, int yres)
{ 

    int i;
    Sint32 n;
    PAPERINFO * np = (PAPERINFO *) paper_table_variable_resolution;
    const PAPERINFO * op = (const PAPERINFO *) System_Paper_table;
    Boolean convert8 = ( xres % 300 );
#if defined(SUPPORT_EDGE2EDGE) || defined(RXPS_EDGE_TO_EDGE)
    Boolean edge2edge  = OMGetCurrentBool(OMEDGETOEDGE,OMSYSTEM);
#ifdef PCL_CUSTOM_EDGE2EDGE
    Boolean enter_lang;
    int NBITS=g_pstCurrentJob->uOutputBPP; /* temporarily*/
	if(customEdge2Edge){
		int njobid, ujobid;
    	enter_lang = OMGetCurrentEnum(OMREQPROCREASON, OMSYSTEM) ==
						GPS_PENV_VAL_INT_REQPROCREASON_ENTERLANGUAGE;
		PrintSysGetjobid(&njobid);
		/*PrintSysGetjobid( &njobid, &ujobid);
		if(njobid == pre_njobid && ujobid == pre_ujobid)
			enter_lang = pre_enter_lang_custom;
		else {
			pre_njobid = njobid;
			pre_ujobid = ujobid;
		}*/
	}
#endif /* PCL_CUSTOM_EDGE2EDGE */
#endif /* SUPPORT_EDGE2EDGE || RXPS_EDGE_TO_EDGE */

#if defined(SUPPORT_EDGE2EDGE) || defined(RXPS_EDGE_TO_EDGE)
    if (cvtx == xres && cvty == yres && cvtw == pwidth && cvtl == plength && set_edge2edge_custom == edge2edge
#ifdef PCL_CUSTOM_EDGE2EDGE
					 && (!customEdge2Edge || enter_lang == pre_enter_lang_custom) 
#endif
       )
        return;
#else
    if (cvtx == xres && cvty == yres && cvtw == pwidth && cvtl == plength)
        return;
#endif /* SUPPORT_EDGE2EDGE || RXPS_EDGE_TO_EDGE */

	for (i = MAX_TABLE_SIZE; i > 0; i--, np++, op++) {
        if (op->OMcode == PAPERSIZE_CUSTOM)
            break;
    }

    if (i == 0)
        return;

#if defined(SUPPORT_EDGE2EDGE) || defined(RXPS_EDGE_TO_EDGE)
    if ( edge2edge ) {
#ifdef PCL_CUSTOM_EDGE2EDGE
		if (customEdge2Edge && !enter_lang) {
			np->size.x = np->printable.x = np->rotnomsize.x = pwidth;
			/*np->nominal.x = pwidth - CONVERT_XONE(nomoffset);*/
			np->size.y = np->printable.y = np->nominal.y = plength;
			/*np->rotnomsize.y = plength - CONVERT_YONE(rotnomoffset);*/
			np->offset.x = np->offset.y = 0;
			/*CONVERT(nomoffset);
			if (pwidth >= plength) {
				CONVERT(rotnomoffset);
			} else {
				np->rotnomoffset.x = np->rotnomoffset.y = 0;
			}*/  /* commenting as the function CONVERT() not available*/
	
			/*	The next 2 entries are NOT scaled. They get scaled when they used.
			 */
			np->HPnomoffset.x = np->nomoffset.x;
			np->HPnomoffset.y = np->HProtnomoffset.x = 0;
			np->HProtnomoffset.y = np->rotnomoffset.y;
		} else {
#endif /*PCL_CUSTOM_EDGE2EDGE*/   

#ifdef RP_CUSTOMPAPERSIZE
#if (defined(EMPCL5)||defined(EMPCLXL)) && (defined(EMPOSTSCRIPT)||defined(EMPDF))
	if ((current_pdlid == GPS_PDL_POSTSCRIPT) || (current_pdlid == GPS_PDL_PDF)){
#endif
    if(pwidth > plength){
        np->size.x = np->printable.x = np->nominal.x = np->rotnomsize.x = plength;
        np->size.y = np->printable.y = np->nominal.y = np->rotnomsize.y = pwidth;
    } else {
        np->size.x = np->printable.x = np->nominal.x = np->rotnomsize.x = pwidth;
        np->size.y = np->printable.y = np->nominal.y = np->rotnomsize.y = plength;
	}   
#if (defined(EMPCL5)||defined(EMPCLXL)) && (defined(EMPOSTSCRIPT)||defined(EMPDF))
    } else {		
        np->size.x = np->printable.x = np->nominal.x = np->rotnomsize.x = pwidth;
        np->size.y = np->printable.y = np->nominal.y = np->rotnomsize.y = plength;
	}   
#endif
#else    /* RP_CUSTOMPAPERSIZE */ 
        np->size.x = np->printable.x = np->nominal.x = np->rotnomsize.x = pwidth;
        np->size.y = np->printable.y = np->nominal.y = np->rotnomsize.y = plength;
#endif  /* RP_CUSTOMPAPERSIZE */ 
        np->offset.x = np->nomoffset.x = np->rotnomoffset.x = 0;
        np->offset.y = np->nomoffset.y = np->rotnomoffset.y = 0;

		/*  The next 2 entries are NOT scaled. They get scaled when they used.
         */
        np->HPnomoffset.x = np->HProtnomoffset.x = 0;
        np->HPnomoffset.y = np->HProtnomoffset.y = 0;
#ifdef PCL_CUSTOM_EDGE2EDGE
		}
#endif

    } else {
#endif

#ifdef RP_CUSTOMPAPERSIZE
#if (defined(EMPCL5)||defined(EMPCLXL)) && (defined(EMPOSTSCRIPT)||defined(EMPDF))
	if ((current_pdlid == GPS_PDL_POSTSCRIPT) || (current_pdlid == GPS_PDL_PDF)){
#endif
    /*np->printable.x = pwidth - 2 * CONVERT_XONE(offset);
    np->printable.y = plength - 2 * CONVERT_YONE(offset);*/
    if(pwidth > plength){
    np->size.x = plength;
    np->size.y = pwidth;
   /* np->nominal.x = plength - 2 * CONVERT_XONE(nomoffset);
    np->nominal.y = pwidth - 2 * CONVERT_YONE(nomoffset);
    np->rotnomsize.x = plength - 2 * CONVERT_XONE(rotnomoffset);
    np->rotnomsize.y = pwidth - 2 * CONVERT_YONE(rotnomoffset);*/
    } else {
    np->size.x = pwidth;
    np->size.y = plength;
    /*np->printable.x = pwidth - 2 * CONVERT_XONE(offset);
    np->printable.y = plength - 2 * CONVERT_YONE(offset);
    np->nominal.x = pwidth - 2 * CONVERT_XONE(nomoffset);
    np->nominal.y = plength - 2 * CONVERT_YONE(nomoffset);
    np->rotnomsize.x = pwidth - 2 * CONVERT_XONE(rotnomoffset);
    np->rotnomsize.y = plength - 2 * CONVERT_YONE(rotnomoffset);*/
    }
#if (defined(EMPCL5)||defined(EMPCLXL)) && (defined(EMPOSTSCRIPT)||defined(EMPDF))
    } else{
    np->size.x = pwidth;
    np->size.y = plength;
    /*np->printable.x = pwidth - 2 * CONVERT_XONE(offset);
    np->printable.y = plength - 2 * CONVERT_YONE(offset);
    np->nominal.x = pwidth - 2 * CONVERT_XONE(nomoffset);
    np->nominal.y = plength - 2 * CONVERT_YONE(nomoffset);
    np->rotnomsize.x = pwidth - 2 * CONVERT_XONE(rotnomoffset);
    np->rotnomsize.y = plength - 2 * CONVERT_YONE(rotnomoffset);*/
	}
#endif
#else   /* RP_CUSTOMPAPERSIZE */ 
	
    np->size.x = pwidth;
    np->size.y = plength;
  /*  np->printable.x = pwidth - 2 * CONVERT_XONE(offset);
    np->printable.y = plength - 2 * CONVERT_YONE(offset);
    np->nominal.x = pwidth - 2 * CONVERT_XONE(nomoffset);
    np->nominal.y = plength - 2 * CONVERT_YONE(nomoffset);
    np->rotnomsize.x = pwidth - 2 * CONVERT_XONE(rotnomoffset);
    np->rotnomsize.y = plength - 2 * CONVERT_YONE(rotnomoffset);*/
#endif /* RP_CUSTOMPAPERSIZE */ 

    /*
    CONVERT(offset);
    CONVERT(nomoffset);
    CONVERT(rotnomoffset);*/ /* commenting as the function CONVERT() not available*/
    
    /*  The next 2 entries are NOT scaled. They get scaled when they used.
     */
    /*FIELDCOPY(HPnomoffset);
    FIELDCOPY(HProtnomoffset);*/ /* commenting as the function FIELDCOPY() not available*/

#if defined(SUPPORT_EDGE2EDGE) || defined(RXPS_EDGE_TO_EDGE)
    }
#endif

#ifdef PCL5_CUSTOMSIZE_COMMAND
#if (defined(EMPCL5)||defined(EMPCLXL)) && (defined(EMPOSTSCRIPT)||defined(EMPDF))
	if ((current_pdlid == GPS_PDL_PCL) || (current_pdlid == GPS_PDL_PCLXL)){
#endif
    if (np->printable.x <= 0)
        np->printable.x = NBITS;
    if (np->nominal.x <= 0)
        np->nominal.x = NBITS;
    if (np->rotnomsize.x <= 0)
        np->rotnomsize.x = NBITS;
    if (np->printable.y <= 0)
        np->printable.y = 1;
    if (np->nominal.y <= 0)
        np->nominal.y = 1;
    if (np->rotnomsize.y <= 0)
        np->rotnomsize.y = 1;
#if (defined(EMPCL5)||defined(EMPCLXL)) && (defined(EMPOSTSCRIPT)||defined(EMPDF))
	}
#endif
#endif /* PCL5_CUSTOMSIZE_COMMAND */

    np->OMcode = op->OMcode;
    np->PCLpaperID = op->PCLpaperID;
    np->XLpaperID = op->XLpaperID;
    np->envelope = op->envelope;
    np->noduplex = op->noduplex;

#ifdef EMPOSTSCRIPT /* RP_CUSTOMPAPERSIZE */
#if (defined(EMPCL5)||defined(EMPCLXL)) && (defined(EMPOSTSCRIPT)||defined(EMPDF))
	if ((current_pdlid == GPS_PDL_POSTSCRIPT) || (current_pdlid == GPS_PDL_PDF)){
#endif
#ifdef RP_CUSTOMPAPERSIZE
      if(pwidth > plength){
	np->PS_PageSize.x = (int)(((float)plength/xres)*72);  /* dot -> pt */
	np->PS_PageSize.y = (int)(((float)pwidth/yres)*72); /* dot -> pt */
      	}else{
	np->PS_PageSize.x = (int)(((float)pwidth/xres)*72);  /* dot -> pt */
	np->PS_PageSize.y = (int)(((float)plength/yres)*72); /* dot -> pt */
	  	}
#endif /* RP_CUSTOMPAPERSIZE */ 
#if defined(SUPPORT_EDGE2EDGE) || defined(RXPS_EDGE_TO_EDGE)
    if ( edge2edge ) {
		np->PS_printable.x = pwidth;
		np->PS_printable.y = plength;
		np->PS_margins.x = 0;
		np->PS_margins.y = 0;
    } else {
#endif /* SUPPORT_EDGE2EDGE || RXPS_EDGE_TO_EDGE */
		/*np->PS_printable.x = pwidth - 2 * CONVERT_XONE(PS_margins);
		np->PS_printable.y = plength - 2 * CONVERT_YONE(PS_margins);
		CONVERT(PS_margins);*/
#if defined(SUPPORT_EDGE2EDGE) || defined(RXPS_EDGE_TO_EDGE)
    }
#endif
#if (defined(EMPCL5)||defined(EMPCLXL)) && (defined(EMPOSTSCRIPT)||defined(EMPDF))
	}
#endif
#endif /* EMPOSTSCRIPT (RP_CUSTOMPAPERSIZE) */

    np->resolution.x = xres;
    np->resolution.y = yres;

#ifdef GPS_REJECTION
	np->Direction = op->Direction;
	np->Duplex = op->Duplex;
	np->Staple = op->Staple;
	np->RotateCollate = op->RotateCollate;
	np->StandardTray = op->StandardTray;
	np->ShiftBin = op->ShiftBin;
	np->MailBoxBin = op->MailBoxBin;
#endif /* GPS_REJECTION */

    cvtx = xres;
    cvty = yres;
    cvtw = pwidth;
    cvtl = plength;
#if defined(SUPPORT_EDGE2EDGE) || defined(RXPS_EDGE_TO_EDGE)
    set_edge2edge_custom = edge2edge;
#ifdef PCL_CUSTOM_EDGE2EDGE
	if(customEdge2Edge){
		pre_enter_lang_custom = enter_lang;
	}
#endif
#endif /* SUPPORT_EDGE2EDGE || RXPS_EDGE_TO_EDGE */

}


const PAPERINFO * PRpaperfirst(Sint32 code, int xres, int yres, int (*comp)())
{
    int nPapers;
    PAPERINFO * papers;

    papers = (PAPERINFO*)malloc(115 * sizeof(PAPERINFO));
    nPapers = PRpapertable(papers, xres, yres);
    curPaper = papers;
    endPaper = papers+nPapers;
    /*ASSERT(comp && curPaper);*/

    while (curPaper != endPaper) {
        if ((*comp)(code, curPaper) == TRUE)
            if (PrintSysGetPaperInfo(curPaper->OMcode))
            return curPaper ++;
        curPaper ++;
    }
    return (PAPERINFO *)NULL;       /* not found */
}

PAPERINFO * PRpaperinfoOriginal (PAPERCODE size, int xres, int yres)
{
	int i;
	PAPERINFO  *p, * papers;
        papers = (PAPERINFO*)malloc(115 * sizeof(PAPERINFO));
	i = PRpapertable(papers, xres, yres);

	for (p = papers; i > 0; i--, p++) {
		/*ASSERT(p);*/
		if (p->OMcode == size) {
#ifdef LONG_EDGE_FEED
		/*	For these four sizes, we have matched pairs of entries in the table,
		 *	with the short-edge version preceeding the long-edge version, such that
		 *	when we have the first one in 'p', the second is implicitly at 'p+1'.
		 *	The option that we are interrogating is normally implemented, for Core
		 *	testing, by the "-L" command-line switch; for porting/customer purposes,
		 *	this may have to be modified.  (A long-edge version of A3, for example,
		 *	is quite unlikely in a typical printer.)
		 *
		 *	Because this OM call will lock a semaphore, it is inadvisable to call
		 *	PRpaperinfo() before the Options Manager has been initialized.
		 *	If this proves to be a problem, Core can replace the option with
		 *	a simple global flag; customers might need something more elaborate.
		 */
			  if (p->OMcode == PAPERSIZE_A4 && OMGetCurrentBool(LONGEDGEFEED, OMPRINTER))
			    return (p + 1);
			   else if (p->OMcode == PAPERSIZE_LETTER && OMGetCurrentBool(LONGEDGEFEED, OMPRINTER))
			    return (p + 1);
#endif
			return p;
		}
	}
	return NULL;
return papers;
}
