
#include <Arduino_GFX_Library.h>


/* More data bus class: <https://github.com/moononournation/Arduino_GFX/wiki/Data-Bus-Class> */
//Arduino_DataBus *bus = create_default_Arduino_DataBus();
Arduino_DataBus *bus = new Arduino_ESP32SPI(
  13 /* DC */, 
  5 /* CS */, 
  18 /* SCK */, 
  23 /* MOSI */, 
  GFX_NOT_DEFINED /* MISO */, 
  VSPI /* spi_num */
  );

/* More display class: <https://github.com/moononournation/Arduino_GFX/wiki/Display-Class> */
Arduino_GFX *gfx = new Arduino_ST7789(
  bus, 
  14 /* RST */, 
  1 /* rotation */, 
  true /* IPS */,
  240 /* width */, 
  320 /* height */,
  0 /* col offset 1 */, 
  0 /* row offset 1 */
  );

void setup() {
  gfx->begin();
  gfx->fillScreen(BLACK);

#ifdef GFX_BL
  pinMode(GFX_BL, OUTPUT);
  digitalWrite(GFX_BL, HIGH);
#endif

  gfx->setCursor(10, 10);
  gfx->setTextColor(RED);
  gfx->setTextSize(6 /* x scale */, 6 /* y scale */, 2 /* pixel_margin */);
  gfx->println("Hello CP IOT");
  delay(5000); // 5 seconds
}


void loop() {
  gfx->setCursor(random(gfx->width()), 20+random(gfx->height()));
  gfx->setTextColor(random(0xffff), random(0xffff));
  gfx->setTextSize(random(6) /* x scale */, random(6) /* y scale */, random(2) /* pixel_margin */);
  gfx->println("Hello CP IOT MING MING!");

  delay(1000); // 1 second 
}
