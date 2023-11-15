#pragma once
#include <iostream>

const int MAX_VECTOR_SIZE = 100000000;

template <class T>
class TDynamicVector
{
protected:
  T* pMem;
  int sz;
public:
  TDynamicVector(int n = 1);
  TDynamicVector(T* arr, int s);
  TDynamicVector(const TDynamicVector<T>& p);
  TDynamicVector(TDynamicVector<T>&& p) noexcept;
  ~TDynamicVector();


  TDynamicVector<T> operator+(const TDynamicVector<T>& p);
  TDynamicVector<T> operator-(const TDynamicVector<T>& p);
  T operator*(const TDynamicVector<T>& p);
  TDynamicVector<T> operator+(T p);
  TDynamicVector<T> operator-(T p);
  TDynamicVector<T> operator*(T p);

  TDynamicVector<T>& operator=(const TDynamicVector<T>& p);
  TDynamicVector<T>& operator=(TDynamicVector<T>&& p) noexcept;

  bool operator==(const TDynamicVector<T>& p);
  bool operator!=(const TDynamicVector<T>& p);

  T& operator[](int i);
  T& at(size_t ind);
  const T& at(size_t ind) const;

  size_t size() const noexcept { return sz; }

  friend std::ostream& operator<<(std::ostream& a, TDynamicVector<T>& p) {
    for (int i = 0; i < p.sz; i++) a << p[i] << " ";
    a << "\n";
    return a;
  }
  friend std::istream& operator>>(std::istream& a, TDynamicVector<T>& p) {
    int l;
    a >> l;
    p = TDynamicVector<T>(l);
    for (int i = 0; i < l; i++) a >> p[i];
    return a;
  }
};

template<class T>
inline TDynamicVector<T>::TDynamicVector(int n = 1): sz(n)
{
  if (sz == 0)
    throw "Vector size should be greater than zero";
  if (n > MAX_VECTOR_SIZE)
    throw "over then max size";
  pMem = new T[sz]();
}

template<class T>
inline TDynamicVector<T>::TDynamicVector(T* arr, int s)
{
  if (s <= 0) throw "TDynamicVector size <= 0";
  if (arr == nullptr) throw "TDynamicVector arr == nullptr";

  sz = s;
  pMem = new T[sz];

  for (int i = 0; i < sz; i++)
    pMem[i] = arr[i];
}

template<class T>
inline TDynamicVector<T>::TDynamicVector(const TDynamicVector<T>& p)
{
  if (p.pMem == 0) {
    pMem = 0;
    sz = 0;
  }
  else {
    sz = p.sz;
    pMem = new T[sz];
    for (int i = 0; i < sz; i++)
      pMem[i] = p.pMem[i];
  }
}

template<class T>
inline TDynamicVector<T>::TDynamicVector(TDynamicVector<T>&& p) noexcept
{
  sz = p.sz;
  pMem = p.pMem;

  p.sz = 0;
  p.pMem = nullptr;
}

template<class T>
inline TDynamicVector<T>::~TDynamicVector()
{
  if (pMem != 0) {
    delete[]pMem;
    pMem = 0;
  }
  sz = 0;
}

template<class T>
inline TDynamicVector<T> TDynamicVector<T>::operator+(const TDynamicVector<T>& p)
{
  if (sz == 0) throw "Err";
  if (sz != p.sz) throw "Err";
  TDynamicVector<T> A(sz);
  for (int i = 0; i < sz; i++)
    A[i] = pMem[i] + p.pMem[i];
  return A;
}

template<class T>
inline TDynamicVector<T> TDynamicVector<T>::operator-(const TDynamicVector<T>& p)
{
  if (sz == 0) throw "Err";
  if (sz != p.sz) throw "Err";
  TDynamicVector<T> A(*this);
  for (int i = 0; i < sz; i++)
    A.pMem[i] -= p.pMem[i];
  return A;
}

template<class T>
inline T TDynamicVector<T>::operator*(const TDynamicVector<T>& p)
{
  if (sz == 0) throw "Err";
  if (sz != p.sz) throw "Err";
  T A = 0;
  for (int i = 0; i < sz; i++)
    A += p.pMem[i] * pMem[i];
  return A;
}

template<class T>
inline TDynamicVector<T> TDynamicVector<T>::operator+(T p)
{
  TDynamicVector<T> tmp(sz);
  for (int i = 0; i < sz; i++)
    tmp.pMem[i] = pMem[i] + p;
  return tmp;
}

template<class T>
inline TDynamicVector<T> TDynamicVector<T>::operator-(T p)
{
  TDynamicVector<T> tmp(sz);
  for (int i = 0; i < sz; i++)
    tmp.pMem[i] = pMem[i] - p;
  return tmp;
}

template<class T>
inline TDynamicVector<T> TDynamicVector<T>::operator*(T p)
{
  TDynamicVector<T> A(*this);
  for (int i = 0; i < sz; i++)
    A.pMem[i] *= p;
  return A;
}


template<class T>
inline TDynamicVector<T>& TDynamicVector<T>::operator=(const TDynamicVector<T>& p)
{
  if (this == &p)
    return *this;
  if (pMem != 0)
    delete[]pMem;
  if (p.pMem == 0)
    pMem = 0;
  else
    pMem = new T[p.sz];
  sz = p.sz;
  for (int i = 0; i < sz; i++)
    pMem[i] = p.pMem[i];
  return *this;
}

template<class T>
inline TDynamicVector<T>& TDynamicVector<T>::operator=(TDynamicVector<T>&& p) noexcept
{
  if (this != &p)
  {
    if (pMem != nullptr)
      delete[] pMem;

    sz = p.sz;
    pMem = p.pMem;

    p.sz = 0;
    p.pMem = nullptr;
  }
  return *this;
}

template<class T>
inline bool TDynamicVector<T>::operator==(const TDynamicVector<T>& p)
{
  if (this == &p)
    return true;
  if (sz != p.sz)
    return false;
  for (int i = 0; i < sz; i++) {
    if (pMem[i] != p.pMem[i])
      return false;
  }
  return true;
}

template<class T>
inline bool TDynamicVector<T>::operator!=(const TDynamicVector<T>& p)
{
  if (this == &p)
    return false;
  if (sz != p.sz)
    return true;
  for (int i = 0; i < sz; i++) {
    if (pMem[i] != p.pMem[i])
      return true;
  }
  return false;
}

template<class T>
inline T& TDynamicVector<T>::operator[](int i)
{
  if (pMem == 0) throw "Err";
  if ((i < 0) || (i >= sz)) throw "Err";
  return pMem[i];
}

template<class T>
inline T& TDynamicVector<T>::at(size_t ind)
{
  if (ind < 0 || ind >= sz)
    throw "Index is invalid";
  return pMem[ind];
}

template<class T>
inline const T& TDynamicVector<T>::at(size_t ind) const
{
  if (ind < 0 || ind >= sz)
    throw "Index is invalid";
  return pMem[ind];
}
