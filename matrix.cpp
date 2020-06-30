#include "matrix.h"
#include <cmath>
#include <cassert>
#include <random>
#include <ctime>
Matrix::Matrix() : rowCount_(1), columnCount_(1)
{
    matrix_ = new double* [rowCount_];
    matrix_[0] = new double [columnCount_];
    matrix_[0][0] = 0;
}

Matrix::~Matrix()
{
    delete [] matrix_[0];
    delete matrix_;
}

Matrix::Matrix(const Matrix& other)
{
    rowCount_ = other.rowCount_;
    columnCount_ = other.columnCount_;
    matrix_ = new double * [rowCount_];
    matrix_[0] = new double [rowCount_*columnCount_];
    for (uint r = 1; r != rowCount_; r++)
        matrix_[r] = matrix_[r-1] + columnCount_;
    for (uint i = 0; i < rowCount_; i++)
        for (uint j = 0; j < columnCount_; j++)
            matrix_[i][j] = other.matrix_[i][j];
}

Matrix& Matrix::operator=(const Matrix& other)
{
    delete [] matrix_[0];
    delete matrix_;
    rowCount_ = other.rowCount_;
    columnCount_ = other.columnCount_;
    matrix_ = new double * [rowCount_];
    matrix_[0] = new double [rowCount_*columnCount_];
    for (uint r = 1; r != rowCount_; r++)
        matrix_[r] = matrix_[r-1] + columnCount_;
    for (uint i = 0; i < rowCount_; i++)
        for (uint j = 0; j < columnCount_; j++)
            matrix_[i][j] = other.matrix_[i][j];
}

Matrix::Matrix(uint row, uint column)
{
    assert(row > 0 || column > 0);
    rowCount_ = row;
    columnCount_ = column;
    matrix_ = new double * [rowCount_];
    matrix_[0] = new double [rowCount_*columnCount_];
    for (uint r = 1; r != rowCount_; r++)
    {
        matrix_[r] = matrix_[r-1] + columnCount_;
    }
}

Matrix& Matrix::setSize(uint row, uint column)
{
    assert(row > 0 || column > 0);
    delete [] matrix_[0];
    delete matrix_; 
    rowCount_ = row;
    columnCount_ = column;
    matrix_ = new double * [rowCount_];
    matrix_[0] = new double [rowCount_*columnCount_];
    for (uint r = 1; r != rowCount_; r++)
    {
        matrix_[r] = matrix_[r-1] + columnCount_;
    }
}

unsigned int Matrix::getRowCount() const { return rowCount_; }

unsigned int Matrix::getColumnCount() const { return columnCount_; }

double* Matrix::operator[](uint i) const { return matrix_[i]; }

int random(const uint MAXRAND)
{
    return rand()%MAXRAND;
}

Matrix& Matrix::fillRandom(const uint MAXRAND)
{
    srand(time(NULL));
    for(uint r = 0; r != rowCount_; ++r)
        for(uint c = 0; c != columnCount_; ++c)
            matrix_[r][c] = random(MAXRAND);
}

//deleting row[k] & column[k]
Matrix matrixReduction(const Matrix& m, int k)
{
    Matrix C(m.getRowCount() - 1, m.getRowCount() - 1);
    for(int r = 0; r != m.getRowCount(); r++)
    {
        for(int c = 0; c != m.getColumnCount(); c++)
        {
            if(r != 0 && c != k)
            {
                if(c-k < 0)
                {
                    C[r - 1][c] = m[r][c];
                }
                else
                {
                    C[r - 1][c - k] = m[r][c];
                }
            }
        }
    }
    return C;
}

double matrixDeterminant(const Matrix& m)
{
    double determinant = 0;
    int size = m.getRowCount();
    if (size == 2)
    {
        return m[0][0]*m[1][1] - m[0][1]*m[1][0];
    }
    else
    {
        for (int i = 0; i != size; i++)
        {
            Matrix m_red = matrixReduction(m,i);
            determinant += pow(-1,i+2)*m[0][i]*matrixDeterminant(m_red);
        }
        size--;
    }
    return determinant;
}

Matrix matrixTranspose(const Matrix& m)
{
    Matrix C(m.getColumnCount(), m.getRowCount());
    for(int i=0; i!=m.getRowCount(); i++)
        for(int j=0; j!=m.getColumnCount(); j++)
            C[j][i] = m[i][j];
    return C;
}

void matrixScalarMultiply(Matrix &m, int s)
{
    int row = m.getRowCount();
    int col = m.getColumnCount();
    for(int r = 0; r != row; r++)
        for(int c = 0; c != col;c++)
            m[r][c] = m[r][c] * s;
}

Matrix matrixSum(const Matrix& A, const Matrix& B)
{
    Matrix C(A.getRowCount(), A.getColumnCount());
    for(int i = 0; i != A.getRowCount(); i++)
        for(int j = 0; j != A.getColumnCount(); j++)
            C[i][j] = A[i][j] + B[i][j];
    return C;
}

Matrix matrixMultiply(const Matrix& A, const Matrix& B)
{
    Matrix C(A.getRowCount(), B.getColumnCount());
        for(int i=0; i!=C.getRowCount(); i++)
            for(int j=0; j!=C.getColumnCount(); j++)
                for(int l=0; l!=A.getColumnCount(); l++)
                    C[i][j] += A[i][l]*B[l][j];
    return C;
}

Matrix matrixLeftDivision(const Matrix& A, const Matrix& B)
{
    return matrixMultiply(matrixTranspose(A), B);
}

Matrix matrixRightDivision(const Matrix& A, const Matrix& B)
{
    return matrixMultiply(A, matrixTranspose(B));
}
