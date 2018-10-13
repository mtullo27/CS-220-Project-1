#include <stdio.h>

//enumerator sets value for different cards
//2 is 1, 3 is 2, 4 is 3 ect
//suit is set to a chat
Struct Card{
  enum {2,3,4,5,6,7,8,9,10,J,K,Q,A}cards;
  char suit;
//Hand consists of an array of five cards, a total which is going to 
//be the designated value for the hand and a high card 
Struct Hand{
  card h[5];
  int total;
}

//Has 2 cards, a hand(the best hand) the hands value and a high card
Struct Player{
  card c[2];
  hand h;
  int total;
  card high;
}

//The "river" five cards and the high card
Struct Pile{
  card p[5];
}

//define for the structures
#define Struct Card card;
#define Struct Hand hand;
#define Struct Player player;
#define Struct Pile pile;

//sorts the players into an array(highest value to lowest value) to make
//output easier
player[3] sort_players(player p1, player p2, player p3);

//determines the best hand for a given player
void get_hand(player p, pile p);

//returns the high card for a given player.
void get_high_card(player p, pile p);

//to make the output for each match
void print_results(player p1, player p2, player p3);
