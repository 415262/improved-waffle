#ifndef GAMES_H
#define GAMES_H

#include <iostream>
#include <cstring>
#include "media.h"

using namespace std;

class games : public media {
 public:
  games();

  void newPublisher(char*);
  void newRating(int);

  char* getPublisher();
  int getRating();
 protected:
  char* publisher;
  int rating;
};

#endif
