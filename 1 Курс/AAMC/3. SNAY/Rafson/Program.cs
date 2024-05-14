using System;

class Program
{
    static (double, double) Equations(double x, double y)
    {
        double func1 = Math.Cos(y + 0.5) + x - 0.8;
        double func2 = Math.Sin(x) - 2 * y - 1.6;
        return (func1, func2);
    }

    // Частные производные
    static (double, double, double, double) Jacobian(double x, double y)
    {
        double df1_dx = 1;
        double df1_dy = -Math.Sin(y + 0.5);
        double df2_dx = Math.Cos(x);
        double df2_dy = -2;
        return (df1_dx, df1_dy, df2_dx, df2_dy);
    }

    // Заполнение матрицы
    static (double, double) NewtonRaphson(double x, double y, double tolerance)
    {
        while (true)
        {
            (double f1, double f2) = Equations(x, y);
            (double df1_dx, double df1_dy, double df2_dx, double df2_dy) = Jacobian(x, y);

            double determinant = df1_dx * df2_dy - df1_dy * df2_dx;

            double inv_df1_dx = df2_dy / determinant;
            double inv_df1_dy = -df1_dy / determinant;
            double inv_df2_dx = -df2_dx / determinant;
            double inv_df2_dy = df1_dx / determinant;

            double dx = inv_df1_dx * f1 + inv_df1_dy * f2;
            double dy = inv_df2_dx * f1 + inv_df2_dy * f2;

            x -= dx;
            y -= dy;

            if (Math.Abs(dx) < tolerance && Math.Abs(dy) < tolerance)
            {
                break;
            }
        }
        return (x, y);
    }

    static void Main(string[] args)
    {
        // Первое схождение
        (double x, double y) = NewtonRaphson(-2, -2, 1e-4);
        Console.WriteLine("x = " + x + "\t" + "y = " + y);
    }
}
