#include "pattern.h"

// 步骤3：声明所有图案数据（游戏机中常放在ROM/静态区，const只读）
const char JACKPOT[15] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14};
const char EYE[10]     = {1,2,3,5,6,8,9,11,12,13};
const char BELOW[8]    = {0,1,2,3,4,6,8,12};
const char ABOVE[8]    = {2,6,8,10,11,12,13,14};
const char ZAG[5]      = {0,4,6,8,12};
const char ZIG[5]      = {2,6,8,10,14};
const char HOR_XL1[5]  = {0,1,2,3,4};
const char HOR_XL2[5]  = {5,6,7,8,9};
const char HOR_XL3[5]  = {10,11,12,13,14};
const char HOR_L1[4]   = {0,1,2,3};
const char HOR_L2[4]   = {1,2,3,4};
const char HOR_L3[4]   = {5,6,7,8};
const char HOR_L4[4]   = {6,7,8,9};
const char HOR_L5[4]   = {10,11,12,13};
const char HOR_L6[4]   = {11,12,13,14};
const char DIAG1[3]    = {0,6,12};
const char DIAG2[3]    = {1,7,13};
const char DIAG3[3]    = {2,8,14};
const char DIAG4[3]    = {2,6,10};
const char DIAG5[3]    = {3,7,11};
const char DIAG6[3]    = {4,8,12};
const char VERT1[3]    = {0,5,10};
const char VERT2[3]    = {1,6,11};
const char VERT3[3]    = {2,7,12};
const char VERT4[3]    = {3,8,13};
const char VERT5[3]    = {4,9,14};
const char HOR1[3]     = {0,1,2};
const char HOR2[3]     = {1,2,3};
const char HOR3[3]     = {2,3,4};
const char HOR4[3]     = {5,6,7};
const char HOR5[3]     = {6,7,8};
const char HOR6[3]     = {7,8,9};
const char HOR7[3]     = {10,11,12};
const char HOR8[3]     = {11,12,13};
const char HOR9[3]     = {12,13,14};

const Pattern g_Patterns[PATTERN_COUNT] = {
    [PATTERN_JACKPOT] = {"JACKPOT", JACKPOT,  10, sizeof(JACKPOT)/sizeof(JACKPOT[0])},
    [PATTERN_EYE]     = {"EYE",     EYE,       8, sizeof(EYE)/sizeof(EYE[0])},
    [PATTERN_BELOW]   = {"BELOW",   BELOW,     7, sizeof(BELOW)/sizeof(BELOW[0])},
    [PATTERN_ABOVE]   = {"ABOVE",   ABOVE,     7, sizeof(ABOVE)/sizeof(ABOVE[0])},
    [PATTERN_ZAG]     = {"ZAG",     ZAG,       4, sizeof(ZAG)/sizeof(ZAG[0])},
    [PATTERN_ZIG]     = {"ZIG",     ZIG,       4, sizeof(ZIG)/sizeof(ZIG[0])},
    [PATTERN_HOR_XL1] = {"HOR_XL1", HOR_XL1,   3, sizeof(HOR_XL1)/sizeof(HOR_XL1[0])},
    [PATTERN_HOR_XL2] = {"HOR_XL2", HOR_XL2,   3, sizeof(HOR_XL2)/sizeof(HOR_XL2[0])},
    [PATTERN_HOR_XL3] = {"HOR_XL3", HOR_XL3,   3, sizeof(HOR_XL3)/sizeof(HOR_XL3[0])},
    [PATTERN_HOR_L1]  = {"HOR_L1",  HOR_L1,    2, sizeof(HOR_L1)/sizeof(HOR_L1[0])},
    [PATTERN_HOR_L2]  = {"HOR_L2",  HOR_L2,    2, sizeof(HOR_L2)/sizeof(HOR_L2[0])},
    [PATTERN_HOR_L3]  = {"HOR_L3",  HOR_L3,    2, sizeof(HOR_L3)/sizeof(HOR_L3[0])},
    [PATTERN_HOR_L4]  = {"HOR_L4",  HOR_L4,    2, sizeof(HOR_L4)/sizeof(HOR_L4[0])},
    [PATTERN_HOR_L5]  = {"HOR_L5",  HOR_L5,    2, sizeof(HOR_L5)/sizeof(HOR_L5[0])},
    [PATTERN_HOR_L6]  = {"HOR_L6",  HOR_L6,    2, sizeof(HOR_L6)/sizeof(HOR_L6[0])},
    [PATTERN_DIAG1]   = {"DIAG1",   DIAG1,     1, sizeof(DIAG1)/sizeof(DIAG1[0])},
    [PATTERN_DIAG2]   = {"DIAG2",   DIAG2,     1, sizeof(DIAG2)/sizeof(DIAG2[0])},
    [PATTERN_DIAG3]   = {"DIAG3",   DIAG3,     1, sizeof(DIAG3)/sizeof(DIAG3[0])},
    [PATTERN_DIAG4]   = {"DIAG4",   DIAG4,     1, sizeof(DIAG4)/sizeof(DIAG4[0])},
    [PATTERN_DIAG5]   = {"DIAG5",   DIAG5,     1, sizeof(DIAG5)/sizeof(DIAG5[0])},
    [PATTERN_DIAG6]   = {"DIAG6",   DIAG6,     1, sizeof(DIAG6)/sizeof(DIAG6[0])},
    [PATTERN_VERT1]   = {"VERT1",   VERT1,     1, sizeof(VERT1)/sizeof(VERT1[0])},
    [PATTERN_VERT2]   = {"VERT2",   VERT2,     1, sizeof(VERT2)/sizeof(VERT2[0])},
    [PATTERN_VERT3]   = {"VERT3",   VERT3,     1, sizeof(VERT3)/sizeof(VERT3[0])},
    [PATTERN_VERT4]   = {"VERT4",   VERT4,     1, sizeof(VERT4)/sizeof(VERT4[0])},
    [PATTERN_VERT5]   = {"VERT5",   VERT5,     1, sizeof(VERT5)/sizeof(VERT5[0])},
    [PATTERN_HOR1]    = {"HOR1",    HOR1,      1, sizeof(HOR1)/sizeof(HOR1[0])},
    [PATTERN_HOR2]    = {"HOR2",    HOR2,      1, sizeof(HOR2)/sizeof(HOR2[0])},
    [PATTERN_HOR3]    = {"HOR3",    HOR3,      1, sizeof(HOR3)/sizeof(HOR3[0])},
    [PATTERN_HOR4]    = {"HOR4",    HOR4,      1, sizeof(HOR4)/sizeof(HOR4[0])},
    [PATTERN_HOR5]    = {"HOR5",    HOR5,      1, sizeof(HOR5)/sizeof(HOR5[0])},
    [PATTERN_HOR6]    = {"HOR6",    HOR6,      1, sizeof(HOR6)/sizeof(HOR6[0])},
    [PATTERN_HOR7]    = {"HOR7",    HOR7,      1, sizeof(HOR7)/sizeof(HOR7[0])},
    [PATTERN_HOR8]    = {"HOR8",    HOR8,      1, sizeof(HOR8)/sizeof(HOR8[0])},
    [PATTERN_HOR9]    = {"HOR9",    HOR9,      1, sizeof(HOR9)/sizeof(HOR9[0])}
};

uint8_t patIsSame(char *RESULT,const char *PATTERNS,char len)
{
  for(int i = 0;i < len-1;i++)
  {
    if(RESULT[PATTERNS[i]] != RESULT[PATTERNS[i+1]])
    {
      return 0;
    }
  }
  return 1;
}
uint8_t elementInArray(char element,char *Array,char len)
{
  for(int i = 0;i < len;i++)
  {
    if(Array[i] == element)
    {
      return 1;
    }
  }
  return 0;
}
uint8_t arrayInArray(const char *array,char len_a,const char *ARRAY,char len_A)
{
  if(len_a > len_A)
  {
    return 0;
  }
  for(int i = 0;i < len_a;i++)
  {
    for(int j = 0;j < len_A;j++)
    {
      if(array[i] == ARRAY[j])
      {
        break;
      }
      else if(j == len_A-1)
      {
        return 0;
      }
    }
  }
  return 1;
}
uint8_t arrayInArrays(const char *array,char len_a,char end)
{
  for(int i = 0;i < end;i++)
  {
    if(arrayInArray(array,len_a,g_Patterns[had_pattern[i]].arr,g_Patterns[had_pattern[i]].len))
    {
      return 1;
    }
  }
  return 0;
}

