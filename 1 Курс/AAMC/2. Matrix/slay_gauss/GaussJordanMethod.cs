using System;

public class GaussJordanMethod
{
    public static double[] Solve(double[,] A, double[] b)
    {
        int n = b.Length;
        double[,] AB = AugmentedMatrix(A, b);

        // Прямой ход метода Гаусса-Жордана
        for (int i = 0; i < n; i++)
        {
            // Поиск максимального элемента в столбце для выбора ведущего элемента
            double maxElement = Math.Abs(AB[i, i]);
            int maxIndex = i;
            for (int k = i + 1; k < n; k++)
            {
                if (Math.Abs(AB[k, i]) > maxElement)
                {
                    maxElement = Math.Abs(AB[k, i]);
                    maxIndex = k;
                }
            }

            // Обмен строк
            if (maxIndex != i)
            {
                for (int k = 0; k < n + 1; k++)
                {
                    double temp = AB[i, k];
                    AB[i, k] = AB[maxIndex, k];
                    AB[maxIndex, k] = temp;
                }
            }

            // Преобразование ступенчатого вида
            double divider = AB[i, i];
            for (int j = i; j < n + 1; j++)
            {
                AB[i, j] /= divider;
            }
            for (int k = 0; k < n; k++)
            {
                if (k != i)
                {
                    double multiplier = AB[k, i];
                    for (int j = i; j < n + 1; j++)
                    {
                        AB[k, j] -= AB[i, j] * multiplier;
                    }
                }
            }
        }

        // Обратный ход метода Гаусса-Жордана
        double[] x = new double[n];
        for (int i = 0; i < n; i++)
        {
            x[i] = AB[i, n];
        }
        return x;
    }

    // Вспомогательный метод для создания расширенной матрицы
    static double[,] AugmentedMatrix(double[,] A, double[] b)
    {
        int n = b.Length;
        double[,] AB = new double[n, n + 1];
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                AB[i, j] = A[i, j];
            }
            AB[i, n] = b[i];
        }
        return AB;
    }
}
