using System;

class Program
{
    // Функция для оценки интеграла методом Монте-Карло
    static double[] MonteCarloIntegral(Func<double, double> func, double a, double b, int n, int iteration)
    {
        double J = 0; // Суммы значений функции в точках
        double[] result = new double[2] { 0, 0 }; // Массив для хранения результатов
        double s_2q = 0, s_q2 = 0; // Среднего квадрат и квадрат среднего значения
        Random rand = new Random();

        for (int k = 0; k < iteration; k++)
        {
            // Генерация случайных точек и вычисление суммы значений функции в этих точках
            for (int i = 1; i <= n; i++)
            {
                double u = a + rand.NextDouble() * (b - a); // Случайную точка
                J += func(u);
            }
            J = ((b - a) / n) * J; // Оценка интеграла по методу Монте-Карло
            result[0] += J;

            s_2q += J * J; // Вычисление среднего квадрата
            s_q2 += J; // Значение вычисления квадрата среднего значения
        }

        // Среднее значение среднего квадрата и квадрата среднего значения
        s_2q /= iteration;
        s_q2 /= iteration;

        // Среднее значение оценки интеграла
        result[0] /= iteration;

        // Оценка погрешности по методу Монте-Карло
        result[1] = Math.Sqrt(s_2q - (s_q2 * s_q2));
        return result;
    }

    static void Main(string[] args)
    {
        Func<double, double> func = x => x * Math.Exp(x) / Math.Pow(1 + x, 2); // Функция
        double a = 0.3; // Нижний предел интегрирования
        double b = 1.1; // Верхний предел интегрирования
        int n = 1000; // Количество разбиений
        int iteration = 100; // Количество итераций метода Монте-Карло

        double[] result = MonteCarloIntegral(func, a, b, n, iteration);

        Console.WriteLine("Integral estimate: " + result[0]);
        Console.WriteLine("Error estimate: " + result[1]);
    }
}
