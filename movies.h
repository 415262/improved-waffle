#ifndef MOVIES_H
#define MOVIES_H

#include <iostream>
#include <cstring>
#include "media.h"

using namespace std;

class movies : public media {
 public:
  movies();
  
  void newDirector(char*);
  void newDuration(int);
  void newRating(int);
  
  char* getDirector();
  int getDuration();
  int getRating();
 protected:
  char* director;
  int rating;
  int duration;
};

#endif
