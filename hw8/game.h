#ifndef GAME_H
#define GAME_H
#include "gba.h"
#define REG_DISPCTL *(unsigned short *)0x4000000
//----------------------------------------------------------------
//                       Box struct
//----------------------------------------------------------------
typedef struct box {
   int width;
   int length;
   int row;
   int col;
   int color;
} BOX;

typedef enum {
  START,
  PLAY,
  TEST1,
  TEST2,
  WIN,
  LOSE,
} GBAState;
//----------------------------------------------------------------
//                    functions may need
//----------------------------------------------------------------
void displayResetInfor(void);
void delay(int n);
void resetFunction(void);

#endif
