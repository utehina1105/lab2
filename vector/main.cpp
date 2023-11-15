#include <iostream>
#include <Matrix.h>

int main() {
  TDynamicVector<int> vector2(4);
  TDynamicVector<int> vector3(vector2);

  int* arr = new int[4];
  arr[0] = 3; arr[1] = 2; arr[2] = 3; arr[3] = 3;
  TDynamicVector<int> vector1(arr,4);

  TDynamicVector<double> vector1d;
  TDynamicVector<double> vector2d(5);
  TDynamicVector<double> vector3d(vector2d);

  std::cin >> vector3;
  vector2 = vector3 + vector1;
  std::cout << vector2;

  vector2 = vector3 - vector1;

  if (vector1 == vector2) std::cout << true << std::endl;
  if (vector1 != vector2) std::cout << false << std::endl;

  std::cout << vector2;

  std::cout << vector3 * vector2 << std::endl;
  std::cout << vector3 + 1;
  std::cout << vector3 - 3;
  std::cout << vector3 * 4 << std::endl;

  TDynamicMatrix<int> mat2;
  TDynamicMatrix<int> mat3(3);
  TDynamicMatrix<int> mat4(mat2);

  std::cin >> mat2;

  mat3[0][0] = 5; mat3[0][1] = 5; mat3[0][2] = 0;
  mat3[1][0] = 6; mat3[1][1] = 2; mat3[1][2] = 1;
  mat3[2][0] = 7; mat3[2][1] = 2; mat3[2][2] = 3;


  if (mat3 == mat2) std::cout << true << std::endl;
  if (mat3 != mat2) std::cout << false << std::endl;

  mat4 = mat2 * mat3;

  std::cout << mat4 << std::endl;
  std::cout << mat2 - mat3 << std::endl;
  std::cout << mat2 + mat3;


  return 0;
}