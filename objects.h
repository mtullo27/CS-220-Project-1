#include <stdio.h>

//Card structure with int rank and char suit
//rank for 
struct Card{
  int rank;
  //Spade = S = ASCII 083
  //Heart = H = ASCII 072
  //Club = C = ASCII 067
  //Diamond = D = ASCII 068
  char suit;
};
typedef struct Card card;

//Hand consists of an array of five cards, a total which is going to 
//be the designated value for the hand and a high card 
struct Hand{
  card h[5];
  int total;
};
typedef struct Hand hand;

//Has 2 cards, a hand(the best hand) the hands value and a high card
struct Player{
	card c1;
	card c2;
  card high;
  hand h;  
	int id;
	int total;
};
typedef struct Player player;

//The "river" five cards and the high card
struct Pile{
  card p[5];
};
typedef struct Pile pile;
