using System;

class GaussJordanSolver
{
    static double[] GaussJordan(double[][] A, double[] b)
    {
        int n = A.Length;

        // В конец строки А добавляется В
        for (int i = 0; i < n; i++)
        {
            double[] row = A[i];
            row = row.Concat(new double[] { b[i] }).ToArray();
            A[i] = row;
        }

        // Процесс приведения матрицы к треугольному виду
        for (int k = 0; k < n; k++)
        {
            // Меняем строки местами
            for (int i = k; i < n; i++)
            {
                if (Math.Abs(A[i][k]) > Math.Abs(A[k][k]))
                {
                    double[] temp = A[k];
                    A[k] = A[i];
                    A[i] = temp;
                }
            }

            // Делаем нули в нижней строке
            for (int j = k + 1; j < n; j++)
            {
                double q = A[j][k] / A[k][k];
                for (int m = k; m < n + 1; m++)
                {
                    A[j][m] -= q * A[k][m];
                }
            }
        }

        double[] x = new double[n];
        x[n - 1] = A[n - 1][n] / A[n - 1][n - 1];

        // Вычисление результата
        for (int i = n - 1; i >= 0; i--)
        {
            double z = 0;
            for (int j = i + 1; j < n; j++)
            {
                z += A[i][j] * x[j];
            }
            x[i] = (A[i][n] - z) / A[i][i];
        }

        return x;
    }

    static void Main(string[] args)
    {
        double[][] A = new double[3][];
        Console.WriteLine("Введите матрицу:");
        for (int i = 0; i < 3; i++)
        {
            A[i] = Array.ConvertAll(Console.ReadLine().Split(), double.Parse);
        }

        Console.WriteLine("Введите столбец свободных членов:");
        double[] b = Array.ConvertAll(Console.ReadLine().Split(), double.Parse);

        double[] result = GaussJordan(A, b);
        Console.WriteLine("Решение:");
        foreach (double value in result)
        {
            Console.WriteLine(value);
        }
    }
}
