#include "headerfile.h"
//#include "Images.h"
#include "Images2.h"

#define X 75
#define Y 60
#define H 40
#define W 40

extern uint8_t key;
extern uint8_t key1_0,key1_1;
extern uint8_t key2_0,key2_1;
extern uint8_t key3_0,key3_1;
extern uint8_t key4_0,key4_1;
uint32_t ms;
uint32_t random32bit;
uint32_t coin;
uint8_t n = 35;
uint8_t len = 0;
uint8_t s = 55;
uint8_t m = 59;
uint8_t h = 23;
uint8_t led = 0x01;
char text[20];
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

// 步骤3：声明所有图案数据（游戏机中常放在ROM/静态区，const只读）
static const char JACKPOT[15] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14};
static const char EYE[10]     = {1,2,3,5,6,8,9,11,12,13};
static const char BELOW[8]    = {0,1,2,3,4,6,8,12};
static const char ABOVE[8]    = {2,6,8,10,11,12,13,14};
static const char ZAG[5]      = {0,4,6,8,12};
static const char ZIG[5]      = {2,6,8,10,14};
static const char HOR_XL1[5]  = {0,1,2,3,4};
static const char HOR_XL2[5]  = {5,6,7,8,9};
static const char HOR_XL3[5]  = {10,11,12,13,14};
static const char HOR_L1[4]   = {0,1,2,3};
static const char HOR_L2[4]   = {1,2,3,4};
static const char HOR_L3[4]   = {5,6,7,8};
static const char HOR_L4[4]   = {6,7,8,9};
static const char HOR_L5[4]   = {10,11,12,13};
static const char HOR_L6[4]   = {11,12,13,14};
static const char DIAG1[3]    = {0,6,12};
static const char DIAG2[3]    = {1,7,13};
static const char DIAG3[3]    = {2,8,14};
static const char DIAG4[3]    = {2,6,10};
static const char DIAG5[3]    = {3,7,11};
static const char DIAG6[3]    = {4,8,12};
static const char VERT1[3]    = {0,5,10};
static const char VERT2[3]    = {1,6,11};
static const char VERT3[3]    = {2,7,12};
static const char VERT4[3]    = {3,8,13};
static const char VERT5[3]    = {4,9,14};
static const char HOR1[3]     = {0,1,2};
static const char HOR2[3]     = {1,2,3};
static const char HOR3[3]     = {2,3,4};
static const char HOR4[3]     = {5,6,7};
static const char HOR5[3]     = {6,7,8};
static const char HOR6[3]     = {7,8,9};
static const char HOR7[3]     = {10,11,12};
static const char HOR8[3]     = {11,12,13};
static const char HOR9[3]     = {12,13,14};

// 步骤4：初始化结构体数组，顺序与枚举值严格对应
static const Pattern g_Patterns[PATTERN_COUNT] = {
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
char result[3][5] = {{ 0, 1, 2, 3, 4},
                     { 5, 6, 7, 8, 9},
                     {10,11,12,13,14}};
char result2[15];
char had_pattern[15];
                     
u8 patIsSame(char *RESULT,const char *PATTERNS,char len)
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
u8 elementInArray(char element,char *Array,char len)
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
u8 arrayInArray(const char *array,char len_a,const char *ARRAY,char len_A)
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
u8 arrayInArrays(const char *array,char len_a,char end)
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

void start(void)
{
  int n = 0;
  for(int i = 0;i < 3;i++)
  {
    for(int j = 0;j < 5;j++)
    {
      HAL_RNG_GenerateRandomNumber(&hrng,&random32bit);
      result[i][j] = random32bit%7;
      result2[n++] = result[i][j];
    }
  }
  if(n > 14){n = 0;}  
  for(int i = 0;i < 3;i++)
  {
    for(int j = 4;j > -1;j--)
    {
      LCD_MySetDisplayWindow(X+i*50, Y+j*42, H, W);
      LCD_MyDrawPicture(PicAddrMap[result[i][4-j]+1]);
    }
  }
  coin = 0;
  char a = 0;
  if(patIsSame(result2,g_Patterns[0].arr,g_Patterns[0].len))
  {
    coin += g_Patterns[0].value;
  }
  for(int i = 1;i < PATTERN_COUNT;i++)
  {
    if(!arrayInArrays(g_Patterns[i].arr,g_Patterns[i].len,a))
    {
      if(patIsSame(result2,g_Patterns[i].arr,g_Patterns[i].len))
      {
        coin += g_Patterns[i].value;
        had_pattern[a++] = i;
      }
    }
  }
  LCD_WindowModeDisable();
  sprintf(text,"        coin:%d         ",coin);
  LCD_DisplayStringLine(Line1, (unsigned char *)text);
  sprintf(text,"     Time:%d:%d:%d         ",h,m,s);
  LCD_DisplayStringLine(Line0, (unsigned char *)text);

}  
                   
void fun_Init(void)
{
  LED_Init();
  LCD_Init();
	HAL_Delay(100);
  HAL_TIM_Base_Start_IT(&htim2);
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_SET);
  LCD_SetBackColor(Black);
  LCD_SetTextColor(White);
  LCD_Clear(Black);
  HAL_Delay(100);
  int n = 0;
  for(int i = 0;i < 3;i++)
  {
    for(int j = 0;j < 5;j++)
    {
      HAL_RNG_GenerateRandomNumber(&hrng,&random32bit);
      result[i][j] = random32bit%7;
      result2[n++] = result[i][j];
    }
  }
  for(int i = 0;i < 3;i++)
  {
    for(int j = 4;j > -1;j--)
    {
      LCD_MySetDisplayWindow(X+i*50, Y+j*42, H, W);
      LCD_MyDrawPicture(PicAddrMap[result[i][4-j]+1]);
    }
  }

}

void fun(void)
{
  LED_Show();
  LCD_Show();
  key = KEY_Scan(ms);
  if(key)
  {
    if(key == 1)
    {
      start();
    }
  }
  if(s >= 60)
  {
    s = 0;
    m++;
  }
  if(m >= 60)
  {
    m = 0;
    h++;
  }
  if(h >= 24)
  {
    h = 0;
  }
 }
void LED_Show(void)
{
    LED_Set(led);
}
void LCD_Show(void)
{
  LCD_WindowModeDisable();
  sprintf(text,"        coin:%d         ",coin);
  LCD_DisplayStringLine(Line1, (unsigned char *)text);
  sprintf(text,"     Time:%d:%d:%d         ",h,m,s);
  LCD_DisplayStringLine(Line0, (unsigned char *)text);
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if(htim->Instance == TIM2)
  {
    ms++;
     if(ms%1000 <= n*10)
    {
      led = 0x01;
    }
    else
    {
      led = 0x00;
    }

    if(ms%1000 == 0)
    {
      s++;
    }
  }
}
