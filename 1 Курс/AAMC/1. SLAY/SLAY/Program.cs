using System;

public class Program
{
    public static double SimpsonIntegral(Func<double, double> func, double a, double b, double e)
    {
        double rungeErr = e + 1;    // Погрешность Рунге, инициализированная значением, превышающим e
        double jTemp = 0;   // Временное значение интеграла
        int n = 2;  // Начальное количество разбиений
        double integral = 0;   // Результат интегрирования

        while (true)
        {
            if (rungeErr < e)
                break;

            double rightMultiplier = func(a) + func(b); // Правый множитель в формуле Симпсона.
            jTemp = integral;  // Сохраняем предыдущее значение интеграла

            // Суммируем значения функции на четных и нечетных узлах
            for (int i = 1; i < n; i++)
            {
                rightMultiplier += (2 + 2 * (i % 2)) * func(a + (b - a) * (i / (double)n));
            }

            // Вычисляем значение интеграла по формуле Симпсона
            integral = ((b - a) / (3 * n)) * rightMultiplier;

            if (n != 2) // Проверяем, не первая ли итерация
                rungeErr = Math.Abs(integral - jTemp) / 15.0;  // Вычисляем погрешность Рунге

            Console.WriteLine("n:" + n);
            Console.WriteLine("integral:" + integral);
            Console.WriteLine("runge:" + rungeErr);

            n *= 2;
        }

        return integral;
    }

    public static void Main(string[] args)
    {
        // Пример использования:
        Func<double, double> func = x => (Math.Log(x + Math.Pow((Math.Pow(x, 2) - 0.25), 1 / 2)) / (2 * Math.Pow(x, 2))); ; // функция
        double result = SimpsonIntegral(func, 0.5, 1.7, 0.0001);
        Console.WriteLine("Result: " + result);
    }
}
