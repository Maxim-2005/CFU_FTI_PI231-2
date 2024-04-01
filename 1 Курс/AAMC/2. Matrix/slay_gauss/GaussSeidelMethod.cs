using System;

public class GaussSeidelMethod
{
    public static double[] Solve(double[,] A, double[] b)
    {
        int n = b.Length;
        double[] x = new double[n];
        double[] xPrev = new double[n];
        double epsilon = 1e-6; // Точность

        // Начальное приближение
        for (int i = 0; i < n; i++)
        {
            x[i] = 0;
        }

        // Итерационный процесс
        int iter = 0;
        while (true)
        {
            iter++;
            Array.Copy(x, xPrev, n);
            for (int i = 0; i < n; i++)
            {
                double sum1 = 0;
                for (int j = 0; j < i; j++)
                {
                    sum1 += A[i, j] * x[j];
                }
                double sum2 = 0;
                for (int j = i + 1; j < n; j++)
                {
                    sum2 += A[i, j] * xPrev[j];
                }
                x[i] = (b[i] - sum1 - sum2) / A[i, i];
            }

            // Проверка сходимости
            double maxDiff = double.MinValue;
            for (int i = 0; i < n; i++)
            {
                double diff = Math.Abs(x[i] - xPrev[i]);
                if (diff > maxDiff)
                {
                    maxDiff = diff;
                }
            }
            if (maxDiff < epsilon)
            {
                break;
            }
        }
        Console.WriteLine($"Количество итераций: {iter}");
        return x;
    }
}
