#ifndef VIEW_H
#define VIEW_H

#include "../struct.h"

class View {
 public:
  virtual ~View() {};

  virtual UserAction_t getUserInput() = 0;
  virtual void render(GameInfo_t game_info) = 0;
};

#endif