from PIL import Image
import os

# ------------------- 匹配截图的文件名配置 -------------------
IMAGE_CONFIGS = [
    ("Bell.png", "Img_Bell2"),  # Bell.png → Img_Bell数组
    ("Cherry.png", "Img_Cherry2"),  # Cherry.png → Img_Cherry数组
    ("Clover.png", "Img_Clover2"),  # Clover.png → Img_Clover数组
    ("Diamond.png", "Img_Diamond2"),  # Diamond.png → Img_Diamond数组
    ("Lemon.png", "Img_Lemon2"),  # Lemon.png → Img_Lemon数组
    ("Seven.png", "Img_Seven2"),  # Seven.png → Img_Seven数组
    ("Treasure.png", "Img_Treasure2")  # Treasure.png → Img_Treasure数组
]
BASE_PATH = r"D:\MyCloverPit\Picture2"  # 图片目录
OUTPUT_H_FILE = r"D:\MyCloverPit\Picture2\Images2.h"  # 输出的头文件
REQUIRED_SIZE = (40, 40)  # 强制尺寸40×40
TOTAL_PIXELS = REQUIRED_SIZE[0] * REQUIRED_SIZE[1]  # 总像素数：1600


def rgb888_to_rgb565(r, g, b):
    """8位RGB转16位RGB565"""
    r_5 = (r >> 3) & 0x1F
    g_6 = (g >> 2) & 0x3F
    b_5 = (b >> 3) & 0x1F
    return (r_5 << 11) | (g_6 << 5) | b_5


def generate_single_header_file():
    # 初始化头文件内容（添加防重复包含保护）
    h_code = f"""/* Auto generated: Slot Machine Images RGB565 Header File */
/* Image size: {REQUIRED_SIZE[0]}×{REQUIRED_SIZE[1]} | Total pixels per image: {TOTAL_PIXELS} */
#ifndef __IMAGES2_H
#define __IMAGES2_H

#include "stdint.h"

// 图片尺寸宏定义（40×40）
#define IMG_WIDTH  40
#define IMG_HEIGHT 40
#define IMG_TOTAL_PIXELS {TOTAL_PIXELS}

"""

    # 逐个处理图片，生成数组
    for img_name, array_name in IMAGE_CONFIGS:
        img_path = os.path.join(BASE_PATH, img_name)
        if not os.path.exists(img_path):
            print(f"❌ Skip {img_name}: File not found")
            h_code += f"// Error: {img_name} not found!\n"
            continue

        try:
            # 打开图片并校验尺寸
            img = Image.open(img_path).convert('RGB')
            img_width, img_height = img.size
            if (img_width, img_height) != REQUIRED_SIZE:
                print(f"❌ Skip {img_name}: Size not {REQUIRED_SIZE} (current {img_width}×{img_height})")
                h_code += f"// Error: {img_name} size error (need {REQUIRED_SIZE}, got {img_width}×{img_height})!\n"
                continue

            # 转换为RGB565数组
            pixels = list(img.getdata())
            rgb565_list = [rgb888_to_rgb565(r, g, b) for (r, g, b) in pixels]

            # 生成当前图片的数组代码
            h_code += f"// {img_name} RGB565 array\n"
            h_code += f"const uint16_t {array_name}[IMG_TOTAL_PIXELS] = {{\n"

            # 格式化输出：每行10个元素，缩进+十六进制
            for idx, val in enumerate(rgb565_list):
                if idx % 40 == 0:
                    h_code += "    "
                h_code += f"0x{val:04X}, "
                if (idx + 1) % 40 == 0 or idx == len(rgb565_list) - 1:
                    h_code += "\n"

            h_code += "};\n\n"
            print(f"✅ Added {img_name} to header file")

        except Exception as e:
            print(f"❌ Error processing {img_name}: {str(e)}")
            h_code += f"// Error processing {img_name}: {str(e)}\n\n"

    # 结束头文件保护
    h_code += "#endif /* __SLOT_MACHINE_IMAGES_H */\n"

    # 写入头文件
    with open(OUTPUT_H_FILE, "w", encoding="utf-8") as f:
        f.write(h_code)

    print(f"\n✅ All done! Header file generated: {OUTPUT_H_FILE}")


if __name__ == "__main__":
    print("===== Start generating single header file =====")
    generate_single_header_file()
    print("===== Finish =====")