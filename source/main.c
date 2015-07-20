#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <3ds.h>

int main()
{
	gfxInitDefault();
	consoleInit(GFX_TOP,NULL);
	printf("Homebrew hype train\n");
	// Main loop
	while (aptMainLoop())
	{
		gspWaitForVBlank();
		hidScanInput();

		u32 kDown = hidKeysDown();
		if (kDown & KEY_START)
			break; // break in order to return to hbmenu
		// Flush and swap framebuffers
		gfxFlushBuffers();
		gfxSwapBuffers();
	}

	gfxExit();
	return 0;
}
