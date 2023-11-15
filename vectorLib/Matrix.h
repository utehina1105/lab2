#pragma once
#include <Vector.h>

const int MAX_MATRIX_SIZE = 10000;

template <class T>
class TDynamicMatrix : public TDynamicVector<TDynamicVector<T>>
{
public:
  TDynamicMatrix(int l = 1);
  TDynamicMatrix(const TDynamicMatrix<T>& p);
  TDynamicMatrix(const TDynamicVector<TDynamicVector<T>>& p);
  ~TDynamicMatrix();
  TDynamicMatrix<T> operator+(const TDynamicMatrix<T>& p);
  TDynamicMatrix<T> operator-(const TDynamicMatrix<T>& p);
  TDynamicMatrix<T> operator*(const TDynamicMatrix<T>& p);

  TDynamicVector<T> operator*(const TDynamicVector<T>& p);
  TDynamicVector<T> operator*(const T& val);

  TDynamicMatrix<T>& operator=(const TDynamicMatrix<T>& p);
  TDynamicMatrix<T>& operator=(const TDynamicVector<TDynamicVector<T>>& p);

  bool operator==(const TDynamicMatrix<T>& p) const noexcept;
  bool operator!=(const TDynamicMatrix<T>& p);
  TDynamicVector<T>& operator[](int i);

  friend std::ostream& operator<<(std::ostream& a, TDynamicMatrix<T>& p) {
    for (int i = 0; i < p.sz; i++) {
      for (int j = 0; j < p.sz; j++)
        a << p[i][j] << " ";
      a << "\n";
    }
    return a;
  }
  friend std::istream& operator>>(std::istream& a, TDynamicMatrix<T>& p) {
    int l = 0;
    a >> l;
    p = TDynamicMatrix<T>(l);
    for (int i = 0; i < l; i++)
      for (int j = 0; j < l; j++)
        a >> p[i][j];
    return a;
  }
};

template<class T>
inline TDynamicMatrix<T>::TDynamicMatrix(int l = 1): TDynamicVector<TDynamicVector<T>>(l)
{
  if (l > MAX_MATRIX_SIZE)
    throw "size is under MAX_MATRIX_SIZE";
  for (int i = 0; i < sz; i++)
    pMem[i] = TDynamicVector<T>(sz);
}


template<class T>
inline TDynamicMatrix<T>::TDynamicMatrix(const TDynamicMatrix<T>& p)
{
  this->sz = p.sz;
  if (p.pMem == 0)
    this->pMem = 0;
  else {
    this->pMem = new TDynamicVector<T>[sz];
    for (int i = 0; i < sz; i++)
      this->pMem[i] = p.pMem[i];
  }
}

template<class T>
inline TDynamicMatrix<T>::TDynamicMatrix(const TDynamicVector<TDynamicVector<T>>& p) :TDynamicVector<TDynamicVector<T>>(p)
{
}

template<class T>
inline TDynamicMatrix<T>::~TDynamicMatrix()
{
  if (this->pMem != 0) {
    delete[]this->pMem;
    this->pMem = 0;
  }
  this->sz = 0;
  sz = 0;
}

template<class T>
inline TDynamicMatrix<T> TDynamicMatrix<T>::operator+(const TDynamicMatrix<T>& p)
{
  TDynamicMatrix<T> res(this->sz);
  if ((this->sz != p.sz) || (sz != p.sz)) throw "Err";
  for (int j = 0; j < p.sz; j++)
    for (int i = 0; i < sz; i++)
      res.pMem[j][i] = this->pMem[j][i] + p.pMem[j][i];
  return res;
}

template<class T>
inline TDynamicMatrix<T> TDynamicMatrix<T>::operator-(const TDynamicMatrix<T>& p)
{
  TDynamicMatrix<T> res(this->sz);
  if ((this->sz != p.sz) || (sz != p.sz)) throw "Err";
  for (int j = 0; j < p.sz; j++)
    for (int i = 0; i < sz; i++)
      res.pMem[j][i] = this->pMem[j][i] - p.pMem[j][i];
  return res;
}

template<class T>
inline TDynamicMatrix<T> TDynamicMatrix<T>::operator*(const TDynamicMatrix<T>& p)
{
  if ((this->sz != p.sz) || (sz != p.sz)) throw "Err";
  TDynamicMatrix<T> res(sz);
  for (int i = 0; i < sz; i++)
    for (int j = 0; j < sz; j++) {
      res[i][j] = 0;
      for (int n = 0; n < sz; n++)
        res[i][j] += (this->pMem[i][n] * p.pMem[n][j]);
    }
  return res;
}

template<class T>
inline TDynamicVector<T> TDynamicMatrix<T>::operator*(const TDynamicVector<T>& p)
{
  TDynamicVector<T> tmp(sz);
  for (int i = 0; i < sz; i++)
    tmp[i] = pMem[i] * p;
  return tmp;
}

template<class T>
inline TDynamicVector<T> TDynamicMatrix<T>::operator*(const T& val)
{
  TDynamicMatrix<T> tmp(sz);
  for (int i = 0; i < sz; i++)
    tmp.pMem[i] = pMem[i] * val;
  return tmp;
}

template<class T>
inline TDynamicMatrix<T>& TDynamicMatrix<T>::operator=(const TDynamicMatrix<T>& p)
{
  this->sz = p.sz;
  if (this == &p) return*this;
  sz = p.sz;
  if (this->pMem != 0) delete[]this->pMem;
  if (p.pMem == 0) this->pMem = 0;
  else {
    this->pMem = new TDynamicVector<T>[p.sz];
    for (int i = 0; i < p.sz; i++)
      this->pMem[i] = p.pMem[i];
  }
  return*this;
}

template<class T>
inline TDynamicMatrix<T>& TDynamicMatrix<T>::operator=(const TDynamicVector<TDynamicVector<T>>& p)
{
}

template<class T>
inline bool TDynamicMatrix<T>::operator==(const TDynamicMatrix<T>& p) const noexcept
{
  if (sz != p.sz)
    return false;
  for (int i = 0; i < sz; i++)
    for (int j = 0; j < this->sz; j++)
      if (this->pMem[i][j] != p.pMem[i][j])
        return false;
  return true;
}

template<class T>
inline bool TDynamicMatrix<T>::operator!=(const TDynamicMatrix<T>& p)
{
  return false;
}

template<class T>
inline TDynamicVector<T>& TDynamicMatrix<T>::operator[](int i)
{
  if (i<0 || i>=sz)
    throw "err";
  return pMem[i];
}