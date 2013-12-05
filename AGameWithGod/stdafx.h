// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently

#ifndef STDAFX_H
#define STDAFX_H

#include <SDKDDKVer.h>

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>
#include <windowsx.h>

// C RunTime Header Files
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

//OpenGL header files
#include <GL/glew.h>

//assimp
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

//Other headers
#include "stb_image.h"

//program constants
#define PI 3.14159265
#define DEG2RAD PI/180
#define RAD2DEG 180/PI
#define TERRAINSIZE 512*512;

#endif