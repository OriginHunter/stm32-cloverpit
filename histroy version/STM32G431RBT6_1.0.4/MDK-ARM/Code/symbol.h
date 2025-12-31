#ifndef __SYMBOL_H__
#define __SYMBOL_H__

#include "stdint.h"

#define IMG_WIDTH  40
#define IMG_HEIGHT 40
#define IMG_TOTAL_PIXELS 1600

extern const uint16_t Img_Lemon[IMG_TOTAL_PIXELS];
extern const uint16_t Img_Cherry[IMG_TOTAL_PIXELS];
extern const uint16_t Img_Clover[IMG_TOTAL_PIXELS];
extern const uint16_t Img_Bell[IMG_TOTAL_PIXELS];
extern const uint16_t Img_Diamond[IMG_TOTAL_PIXELS];
extern const uint16_t Img_Treasure[IMG_TOTAL_PIXELS];
extern const uint16_t Img_Seven[IMG_TOTAL_PIXELS];
extern const uint16_t *PicAddrMap[];
// 枚举：把7个图片映射成易记的名字（不用记Img_Bell这种长名）

typedef enum {
  PIC_LEMON = 1,     // 对应柠檬图片
  PIC_CHERRY,    // 对应樱桃图片
  PIC_CLOVER,    // 对应四叶草图片
  PIC_BELL,      // 对应铃铛图片
  PIC_DIAMOND,   // 对应钻石图片
  PIC_TREASURE ,  // 对应宝箱图片
  PIC_SEVEN     // 对应数字7图片
} PicType;


#endif /* __SLOT_MACHINE_IMAGES_H */
