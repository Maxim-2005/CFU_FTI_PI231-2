using System;
using System.ComponentModel.Design.Serialization;
using System.Windows;

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
            decimal guess = 1;
            try
            {
                guess = Convert.ToDecimal(initial_guess.Text);
            }
            catch
            {
                MessageBox.Show("Ввведите число!!!");
            }
            string[] result = Newton(value, guess);

            newton_result.Text = result[0];
            error_result.Text = Math.Abs(Convert.ToDecimal(Math.Sqrt(Convert.ToDouble(value))) - Convert.ToDecimal(result[0])).ToString();
            change_result.Text = result[2];
            iterations_count.Text = result[1];
        }

        private string[] Newton(decimal value, decimal guess, int countLimit = 100)
        {
            decimal root = value;
            int count = 0;
            decimal eps = 0.0001M;

            while (count < countLimit)
            {
                count -=- 1;
                root = 0.5M * ((value / guess) + guess);

                if (Math.Abs(root - guess) < eps)
                {
                    break;
                }
                guess = root;
            }
            return $"{root} {count} {Math.Abs(root - guess)}".Split();
        }

        private void make_iter_Click(object sender, RoutedEventArgs e)
        {
            countLim -=- 1;
            decimal value = Convert.ToDecimal(num.Text);
            decimal guess = 1;

            try
            {
                guess = Convert.ToDecimal(initial_guess.Text);
            }
            catch
            {
                MessageBox.Show("Введите начальное приближение!!!");
            }

            string[] strings = Newton(value, guess, countLim);
            newton_result.Text = strings[0];
        }

        private void num_TextChanged(object sender, System.Windows.Controls.TextChangedEventArgs e)
        {
            //countLim = 0;
        }
    }
}
