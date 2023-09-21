using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Windows.UI;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Shapes;

namespace TraficLights
{
    class TraficLight
    {
        public enum TraficLightState
        {
            Red,
            Yellow,
            Green
        }
        private TraficLightState _state;//the state that a light can be in

        private Ellipse _elpRed;
        private Ellipse _elpGreen;
        private Ellipse _elpYellow;

        private bool _isAuto;

        public TraficLight(Ellipse elpRed ,Ellipse elpGreen, Ellipse elpYellow)
        {
            _elpRed = elpRed;
            _elpGreen = elpGreen;
            _elpYellow = elpYellow;
            _state = TraficLightState.Red;
        }

        /// <summary>
        /// the function movest the traffic light to its necct state in a infinite loop
        /// </summary>
        public void SetState()
        {
            Reset();
            switch (_state)
            {
                case TraficLightState.Red:
                    _state = TraficLightState.Yellow;
                    _elpYellow.Fill = new SolidColorBrush(Colors.Yellow);
                    break;
                case TraficLightState.Yellow:
                    _state = TraficLightState.Green;
                    _elpGreen.Fill = new SolidColorBrush(Colors.Green);
                    break;
                default:
                    _state = TraficLightState.Red;
                    _elpRed.Fill = new SolidColorBrush(Colors.Red);
                    break;
            }
        }

        /// <summary>
        /// the functions resets the traficlight colors.
        /// </summary>
        private void Reset()
        {
            _elpRed.Fill = new SolidColorBrush(Colors.Gray);
            _elpGreen.Fill = new SolidColorBrush(Colors.Gray);
            _elpYellow.Fill = new SolidColorBrush(Colors.Gray);
        }
    }
}
