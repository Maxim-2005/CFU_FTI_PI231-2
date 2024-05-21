using System;
using System.Windows;
using MathNet.Numerics;
using System.Windows.Controls;
using OxyPlot;
using OxyPlot.Series;
using MathNet.Numerics.Interpolation;
using OxyPlot.Wpf;

namespace SplineInterpolation
{
    public partial class MainWindow : System.Windows.Window
    {
        public PlotModel PlotModel { get; private set; }

        public MainWindow()
        {
            InitializeComponent();
            PlotModel = new PlotModel { Title = "Cubic Spline Interpolation" };
            CreatePlot();
            plotView.DataContext = this;
        }

        private void CreatePlot()
        {
            // Создание точек для интерполяции функции sin(x)
            int numberOfPoints = 5; // Количество точек для интерполяции
            double[] x = new double[numberOfPoints];
            double[] y = new double[numberOfPoints];

            // Заполнение массивов x и y значениями функции sin(x)
            for (int i = 0; i < numberOfPoints; i++)
            {
                // Вычисление значения x в диапазоне [0, 2 * Pi]
                x[i] = i * 2 * Math.PI / (numberOfPoints - 1);
                // Значение y - sin(x)z
                y[i] = Math.Exp(x[i]);
            }

            // Создание кубического сплайна для интерполяции
            var spline = CubicSpline.InterpolateNatural(x, y);

            // Очистить предыдущие данные графика, если такие были
            PlotModel.Series.Clear();

            // Создать ScatterSeries для отображения исходных данных точек
            var scatterSeries = new ScatterSeries { MarkerType = MarkerType.Circle };
            for (int i = 0; i < x.Length; i++)
            {
                scatterSeries.Points.Add(new ScatterPoint(x[i], y[i]));
            }

            // Создать LineSeries для отображения интерполированной кривой
            var lineSeries = new LineSeries { Title = "Cubic Spline Interpolation", StrokeThickness = 2 };
            for (double i = x[0]; i <= x[x.Length - 1]; i += 0.1)
            {
                lineSeries.Points.Add(new DataPoint(i, spline.Interpolate(i)));
            }

            // Добавить созданные серии в PlotModel
            PlotModel.Series.Add(scatterSeries);
            PlotModel.Series.Add(lineSeries);
        }

    }
}
