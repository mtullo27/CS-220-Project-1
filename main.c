#include "objects.h"
#include <stdlib.h>
#include <stdio.h>

//this function sorts an array of players in descending order based on thier hand totals
//This is done to make output easier. First slot in array is the winner. 
void sort_players(player players[3]){
  player temp;
  int i,j;
  for(i = 0; i<2; i++){
    for(j=0; j<2-i; j++){
			if(players[j].total == players[j+1].total){
				if(players[j].high.rank < players[j+1].high.rank){
					temp = players[j];
          players[j] = players[j+1];
          players[j+1] = temp;
				}
			}
			else{
				if(players[j].total < players[j+1].total){
					temp = players[j];
          players[j] = players[j+1];
          players[j+1] = temp;
				}
			}
		}
  }
}
//picks the best hand for a player out of 21 possible hands
hand* pick_hand(hand handy[21]){
	int i,j;
	hand temp;
	for(i = 0; i<20; i++){
		for(j = 0; j<20-i; j++){
			if(handy[j].total == handy[j+1].total){
				if(handy[j].h[4].rank > handy[j+1].h[4].rank){
					temp = handy[j];
          handy[j] = handy[j+1];
          handy[j+1] = temp;
				}
			}
			else{
				if(handy[j].total < handy[j+1].total){
					temp = handy[j];
          handy[j] = handy[j+1];
          handy[j+1] = temp;
				}
			}
		}
	}
	return *handy[0];
}
//Sorts hand in ascending order. Makes finding pairs and straights easier
void sort_hand(hand p){
  card temp;
  int i,j;
  for(i = 0; i<4; i++){
    for(j = 0; j<5-i-1; j++){
      if(p.h[j].rank>p.h[j+1].rank){
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
	card temp;
  for(i == 1; i<5; i++){
     if(handy.h[i].rank == start+i)
	sum++;
  }
  if(start = 2 && handy.h[4].rank == 14){
    sum++;
		handy.h[4].rank = 1;
		sort_hand(handy);
	}
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
  int i,high;
  if(soloPair(handy)){
    if(indexPair(handy) == 4 || indexPair(handy) == 5)
      return 0;
    for(i = indexPair(handy);i<4; i++){
       if(handy.h[i].rank == handy.h[i+1].rank){
         high = handy.h[i].rank;
       }
    }
    if(high<soloPair(handy)){
      return soloPair(handy);}
    else{ 
      return high;
		}
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
  for(i = 0; i<5; i++){
      cardy[i] = piley.p[i];
  }
	cardy[5] = playery.c1;
	cardy[6] = playery.c2;
  max = cardy[0];
  for(j = 1; j<7; j++){
    if(cardy[i].rank>max.rank)
      max = cardy[i];
  }
  return max; 
}

//given a hand, returns the designated value for the given hand.
// RF = 900 SF = 800 Four = 700 FH = 600 Flush = 500 S = 400 Three = 300 DP = 200 SP = 100
//returns 0 if only high card
int getValue(hand handy){
  if(straight(handy)){
    if(straightFlush(handy)){
      if(royalFlush(handy))
        return 900;
      return 800+handy.h[4].rank;
     }
  return 400+handy.h[4].rank;
  }
  if(soloPair(handy)){
    if(doublePair(handy))
      return 200+doublePair(handy);
    return 100+soloPair(handy);
  }
  if(three(handy)){
    if(fullHouse(handy))
      return 600;
    return 300+handy.h[2].rank;
  }
  if(four(handy)){
    return 700+handy.h[2].rank;
  }
  if(flush(handy)){
    return 500;
  }
  return 0;
}
int count;

void makehandsHelper(card ca[], card temp[], int start, int end, int in, int k, hand hands[]) { 
	if (in == k) { 
		int i;
		for(i = 0; i<k; i++) {
			hands[count].h[i] = temp[i];
		}
		count++;
      return; 
   } 
	int i;
	for (i = start; (i<=end)&&(end-i+1>=k-in); i++){ 
		temp[in] = ca[i]; 
		makehandsHelper(ca, temp, i+1, end, in+1, k,hands); 
	} 
} 
void makehands(card ca[], int n, int k, hand hands[]) {  
	count = 0;
	card temp[k]; 
	makehandsHelper(ca, temp, 0, n-1, 0, k, hands); 
} 

int main(){
	
	char game1[33];
	FILE *fp = fopen("samplehands.txt", "r");
	//while(fgets(game1, 32, fp)!=NULL) {
 
		fgets(game1, 33, fp);
		player p1, p2, p3;
		pile pi;
		//changes the face cards into number values for easier comparing later
		int i;
		for(i = 0; i<32; i++) {
			if(game1[i]==('T')){
				game1[i] = 10;
			}
			if(game1[i]==('J')){
				game1[i] = 11;
			}
			if(game1[i]==('Q')){
				game1[i] = 12;
			}
			if(game1[i]==('K')){
				game1[i] = 13;
			}
			if(game1[i]==('A')){
				game1[i] = 14;
			}
		}
		int y;
		for(y = 0; y<32; y++) {
				printf("%c", game1[y]);
		}
		printf("\n");
		//assigns the players cards and the piles cards
		p1.c1.suit = game1[1];
		p1.c1.rank = game1[0]-'0';

		p1.c2.suit = game1[4];
		p1.c2.rank = game1[3]-'0';

		p2.c1.suit = game1[7];
		p2.c1.rank = game1[6]-'0';
		p2.c2.suit = game1[10];
		p2.c2.rank = game1[9]-'0';
		
		p3.c1.suit = game1[13];
		p3.c1.rank = game1[12]-'0';
		p3.c2.suit = game1[16];
		p3.c2.rank = game1[15]-'0';

		pi.p[0].suit = game1[19];
		pi.p[0].rank = game1[18]-'0';
		pi.p[1].suit = game1[22];
		pi.p[1].rank = game1[21]-'0';
		pi.p[2].suit = game1[25];
		pi.p[2].rank = game1[24]-'0';
		pi.p[3].suit = game1[28];
		pi.p[3].rank = game1[27]-'0';
		pi.p[4].suit = game1[31];
		pi.p[4].rank = game1[30]-'0';
		
		card ca1[7] = {p1.c1, p1.c2, pi.p[0], pi.p[1], pi.p[2], pi.p[3], pi.p[4]};
		card ca2[7] = {p2.c1, p2.c2, pi.p[0], pi.p[1], pi.p[2], pi.p[3], pi.p[4]};
		card ca3[7] = {p3.c1, p3.c2, pi.p[0], pi.p[1], pi.p[2], pi.p[3], pi.p[4]};
		hand hands1[21];
		makehands(ca1, 7, 5, hands1);
		hand hands2[21];
		makehands(ca2, 7, 5, hands2);
		hand hands3[21];
		makehands(ca3, 7, 5, hands3);
		
		int z;
		for(z = 0; z<21; z++){
			sort_hand(hands1[z]);	
			//hands1[z].total = getValue(hands1[z]);
			sort_hand(hands2[z]);
			//hands2[z].total = getValue(hands2[z]);
			sort_hand(hands3[z]);
			//hands3[z].total = getValue(hands3[z]);
		}	

		p1.h = pick_hand(hands1);
		p2.h = pick_hand(hands2);
		p3.h = pick_hand(hands3);
		
		p1.high = highCard(pi, p1);
		p2.high = highCard(pi, p2);
		p3.high = highCard(pi, p3);
	
		p1.h.total = getValue(p1.h);
		p2.h.total = getValue(p2.h);
		p3.h.total = getValue(p3.h);
	
		p1.id = 1;
		p2.id = 2;
		p3.id = 3;
		fclose(fp);
 



		printf("\n");

		player gamey1[3] = {p1,p2,p3};
		sort_players(gamey1);		
		for(i = 0; i<5; i++) {
			printf("%u ", p1.h.h[i].rank);
		}

		//FILE *fp2 = fopen("output.txt", "w+");
		//fprintf(fp2, "%s %d %s", "Player ",  gamey1[0].id, " wins.");
		//fclose(fp2);
		return 0;
	
}
	

	
