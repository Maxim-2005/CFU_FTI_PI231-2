using System;
using System.Windows;
using System.Security.Cryptography;
using System.Runtime.InteropServices;
using System.Text;


namespace _3.Использование_Checked_AnChecked
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

        private string Calculate()
        {
            int firstdigit = Convert.ToInt32(first.Text);
            int seconddigit = Convert.ToInt32(second.Text);

            return (firstdigit * seconddigit).ToString();
        }

        private void Multiply_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                checked
                {
                    result.Text = Calculate();
                }
                
            }
            catch (OverflowException ex)
            {
                MessageBox.Show(ex.Message);
            }
            catch (FormatException ex)
            {
                MessageBox.Show(ex.Message);
            }
        }
    }
}
