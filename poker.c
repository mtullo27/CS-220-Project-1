#include "objects.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


//Sorts cards in ascending order. Makes finding pairs and straights easier
void sort_cards(card *p, int size){
  int i,j;
	card temp;
  for(i = 0; i<size-1; i++){
    for(j = 0; j<size-i-1; j++){
      if(p[j].rank>p[j+1].rank){
				temp = p[j+1];
        p[j+1] = p[j];
        p[j] = temp;
      } 
    }
  }
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
  for(i = 0; i<4; i++){
    if(handy.h[i].rank == handy.h[i+1].rank)
      r = i+1;
    }
  return r;
}

//Returns value of the pairs if two pairs and 0 otherwise
int doublePair(hand handy){
  int i,high, low;
	int sum = 0;
    for(i = 0;i<4; i++){
       if(handy.h[i].rank == handy.h[i+1].rank){
				if(!low){        
					low = handy.h[i+1].rank;	
					sum++;
				}
				if(low){
					high = handy.h[i+1].rank;
					sum++;
				}
       }
    }	
		if(sum == 2){			
			return high;
		}
  return 0;
}
int doublePairHelper(hand handy){
	if(doublePair(handy)){
		if(soloPair(handy)>doublePair(handy))
			return doublePair(handy);
		else
			return soloPair(handy);
	}
	return 0;
}
//Returns 1 if a hand is a straight and 0 if otherwise.
int straight(hand handy){
  int i;
  int sum = 1;
  int start = handy.h[0].rank;
  for(i = 1; i<5; i++){
     if(handy.h[i].rank == start+i)
	sum++;
  }
  if(start == 2 && handy.h[4].rank == 14){
    sum++;
		handy.h[4].rank = 1;
		sort_cards((handy.h), 5);
	}
  if(sum == 5)
    return handy.h[0].rank;
  else 
    return 0;
}

//Returns 1 if a hand is a flush and 0 if otherwise.
int flush(hand handy){
  int i;
  int sum = 1;
  char start = handy.h[0].suit;
  for(i = 1; i<5; i++){
     if(handy.h[i].suit == start)
	sum++;
  }
  if(sum == 5)
    return handy.h[4].rank;
  else 
    return 0;
}
//Returns 1 if hand is a flush and 0 if otherwise
int straightFlush(hand handy){
  int sum = 1;
  char suit1 = handy.h[0].suit;
  if(straight(handy)){
    if(flush(handy))
       return handy.h[0].rank;
  }
  return 0;
}

//Returns 1 if hand is a royal flush and 0 if otherwise
int royalFlush(hand handy){
  if(straight(handy)){
    if(flush(handy)){
      if(handy.h[0].rank==10)
        return 10;
    }
  }
  return 0;
}

//Returns 1 if hand has four of a kind and 0 otherwise
int four(hand handy){
  if(handy.h[0].rank == handy.h[3].rank){
    return handy.h[3].rank;
  }
  if(handy.h[1].rank == handy.h[4].rank){
    return handy.h[3].rank;
  }
  else 
    return 0;
}

//Returns 1 if hand is three of a kind and 0 otherwise
int three(hand handy){
  if(handy.h[0].rank == handy.h[2].rank){
    return handy.h[1].rank;
  }
  if(handy.h[1].rank == handy.h[3].rank){
    return handy.h[2].rank;
  }
  if(handy.h[2].rank == handy.h[4].rank){
    return handy.h[3].rank;
  }
  else 
    return 0;
} 


//returns 1 if hand is full house and 0 otherwise
int fullHouse(hand handy){
  if(soloPair(handy)){
    if(three(handy)){
      return three(handy);
    }
  }
  return 0;
}
int fullHouseHelper(hand handy){
  if(soloPair(handy)){
    if(three(handy)){
      return soloPair(handy);
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
	hand handy = playery.h;
  int i,j;
  for(i = 0; i<5; i++){
      cardy[i] = piley.p[i];
  }
	cardy[5] = playery.c1;
	cardy[6] = playery.c2;
	for(i = 0; i<7; i++){
		if(soloPair(handy)){
			if(cardy[i].rank = soloPair(handy))
				cardy[i].rank = 0;
		}
		if(doublePair(handy)){ 
			if(cardy[i].rank = doublePair(handy))
				cardy[i].rank = 0;
		}
		if(three(handy)){ 
			if(cardy[i].rank = three(handy))
				cardy[i].rank = 0;
		}
		if(four(handy)){ 
			if(cardy[i].rank = four(handy))
				cardy[i].rank = 0;
		}
		if(fullHouse(handy)){ 
			if(cardy[i].rank = fullHouse(handy))
				cardy[i].rank = 0;
		}
	}
  max = cardy[0];
  for(j = 1; j<7; j++){
    if(cardy[i].rank>max.rank)
      max = cardy[i];
  }
  return max; 
}

int tieBreak(player p1, player p2){
	card high1 = p1.h.h[4];
	card high2 = p2.h.h[4];
	if(doublePair(p1.h) == doublePair(p2.h)){
		if(doublePairHelper(p1.h)>doublePairHelper(p2.h))
			return 1;
	}	
	if(fullHouse(p1.h) == fullHouse(p2.h)){
		if(fullHouseHelper(p1.h)>fullHouseHelper(p2.h)){
			return 1;
		}
	}
	if(high1.rank==high2.rank){
	high1 = p1.h.h[3];
	high2 = p2.h.h[3];
	if(high1.rank==high2.rank){
		high1 = p1.h.h[2];
		high2 = p2.h.h[2];
		if(high1.rank==high2.rank){
			high1 = p1.h.h[1];
			high2 = p2.h.h[1];
				if(high1.rank==high2.rank){
					high1 = p1.h.h[0];
					high2 = p2.h.h[0];
				}
			}
		}
	}
	if(high1.rank>high2.rank)
		return 1;	
	return 0;
}
int handBreak(hand p1, hand p2){	
	int i;
	if(doublePair(p1) == doublePair(p2)){
		if(doublePairHelper(p1)>doublePairHelper(p2))
			return 1;
	}	
	if(fullHouse(p1) == fullHouse(p2)){
		if(fullHouseHelper(p1)>fullHouseHelper(p2)){
			return 1;
		}
	}
	card high1 = p1.h[4];
	card high2 = p2.h[4];
	if(high1.rank==high2.rank){
		high1 = p1.h[3];
		high2 = p2.h[3];
		if(high1.rank==high2.rank){
			high1 = p1.h[2];
			high2 = p2.h[2];
			if(high1.rank==high2.rank){
				high1 = p1.h[1];
				high2 = p2.h[1];
					if(high1.rank==high2.rank){
						high1 = p1.h[0];
						high2 = p2.h[0];
					}
			}
		}
	}
	if(high1.rank<high2.rank){
		return 1;
	}
	for(i = 0; i<4; i++){
		if(p1.h[i].rank<p2.h[i].rank)
			return 1;
	}
	return 0;
}
//picks the best hand for a player out of 21 possible hand
void pick_hand(hand *handy, int size){
	int i,j;
	hand temp;
	for(i = 0; i<size-1; i++){
		for(j = 0; j<size-i-1; j++){
			if(handy[j].total == handy[j+1].total){
				if(handBreak(handy[j], handy[j+1])){
					temp = handy[j+1];
        	handy[j+1] = handy[j];
        	handy[j] = temp;
				}
			}
			else{
				if(handy[j].total < handy[j+1].total){
					temp = handy[j+1];
        	handy[j+1] = handy[j];
        	handy[j] = temp;
				}
			}
		}
	}
}

//this function sorts an array of players in descending order based on thier hand totals
//This is done to make output easier. First slot in array is the winner. 
void sort_players(player *players, int size){
  int i,j;
	player temp;
  for(i = 0; i<size-1; i++){
    for(j=0; j<size-i-1; j++){			
		if(players[j].total < players[j+1].total){
					temp = players[j];
					players[j] = players[j+1];
					players[j+1] = temp;
			}
			if(players[j].total == players[j+1].total){
				if(tieBreak(players[j], players[j+1])==0){
					temp = players[j];
					players[j] = players[j+1];
					players[j+1] = temp;
				}
			}
		}
  }
}




//given a hand, returns the designated value for the given hand.
// RF = 900 SF = 800 Four = 700 FH = 600 Flush = 500 S = 400 Three = 300 DP = 200 SP = 100
//returns 0 if only high card
int getValue(hand handy){
  if(straight(handy)){
    if(straightFlush(handy)){
      if(royalFlush(handy)){
        return 900;
			}
      return 800+straight(handy);
     }
  return 400+straight(handy);
  }
  if(soloPair(handy)){
    if(doublePair(handy)){
      return 200+doublePair(handy);
		}
    return 100+soloPair(handy);
  }
  if(three(handy)){
    if(fullHouse(handy)){
      return (600+fullHouse(handy));
		}
    return (300+three(handy));
  }
  if(four(handy)){
    return (700+four(handy));
  }
  if(flush(handy)){
    return (500+flush(handy));
  }
  return handy.h[4].rank;
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
	
	char game1[256];
	FILE *fp = fopen("sample_hands.txt", "r");
	FILE *fp2 = fopen("output.txt", "w+");
	int counter = 0;
	while(fgets(game1, 300, fp)) {
		player p1, p2, p3;
		pile pi;
		//changes the face cards into number values for easier comparing later
		int zed;
		int ranks[300];
		for(zed = 0; zed < 300; zed++){
			switch(game1[zed]){
				case '2':
					ranks[zed] = 2;
					break;
				case '3':
					ranks[zed] = 3;
					break;
				case '4':
					ranks[zed] = 4;
					break;
				case '5':
					ranks[zed] = 5;
					break;
				case '6':
					ranks[zed] = 6;
					break;
				case '7':
					ranks[zed] = 7;
					break;
				case '8':
					ranks[zed] = 8;
					break;
				case '9':
					ranks[zed] = 9;
					break;
				case 'T':
					ranks[zed] = 10;
					break;
				case 'J':
					ranks[zed] = 11;
					break;
				case 'Q':
					ranks[zed] = 12;
					break;
				case 'K':
					ranks[zed] = 13;
					break;
				case 'A':
					ranks[zed] = 14;
					break;
				default:
					ranks[zed] = 0;
					break;
			}
		}
		//assigns the players cards and the piles cards
		p1.c1.suit = game1[1];
		p1.c1.rank = ranks[0];
		p1.c2.suit = game1[4];
		p1.c2.rank = ranks[3];

		p2.c1.suit = game1[7];
		p2.c1.rank = ranks[6];
		p2.c2.suit = game1[10];
		p2.c2.rank = ranks[9];
		
		p3.c1.suit = game1[13];
		p3.c1.rank = ranks[12];
		p3.c2.suit = game1[16];
		p3.c2.rank = ranks[15];

		pi.p[0].suit = game1[19];
		pi.p[0].rank = ranks[18];
		pi.p[1].suit = game1[22];
		pi.p[1].rank = ranks[21];
		pi.p[2].suit = game1[25];
		pi.p[2].rank = ranks[24];
		pi.p[3].suit = game1[28];
		pi.p[3].rank = ranks[27];
		pi.p[4].suit = game1[31];
		pi.p[4].rank = ranks[30];
		
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
			sort_cards(hands1[z].h, 5);	
			hands1[z].total = getValue(hands1[z]);
			sort_cards(hands2[z].h, 5);	
			hands2[z].total = getValue(hands2[z]);
			sort_cards(hands3[z].h, 5);	
			hands3[z].total = getValue(hands3[z]);
		}			
		pick_hand(hands1, 21);
		pick_hand(hands2, 21);
		pick_hand(hands3, 21);
		p1.h = hands1[0];
		p2.h = hands2[0];
		p3.h = hands3[0];		

		p1.high = highCard(pi, p1);
		p2.high = highCard(pi, p2);
		p3.high = highCard(pi, p3);
	
		p1.h.total = getValue(p1.h);
		p2.h.total = getValue(p2.h);
		p3.h.total = getValue(p3.h);
	
		p1.id = 1;
		p2.id = 2;
		p3.id = 3;
    
		p1.total = p1.h.total;    
		p2.total = p2.h.total;
		p3.total = p3.h.total;    

		player gamey1[3] = {p1,p2,p3};
		sort_players(gamey1, 3);		

		fprintf(fp2, "%s %d %s", "Player ",  gamey1[0].id, " wins. ");
		fprintf(fp2, "\n");
	
	}		
	fclose(fp2);	
	fclose(fp);
	return 0;
}
	

	
