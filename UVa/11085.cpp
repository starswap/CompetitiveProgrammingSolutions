//Fully optimised nQueens, for book 1 at least;

#include <bits/stdc++.h>
using namespace std;

vector<int> rows(9,0);
vector<vector<int>> nQueens;
int rowsUsed;
int rowColSums;
int rowColDelta;

bool canPlace(int r, int c) {
  if (rowsUsed & (1<<r))
    return false;
  if (rowColSums & (1<<(r+c)))
    return false;  
  if (rowColDelta & (1<<(r-c)))
    return false;
  return true;
}

void backtrack(int c) {
  if (c == 9)
    nQueens.push_back(rows);
  else {
    for (int r=1;r<=8;++r) {
      if (canPlace(r,c)) {
        rows[c] = r; //no need to reset this afterwards because it will be overwritten before the solution comes out.
        rowsUsed ^= 1<<r;
        rowColSums ^= 1<<(r+c);
        rowColDelta ^= 1<<(r-c);
        backtrack(c+1);
        rowColSums ^= 1<<(r+c);
        rowsUsed ^= 1<<r;
        rowColDelta ^= 1<<(r-c);        
      }
    }
  }
}

int main() {
  rowsUsed = 0;
  rowColSums = 0;
  backtrack(1); //precalculate

  vector<int> pR(9,0);
  int caseNo = 1;
  while (scanf("%d %d %d %d %d %d %d %d",&pR[1],&pR[2],&pR[3],&pR[4],&pR[5],&pR[6],&pR[7],&pR[8]) != EOF) { //for each test case 
    int bestScore = 10;
    for (vector<int> soln : nQueens) {  //try all pre-generated solutions
      int score = 0;
      for (int i=1;i<=8;++i) //score them based on number of moves
        score += (soln[i] != pR[i]);
      bestScore = min(score,bestScore); //minimum score is optimal
    }
    printf("Case %d: %d\n",caseNo,bestScore); //output
    caseNo++;
  }
          
  return 0;
}