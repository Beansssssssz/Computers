using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Media.Imaging;

namespace TraficLights
{
  public abstract class Characters
  {
    public enum StateType {// the current state of the character
      standing,
      ready,
      going
    }

    private Image _imageAnimal;
    protected BitmapImage _bitmapImage;
    protected StateType _state;

    public Characters(Image imageAnimale)
    {
      _state = StateType.standing;
      _imageAnimal = imageAnimale;
      _bitmapImage = new BitmapImage();
      _imageAnimal.Source = _bitmapImage;
      MatchGifToState();
    }

    protected virtual void MatchGifToState()
    {

    }

  }
}
