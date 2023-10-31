using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Windows.UI.Xaml.Controls;

namespace TraficLights
{
  public class Santa : Characters
  {
    public Santa(Image ImageAnimal) : base(ImageAnimal)
    {

    }

    protected override void MatchGifToState()
    {
      switch (_state)
      {
        case StateType.standing:
          _bitmapImage.UriSource = new Uri("ms-appx:///Assets/Character/Santa/santa_idle.gif");
          break;
        case StateType.ready:
          _bitmapImage.UriSource = new Uri("ms-appx:///Assets/Character/Santa/santa_jump.gif");
          break;
        default:
          _bitmapImage.UriSource = new Uri("ms-appx:///Assets/Character/Santa/santa_run.gif");
          break;
      }
    }
  }
}
