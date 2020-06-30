#ifndef MATRIX_H
#define MATRIX_H

class Matrix
{
public:
    Matrix();
    ~Matrix();
    Matrix(const Matrix&);
    Matrix& operator=(const Matrix&);
    Matrix(unsigned int row, unsigned int column);
    Matrix& setSize(unsigned int row, unsigned int column);
    unsigned int getRowCount() const;
    unsigned int getColumnCount() const;
    double* operator[] (unsigned int i) const;

private:
    unsigned int rowCount_;
    unsigned int columnCount_;
    double** matrix_;
};

// Matrix MatrixReduction(Matrix m, int k);
// double MatrixDeterminant(Matrix);
// Matrix MatrixTranspose(Matrix);
// void MatrixScalarMultiply(Matrix&, int);
// Matrix MatrixSum(Matrix, Matrix);
// Matrix MatrixMultiply(Matrix, Matrix);
// Matrix MatrixLeftDivision(Matrix, Matrix);
// Matrix MatrixRightDivision(Matrix, Matrix);

#endif // MATRIX_H
