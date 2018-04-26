#pragma once

#include "IndexSet.h"

typedef double mT;
class Matrix
{
private:
  int row = 0 , col = 0;
public:
  mT ** data;

  Matrix();
  Matrix(const Matrix& m);
  Matrix(int row_, int col_);
  ~Matrix();
  Matrix& operator=(const Matrix& m);

  Matrix getInvertible(const IndexSet& iSetRows, const IndexSet& iSetCols) const;


  Matrix  MatrixMulMatrix(const IndexSet& iSetRowsA,const IndexSet& iSetColsB, const Matrix& mB) const;

  void Print(const char * s) const;
  void Print(const char * s, const IndexSet & ColSet) const;

  bool FullRang(const IndexSet& iSetRows, const IndexSet& iSetCols) const;


  mT* operator[](size_t ind);
  const mT*  operator[](size_t ind) const;

  int getRowCnt() const
  {
    return row;
  }
  int getColCnt()const
  {
    return col;
  }
};


Matrix operator*(const Matrix& m1, const Matrix& m2);

