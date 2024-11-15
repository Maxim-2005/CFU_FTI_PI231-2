using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Обработка_исключительных_состояний_матриц
{
    /// <summary>
    /// Логика взаимодействия для MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private Matrix matrix1;
        private Matrix matrix2;
        private Matrix result;
        private Make_Grid make_Grid;

        public MainWindow()
        {
            InitializeComponent();

            make_Grid = new Make_Grid();
            InitializeMatrixGrids();
        }
        private void InitializeMatrixGrids()
        {
            UpdateMatrix1Grid();
            UpdateMatrix2Grid();
        }

        private void UpdateMatrix1Grid()
        {
            if (matrix1Columns != null && matrix1Rows != null && grid1 != null)
            {
                int rows = matrix1Rows.SelectedIndex + 1;
                int columns = matrix1Columns.SelectedIndex + 1;

                matrix1 = new Matrix(rows, columns);
                make_Grid.InitializeGrid(grid1, columns, rows);
            }
        }


        private void UpdateMatrix2Grid()
        {
            if (matrix2Columns != null && matrix1Columns != null && grid2 != null)
            {
                int rows = matrix1Columns.SelectedIndex + 1;
                int columns = matrix2Columns.SelectedIndex + 1;

                matrix2 = new Matrix(rows, columns);
                make_Grid.InitializeGrid(grid2, columns, rows);
            }
        }


        private void Matrix1Dimensions_Changed(object sender, SelectionChangedEventArgs e)
        {
            UpdateMatrix1Grid();
            UpdateMatrix2Grid();
        }

        private void Matrix2Dimensions_Changed(object sender, SelectionChangedEventArgs e)
        {
            UpdateMatrix2Grid();
        }

        private void Calculate_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                int m1rows = matrix1Rows.SelectedIndex + 1;
                int m1columns_m2rows = matrix1Columns.SelectedIndex + 1;
                int m2columns = matrix2Columns.SelectedIndex + 1;

                matrix1 = new Matrix(m1rows, m1columns_m2rows);
                matrix2 = new Matrix(m1columns_m2rows, m2columns);

                make_Grid.GetValuesFromGrid(grid1, matrix1);
                make_Grid.GetValuesFromGrid(grid2, matrix2);

                result = Matrix.Multiply(matrix1, matrix2);
                make_Grid.DisplayResult(grid3, result);
            }
            catch (FormatException ex)
            {
                MessageBox.Show(ex.Message);
            }
        }
    }
}
