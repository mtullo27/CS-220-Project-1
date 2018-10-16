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

//Returns 1 if hand is a flush and 0 if otherwise
int flush(hand handy){
  int i;
  int sum = 1;
  char suit1 = handy.h[0].suit;
  if(straight(handy)){
   for(i = 1; i<5; i++){
     if(handy.h[i].suit == suit1)
        sum++; 
   }
  }
  if(sum == 5)
    return 1;
  else 
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

//Returns 1 if hand is only one pair and 0 otherwise
int soloPair(hand handy){
  int i,j;
  for(i = 0; i<4; i++){
    if(handy.h[i].rank == handy.h[i+1].rank)
      return 1;
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
//Returns 1 if two pairs and 0 otherwise
int doublePair(hand handy){
  int i;
  if(soloPair(handy)){
    if(indexPair(handy) == 4 || indexPair(handy) == 5)
      return 0;
    for(i = indexPair(handy);i<4; i++){
       if(handy.h[i].rank == handy.h[i+1].rank){
         return 1;
       }
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
//puts all available cards into array and sorts it in ascending order
//first card in array is the high card
card highCard(pile piley, player playery){
  card cardy[7];
  card temp;
  int i,j,k;
  for(i = 0; i<sizeof(cardy); i++){
    if(i<5)
      cardy[i] = piley.p[i];
    else
      cardy[i] = playery.c[i-5];
  }
  for(j = 0; j<6; j++){
    for(k = 0; k<7-j-1; k++){
      if(cardy[k].rank>cardy[k+1].rank){
        temp = cardy[k];
        cardy[k] = cardy[k+1];
	cardy[k+1] = temp;
      } 
    }
  }
  return cardy[0]; 
}

int main(){
  return 0;
}
