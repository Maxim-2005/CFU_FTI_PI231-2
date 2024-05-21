using System;

class Program
{
    static double Function(double x)
    {
        return 2 * x - Math.Log(x) - 4;
    }

    static double Dichotomy(double a, double b, double e)
    {
        double c = 0.0;
        while (Math.Abs(b - a) > e)
        {
            c = (a + b) / 2.0;

            if (Function(a) * Function(c) < 0)
                b = c;
            else if (Function(c) * Function(b) < 0)
                a = c;
            else
                return 0;
        }

        return c;
    }

    static double SecantMethod(double x0, double x1, double epsilon)
    {
        double x2;

        do
        {
            x2 = x1 - Function(x1) * (x1 - x0) / (Function(x1) - Function(x0));
            x0 = x1;
            x1 = x2;
        } while (Math.Abs(Function(x2)) > epsilon);

        return x2;
    }

    static void Main(string[] args)
    {
        double a = 1; // Начальное значение интервала
        double b = 5; // Конечное значение интервала
        double epsilon = 1e-10; // Точность
        double step = 0.1; // Шаг

        // Находим корни уравнения с помощью графического метода
        static void GraphicalMethod(double a, double b, double step)
        {
            double x = a;
            while (x <= b)
            {
                if (Function(x) * Function(x + step) < 0)
                {
                    Console.WriteLine($"Корень найденный между {x} и {x + step}");
                }
                x += step;
            }
        }

        GraphicalMethod(a, b, step);

        // Находим корни уравнения с помощью метода золотого сечения
        double rootDichotomy = Dichotomy(a, b, epsilon);
        Console.WriteLine("Корень найденый дихотомией: " + rootDichotomy);

        // Находим корни уравнения с помощью метода секущих
        double rootSecant = SecantMethod(a, b, epsilon);
        Console.WriteLine("Корень найденый методом секущих: " + rootSecant);
    }
}
