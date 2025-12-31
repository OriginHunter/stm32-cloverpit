#ifndef __PATTERN_H__
#define __PATTERN_H__

#include "main.h"

extern char result[3][5];
extern char result2[15];
extern char had_pattern[15];
extern uint32_t random32bit;
extern const uint16_t *PicAddrMap[];

// 步骤1：定义枚举，封装所有图案的名称（与结构体数组下标一一对应）
// 枚举值默认从0开始递增，正好匹配结构体数组的下标
typedef enum {
    PATTERN_JACKPOT,  // 0
    PATTERN_EYE,      // 1
    PATTERN_BELOW,    // 2
    PATTERN_ABOVE,    // 3
    PATTERN_ZAG,      // 4
    PATTERN_ZIG,      // 5
    PATTERN_HOR_XL1,  // 6
    PATTERN_HOR_XL2,  // 7
    PATTERN_HOR_XL3,  // 8
    PATTERN_HOR_L1,   // 9
    PATTERN_HOR_L2,   // 10
    PATTERN_HOR_L3,   // 11
    PATTERN_HOR_L4,   // 12
    PATTERN_HOR_L5,   // 13
    PATTERN_HOR_L6,   // 14
    PATTERN_DIAG1,    // 15
    PATTERN_DIAG2,    // 16
    PATTERN_DIAG3,    // 17
    PATTERN_DIAG4,    // 18
    PATTERN_DIAG5,    // 19
    PATTERN_DIAG6,    // 20
    PATTERN_VERT1,    // 21
    PATTERN_VERT2,    // 22
    PATTERN_VERT3,    // 23
    PATTERN_VERT4,    // 24
    PATTERN_VERT5,    // 25
    PATTERN_HOR1,     // 26
    PATTERN_HOR2,     // 27
    PATTERN_HOR3,     // 28
    PATTERN_HOR4,     // 29
    PATTERN_HOR5,     // 30
    PATTERN_HOR6,     // 31
    PATTERN_HOR7,     // 32
    PATTERN_HOR8,     // 33
    PATTERN_HOR9,     // 34
    PATTERN_COUNT     // 35：标记枚举总数（方便遍历/校验）
} PatternType;

// 步骤2：定义图案结构体（游戏机风格：精简、固定类型）
typedef struct {
    const char* name;   // 图案名称（调试/显示用）
    const char* arr;    // 图案数据数组
    uint8_t value ;     // 图案倍率
    uint8_t len;        // 数组长度（用uint8_t节省内存，游戏机内存宝贵）
} Pattern;


extern const Pattern g_Patterns[PATTERN_COUNT];

uint8_t patIsSame(char *RESULT,const char *PATTERNS,char len);
uint8_t elementInArray(char element,char *Array,char len);
uint8_t arrayInArray(const char *array,char len_a,const char *ARRAY,char len_A);
uint8_t arrayInArrays(const char *array,char len_a,char end);


#endif
