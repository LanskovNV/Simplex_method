#include "SimplexSolver.h"
#include <iostream>
#include <fstream>

#define EPS 1e-6
using namespace std;


int main(void)
{
  /*
   *Read Task from file
   */
  ifstream mAstream("tasks/transp_mC.txt");
  ifstream vBstream("tasks/transp_vA.txt");
  ifstream vCstream("tasks/transp_vB.txt");

  int mArows, mAcols;
  mAstream >> mArows;
  mAstream >> mAcols;
  
  Matrix mA = Matrix(mArows, mAcols);
  for (int iRow = 0; iRow < mArows; ++iRow)
  {
    for (int iCol = 0; iCol < mAcols; ++iCol)
      mAstream >> mA[iRow][iCol];
  }
  mAstream.close();

  int vBRows;
  vBstream >> vBRows;
  Vec vB = Vec(vBRows);
  for (int iRow = 0; iRow < vBRows; ++iRow)
  {
      vBstream >> vB[iRow];
  }
  vBstream.close();

  int vCrows;
  vCstream >> vCrows;
  Vec vC = Vec(vCrows);
  for (int iRow = 0; iRow < vCrows; ++iRow)
  {
    vCstream >> vC[iRow];
  }
  vCstream.close();

  mA.Print("Default A:");
  vB.Print("Default b:");
  vC.Print("Default c:");

  /*
   * Create additional extended task to find initial X vector for original task
   */
  Matrix mAE(mA.getRowCnt(), mA.getColCnt());
  Vec vCE(mA.getColCnt() + mA.getRowCnt()),
    vBN(vB.getSize()),
    vX0E(mA.getColCnt() + mA.getRowCnt());

  SimplexSolver::ExtendTask(mA, vB, vCE, mAE, vBN, vX0E);
  mAE.Print("Ext A:");
  vCE.Print("Ext c:");
  vX0E.Print("Initial Ext BFS Vector:");


  /*
   *Solve additional extended task
   */

  Vec BasicE = SimplexSolver::Solve(vCE, mAE, vBN, vX0E);
  if (BasicE[0] == -1)
  {
    cout << " Simplex Error!" << endl;
    return 0;
  }
  //BasicE.Print("Getted Basis: ");


  // Check gotten solution to analyze domain
  for (int i = mA.getColCnt(); i < BasicE.getSize(); ++i)
  {
    if (BasicE[i] > EPS)
    {
      cout << "Domain is empty!" << endl;
      return 0;
    }
  }

  // Form initial X vector for original task
  Vec Basic(mA.getColCnt());
  for (int i = 0; i < mA.getColCnt(); ++i)
    Basic[i] = BasicE[i];

  Basic.Print("Basic");

  // Solve Original Task
  Vec FinalOpt = SimplexSolver::Solve(vC, mA, vB, Basic);

  cout << "###############################" << endl;
  cout << "_____________RESULT____________" << endl;
  cout << "###############################" << endl;
  FinalOpt.Print("Optimum: ");
  cout << "Value: " << FinalOpt * vC << endl;
  return 0;
}