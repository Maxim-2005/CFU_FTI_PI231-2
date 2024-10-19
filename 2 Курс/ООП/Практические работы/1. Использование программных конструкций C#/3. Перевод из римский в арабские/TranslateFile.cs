using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _3.Перевод_из_римский_в_арабские
{
    class TranslateFile
    {
        public static string _currentFromType = "Арабские цифры";
        public static string _currentToType = "Римские цифры";

        public static readonly Dictionary<int, string> _romanNumerals = new Dictionary<int, string>
        {
            { 1000, "M" },
            { 900, "CM" },
            { 500, "D" },
            { 400, "CD" },
            { 100, "C" },
            { 90, "XC" },
            { 50, "L" },
            { 40, "XL" },
            { 10, "X" },
            { 9, "IX" },
            { 5, "V" },
            { 4, "IV" },
            { 1, "I" }
        };

        public static readonly Dictionary<string, int> _romanToArabicMap = new Dictionary<string, int>
        {
            { "CM", 900 },
            { "M", 1000 },
            { "CD", 400 },
            { "D", 500 },
            { "XC", 90 },
            { "C", 100 },
            { "XL", 40 },
            { "L", 50 },
            { "IX", 9 },
            { "X", 10 },
            { "IV", 4 },
            { "V", 5 },
            { "I", 1 }
        };

        public static string ConvertFromArabicToRoman(int number)
        {
            StringBuilder result = new StringBuilder();

            foreach (var item in _romanNumerals)
            {
                int arabicValue = item.Key;
                string romanSymbol = item.Value;
                int count = number / arabicValue;
                number %= arabicValue;

                for (int i = 0; i < count; i++)
                {
                    result.Append(romanSymbol);
                }
            }
            return result.ToString();
        }

        public static string ConvertFromRomanToArabic(string romanNumeral)
        {
            int result = 0;

            foreach (var item in _romanToArabicMap)
            {
                int arabicValue = item.Value;
                string romanSymbol = item.Key;
                romanNumeral = romanNumeral.Replace(romanSymbol, "!");

                foreach (var character in romanNumeral)
                {
                    if (character == '!')
                    {
                        if (romanNumeral.Substring(0, 1) != "!")
                        {
                            return "";
                        }
                        result += arabicValue;
                    }
                }
                romanNumeral = romanNumeral.Replace("!", "");
            }

            return romanNumeral.Length == 0 ? result.ToString() : "";
        }

    }
}
