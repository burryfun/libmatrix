#include "matrix.h"
#include "cmath"
Matrix::Matrix()
{
    matrix = new double* [0];
}
Matrix::Matrix(int row, int column)
{
    rowCount = row;
    columnCount = column;
    matrix = new double * [rowCount];
    matrix[0] = new double [rowCount*columnCount];
    for (int r = 1; r != rowCount; r++)
    {
        matrix[r] = matrix[r-1] + columnCount;
    }
}

Matrix::Matrix(const Matrix& _M)
{
    rowCount = _M.rowCount;
    columnCount = _M.columnCount;
    // Выделение памяти под 2D-массив с данными
    matrix = new double * [rowCount];
    matrix[0] = new double [rowCount*columnCount];
    for (int r = 1; r != rowCount; r++)
    {
        matrix[r] = matrix[r-1] + columnCount;
    }
    // заполнение
    for (int i = 0; i < rowCount; i++)
        for (int j = 0; j < columnCount; j++)
            matrix[i][j] = _M.matrix[i][j];
}

Matrix::~Matrix()
{
    delete [] matrix[0];
    delete matrix;
}

double* Matrix::operator[](int i)
{
    return matrix[i];
}
void Matrix::setSize(int row, int column)
{
    rowCount = row;
    columnCount = column;
    matrix = new double * [rowCount];
    matrix[0] = new double [rowCount*columnCount];
    for (int r = 1; r != rowCount; r++)
    {
        matrix[r] = matrix[r-1] + columnCount;
    }
}

int Matrix::getRowCount()
{
    return this->rowCount;
}
int Matrix::getColumnCount()
{
    return this->columnCount;
}

Matrix MatrixReduction(Matrix m, int k)
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

double MatrixDeterminant(Matrix m)
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
            Matrix m_red = MatrixReduction(m,i);
            determinant += pow(-1,i+2)*m[0][i]*MatrixDeterminant(m_red);
        }
        size--;
    }
    return determinant;
}

Matrix MatrixTranspose(Matrix m)
{
    Matrix C(m.getColumnCount(), m.getRowCount());
    for(int i=0; i!=m.getRowCount(); i++)
        for(int j=0; j!=m.getColumnCount(); j++)
            C[j][i] = m[i][j];
    return C;
}
void MatrixScalarMultiply(Matrix &m, int s)
{
    int row = m.getRowCount();
    int col = m.getColumnCount();
    for(int r = 0; r != row; r++)
        for(int c = 0; c != col;c++)
            m[r][c] = m[r][c] * s;
}

Matrix MatrixSum(Matrix A, Matrix B)
{
    Matrix C(A.getRowCount(), A.getColumnCount());
    for(int i = 0; i != A.getRowCount(); i++)
        for(int j = 0; j != A.getColumnCount(); j++)
            C[i][j] = A[i][j] + B[i][j];
    return C;
}

Matrix MatrixMultiply(Matrix A, Matrix B)
{
    Matrix C(A.getRowCount(), B.getColumnCount());
        for(int i=0; i!=C.getRowCount(); i++)
            for(int j=0; j!=C.getColumnCount(); j++)
                for(int l=0; l!=A.getColumnCount(); l++)
                    C[i][j] += A[i][l]*B[l][j];
    return C;
}

Matrix MatrixLeftDivision(Matrix A, Matrix B)
{
    return MatrixMultiply(MatrixTranspose(A), B);
}
Matrix MatrixRightDivision(Matrix A, Matrix B)
{
    return MatrixMultiply(A, MatrixTranspose(B));
}
