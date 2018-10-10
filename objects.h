#include <stdio.h>

Struct card{
  char c;
  int val;
}

Struct hand{
  card a;
  card b;
  card c;
  card d;
  card e;
  int total;
}

Struct player{
  card c1;
  card c2;
  hand h;
  int total;
}

Struct pile{
  card a;
  card b;
  card c; 
  card d;
  card e;
}
