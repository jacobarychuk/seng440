int A[16][16], B[16][16], diff, sad = 0;
int i, j;

for (i=0; i<16; i++) {
  for ( j=0; j<16; j++) {
    diff = A[x+i][y+j] - B[(x+r)+i][(y+s)+j];
    
    if (diff < 0) {
      sad -= diff;
    }
    else {
      sad += diff;
    }
  }
}
