
#include "app_controller.h"

using namespace mono::geo;
using mono::display::Color;
using mono::media::BMPImage;

// Contructor
// Initializes the label object with position and text content
// You should init only data here, since I/O is not setup yet.

static char const * fileName[] =
{
    "MonoDemo1",
    "MonoDemo2",
    "MonoDemo3",
    "MonoDemo4",
    "MonoDemo5",
    "MonoDemo6",
    "MonoDemo7",
    0
};

Toucher::Toucher (AppController * ctrl_)
:
    ctrl(ctrl_)
{
}

void Toucher::RespondTouchEnd(TouchEvent & event)
{
    if (TouchEvent::TOUCH_END == event.EventType)
        ctrl->handleTouch(event.Position);
}

AppController::AppController() :

    // Call the TextLabel's constructor, with a Rect and a static text
    fs(SD_SPI_MOSI,SD_SPI_MISO,SD_SPI_CLK,SD_SPI_CS,"sd"),
    toucher(this),
    imageTimer(5000),
	helloLabel(Rect(0,100,176,20), "")
{
    imageIndex = 1;

    // the label is the full width of screen, set it to be center aligned
    helloLabel.setAlignment(TextLabelView::ALIGN_CENTER);

    // set another text color
    helloLabel.setTextColor(display::TurquoiseColor);

    imageTimer.setCallback(this,&AppController::updateScreen);
    imageTimer.Start();
}

void AppController::handleTouch (geo::Point const & point)
{
    updateScreen();
}

void AppController::monoWakeFromReset()
{
    // At this point after reset we can safely expect all peripherals and
    // I/O to be setup & ready.

    // tell the label to show itself on the screen

    helloLabel.show();
	  updateScreen();
}


void AppController::monoWillGotoSleep()
{
    // Do any clean up here, before system goes to sleep and power
    // off peripherals.

}


void AppController::monoWakeFromSleep()
{
    // After sleep, the screen memory has been cleared - tell the label to
    // draw itself again
    helloLabel.scheduleRepaint();
	   iv.scheduleRepaint();
}

void AppController::showImage()
{
	//String path = String::Format("/sd/img/MonoDemo1.bmp");
  String path = String::Format("/sd/img/%s.bmp",fileName[imageIndex]);
  helloLabel.setText(path);
  helloLabel.show();

	FILE *tf = fopen(path(), "r");
	if(tf == 0)
	{
		helloLabel.setText("Can not find file");
		helloLabel.show();
		return;
	}
	fclose(tf);
	image = BMPImage(path);
	if (!image.IsValid())
	{
		helloLabel.setText("Faild to load image!");
		helloLabel.show();
	}
	iv = ImageView(&image);
	iv.setRect(Rect(0,0,176,220));
	iv.show();
}

void AppController::updateScreen ()
{
    bg.show();
    bg.setBackgroundColor(BlackColor);
    bg.scheduleRepaint();
    nextImageIndex();
    showImage();
}
void AppController::nextImageIndex ()
{
    ++imageIndex;
    if (0 == fileName[imageIndex]) imageIndex = 0;
}
