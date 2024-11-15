using System;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows;

namespace Task4
{
    internal class Make_Grid
    {
        public void InitializeGrid(Grid grid, int columns, int rows)
        {
            if (grid == null)
                return;

            grid.Children.Clear();
            grid.ColumnDefinitions.Clear();
            grid.RowDefinitions.Clear();

            for (int x = 0; x < columns; x++)
            {
                grid.ColumnDefinitions.Add(new ColumnDefinition() { Width = new GridLength(1, GridUnitType.Star) });
            }

            for (int y = 0; y < rows; y++)
            {
                grid.RowDefinitions.Add(new RowDefinition() { Height = new GridLength(1, GridUnitType.Star) });
            }

            var rand = new Random();

            for (int y = 0; y < rows; y++)
            {
                for (int x = 0; x < columns; x++)
                {
                    double Value = rand.NextDouble()*10; 

                    TextBox textBox = new TextBox
                    {
                        Text = Value.ToString("F2"),
                        VerticalAlignment = VerticalAlignment.Center,
                        HorizontalAlignment = HorizontalAlignment.Center,
                        TextAlignment = TextAlignment.Center
                    };

                    Border border = new Border
                    {
                        BorderThickness = new Thickness(1),
                        BorderBrush = Brushes.Black,
                        Child = textBox
                    };

                    border.SetValue(Grid.RowProperty, y);
                    border.SetValue(Grid.ColumnProperty, x);

                    grid.Children.Add(border);
                }
            }
        }


        public void GetValuesFromGrid(Grid grid, Matrix matrix)
        {
            int rows = matrix.Data.GetLength(0);
            int columns = matrix.Data.GetLength(1);

            for (int r = 0; r < rows; r++)
            {
                for (int c = 0; c < columns; c++)
                {
                    Border border = (Border)grid.Children[r * columns + c];
                    TextBox t = (TextBox)border.Child;
                    matrix.SetValue(r, c, double.Parse(t.Text));
                }
            }
        }

        public void DisplayResult(Grid grid, Matrix matrix)
        {
            int rows = matrix.Data.GetLength(0);
            int columns = matrix.Data.GetLength(1);

            InitializeGrid(grid, columns, rows);

            for (int r = 0; r < rows; r++)
            {
                for (int c = 0; c < columns; c++)
                {
                    Border border = (Border)grid.Children[r * columns + c];
                    TextBox t = (TextBox)border.Child;
                    t.Text = matrix.GetValue(r, c).ToString();
                }
            }
        }
    }
}
