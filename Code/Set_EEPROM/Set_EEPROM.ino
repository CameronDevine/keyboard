#include <EEPROM.h>

struct Storage  {
  char left[11];
  char center[11];
  char right[11];
};

Storage storage;

void setup() {
  strcpy(storage.left, "left");
  strcpy(storage.center, "center");
  strcpy(storage.right, "right");
  EEPROM.put(0, storage);
}

void loop() {

}
