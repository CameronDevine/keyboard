#include <TrinketKeyboard.h>
#include <EEPROM.h>

struct Storage  {
  char left[11];
  char center[11];
  char right[11];
};

Storage storage;

void menu() {
  char button_sel;
  char text_sel[10];
  int i = 0;
  while (true) {
    if (storage.center[i] == '\0') {
      break;
    }
    else {
      backspace(1);
      i++;
    }
  }
  TrinketKeyboard.print("Entering Menu");
  while (pressed() != 'n') {
    TrinketKeyboard.poll();
  }
  backspace(13);
  TrinketKeyboard.print("Press the button you would like to change.");
  enter();
  while (pressed() == 'n')  {
    TrinketKeyboard.poll();
  }
  button_sel = pressed();
  switch (pressed())  {
    case 'l':
      TrinketKeyboard.print("left");
      break;
    case 'c':
      TrinketKeyboard.print("center");
      break;
    case 'r':
      TrinketKeyboard.print("right");
      break;
  }
  enter();
  TrinketKeyboard.print("Use the left and right buttons to select the character,\n"
  "then press the center button to confirm the selection.\n"
  "When completed select 'Done'.\n"
  "The character order is as follows:");
  enter();
  for(i=30;i<126;i++)  {
    TrinketKeyboard.print(char(i));
  }
  enter();
  enter();
  i = 0;
  int p;
  int char_i = 0;
  boolean done = false;
  while (!done)  {
    if (i == 0) {
      TrinketKeyboard.print("done");
    }
    else  {
      TrinketKeyboard.print(char(i + 31));
    }
    p = i;
    while (pressed() == 'n')  {
      TrinketKeyboard.poll();
    }
    switch (pressed())  {
      case 'l':
        i--;
        break;
      case 'r':
        i++;
        break;
      case 'c':
        if (i != 0) {
          text_sel[char_i] = char(i + 31);
          char_i++;
          i = 0;
          TrinketKeyboard.print(" ");
          if (char_i == 10) {
            text_sel[char_i] = '\0';
            done = true;
            enter();
            TrinketKeyboard.print("Maximum text length reached. ");
          }
        }
        else  {
          text_sel[char_i] = '\0';
          done = 1;
        }
    }
    while (pressed()!='n') {
      TrinketKeyboard.poll();
    }
    switch (i)  {
      case -1:
        i = 95;
        break;
      case 96:
        i = 0;
        break;
    }
    switch (p)  {
      case 0:
        backspace(4);
        break;
      default:
        backspace(1);
        break;
    }
  }
  enter();
  enter();
  TrinketKeyboard.print("Selection:  ");
  TrinketKeyboard.print(text_sel);
  enter();
  switch (button_sel)  {
    case 'l':
      strcpy(storage.left, text_sel);
      break;
    case 'c':
      strcpy(storage.center, text_sel);
      break;
    case 'r':
      strcpy(storage.right, text_sel);
      break;
  }
  EEPROM.put(0, storage);
  TrinketKeyboard.print("Saved");
}

void enter()  {
  TrinketKeyboard.pressKey(0, KEYCODE_ENTER);
  TrinketKeyboard.pressKey(0, 0);
}

void backspace(int n)  {
  for (int i = 0; i < n; i++) {
    TrinketKeyboard.pressKey(0, KEYCODE_BACKSPACE);
    TrinketKeyboard.pressKey(0, 0);
  }
}

char pressed()  {
  if (digitalRead(0)==LOW) {
    return 'l';
  }
  else if (digitalRead(1)==LOW) {
    return 'c';
  }
  else if (digitalRead(2)==LOW) {
    return 'r';
  }
  else  {
    return 'n';
  }
}

void setup() {
  digitalWrite(0,HIGH);
  digitalWrite(1,HIGH);
  digitalWrite(2,HIGH);
  EEPROM.get(0, storage);
  TrinketKeyboard.begin();
}

void loop() {
  TrinketKeyboard.poll();
  switch (pressed())  {
    case 'l':
      TrinketKeyboard.print(storage.left);
      while (pressed() == 'l') {
        TrinketKeyboard.poll();
      }
      break;
    case 'c': {
        TrinketKeyboard.print(storage.center);
        unsigned long count = millis();
        while (pressed() == 'c') {
          TrinketKeyboard.poll();
          if ((millis() - count) > 2000) {
            menu();
            break;
          }
        }
        while (pressed() == 'c') {
          TrinketKeyboard.poll();
        }
        break;
      }
    case 'r':
      TrinketKeyboard.print(storage.right);
      while (pressed() == 'r') {
        TrinketKeyboard.poll();
      }
      break;
  }
}
