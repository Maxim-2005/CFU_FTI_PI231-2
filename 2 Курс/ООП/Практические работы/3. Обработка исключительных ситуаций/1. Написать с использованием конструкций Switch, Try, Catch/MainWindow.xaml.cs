using System.Windows;


namespace _1.Использование_конструкций_Switch_Try_Catch
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

        private void shutdown_Click(object sender, RoutedEventArgs e)
        {
            var sw = new Switch();
            try
            {
                sw.DisconnectPowerGenerator();
            }
            catch (PowerGeneratorCommsException ex)
            {
                MessageBox.Show($"Исключение на 1 этапе, {ex.Message}\n");
            }

            try
            {
                sw.VerifyPrimaryCoolantSystem();
            }
            catch (CoolantTemperatureReadException ex)
            {
                MessageBox.Show($"Исключение на 2 этапе, {ex.Message}\n");
            }
            catch (CoolantPressureReadException ex)
            {
                MessageBox.Show($"Исключение на 2 этапе, {ex.Message}\n");
            }

            try
            {
                sw.VerifyBackupCoolantSystem();
            }
            catch (CoolantTemperatureReadException ex)
            {
                MessageBox.Show($"Исключение на 3 этапе, {ex.Message}\n");
            }
            catch (CoolantPressureReadException ex)
            {
                MessageBox.Show($"Исключение на 3 этапе, {ex.Message}\n");
            }

            try
            {
                sw.GetCoreTemperature();
            }
            catch (CoreTemperatureReadException ex)
            {
                MessageBox.Show($"Исключение на 4 этапе, {ex.Message}\n");
            }

            try
            {
                sw.InsertRodCluster();
            }
            catch (RodClusterReleaseException ex)
            {
                MessageBox.Show($"Исключение на 5 этапе, {ex.Message}\n");
            }

            try
            {
                sw.GetCoreTemperature();
            }
            catch (CoreTemperatureReadException ex)
            {
                MessageBox.Show($"Исключение на 6 этапе, {ex.Message}\n");
            }

            try
            {
                sw.GetRadiationLevel();
            }
            catch (CoreRadiationLevelReadException ex)
            {
                MessageBox.Show($"Исключение на 7 этапе, {ex.Message}\n");
            }

            try
            {
                sw.SignalShutdownComplete();
            }
            catch (SignallingException ex)
            {
                MessageBox.Show($"Исключение на 8 этапе, {ex.Message}\n");
            }
        }
    }
}
