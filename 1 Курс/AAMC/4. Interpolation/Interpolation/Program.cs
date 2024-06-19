using System;

public class LagrangeInterpolation
{
    private static double BasicPolynomial(double x, double[] xVal, int i)
    {
        double Div = 1;
        double Result = 1;
        for (int j = 0; j < xVal.Length; j++)
        {
            if (j != i)
            {
                Result *= (x - xVal[j]);
                Div *= (xVal[i] - xVal[j]);
            }
        }
        return Result / Div;
    }

    private static Func<double, double> Lagrange(double[] xVal, double[] yVal)
    {
        return (double x) =>
        {
            double Result = 0;
            for (int i = 0; i < yVal.Length; i++)
            {
                Result += yVal[i] * BasicPolynomial(x, xVal, i);
            }
            return Result;
        };
    }

    public static void Main(string[] args)
    {
        double[] xVal = { 1, 2, 3, 4, 5 };
        double[] yVal = { 0.25, 0.111, 0.071, 0.053, 0.042 };

        Func<double, double> lagPol = Lagrange(xVal, yVal);

        Console.WriteLine("Enter a value for x:");
        double x = double.Parse(Console.ReadLine());
        double y = lagPol(x);

        Console.WriteLine($"x = {x}\t y = {y}");
    }
}