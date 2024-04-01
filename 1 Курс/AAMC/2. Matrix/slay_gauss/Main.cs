using System;

class Program
{
    static void Main()
    {
        // Пример задачи: система линейных уравнений 3x3
        double[,] A = {
            {2, 1, -1},
            {-3, -1, 2},
            {-2, 1, 2}
        };
        double[] b = { 8, -11, -3 };

        // Усиление диагонали матрицы для предотвращения расходимости метода Зейделя
        StrengthenDiagonal(ref A);

        // Решение методом Гаусса-Жордана
        double[] xGaussJordan = GaussJordanMethod.Solve(A, b);
        PrintSolution("Гаусса-Жордана", xGaussJordan);

        // Решение методом Гаусса-Зейделя
        double[] xGaussSeidel = GaussSeidelMethod.Solve(A, b);
        PrintSolution("Гаусса-Зейделя", xGaussSeidel);
    }

    static void StrengthenDiagonal(ref double[,] A)
    {
        // Усиление диагонали матрицы для предотвращения расходимости метода Зейделя
        int n = A.GetLength(0);
        for (int i = 0; i < n; i++)
        {
            double sum = 0;
            for (int j = 0; j < n; j++)
            {
                if (i != j)
                {
                    sum += Math.Abs(A[i, j]);
                }
            }
            A[i, i] += sum;
        }
    }

    static void PrintSolution(string method, double[] solution)
    {
        Console.WriteLine($"Решение методом {method}:");
        foreach (var x in solution)
        {
            Console.WriteLine(x);
        }
    }
}
