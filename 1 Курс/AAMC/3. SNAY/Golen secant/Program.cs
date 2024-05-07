using System;

class Program
{
    static double Function(double x)
    {
        return x * x - Math.Cos(x);
        // return 2 * x - Math.Log(x) - 4;
    }

    static double GoldenSectionMethod(double a, double b, double epsilon)
    {
        double phi = (1 + Math.Sqrt(5)) / 2; // Золотое сечение
        double x1 = b - (b - a) / phi;
        double x2 = a + (b - a) / phi;

        while (Math.Abs(b - a) > epsilon)
        {
            if (Function(x1) < Function(x2))
            {
                b = x2;
            }
            else
            {
                a = x1;
            }

            x1 = b - (b - a) / phi;
            x2 = a + (b - a) / phi;
        }

        return (a + b) / 2;
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
        double a = -0.5; // Начальное значение интервала
        double b = 1; // Конечное значение интервала
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
        double rootGoldenSection = GoldenSectionMethod(a, b, epsilon);
        Console.WriteLine("Корень найденый золотым сечением: " + rootGoldenSection);

        // Находим корни уравнения с помощью метода секущих
        double rootSecant = SecantMethod(a, b, epsilon);
        Console.WriteLine("Корень найденый методом секущих: " + rootSecant);
    }
}
