
namespace Task4
{
    internal class Matrix
    {
        public double[,] Data { get; private set; }

        public Matrix(int rows, int columns)
        {
            Data = new double[rows, columns];
        }

        public void SetValue(int row, int column, double value)
        {
            Data[row, column] = value;
        }

        public double GetValue(int row, int column)
        {
            return Data[row, column];
        }

        public static Matrix Multiply(Matrix matrix1, Matrix matrix2)
        {
            int m1rows = matrix1.Data.GetLength(0);
            int m1columns_m2rows = matrix1.Data.GetLength(1);
            int m2columns = matrix2.Data.GetLength(1);

            Matrix result = new Matrix(m1rows, m2columns);

            for (int row = 0; row < m1rows; row++)
            {
                for (int column = 0; column < m2columns; column++)
                {
                    double accumulator = 0;
                    for (int cell = 0; cell < m1columns_m2rows; cell++)
                    {
                        accumulator += matrix1.GetValue(row, cell) * matrix2.GetValue(cell, column);
                    }
                    result.SetValue(row, column, accumulator);
                }
            }

            return result;
        }
    }
}
