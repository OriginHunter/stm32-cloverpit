#include "symbol.h"
#include "Images.h"


// 关键：用一个数组存所有图片的地址，下标对应上面的枚举
const uint16_t *PicAddrMap[] = {
  0x0000,
  Img_Lemon,     // PIC_LEMON (下标1) → 柠檬地址
  Img_Cherry,    // PIC_CHERRY (下标2) → 樱桃地址
  Img_Clover,    // PIC_CLOVER (下标3) → 四叶草地址
  Img_Bell,      // PIC_BELL (下标4) → 铃铛地址
  Img_Diamond,   // PIC_DIAMOND (下标5) → 钻石地址
  Img_Treasure,   // PIC_TREASURE (下标6) → 宝箱地址
  Img_Seven     // PIC_SEVEN (下标7) → 数字7地址
};
