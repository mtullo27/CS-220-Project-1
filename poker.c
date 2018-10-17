#include "objects.h"

//this function sorts an array of players in descending order based on thier hand totals
//This is done to make output easier. First slot in array is the winner. 
void sort_players(player players[3]){
  player temp;
  int i,j;
  for(i = 0; i<2; i++){
    for(j = 0; j<3-i-1; j++){
      if(players[j].total> players[j+1].total){
        temp = players[j];
        players[j] = players[j+1];
        players[j+1] = temp;
      }
    }
  }
}

//Sorts hand in ascending order. Makes finding pairs and straights easier
void sort_hand(hand p){
  card temp;
  int i,j;
  for(i = 0; i<4; i++){
    for(j = 0; j<5-i-1; j++){
      if(p.h[j].rank<p.h[j+1].rank){
        temp = p.h[j];
        p.h[j] = p.h[j+1];
	p.h[j+1] = temp;
      } 
    }
  }
}

//Returns 1 if a hand is a straight and 0 if otherwise.
int straight(hand handy){
  int i;
  int sum = 1;
  int start = handy.h[0].rank;
  for(i == 1; i<5; i++){
     if(handy.h[i].rank == start+i)
	sum++;
  }
  if(start = 2 && handy.h[4].rank == 14)
    sum++;
  if(sum == 5)
    return 1;
  else 
    return 0;
}

//Returns 1 if a hand is a flush and 0 if otherwise.
int flush(hand handy){
  int i;
  int sum = 1;
  char start = handy.h[0].suit;
  for(i == 1; i<5; i++){
     if(handy.h[i].suit == start)
	sum++;
  }
  if(sum == 5)
    return 1;
  else 
    return 0;
}
//Returns 1 if hand is a flush and 0 if otherwise
int straightFlush(hand handy){
  int i;
  int sum = 1;
  char suit1 = handy.h[0].suit;
  if(straight(handy)){
    if(flush(handy))
       return 1;
  }
  return 0;
}

//Returns 1 if hand is a royal flush and 0 if otherwise
int royalFlush(hand handy){
  if(straight(handy)){
    if(flush(handy)){
      if(handy.h[0].rank==10)
        return 1;
    }
  }
  return 0;
}

//Returns 1 if hand has four of a kind and 0 otherwise
int four(hand handy){
  if(handy.h[0].rank == handy.h[3].rank){
    return 1;
  }
  if(handy.h[1].rank == handy.h[4].rank){
    return 1;
  }
  else 
    return 0;
}

//Returns 1 if hand is three of a kind and 0 otherwise
int three(hand handy){
  if(handy.h[0].rank == handy.h[2].rank){
    return 1;
  }
  if(handy.h[1].rank == handy.h[3].rank){
    return 1;
  }
  if(handy.h[2].rank == handy.h[4].rank){
    return 1;
  }
  else 
    return 0;
} 

//Returns value of pair if hand is only one pair and 0 otherwise
int soloPair(hand handy){
  int i;
  for(i = 0; i<4; i++){
    if(handy.h[i].rank == handy.h[i+1].rank)
      return handy.h[i].rank;
  }
  return 0;
}
//returns last occurance of the rank in a pair to make finding double pairs easier
//also makes finding highest pair easier
int indexPair(hand handy){
  int r,i;
  if(soloPair(handy)){
  for(i = 0; i<4; i++){
    if(handy.h[i].rank == handy.h[i+1].rank)
      r = i+1;
    }
  }
  return r;
}

//Returns higher value of the pairs if two pairs and 0 otherwise
int doublePair(hand handy){
  int i,int high;
  if(soloPair(handy)){
    if(indexPair(handy) == 4 || indexPair(handy) == 5)
      return 0;
    for(i = indexPair(handy);i<4; i++){
       if(handy.h[i].rank == handy.h[i+1].rank){
         high = handy.h[i].rank;
       }
    }
    if(high<soloPair(handy))
      return soloPair(handy))
    else 
      return high;
  }
  return 0;
}

//returns 1 if hand is full house and 0 otherwise
int fullHouse(hand handy){
  if(soloPair(handy)){
    if(three(handy)){
      return 1;
    }
  }
  return 0;
}

//finds the high card for a player given a player and the pile
//puts all cards player can have into an array and finds the highest
//rank of all the cards
card highCard(pile piley, player playery){
  card cardy[7];
  card max;
  int i,j;
  for(i = 0; i<sizeof(cardy); i++){
    if(i<5)
      cardy[i] = piley.p[i];
    else
      cardy[i] = playery.c[i-5];
  }
  max = cardy[0];
  for(j = 1; j<7; j++){
    if(cardy[i].rank>max.rank)
      max = cardy[i];
  }
  return max; 
}

//given a hand, returns the designated value for the given hand.
// RF = 135 SF = 120 Four = 105 FH = 90 Flush = 75 S = 60 Three = 45 DP = 30 SP = 15
//returns 0 if only high card
int getValue(player playery){
  hand handy = playery.h;
  if(straight(handy)){
    if(straightFlush(handy)){
      if(royalFlush(handy))
        return 135;
      return 120;
     }
  return 60;
  }
  if(soloPair(handy)){
    if(doublePair(handy))
      return 30+doublePair(handy);
    return 15+soloPair(handy);
  }
  if(three(handy)){
    if(fullHouse(handy))
      return 90;
    return 45;
  }
  if(four(handy)){
    return 105;
  }
  if(flush(handy)){
    return 75;
  }
  return 0;
}

int main(){
  return 0;
}
