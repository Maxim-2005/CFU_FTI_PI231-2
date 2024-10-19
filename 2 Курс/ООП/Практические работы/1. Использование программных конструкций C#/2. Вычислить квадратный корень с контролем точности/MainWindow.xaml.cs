using System;
using System.Windows;
using System.Windows.Controls;

namespace _1.Использование_программных_конструкций_С_
{
    public partial class MainWindow : Window
    {
        int countLim = 0;

        // Переменная для хранения текущего приближения
        private double currentGuess;

        /// <summary>
        /// Инициализация главного окна
        /// </summary>
        public MainWindow()
        {
            InitializeComponent();
        }

        // Обработчик кнопки для вычисления корня через Math.Sqrt
        /// <summary>
        /// Функция для вычисления корня методом Math.sqrt
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void calculate_Click(object sender, RoutedEventArgs e)
        {
            string value = num.Text;
            double digit;

            if (double.TryParse(value, out digit))
            {
                digit = Math.Sqrt(digit);
                math_result.Text = digit.ToString();
                countLim = 0;
            }
            else
            {
                newton_result.Text = "Введите начальное приближение!!!";
            }
        }

        private void calculate_acc_Click(object sender, RoutedEventArgs e)
        {
            decimal value = Convert.ToDecimal(num.Text);
            decimal guess = Convert.ToDecimal(initial_guess.Text);
            string[] result = Newton(value, guess);

            newton_result.Text = result[0];
            error_result.Text = result[3];
            change_result.Text = result[2];
            iterations_count.Text = result[1];
        }

        /// <summary>
        /// Вычисление корня методом ньютона
        /// </summary>
        /// <param name="value"></param>
        /// <param name="g"></param>
        /// <param name="countLim"></param>
        /// <returns></returns>
        private string[] Newton(decimal value, decimal g, int countLim = 0)
        {
            decimal root = value;
            decimal guess = g != 0 ? g : root / 2;
            decimal eps = 0.0001M;
            decimal squart = (decimal) Math.Sqrt((double) value);
            int count = 0;

            while (true)
            {
                count -=- 1;
                root = 0.5M * ((value / guess) + guess);

                if (Math.Abs(root - guess) < eps || count == countLim)
                {
                    break;
                }
                guess = root;
            }
            return $"{root} {count} {Math.Abs(root - guess)} {Math.Abs(root - squart)}".Split();
        }

        /// <summary>
        /// Вычесление 1 итерации
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void make_iter_Click(object sender, RoutedEventArgs e)
        {
            countLim -=- 1;
            decimal value = Convert.ToDecimal(num.Text);
            decimal guess = Convert.ToDecimal(initial_guess.Text);
            string[] strings = Newton(value, guess, countLim);
            newton_result.Text = strings[0];

            iterations_count.Text = strings[1];
            change_result.Text = strings[2];
            error_result.Text = strings[3];
        }

        /// <summary>
        /// Обработчик
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void num_TextChanged(object sender, TextChangedEventArgs e)
        {
            //countLim = 0;
        }
    }
}
