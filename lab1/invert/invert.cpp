
#include <iostream>
#include <fstream>
#include <optional>
#include <string>
#include <math.h>
#include <iomanip>

const int MATRIX_SIZE_N = 3;

struct Args 
{
    std::string inputFileName;
    std::string findString;
};

struct TransposedMatrixMinors 
{
    float matrix[MATRIX_SIZE_N][MATRIX_SIZE_N];
};


std::optional<Args> ParseArgs(int argc, char* argv[]) 
{
    if (argc != 2)
    {
        std::cout << "Invalid arguments count\n";
        std::cout << "Usage: <matrix file1>\n";
        return std::nullopt;
    }

    Args args;
    args.inputFileName = argv[1];
    return args;
}


float GetMatrixDeterminant(float matrix[MATRIX_SIZE_N][MATRIX_SIZE_N])
{
    float matrixDeterminant = 1;

    for (int i = 0; i < MATRIX_SIZE_N; i++)
    {
        matrixDeterminant *= matrix[i][i];
    }

    matrixDeterminant += matrix[1][0] * matrix[2][1] * matrix[0][2];
    matrixDeterminant += matrix[0][1] * matrix[2][0] * matrix[1][2];

    
    matrixDeterminant -= matrix[0][2] * matrix[1][1] * matrix[2][0];

    matrixDeterminant -= matrix[1][0] * matrix[0][1] * matrix[2][2];
    matrixDeterminant -= matrix[0][0] * matrix[1][2] * matrix[2][1];

    return matrixDeterminant;
}
//разбить на на несколько функций
TransposedMatrixMinors GetTransposedMatrixMinors(float matrix[MATRIX_SIZE_N][MATRIX_SIZE_N])
{
    
    float matrixMinors[MATRIX_SIZE_N][MATRIX_SIZE_N];
    TransposedMatrixMinors transposedMatrixMinors;
    
    int col = 0, row = 0;
    int i = row, k = col;
    while (col < MATRIX_SIZE_N && row < MATRIX_SIZE_N)
    {
        float minor = 0;
        int i = row, k = col;
        int numberCols[2];
        int numberRows[2];
        
        switch (i)
        {
            case 0:
            {
                numberRows[0] = 1;
                numberRows[1] = 2;
                break;
            }
            case 1:
            {
                numberRows[0] = 0;
                numberRows[1] = 2;
                break;
            }
            case 2:
            {
                numberRows[0] = 0;
                numberRows[1] = 1;
                break;
            }
        }

        switch (k)
        {
            case 0:
            {
                numberCols[0] = 1;
                numberCols[1] = 2;
                break;
            }
            case 1:
            {
                numberCols[0] = 0;
                numberCols[1] = 2;
                break;
            }
            case 2:
            {
                numberCols[0] = 0;
                numberCols[1] = 1;
                break;
            }
        }

        minor = matrix[numberRows[0]][numberCols[0]] * matrix[numberRows[1]][numberCols[1]]
            - matrix[numberRows[0]][numberCols[1]] * matrix[numberRows[1]][numberCols[0]];

        minor = minor * static_cast<float>(pow(-1, row + col));

        matrixMinors[row][col] = minor;
        ++col;
        
        if (col == MATRIX_SIZE_N) 
        {
            ++row;
            col = 0;
        }
    }

    for (int i = 0; i < MATRIX_SIZE_N; i++)
    {
        for (int k = 0; k < MATRIX_SIZE_N; k++)
        {
            transposedMatrixMinors.matrix[k][i] = matrixMinors[i][k];
        }
    }


    return transposedMatrixMinors;
}

void outputMatrix(float matrix[MATRIX_SIZE_N][MATRIX_SIZE_N])
{
    for (int i = 0; i < MATRIX_SIZE_N; i++)
    {
        for (int k = 0; k < MATRIX_SIZE_N; k++)
        {
            if (matrix[i][k] >= 0)
            {
                std::cout << "  " << std::left << std::setw(6) << matrix[i][k];
            }
            else
            {
                std::cout << " " << std::left << std::setw(7) << matrix[i][k];
            }
            if (k < MATRIX_SIZE_N - 1)
            {
                std::cout << "| ";
            }
        }
        std::cout << std::endl;
    }
}

int main(int argc, char* argv[])
{
    auto args = ParseArgs(argc, argv);

    if (!args) 
    {
        return 1;
    }

    float matrix[MATRIX_SIZE_N][MATRIX_SIZE_N];

    std::ifstream fileWithMatrix;
    fileWithMatrix.open(args->inputFileName);
    if (!fileWithMatrix.is_open()) 
{
        std::cout << "Failed to open " << argv[1] << " for reading";
        return 1;
    }

    int lineFile = 0, colsFile = 0;

    while (!fileWithMatrix.eof())
    {
        fileWithMatrix >> matrix[lineFile][colsFile];
        colsFile++;

        if (colsFile == MATRIX_SIZE_N)
        {
            lineFile++;
            colsFile = 0;
        }
    }

    if (lineFile != MATRIX_SIZE_N || colsFile != 0)
    {
        std::cout << "the file contains an incorrect matrix\n";
        return 1;
    }

    if (fileWithMatrix.bad())
    {
        std::cout << "Failed to read data from input file " << argv[1] << std::endl;
        return 1;
    }

    float matrixDeterminate = GetMatrixDeterminant(matrix);

    if (matrixDeterminate == 0)
    {
        std::cout << "There is no inverse matrix for this matrix\n";
        return 1;
    }

    TransposedMatrixMinors transposedMatrixMinors = GetTransposedMatrixMinors(matrix);

    float invertMatrix[MATRIX_SIZE_N][MATRIX_SIZE_N];

    for (int i = 0; i < MATRIX_SIZE_N; i++)
    {
        for (int k = 0; k < MATRIX_SIZE_N; k++)
        {
            invertMatrix[i][k] = round((transposedMatrixMinors.matrix[i][k] / matrixDeterminate) * 1000) / 1000;
        }
    }

    outputMatrix(invertMatrix);


    return 0;

}
