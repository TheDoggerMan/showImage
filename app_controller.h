// Mono Application Template V1.1
//

#ifndef app_controller_h
#define app_controller_h

// Include the Mono Framework
#include <mono.h>
#include <SDFileSystem.h>

// Import the mono and mono::ui namespaces into the context
// to avoid writing long type names, like mono::ui::TextLabel
using namespace mono;
using namespace mono::ui;
using namespace mono::display;

class AppController;

class Toucher : public mono::TouchResponder
{
    AppController * ctrl;
    public:
      void RespondTouchEnd (mono::TouchEvent &);
      Toucher (AppController *);
};

// The App main controller object.
// This template app will show a "hello" text in the screen
class AppController : public mono::IApplication {

    // This is the text label object that will displayed
  size_t imageIndex;
  Timer imageTimer;
  BackgroundView bg;
  Toucher toucher;
  TextLabelView helloLabel;
	SDFileSystem fs;
	mono::media::BMPImage image;
	ImageView iv;
  void updateScreen ();
	void showImage();
  void nextImageIndex ();

public:

    // The default constructor
    AppController();

    // Called automaticlly by Mono on device reset
    void monoWakeFromReset();

    // Called automatically by Mono just before it enters sleep mode
    void monoWillGotoSleep();

    // Called automatically by Mono right after after it wakes from sleep
    void monoWakeFromSleep();
    void handleTouch (geo::Point const & point);
};

#endif /* app_controller_h */
