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
      Events.StateChanged += SetState;
    }

    /// <summary>
    /// //the animals changings gifs
    /// </summary>
    /// <param name="state"></param>  
    private void SetState(TraficLight.TraficLightState state)
    {
      switch(state)
      {
        case TraficLight.TraficLightState.Red:
          _state = StateType.standing;
          break;
        case TraficLight.TraficLightState.Yellow:
          _state = StateType.ready;
          break;
        case TraficLight.TraficLightState.Green:
          _state = StateType.going;
          break;
      }
      MatchGifToState();
    } 

    protected virtual void MatchGifToState()
    {

    }

  }
}
