#ifndef MEDIA_H
#define MEDIA_H

#include <iostream>
#include <cstring>

class media {
 public:
  media();

  void newTitle(char*);
  void newYear(int);
  
  char* getTitle();
  int getYear();
 protected:
  char* title;
  int year;

};

#endif
