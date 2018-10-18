#include "objects.h"

//this function sorts an array of players in descending order based on thier hand totals
//This is done to make output easier. First slot in array is the winner. 
void sort_players(player players[3]){
  player temp;
  int i,j;
  for(i = 0; i<2; i++){
    for(j=0; j<2-i; j++){
			if(players[j].total == players[j+1].total){
				if(players[j].h.h[0].rank>players[j+1].h.h[0].rank){
					temp = players[j];
          players[j] = players[j+1];
          players[j+1] = temp;
				}
			}
			else{
				if(players[j].total > players[j+1].total){
					temp = players[j];
          players[j] = players[j+1];
          players[j+1] = temp;
				}
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
      return high;}
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
// RF = 900 SF = 800 Four = 700 FH = 600 Flush = 500 S = 400 Three = 300 DP = 200 SP = 100
//returns 0 if only high card
int getValue(player playery){
  hand handy = playery.h;
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

void makehandsHelper(card ca[], card temp[], int start, int end, int in, int k, hands) { 
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
		makehands(ca, temp, i+1, end, in+1, k,hands); 
	} 
} 
void makehands(card ca[], int n, int k, hand hands[]) {  
	count = 0;
	card temp[k]; 
	makehandsHelper(ca, temp, 0, n-1, 0, k, hands); 
} 
int main(){
	char game1[32];
	char game2[32];
	char game3[32];
	FILE *fp = fopen("example.txt", "r");
	fgets(game1, 32, fp);
	fgets(game2, 32, fp);
	fgets(game3, 32, fp);
	fclose(fp);
	player p1, p2, p3, p4, p5, p6, p7, p8, p9;
	pile pi, pi2, pi3;
	//changes the face cards into number values for easier comparing later
	int i;
	for(i = 0; i<32; i++) {
		if(game1[i].equals('J')){
			game1[i] = '11';
		}
		if(game1[i].equals('Q')){
			game1[i] = '12';
		}
		if(game1[i].equals('K')){
			game1[i] = '13';
		}
		if(game1[i].equals('A')){
			game1[i] = '14';
		}
	}
	for(i = 0; i<32; i++) {
		if(game2[i].equals('J')){
			game2[i] = '11';
		}
		if(game2[i].equals('Q')){
			game2[i] = '12';
		}
		if(game2[i].equals('K')){
			game2[i] = '13';
		}
		if(game2[i].equals('A')){
			game2[i] = '14';
		}
	}
	for(i = 0; i<32; i++) {
		if(game3[i].equals('J')){
			game3[i] = '11';
		}
		if(game3[i].equals('Q')){
			game3[i] = '12';
		}
		if(game3[i].equals('K')){
			game3[i] = '13';
		}
		if(game3[i].equals('A')){
			game3[i] = '14';
		}
	}

	//assigns the players cards and the piles cards
	p1.c[0].suit = game1[0];
	p1.c[0].rank = game1[1];
	p1.c[1].suit = game1[3];
	p1.c[1].rank = game1[4];
	
	p2.c[0].suit = game1[6];
	p2.c[0].rank = game1[7];
	p2.c[1].suit = game1[9];
	p2.c[1].rank = game1[10];
	
	p3.c[0].suit = game1[12];
	p3.c[0].rank = game1[13];
	p3.c[1].suit = game1[15];
	p3.c[1].rank = game1[16];

	pi.p[0].suit = game1[18];
	pi.p[0].rank = game1[19];
	pi.p[1].suit = game1[21];
	pi.p[1].rank = game1[22];
	pi.p[2].suit = game1[24];
	pi.p[2].rank = game1[25];
	pi.p[3].suit = game1[27];
	pi.p[3].rank = game1[28];
	pi.p[4].suit = game1[30];
	pi.p[4].rank = game1[31];
	
	card ca1[7] = {p1[0], p1[1], pi[0], pi[1], pi[2], pi[3], pi[4]};
	card ca2[7] = {p2[0], p2[1], pi[0], pi[1], pi[2], pi[3], pi[4]};
	card ca3[7] = {p3[0], p3[1], pi[0], pi[1], pi[2], pi[3], pi[4]};
	hand hands1[21];
	makehands(ca1, 7, 5, hands1);
	hand hands2[21];
	makehands(ca2, 7, 5, hands2);
	hand hands3[21];
	makehands(ca3, 7, 5, hands3);
	
	p4.c[0].suit = game2[0];
	p4.c[0].rank = game2[1];
	p4.c[1].suit = game2[3];
	p4.c[1].rank = game2[4];
	
	p5.c[0].suit = game2[6];
	p5.c[0].rank = game2[7];
	p5.c[1].suit = game2[9];
	p5.c[1].rank = game2[10];
	
	p6.c[0].suit = game2[12];
	p6.c[0].rank = game2[13];
	p6.c[1].suit = game2[15];
	p6.c[1].rank = game2[16];

	pi2.p[0].suit = game2[18];
	pi2.p[0].rank = game2[19];
	pi2.p[1].suit = game2[21];
	pi2.p[1].rank = game2[22];
	pi2.p[2].suit = game2[24];
	pi2.p[2].rank = game2[25];
	pi2.p[3].suit = game2[27];
	pi2.p[3].rank = game2[28];
	pi2.p[4].suit = game2[30];
	pi2.p[4].rank = game2[31];
	
	card ca4[7] = {p4[0], p4[1], pi2[0], pi2[1], pi2[2], pi2[3], pi2[4]};
	card ca5[7] = {p5[0], p5[1], pi2[0], pi2[1], pi2[2], pi2[3], pi2[4]};
	card ca6[7] = {p6[0], p6[1], pi2[0], pi2[1], pi2[2], pi2[3], pi2[4]};
	hand hands4[21];
	makehands(ca4, 7, 5, hands4);
	hand hands5[21];
	makehands(ca5, 7, 5, hands5);
	hand hands6[21];
	makehands(ca6, 7, 5, hands6);
	
	p7.c[0].suit = game3[0];
	p7.c[0].rank = game3[1];
	p7.c[1].suit = game3[3];
	p7.c[1].rank = game3[4];
	
	p8.c[0].suit = game3[6];
	p8.c[0].rank = game3[7];
	p8.c[1].suit = game3[9];
	p8.c[1].rank = game3[10];
	
	p9.c[0].suit = game3[12];
	p9.c[0].rank = game3[13];
	p9.c[1].suit = game3[15];
	p9.c[1].rank = game3[16];

	pi3.p[0].suit = game3[18];
	pi3.p[0].rank = game3[19];
	pi3.p[1].suit = game3[21];
	pi3.p[1].rank = game3[22];
	pi3.p[2].suit = game3[24];
	pi3.p[2].rank = game3[25];
	pi3.p[3].suit = game3[27];
	pi3.p[3].rank = game3[28];
	pi3.p[4].suit = game3[30];
	pi3.p[4].rank = game3[31];
	
	card ca7[7] = {p7[0], p7[1], pi3[0], pi3[1], pi3[2], pi3[3], pi3[4]};
	card ca8[7] = {p8[0], p8[1], pi3[0], pi3[1], pi3[2], pi3[3], pi3[4]};
	card ca9[7] = {p9[0], p9[1], pi3[0], pi3[1], pi3[2], pi3[3], pi3[4]};
	hand hands7[21];
	makehands(ca7, 7, 5, hands7);
	hand hands8[21];
	makehands(ca8, 7, 5, hands8);
	hand hands9[21];
	makehands(ca9, 7, 5, hands9);
	int z;
	for(z = 0; z<21; z++){
		sort_Hand(hands1[z]);	
		sort_Hand(hands2[z]);
		sort_Hand(hands3[z]);
		sort_Hand(hands4[z]);
		sort_Hand(hands5[z]);
		sort_Hand(hands6[z]);
		sort_Hand(hands7[z]);
		sort_Hand(hands8[z]);
		sort_Hand(hands9[z]);
	}	
	p1.h = pick_hand(hands1);
	p2.h = pick_hand(hands2);
	p3.h = pick_hand(hands3);
	p4.h = pick_hand(hands4);
	p5.h = pick_hand(hands5);
	p6.h = pick_hand(hands6);
	p7.h = pick_hand(hands7);
	p8.h = pick_hand(hands8);
	p9.h = pick_hand(hands9);
	
	p1.high = p1.hand.h[4];
	p2.high = p2.hand.h[4];
	p3.high = p3.hand.h[4];
	p4.high = p4.hand.h[4];
	p5.high = p5.hand.h[4];
	p6.high = p6.hand.h[4];
	p7.high = p7.hand.h[4];
	p8.high = p8.hand.h[4];
	p9.high = p9.hand.h[4];

	p1.hand.total = getValue(p1.hand);
	p2.hand.total = getValue(p2.hand);
	p3.hand.total = getValue(p3.hand);
	p4.hand.total = getValue(p4.hand);
	p5.hand.total = getValue(p5.hand);
	p6.hand.total = getValue(p6.hand);
	p7.hand.total = getValue(p7.hand);
	p8.hand.total = getValue(p8.hand);
	p9.hand.total = getValue(p9.hand);
	
	p1.id = 1;
	p4.id = 1;
	p7.id = 1;
	p2.id = 2;
	p5.id = 2;
	p8.id = 2;
	p3.id = 3;
	p6.id = 3;
	p9.id = 9;
	
	card cardy;
  card cardy2;
  card cardar[2] = {cardy, cardy2};
  hand handy;
	player p1;
	player p2;
  player p3;
	p1 = (player){.c=cardar, .h=handy, .total=300, .high=cardy};
  p2 = (player){.c=cardar, .h=handy, .total=450, .high=cardy};
  p3 = (player){.c=cardar, .h=handy, .total=100, .high=cardy};
	player players[3] = {p1, p2, p3};
	int i;
	for(i=0;i<2;i++){
		printf("%u\n", players[i].total);
	}
  return 0;
}
