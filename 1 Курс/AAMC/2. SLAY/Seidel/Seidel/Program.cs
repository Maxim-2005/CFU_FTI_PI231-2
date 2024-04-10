using System;

class SeidelMethod
{
    static double[] Seidel(double[][] A, double[] b, double eps) // Матрица, Ряд свободных членов, Погрешность
    {
        int n = A.Length;
        double[] x = new double[n];

        bool converge = false; // Сходимость матрицы
        while (!converge)
        {
            double[] xNew = (double[])x.Clone(); // Создание копии вектора решений
            for (int i = 0; i < n; i++)
            {
                double s1 = 0; // Сумма элементов слева от диагонали
                double s2 = 0; // Сумма элементов справа от диагонали
                for (int j = 0; j < i; j++)
                {
                    s1 += A[i][j] * xNew[j];
                }
                for (int j = i + 1; j < n; j++)
                {
                    s2 += A[i][j] * x[j];
                }
                xNew[i] = (b[i] - s1 - s2) / A[i][i]; // Вычисление нового значения для текущего уравнения
            }

            // Проверка сходимости
            converge = Norm(xNew, x) <= eps;
            x = xNew;
        }

        return x;
    }

    // Вычисление нормы разности между двумя векторами
    static double Norm(double[] a, double[] b)
    {
        double max = 0;
        for (int i = 0; i < a.Length; i++)
        {
            double diff = Math.Abs(a[i] - b[i]);
            if (diff > max)
                max = diff;
        }
        return max;
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

        double eps = 0.0001;
        double[] result = Seidel(A, b, eps);
        Console.WriteLine("Решение:");
        foreach (double value in result)
        {
            Console.WriteLine(value);
        }
    }
}
