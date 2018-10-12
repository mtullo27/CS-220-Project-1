#include <stdio.h>

enum Card{2,3,4,5,6,7,8,9,10,J,K,Q,A};

Struct Hand{
  card h[5];
  card high;
  int total;
}

Struct Player{
  card c[2];
  hand h;
  int total;
  crad high;
}

Struct Pile{
  card p[5];
  card high;
}

#define Struct Card card;
#define Struct Hand hand;
#define Struct Player player;
#define Struct Pile pile;

player[3] sort_players(player p1, player p2, player p3);
hand get_highest(player p, pile p);
void print_results(player p1, player p2, player p3);
