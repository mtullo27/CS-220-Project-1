#include "objects.h"

player[3] sort_players(player p1, player p2, player p3){
  player ret[3] = {p1,p2,p3};
  player temp;
  int i,j;
  for(i = 0; i<sizeof(ret)-1; i++){
    for(j = 0; j<sizeof(ret)-i-1; j++){
      if(ret[j].total> ret[j+1].total){
        temp = ret[j];
        ret[j] = ret[j+1];
        ret[j+1] = temp;
    }
  }
  return ret;
}
void get_highest_card(player p, pile p){
  card c[7];
  int i
  card p[5] = pile.c;
  for(i = 0; i<5; i++){
   c[i] = p[i];
  }
  c[5] = player.c1;
  c[6] = player.c2;
  int y;
  int z;
  card temp;
  for(y = 0; y<sizeof(c)-1; y++){
    for(z = 0; z<sizeof(c)-y-1; z++){
      if(
}

int main(){
  return 0;
}
