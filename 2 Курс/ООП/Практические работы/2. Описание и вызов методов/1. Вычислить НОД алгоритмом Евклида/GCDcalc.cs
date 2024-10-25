using ControlzEx.Standard;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace _1.Вычислить_НОД_алгоритмом_Евклида
{
    public static class GCDcalc
    {
        /// <summary>
        /// Метод евклида
        /// </summary>
        /// <param name="a"></param>
        /// <param name="b"></param>
        /// <returns></returns>
        public static int Euclid(int a, int b)
        {
            while (a != 0 && b != 0)
            {
                if (a > b)
                {
                    a -= b;
                }
                else
                {
                    b -= a;
                }
            }

            return a + b;
        }

        /// <summary>
        /// Метод евклида
        /// </summary>
        /// <param name="a"></param>
        /// <param name="b"></param>
        /// <returns></returns>
        public static int Euclid(int a, int b, int c)
        {
            int intermediate = Euclid(a, b);
            while (intermediate != 0 && c != 0)
            {
                if (intermediate > c)
                {
                    intermediate -= c;
                }
                else
                {
                    c -= intermediate;
                }
            }

            return intermediate + c;
        }

        /// <summary>
        /// Метод евклида
        /// </summary>
        /// <param name="a"></param>
        /// <param name="b"></param>
        /// <returns></returns>
        public static int Euclid(int a, int b, int c, int d)
        {
            int intermediate = Euclid(a, b, c);
            while (intermediate != 0 && d != 0)
            {
                if (intermediate > d)
                {
                    intermediate -= d;
                }
                else
                {
                    d -= intermediate;
                }
            }

            return intermediate + d;
        }

        /// <summary>
        /// Метод евклида
        /// </summary>
        /// <param name="a"></param>
        /// <param name="b"></param>
        /// <returns></returns>
        public static int Euclid(int a, int b, int c, int d, int e)
        {
            int intermediate = Euclid(a, b, c, d);
            while (intermediate != 0 && e != 0)
            {
                if (intermediate > e)
                {
                    intermediate -= e;
                }
                else
                {
                    e -= intermediate;
                }
            }

            return intermediate + e;
        }

        /// <summary>
        /// Методот Штейна
        /// </summary>
        /// <param name="a"></param>
        /// <param name="b"></param>
        /// <returns></returns>
        /// <summary>
        /// Метод наибольшего общего делителя бинарным методом Евклида
        /// </summary>
        /// <param name="a"></param>
        /// <param name="b"></param>
        /// <returns></returns>
        public static int Shtein(int a, int b)
        {
            int k;
            if (a == 0 || b == 0)
                return a | b;

            for (k = 0; ((a | b) & 1) == 0; ++k)
            {
                a >>= 1;
                b >>= 1;
            }

            while ((a & 1) == 0)
                a >>= 1;

            do
            {
                while ((b & 1) == 0) // Loop x
                    b >>= 1;

                if (a < b)
                {
                    b -= a;
                }
                else
                {
                    int intermediate = a - b;
                    a = b;
                    b = intermediate;
                }
                b >>= 1;
            } while (b != 0);
            a <<= k;
            return a;
        }
        /// <summary>
        /// Метод наибольшего общего делителя бинарным методом Евклида
        /// </summary>
        /// <param name="a"></param>
        /// <param name="b"></param>
        /// <param name="c"></param>
        /// <returns></returns>
        public static int Shtein(int a, int b, int c)
        {
            int result = Shtein(a, b);
            int k;
            if (result == 0 || c == 0)
                return result | c;

            for (k = 0; ((result | c) & 1) == 0; ++k)
            {
                result >>= 1;
                c >>= 1;
            }

            while ((result & 1) == 0)
                result >>= 1;

            do
            {
                while ((c & 1) == 0)
                    c >>= 1;

                if (result < c)
                {
                    c -= result;
                }
                else
                {
                    int intermediate = result - c;
                    result = c;
                    c = intermediate;
                }
                c >>= 1;
            } while (c != 0);
            result <<= k;
            return result;
        }
        /// <summary>
        /// Метод наибольшего общего делителя бинарным методом Евклида
        /// </summary>
        /// <param name="a"></param>
        /// <param name="b"></param>
        /// <param name="c"></param>
        /// <param name="d"></param>
        /// <returns></returns>
        public static int Shtein(int a, int b, int c, int d)
        {
            int result = Shtein(a, b, c);

            int k;
            if (result == 0 || d == 0)
                return result | d;

            for (k = 0; ((result | d) & 1) == 0; ++k)
            {
                result >>= 1;
                d >>= 1;
            }

            while ((result & 1) == 0)
                result >>= 1;

            do
            {
                while ((d & 1) == 0) // Loop x
                    d >>= 1;

                if (result < d)
                {
                    d -= result;
                }
                else
                {
                    int intermediate = result - d;
                    result = d;
                    d = intermediate;
                }
                d >>= 1;
            } while (d != 0);
            result <<= k;
            return result;
        }
        /// <summary>
        /// Метод наибольшего общего делителя бинарным методом Евклида
        /// </summary>
        /// <param name="a"></param>
        /// <param name="b"></param>
        /// <param name="c"></param>
        /// <param name="d"></param>
        /// <param name="e"></param>
        /// <returns></returns>
        public static int Shtein(int a, int b, int c, int d, int e)
        {
            int result = Shtein(a, b, c, d);

            int k;
            if (result == 0 || e == 0)
                return result | e;

            for (k = 0; ((result | e) & 1) == 0; ++k)
            {
                result >>= 1;
                e >>= 1;
            }

            while ((result & 1) == 0)
                result >>= 1;

            do
            {
                while ((e & 1) == 0) // Loop x
                    e >>= 1;

                if (result < e)
                {
                    e -= result;
                }
                else
                {
                    int intermediate = result - e;
                    result = e;
                    e = intermediate;
                }
                e >>= 1;
            } while (e != 0);
            result <<= k;
            return result;
        }

    }
}