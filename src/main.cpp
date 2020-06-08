#include "SDL2/SDL.h"
#include "include/core/SkGraphics.h"
#include "include/core/SkSurface.h"
#include "include/core/SkCanvas.h"
#include "include/core/SkString.h"
#include "include/core/SkImageInfo.h"
#include "include/core/SkColorSpace.h"

// #include "debug/debug.h"

#include "iostream"

#define WIDTH 640
#define HEIGHT 480

static SDL_Texture *texture; // even with SDL2, we can still bring ancient code back
static SDL_Window *window;
static SDL_Renderer *renderer;
Uint32 timeout;

int main ( int argc, char *argv[] )
{
	// debug("Test");
	SDL_Init(SDL_INIT_VIDEO); // init video
	// create the window like normal
	window = SDL_CreateWindow("Scroll PoC", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	int textureWidth;
	int textureHeight;

	SDL_GetRendererOutputSize(renderer, &textureWidth, &textureHeight);

	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, textureWidth, textureHeight);

	SkBitmap bitmap;
	SkImageInfo ii = SkImageInfo::Make(WIDTH, HEIGHT*2, kBGRA_8888_SkColorType, kPremul_SkAlphaType);
	bitmap.allocPixels(ii, ii.minRowBytes());
	SkCanvas* canvas = new SkCanvas(bitmap);

	SkPaint paint;

	//Set Text ARGB Color
	paint.setARGB(255, 255, 255, 255);

	//Turn AntiAliasing On
	paint.setAntiAlias(true);

	//Set Style and Stroke Width
	paint.setStyle(SkPaint::kStroke_Style);
	paint.setStrokeWidth(3);

	paint.setARGB(255, 120, 255, 255);

	//Text X, Y Position Varibles
	int refX = 0;
	int refY = 0;
	int mX = 0;
	int mY = 0;
	int x = refX + mX;
	int y = refY + mY;
	int aux = 0;
	int numFrames = 0;
  	Uint32 startTime = SDL_GetTicks();
	while (true)
	{
		++numFrames;
    	Uint32 elapsedMS = SDL_GetTicks() - startTime; // Time since start of loop
		
		SDL_Event event;
		/* look for an event */
		if (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				exit(0);
			} else if (event.type == SDL_MOUSEWHEEL) {
				if(event.wheel.y == -1) {
					y += 10;
				} else if (event.wheel.y == 1) {
					y -= 10;
				}
			} else if (event.type == SDL_FINGERUP) {
				y += 10;
			} else if (event.type == SDL_FINGERDOWN) {
				y -= 10;
			} else if (event.type == SDL_MOUSEMOTION) {

				if (event.motion.state == SDL_PRESSED) {
					aux = mY;
					mY =  event.motion.y;
					refY = (aux - mY) + refY;
				}
			}
			
		}

		canvas->clear(SK_ColorYELLOW);

		SkString text("Scroll PoC");

		// Draw a round rectangle
		SkRect rect;
		canvas->drawRoundRect(rect, 20, 20, paint);
        // Draw a oval form
		canvas->drawOval(rect, paint);

		//Draw A Line
		canvas->drawLine(10, refY + 300, 300, refY + 300, paint);

		//Draw Circle (X, refY, Size, Paint)
		canvas->drawCircle(100, refY + 400,  50, paint);
		canvas->drawCircle(200, refY + 800, 250, paint);
		canvas->flush();

		/* update the screen */
		SDL_UpdateTexture(texture, NULL, bitmap.getPixels(), WIDTH * 4);
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);
		SDL_RenderClear(renderer);

        if (elapsedMS) { // Skip this the first frame
      		double elapsedSeconds = elapsedMS / 1000.0; // Convert to seconds
      		double fps = numFrames / elapsedSeconds; // FPS is Frames / Seconds
      		std::cout << fps << std::endl; 
    	}
   		
		SDL_Delay(1.0/60.0); // Use floating point division, not integer
	}

	/* cleanup SDL */
	SDL_Quit();

	return 0;
}