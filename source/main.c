#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <3ds.h>
#include <io.h>

int main(){
	gfxInitDefault();
	fs_init();
	printf("This is a test for the worthy");
	while (aptMainLoop()){
		hidScanInput();
		u8* fb = gfxGetFramebuffer(GFX_TOP,GFX_LEFT,NULL,NULL);
		u32 kDown = hidKeysDown();
		load("test6.bin");
		if (kDown & KEY_START){
			memset(fb,0xAC,240*400*3);
			save("test5.bin");
			memset(fb,0xFF,240*400*3);
			break; // break in order to return to hbmenu
		}
		gfxFlushBuffers();
		gfxSwapBuffers();
		gspWaitForVBlank();
	}

	gfxExit();
	return 0;
}
