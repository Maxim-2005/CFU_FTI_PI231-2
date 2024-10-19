using System;

class Program
{
    static void Main(string[] args)
    {
        /** Типы данных неявного преобразования:
         * sbyte = short, int, long, float, dobule, decimal.
         * byte = short, ushort, int, uint, long, ulong, double, decimal.
         * short = int, long, float, double, decimal.
         * ushort = int, uint, long ulong, float, double, decimal
         * int = long, float, double, decimal.
         * uint = long, ulong, float, double, decimal.
         * long = float, double, decimal.
         * ulong = float, double, decimal.
         * char = ushort, int, uint, long, ulong, float, double, decimal.
         * float = double.
         *
         * Таблица явных преобразований:
         * sbyte = byte, ushort, uint, ulong
         * byte = sbyte
         * short = sbyte, byte, ushort, uint, ulong.
         * ushort = sbyte, byte или short
         * int = sbyte, byte, short, ushort, uint, ulong.
         * uint = sbyte, byte, short, ushort.
         * long = sbyte, byte, short, ushort, int, uint, ulong.
         * ulong = sbyte, byte, short, ushort, int, uint, long.
         * float = sbyte, byte, short, ushort, int, uint, long, ulong, decimal.
         * double = sbyte, byte, short, ushort, int, uint, long, ulong, float, decimal.
         * decimal = sbyte, byte, short, ushort, int, uint, long, ulong, float, double.
        **/

        // Неявное преобразование
        int intNumber = 10;
        double doubleNumber = intNumber; // неявное преобразование
        Console.WriteLine($"Неявное преобразование: {intNumber} -> {doubleNumber}");

        // Явное преобразование
        doubleNumber = 9.78;
        intNumber = (int)doubleNumber; // явное преобразование
        Console.WriteLine($"Явное преобразование: {doubleNumber} -> {intNumber}");

        // Приведение типов с использованием as и is
        object obj = "Это строка";
        if (obj is string str)
        {
            Console.WriteLine($"Приведение с использованием is: {obj} -> {str}");
        }

        // Пример использования класса Convert
        string numberString = "100";
        int convertedValue = Convert.ToInt32(numberString);
        Console.WriteLine($"Преобразование с помощью Convert: \"{numberString}\" -> {convertedValue}");

        // Пример использования TryParse
        string input = "123.45";
        if (double.TryParse(input, out double parsedValue))
        {
            Console.WriteLine($"Преобразование с использованием TryParse: \"{input}\" -> {parsedValue}");
        }

        // Запрос на ввод вещественного числа
        Console.WriteLine("Введите вещественное число со знаком:");
        string userInput = Console.ReadLine();
        if (double.TryParse(userInput, out double userValue))
        {
            Console.WriteLine($"Вы ввели: {userValue}");
        }
        else
        {
            Console.WriteLine($"Неверный формат: \"{userInput}\"");
        }

        // Ожидание ввода перед закрытием консоли
        Console.WriteLine("Нажмите любую клавишу для выхода...");
        Console.ReadKey();
    }
}
