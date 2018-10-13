#include "objects.h"

player[3] sort_players(player p1, player p2, player p3){
  player ret[3] = {p1,p2,p3};
  player temp;
  int i,j;
  for(i = 0; i<sizeof(ret)-1; i++){
    for(j = 0; j<sizeof(ret)-i-1; j++){
      if(ret[j]> ret[j+1]){
        temp = ret[j];
        ret[j] = ret[j+1];
        ret[j+1] = temp;
    }
  }
  return ret;
}

int main(){
  return 0;
}
