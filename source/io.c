#include <stdlib.h>
#include <stdio.h>
#include <3ds.h>
#include <string.h>

FS_archive sdmcArchive;
bool ok(Result ret,char* error){
  if(ret != 0){
    printf(error);
    return false;
  }
  return true;
}
void fs_init(){
  consoleInit(GFX_BOTTOM,NULL);
  printf("Getting archive\n");
  if(fsInit() != 0){
    printf("Error start fs");
    return;
  }
  sdmcArchive=(FS_archive){ARCH_SDMC, (FS_path){PATH_EMPTY, 1, (u8*)""}};
  if(ok(FSUSER_OpenArchive(NULL,&sdmcArchive),"Couldn't open archive") == false){
    return;
  }
}
void save(char* filename){
  printf("Reached here\n");
  static char filepath[256];
  Handle fileHandle;
  u32 written = 0;
  u32 size = 3*240*400;
  u64 offset = 0;
  u8* topBuffer = gfxGetFramebuffer(GFX_BOTTOM,GFX_RIGHT,NULL,NULL);
  snprintf(filepath,256,"/3ds/drawapp/%s",filename);
  if(ok(FSUSER_OpenFile(NULL,&fileHandle,sdmcArchive,FS_makePath(PATH_CHAR,filepath), FS_OPEN_WRITE | FS_OPEN_CREATE ,0),"Couldn't write file") == false){
    return;
  }
  printf("Opened file\n");

  if(ok(FSFILE_Write(fileHandle,&written,offset,&topBuffer,size,FS_WRITE_FLUSH),"Couldn't write to file") == false){
    return;
  }
  printf("Written file\n");
  if(ok(FSFILE_Close(fileHandle),"Couldn't close error") == false){
    return;
  }
  svcCloseHandle(fileHandle);
  printf("%s saved\n",filename);
}

void load(char* filename){
  printf("Reached here\n");
  static char filePath[256];
  Handle fileHandle;
  char* readBuffer = NULL;
  u64 size;
  u32* read = 0;
  u8* topBuffer = gfxGetFramebuffer(GFX_TOP,GFX_RIGHT,NULL,NULL);
  snprintf(filePath,256,"/3ds/drawapp/%s",filename);
  if(ok(FSUSER_OpenFileDirectly(NULL, &fileHandle, sdmcArchive, FS_makePath(PATH_CHAR,filePath), FS_OPEN_READ, FS_ATTRIBUTE_NONE),"Couldn't open file") == false ){
    return;
  }
  printf("Opened file\n");
  if(ok(FSFILE_GetSize(fileHandle,&size),"Couldn't get file size") == false)
    return;
  readBuffer = malloc(size);
  if(ok(FSFILE_Read(fileHandle,read,0x0,readBuffer,size),"Couldn't read file") == false){
    return;
  }

  printf("Read file\n");
  memmove(topBuffer,readBuffer,size);

  printf("Loaded");
  if(ok(FSFILE_Close(fileHandle),"Couldn't close the file") == false){
    return;
  }
  printf("Freed buffered");
  free(readBuffer);
}
