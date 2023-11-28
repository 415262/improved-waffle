#include <iostream>
#include <cstring>
#include "games.h"

using namespace std;

games::games() {
  publisher = new char[40];
  int rating = 0;
}

void games::newPublisher(char* newpublisher) {
  publisher = new char[40];
  strcpy(publisher, newpublisher);
}

void games::newRating(int newrating) {
  rating = 0;
  rating = newrating;
}

char* games::getPublisher() {
  return publisher;
}

int games::getRating() {
  return rating;
}
