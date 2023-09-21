using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

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
        private TraficLightState state;//the state that a light can be in
    }
}
