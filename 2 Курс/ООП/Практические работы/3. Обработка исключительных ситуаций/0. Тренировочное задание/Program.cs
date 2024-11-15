using System;
using System.Security.Cryptography;
using System.Text;

namespace _0.Тренировочное_задание
{
    internal class Program
    {
        private static void Hash()
        {
            string fullName = "Покидько Максим Сергеевич";

            Console.WriteLine($"MD5 хэш: {ComputeHash(fullName, "MD5")}");
            Console.WriteLine($"SHA256 хэш: {ComputeHash(fullName, "SHA256")}");
            Console.WriteLine();
        }

        static string ComputeHash(string input, string algorithm)
        {
            using (var hashAlgorithm = HashAlgorithm.Create(algorithm))
            {
                byte[] hashBytes = hashAlgorithm.ComputeHash(Encoding.UTF8.GetBytes(input));
                return BitConverter.ToString(hashBytes).Replace("-", "").ToLower();
            }
        }

        static void Main(string[] args)
        {
            Hash();
            try
            {
                try
                {
                    int i = Convert.ToInt32(Console.ReadLine());
                    int x = 5;
                    int y = x / i;
                    Console.WriteLine("x = {0}, y = {1}", x, y);
                }
                catch (DivideByZeroException e)
                {
                    Console.WriteLine("Попытка деления на ноль", e.ToString());
                }
                catch (FormatException e)
                {
                    Console.WriteLine("Введено не целое число! Исключение", e.ToString());
                }
                catch
                {
                    Console.WriteLine("Неизвестная ошибка. Перезапустите программу");
                    throw;
                }
                finally
                {
                    Console.WriteLine("Выполнили блок finally");
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
                Console.WriteLine(ex.StackTrace);
                Console.WriteLine(ex.TargetSite);
                Console.WriteLine(ex.InnerException);
                Console.WriteLine(ex.Source);
                Console.WriteLine(ex.Data);
                Console.WriteLine(ex.HelpLink);
            }
        }
    }
}
