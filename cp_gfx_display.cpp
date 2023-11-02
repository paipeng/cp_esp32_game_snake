#include "cp_gfx_display.h"

CPGFXDisplay::CPGFXDisplay():bus(NULL), gfx(NULL) {
  bus = new Arduino_ESP32SPI(
    TFT_DC, 
    TFT_CS /* CS */, 
    TFT_SCK /* SCK */, 
    TFT_MOSI /* MOSI */, 
    GFX_NOT_DEFINED /* MISO */, 
    VSPI /* spi_num */
    );
  gfx = new Arduino_ST7789(
    bus, 
    TFT_RST /* RST */, 
    TFT_SCREEN_ROTATE /* rotation */, 
    true /* IPS */,
    TFT_SCREE_WIDTH /* width */, 
    TFT_SCREE_HEIGHT /* height */,
    0 /* col offset 1 */, 
    0 /* row offset 1 */
    );
  gfx->begin();

#ifdef GFX_BL
  pinMode(GFX_BL, OUTPUT);
  digitalWrite(GFX_BL, HIGH);
#endif 
}

void CPGFXDisplay::init() {
  gfx->fillScreen(BLACK);
  gfx->setCursor(10, 10);
  gfx->setTextColor(RED);
  gfx->setTextSize(6 /* x scale */, 6 /* y scale */, 2 /* pixel_margin */);
  gfx->println("CP-SNAKE");
}

void CPGFXDisplay::update_draw(snake_point* spoints, cp_point p) {
  gfx->fillRect(p.x, p.y, SNAKE_SIZE, SNAKE_SIZE, RED);
}

cp_size CPGFXDisplay::get_size() {
  return (cp_size){TFT_SCREE_HEIGHT, TFT_SCREE_WIDTH};
}