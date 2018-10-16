#include <stdio.h>

//split up the players cards and the communal cards

void makehands(card ca[], int n, int k, hand hands[]) {  
    int temp[k]; 
  	 int x = 0;
    makehandsHelper(ca, temp, 0, n-1, 0, k, x, hands); 
} 
void makehandsHelper(card ca[], card temp[], int start, int end, int in, int k, int x, hand) { 
	if (in == k) { 
		int i;
		for(i = 0; i<k) {
			hands[x].h[i] = temp[i];
		}
      return; 
   } 
   int i;
   for (i = start; i<=end && end-i+1>=k-in; i++){ 
       temp[in] = ca[i]; 
       makehands(ca, temp, i+1, end, in+1, k, x); 
   } 
} 

void main() {
	//reads line from file, puts it into a char array
	FILE *fp = fopen("example.txt", "r");
	char inputfile[32];
	fgets(inputfile, 32, fp);
	fclose(fp);
	player p1, p2, p3;
	pile pi;
	
	//changes the face cards into number values for easier comparing later
	int i;
	for(i = 0; i<32; i++) {
		if(c[i].equals('J')){
			c[i] = 11;
		}
		if(c[i].equals('Q')){
			c[i] = 12;
		}
		if(c[i].equals('K')){
			c[i] = 13;
		}
		if(c[i].equals('A')){
			c[i] = 14;
		}
	}
	
	//assigns the players cards and the piles cards
	p1.c[0].suit = c[0];
	p1.c[0].rank = c[1];
	p1.c[1].suit = c[3];
	p1.c[1].rank = c[4];
	
	p2.c[0].suit = c[6];
	p2.c[0].rank = c[7];
	p2.c[1].suit = c[9];
	p2.c[1].rank = c[10];
	
	p3.c[0].suit = c[12];
	p3.c[0].rank = c[13];
	p3.c[1].suit = c[15];
	p3.c[1].rank = c[16];

	pi.p[0].suit = c[18];
	pi.p[0].rank = c[19];
	pi.p[1].suit = c[21];
	pi.p[1].rank = c[22];
	pi.p[2].suit = c[24];
	pi.p[2].rank = c[25];
	pi.p[3].suit = c[27];
	pi.p[3].rank = c[28];
	pi.p[4].suit = c[30];
	pi.p[4].rank = c[31];
	
	card ca1[7] = {p1[0], p1[1], pi[0], pi[1], pi[2], pi[3], pi[4]};
	card ca2[7] = {p2[0], p2[1], pi[0], pi[1], pi[2], pi[3], pi[4]}
	card ca3[7] = {p3[0], p3[1], pi[0], pi[1], pi[2], pi[3], pi[4]}
	hand hands1[21];
	makehands(ca1, 7, 5, hands1);
	hand hands2[21];
	makehands(ca2, 7, 5, hands2);
	hand hands3[21];
	makehands(ca3, 7, 5, hands3);
	
}


 























