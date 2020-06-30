#ifndef MATRIX_H
#define MATRIX_H
typedef unsigned int uint;
class Matrix
{
public:
    Matrix();
    ~Matrix();
    Matrix(const Matrix&);
    Matrix& operator=(const Matrix&);
    Matrix(uint row, uint column);
    Matrix& setSize(uint row, uint column);
    unsigned int getRowCount() const;
    unsigned int getColumnCount() const;
    double* operator[] (uint i) const;
    Matrix& fillRandom(const uint);
private:
    uint rowCount_;
    uint columnCount_;
    double** matrix_;
};
int random(const uint);
Matrix matrixReduction(const Matrix&, int);
double matrixDeterminant(const Matrix&);
Matrix matrixTranspose(const Matrix&);
void matrixScalarMultiply(Matrix&, int);
Matrix matrixSum(const Matrix&, const Matrix&);
Matrix matrixMultiply(const Matrix&, const Matrix&);
Matrix matrixLeftDivision(const Matrix&, const Matrix&);
Matrix matrixRightDivision(const Matrix&, const Matrix&);

#endif // MATRIX_H
