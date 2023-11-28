#include <iostream>
#include <cstring>
#include "movies.h"

using namespace std;

movies::movies() {
  director = new char[40];
  int rating = 0;
  int duration = 0;
};

void movies::newDirector(char* newdirector) {
  director = new char[40];
  strcpy(director, newdirector);
};

void movies::newRating(int newrating) {
  rating = 0;
  rating = newrating;
}

void movies::newDuration(int newduration) {
  duration = 0;
  duration = newduration;
}

char* movies::getDirector() {
  return director;
}

int movies::getRating() {
  return rating;
}

int movies::getDuration() {
  return duration;
}
