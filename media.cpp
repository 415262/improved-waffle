#include <iostream>
#include <cstring>
#include "media.h"

using namespace std;

media::media() {
  title = new char[40];
  int year = 0;
}

void media::newTitle(char* newtitle){
  title = new char[40];
  strcpy(title, newtitle);
}

void media::newYear(int newyear) {
  year = newyear;
}

char* media::getTitle() {
  return title;
}

int media::getYear() {
  return year;
}
