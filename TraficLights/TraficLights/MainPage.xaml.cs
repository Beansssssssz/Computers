using System;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;


// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

namespace TraficLights
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class MainPage : Page
    {
        private TraficLight _traficLight;
        private Dino _dino;
        private Santa _santa;

        public MainPage()
        {
            this.InitializeComponent();
        }

        private void btnManual_Click(object sender, RoutedEventArgs e)
        {
            _traficLight.SetState();
        }

        private void btnAuto_Click(object sender, RoutedEventArgs e)
        {
            _traficLight.IsAuto =! _traficLight.IsAuto;
            if (_traficLight.IsAuto)
                btnAuto.Content = "Stop";
            else
                btnAuto.Content = "Auto";
            btnManual.IsEnabled =! _traficLight.IsAuto;
        }

        private void Page_Loaded(object sender, RoutedEventArgs e)
        {
           _traficLight = new TraficLight(RedElp, YellowElp, GreenElp);
            _santa = new Santa(imgSanta);
            _dino = new Dino(imgDino);
        }
    }
}
