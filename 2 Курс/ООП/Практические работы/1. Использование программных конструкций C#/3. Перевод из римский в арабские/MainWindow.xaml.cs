using static _3.Перевод_из_римский_в_арабские.TranslateFile;
using System.Collections.Generic;
using System.Windows;
using System.Windows.Controls;

namespace _3.Перевод_из_римский_в_арабские
{
    /// <summary>
    /// Логика взаимодействия для MainWindow.xaml
    // </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
            Select.ItemsSource = new List<string>
            {
                { "Арабские цифры" },
                { "Римские цифры" }
            };
        }

        private void Translate_Click(object sender, RoutedEventArgs e)
        {
            string inputValue = Input.Text;

            if (Select.Text == _currentFromType)
            {
                if (!int.TryParse(inputValue, out int arabicNumber) || arabicNumber < 0)
                {
                    MessageBox.Show("Надо ввести целое положительное число");
                    return;
                }

                string romanResult = _3.Перевод_из_римский_в_арабские.TranslateFile.ConvertFromArabicToRoman(arabicNumber);
                Result.Text = romanResult;
            }
            else
            {
                inputValue = inputValue.ToUpper();
                string arabicResult = _3.Перевод_из_римский_в_арабские.TranslateFile.ConvertFromRomanToArabic(inputValue);

                if (string.IsNullOrEmpty(arabicResult))
                {
                    MessageBox.Show("Неверный формат римских цифр");
                }
                else
                {
                    Result.Text = arabicResult;
                }
            }
        }

        private void Select_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (Select.SelectedItem is ComboBoxItem selectedItem)
            {
                _3.Перевод_из_римский_в_арабские.TranslateFile._currentFromType = selectedItem.Content.ToString();
            }
        }
    }
}
