#ifndef ENGINE_PCH_H
#define ENGINE_PCH_H

	// Get ONLY Windows 32 bits or major (Exclude 16 bits functions)
	#ifndef WIN32_MEAN_AND_LEAN
	#define WIN32_MEAN_AND_LEAN

		// Include "Windows" and "Windows Extended" APIs
		#include <windows.h>
		#include <windowsx.h>
	#endif

	// Standard libraries
	#include <array>
	#include <string>

	// DirectX Libraries
	#include <dxgi.h>
	#include <d3d11.h>

#endif