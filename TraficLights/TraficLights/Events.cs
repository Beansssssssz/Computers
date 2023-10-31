using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TraficLights
{
  public static class Events
  {
    public static Action<TraficLight.TraficLightState> StateChanged;// when the traffic light changed states
  }
}
