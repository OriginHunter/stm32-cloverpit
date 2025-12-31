#include "headerfile.h"

#define X 75
#define Y 60
#define H 40
#define W 40

uint8_t key;
uint8_t key1_0 = 1,key1_1 = 1;
uint8_t key2_0 = 1,key2_1 = 1;
uint8_t key3_0 = 1,key3_1 = 1;
uint8_t key4_0 = 1,key4_1 = 1;

uint32_t ms;
uint16_t n = 500;
uint8_t s = 55;
uint8_t m = 59;
uint8_t h = 23;
uint8_t led = 0x01;
char text[20];
char result[18][5] = {{ 0, 1, 2, 3, 4},
                      { 5, 6, 7, 8, 9},
                      {10,11,12,13,14},
                      {15,16,17,18,19},
                      {20,21,22,23,24},
                      {25,26,27,28,29}};                     
char result2[15];
char had_pattern[15];
static uint32_t random32bit;
uint32_t coin;
uint16_t Image[1600*6];
 //初始化结构体数组，顺序与枚举值严格对应

uint8_t getResults(void)
{
  HAL_RNG_GenerateRandomNumber(&hrng,&random32bit);
  if(random32bit%1000 < 194){return 0;}
  if(random32bit%1000 < 388){return 1;}
  if(random32bit%1000 < 547){return 2;}
  if(random32bit%1000 < 686){return 3;}
  if(random32bit%1000 < 805){return 4;}
  if(random32bit%1000 < 924){return 5;}
  return 6;
}
void LCD_MyDrawPictureX6(const u16 *picture)
{
    int index;
    static int delay;
    LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
    for(int i = 0;i < 40*3;i += 3)
    {
      for(index = 0+i*40; index < 1600*3+i*40; index++)
      {
          LCD_WriteRAM(picture[index]);
      }
      if(delay > 120)
      HAL_Delay(delay/50);
      if(delay > 160)
      HAL_Delay(delay/10);
      delay++;
      if(delay == 200)delay = 0;
    }
}

void start(void)
{
  uint8_t n = 0;
  if(n > 14){n = 0;}  
  for(int i = 0;i < 18;i++)
  {
    for(int j = 0;j < 5;j++)
    {
      result[i][j] = getResults();
      if(i > 14)
      {
        result2[n++] = result[i][j];
      }
    }
  }
  for(int j = 0;j < 5;j++)
  {
    for(int i = 0;i < 6;i++)
    {
      memcpy(Image+1600*(i-0), PicAddrMap[result[i][j]+1], 1600*2);
    }
    LCD_MySetDisplayWindow(X+10, Y+(40*j), H*3, W);
    LCD_MyDrawPictureX6(Image);
    for(int i = 3;i < 9;i++)
    {
      memcpy(Image+1600*(i-3), PicAddrMap[result[i][j]+1], 1600*2);
    }
    LCD_MySetDisplayWindow(X+10, Y+(40*j), H*3, W);
    LCD_MyDrawPictureX6(Image);
    for(int i = 6;i < 12;i++)
    {
      memcpy(Image+1600*(i-6), PicAddrMap[result[i][j]+1], 1600*2);
    }
    LCD_MySetDisplayWindow(X+10, Y+(40*j), H*3, W);
    LCD_MyDrawPictureX6(Image);
    for(int i = 9;i < 15;i++)
    {
      memcpy(Image+1600*(i-9), PicAddrMap[result[i][j]+1], 1600*2);
    }
    LCD_MySetDisplayWindow(X+10, Y+(40*j), H*3, W);
    LCD_MyDrawPictureX6(Image);
    for(int i = 12;i < 18;i++)
    {
      memcpy(Image+1600*(i-12), PicAddrMap[result[i][j]+1], 1600*2);
    }
    LCD_MySetDisplayWindow(X+10, Y+(40*j), H*3, W);
    LCD_MyDrawPictureX6(Image);
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
  uint8_t n = 0;
  for(int i = 0;i < 18;i++)
  {
    for(int j = 0;j < 5;j++)
    {
      result[i][j] = getResults();
      if(i > 14)
      {
        result2[n++] = result[i][j];
      }
    }
  }
  for(int j = 0;j < 5;j++)
  {
    for(int i = 0;i < 6;i++)
    {
      memcpy(Image+1600*i, PicAddrMap[result[i][j]+1], 1600*2);
    }
    LCD_MySetDisplayWindow(X+10, Y+(40*j), H*3, W);
    LCD_MyDrawPictureX6(Image);
    for(int i = 3;i < 9;i++)
    {
      memcpy(Image+1600*(i-3), PicAddrMap[result[i][j]+1], 1600*2);
    }
    LCD_MySetDisplayWindow(X+10, Y+(40*j), H*3, W);
    LCD_MyDrawPictureX6(Image);
    for(int i = 6;i < 12;i++)
    {
      memcpy(Image+1600*(i-6), PicAddrMap[result[i][j]+1], 1600*2);
    }
    LCD_MySetDisplayWindow(X+10, Y+(40*j), H*3, W);
    LCD_MyDrawPictureX6(Image);
    for(int i = 9;i < 15;i++)
    {
      memcpy(Image+1600*(i-9), PicAddrMap[result[i][j]+1], 1600*2);
    }
    LCD_MySetDisplayWindow(X+10, Y+(40*j), H*3, W);
    LCD_MyDrawPictureX6(Image);
    for(int i = 12;i < 18;i++)
    {
      memcpy(Image+1600*(i-12), PicAddrMap[result[i][j]+1], 1600*2);
    }
    LCD_MySetDisplayWindow(X+10, Y+(40*j), H*3, W);
    LCD_MyDrawPictureX6(Image);
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
//  for(int i = 0;i < 3;i++)
//  {
//    for(int j = 0;j < 5;j++)
//    {
//      LCD_MySetDisplayWindow(X+i*50, Y+j*42, H, W);
//      LCD_MyDrawPicture(PicAddrMap[result[i][j]+1]);
//    }
//  }
  
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
     if(ms%1000 <= n)
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
