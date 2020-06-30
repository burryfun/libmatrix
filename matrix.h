#ifndef MATRIX_H
#define MATRIX_H
#include <vector>

class Matrix
{
public:
    Matrix();
    ~Matrix();
    Matrix(const Matrix&);
    Matrix(int row, int column);
    void setSize(int row, int column);
    int getRowCount();
    int getColumnCount();
    double* operator[] (int i);

private:
    int rowCount;
    int columnCount;
    double **matrix;
};

Matrix MatrixReduction(Matrix m, int k);
double MatrixDeterminant(Matrix);
Matrix MatrixTranspose(Matrix);
void MatrixScalarMultiply(Matrix&, int);
Matrix MatrixSum(Matrix, Matrix);
Matrix MatrixMultiply(Matrix, Matrix);
Matrix MatrixLeftDivision(Matrix, Matrix);
Matrix MatrixRightDivision(Matrix, Matrix);

#endif // MATRIX_H
