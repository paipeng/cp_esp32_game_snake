
#include <Arduino_GFX_Library.h>

#define VRX 32
#define VRY 33
#define BUTTON 35

#define SCREEN_ROTATE 1
#define SCREE_WIDTH 240
#define SCREE_HEIGHT 320


int coordination_x = 0;
int coordination_y = 0;
#define SNAKE_SIZE 20

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
  SCREEN_ROTATE /* rotation */, 
  true /* IPS */,
  SCREE_WIDTH /* width */, 
  SCREE_HEIGHT /* height */,
  0 /* col offset 1 */, 
  0 /* row offset 1 */
  );



void readAnalog() {
  // x,y: 0-4095 (right - left; center 2877)
  // k: 1 unpressed; 0: pressed
  int x = analogRead(VRX);
  int y = analogRead(VRY);
  int k = digitalRead(BUTTON);
#if 0
  Serial.print("Joystick: ");
  Serial.printf("x: %4d y: %4d button: %d", x, y, k);
  Serial.println("");
#endif
  int move_x = 0;
  int move_y = 0;
  if (x > 3500) {
    move_x = -1;
  } else if (x < 1000) {
    move_x = 1;
  }
  if (y > 3500) {
    move_y = -1;
  } else if (y < 1000) {
    move_y = 1;
  }
  if (move_x != 0 || move_y != 0) {
    move_snake(move_x, move_y);
  }
}

int get_screen_width() {
#if 0
  if (SCREE_HEIGHT == 1) {
    return SCREE_HEIGHT;
  } else {
    return SCREE_WIDTH;
  }
#else
  return SCREE_WIDTH;
#endif
}

int get_screen_height() {
#if 0
  if (SCREE_HEIGHT == 1) {
    return SCREE_WIDTH;
  } else {
    return SCREE_HEIGHT;
  }
#else
  return SCREE_HEIGHT;
#endif
}

void init_snake() {
  gfx->fillScreen(BLACK);
  gfx->setCursor(10, 10);
  gfx->setTextColor(RED);
  gfx->setTextSize(6 /* x scale */, 6 /* y scale */, 2 /* pixel_margin */);
  gfx->println("CP-SNAKE");

  gfx->fillRect(coordination_x, coordination_y, SNAKE_SIZE, SNAKE_SIZE, RED);
}


void move_snake(int x, int y) {
  if (x > 0 && coordination_x < (get_screen_height() - SNAKE_SIZE)) {
    coordination_x++;
  } else if (x < 0 && coordination_x > 0) {
    coordination_x--;
  }
  if (y > 0 && coordination_y < (get_screen_width() - SNAKE_SIZE)) {
    coordination_y++;
  } else if (y < 0 && coordination_y > 0) {
    coordination_y--;
  }
  gfx->fillScreen(BLACK);
  gfx->fillRect(coordination_x, coordination_y, SNAKE_SIZE, SNAKE_SIZE, RED);

}


void setup() {

  Serial.begin(115200);
  // init joystick
  pinMode(BUTTON, INPUT);

  gfx->begin();
  gfx->fillScreen(BLACK);

#ifdef GFX_BL
  pinMode(GFX_BL, OUTPUT);
  digitalWrite(GFX_BL, HIGH);
#endif
  
  coordination_x = get_screen_height()/2;
  coordination_y = get_screen_width()/2;

  init_snake();

  delay(5000); // 5 seconds
}


void loop() {
#if 0
  gfx->setCursor(random(gfx->width()), 20+random(gfx->height()));
  gfx->setTextColor(random(0xffff), random(0xffff));
  gfx->setTextSize(random(6) /* x scale */, random(6) /* y scale */, random(2) /* pixel_margin */);
  gfx->println("Hello CP IOT MING MING!");

  delay(1000); // 1 second 
#else
  
  readAnalog();
  delay(10);
#endif
}
