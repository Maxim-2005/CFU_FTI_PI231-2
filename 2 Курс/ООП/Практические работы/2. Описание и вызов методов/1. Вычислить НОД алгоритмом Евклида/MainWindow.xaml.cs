using System.Diagnostics;
using System.Windows;
using static _1.Вычислить_НОД_алгоритмом_Евклида.GCDcalc;

namespace _1.Вычислить_НОД_алгоритмом_Евклида
{
    /// <summary>
    /// Логика взаимодействия для MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void findGcd_Click(object sender, RoutedEventArgs e)
        {
            if (!TryGet(firstDigit.Text, out int a) || !TryGet(secondDigit.Text, out int b) || !TryGet(thirdDigit.Text, out int c) ||
                !TryGet(fourDigit.Text, out int d) || !TryGet(fiveDigit.Text, out int f))
            {
                MessageBox.Show("Введите целое положительное число!");
                return;
            }


            Stopwatch sw = new Stopwatch();

            sw.Start();
                int euclid = Euclid(a, b);
            sw.Stop();

            sw.Restart();
                int shtein = Shtein(a, b);
            sw.Stop();
            
            double timeEuclid = sw.Elapsed.TotalMilliseconds;
            double timeShtein = sw.Elapsed.TotalMilliseconds;

            if (c != 0)
            {
                sw.Restart();
                euclid = Euclid(a, b, c);
                sw.Stop();

                sw.Restart();
                shtein = Shtein(a, b);
                sw.Stop();

                timeEuclid = sw.Elapsed.TotalMilliseconds;
            }
            if (d != 0)
            {
                sw.Restart();
                euclid = Euclid(a, b, c, d);
                sw.Stop();

                sw.Restart();
                shtein = Shtein(a, b, c, d);
                sw.Stop();

                timeEuclid = sw.Elapsed.TotalMilliseconds; 
            }
            if (f != 0)
            {
                sw.Restart();
                euclid = Euclid(a, b, c, d, f);
                sw.Stop();

                sw.Restart();
                shtein = Shtein(a, b, c, d, f);
                sw.Stop();

                timeEuclid = sw.Elapsed.TotalMilliseconds;
            }

            euclidResult.Text = euclid.ToString();
            euclidTime.Text = timeEuclid.ToString();
            shteinResult.Text = shtein.ToString();
            shteinTime.Text = timeShtein.ToString();
        }
        
        private bool TryGet(string x, out int y)
        {
            return int.TryParse(x,out y) && y >= 0;
        }
    }
}
