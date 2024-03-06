using System;

class SimpsonIntegration
{
    // Функция, которую мы интегрируем
    static double Function(double x)
    {
        return x * Math.Exp(x) / Math.Pow(1 + 0.4 * x, 2);
    }

    // Метод Симпсона для вычисления интеграла
    static double SimpsonRule(double a, double b, int n)
    {
        double h = (b - a) / n;
        double sum = Function(a) + Function(b);

        for (int i = 1; i < n; i++)
        {
            double x = a + i * h;
            sum += i % 2 == 0 ? 2 * Function(x) : 4 * Function(x);
        }

        return (h / 3) * sum;
    }

    // Контроль погрешности по формуле Рунге
    static double RungeControl(double a, double b, int n)
    {
        double I1 = SimpsonRule(a, b, n); // Интеграл с шагом h
        double I2 = SimpsonRule(a, b, 2 * n); // Интеграл с шагом h/2
        return Math.Abs(I2 - I1) / 15; // Погрешность по формуле Рунге
    }

    static void Main(string[] args)
    {
        double a = 0.5; // Начало интервала
        double b = 1.7; // Конец интервала
        double eps = 1e-4; // Заданная точность 10^-4

        int n = 1; // Начальное число разбиений

        double integral = SimpsonRule(a, b, n);
        double error = RungeControl(a, b, n);

        // Увеличиваем число разбиений, пока погрешность не будет меньше eps
        while (error > eps)
        {
            n *= 2;
            integral = SimpsonRule(a, b, n);
            error = RungeControl(a, b, n);
        }

        Console.WriteLine($"Интеграл: {integral}");
        Console.WriteLine($"Погрешность: {error}");
    }
}
