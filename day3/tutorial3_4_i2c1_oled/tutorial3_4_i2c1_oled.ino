#include "Wire.h"
#include "OLED_Driver.h"
#include "GUI_paint.h"

uint8_t *BlackImage;

void setup() {
  //i2c1 init
  Wire1.setClock(1000000);
  Wire1.setSDA(6);
  Wire1.setSCL(7);
	Wire1.begin();
 
  uint16_t Imagesize = ((OLED_1in5_WIDTH % 2 == 0) ? (OLED_1in5_WIDTH / 2) : (OLED_1in5_WIDTH / 2 + 1)) * OLED_1in5_HEIGHT;

  //Initialize the OLED
  OLED_1in5_Init();
  OLED_1in5_Clear();
  if ((BlackImage = (uint8_t *)malloc(Imagesize)) == NULL) {
    while (1) {
      printf("Failed to apply for black memory...\r\n");
    }
  }
  printf("Paint_NewImage\r\n");
  Paint_NewImage(BlackImage, OLED_1in5_WIDTH, OLED_1in5_HEIGHT, 0, WHITE);
  Paint_SetScale(16);
  Paint_SelectImage(BlackImage);

  Paint_Clear(BLACK);
  //  
  Paint_DrawString_EN(10, 0, "GUI TEST", &Font12, WHITE, WHITE);
  Paint_DrawNum(10, 15, "123.456", &Font12, 2, WHITE, WHITE);
  Paint_DrawPoint(10, 35, WHITE, DOT_PIXEL_1X1, DOT_STYLE_DFT);
  Paint_DrawPoint(20, 35, WHITE, DOT_PIXEL_2X2, DOT_STYLE_DFT);
  Paint_DrawPoint(30, 35, WHITE, DOT_PIXEL_3X3, DOT_STYLE_DFT);
  //
  Paint_DrawLine(10, 40, 30, 40, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
  Paint_DrawLine(10, 45, 30, 45, WHITE, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);


  //
  Paint_DrawCircle(20, 55, 14, WHITE, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
  Paint_DrawRectangle(6, 41, 34, 69, WHITE, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
  Paint_DrawRectangle(10, 45, 30, 65, WHITE, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
  Paint_DrawCircle(20, 55, 10, WHITE, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
  //
  Paint_DrawRectangle(46, 41, 74, 69, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawCircle(60, 55, 14, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);

  OLED_1in5_Display(BlackImage);
  delay(2000);
}

void loop() {
  for(int i=0; i<24; i++) {
    Paint_Clear(BLACK);
    Paint_DrawRectangle(i*5, i*5, 15+i*5, 15+i*5, 0x0F, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    OLED_1in5_Display(BlackImage);
    delay(100);
  }
}
