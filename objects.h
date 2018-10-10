#include <stdio.h>

Struct Card{
  char c;
  int val;
}

Struct Hand{
  card h[5];
  card high;
  int total;
}

Struct Player{
  card c1;
  card c2;
  card high;
  hand h;
  int total;
}

Struct Pile{
  card p[5];
  card high;
}

#define Struct Card card;
#define Struct Hand hand;
#define Struct Player player;
#define Struct Pile pile;
