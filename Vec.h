#pragma once

#include <array>
#include <list>
#include "Matrix.h"
#include "IndexSet.h"
typedef double mT;


class Vec
{
private:
  int size = 0;
public:
  mT * data;
  Vec();
  Vec(int size);
  Vec(const Vec &v);
  Vec& operator=(const Vec& v);
  ~Vec();

  Vec VecMulMatrix(const IndexSet& iSetV, const Matrix& m) const;
  void SetZeros();

  void Print(const char * s) const;
  void Print(const char * s, const IndexSet & rowSet) const;


  IndexSet GetPositiveInds() const;
  IndexSet ChoseNegative(const IndexSet& iSetV) const;
  IndexSet ChosePositive(const IndexSet& iSetV) const ;
  IndexSet ChoseNonPositive(const IndexSet& iSetV) const;

   int getSize() const {
    return size;
  }

   mT& operator[](size_t ind);
   mT operator[](size_t ind) const;

};

Vec operator + (const Vec &v1, const Vec &v2);
Vec operator - (const Vec &v1, const Vec &v2);
Vec operator * (const Vec &v1, mT a);
Vec operator * (mT a, const Vec &v1);
mT operator * (const Vec &v1, const Vec &v2);
