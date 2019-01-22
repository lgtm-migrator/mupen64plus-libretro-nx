#ifdef OS_WINDOWS
# include <windows.h>
#else
# include "winlnxdefs.h"
#endif // OS_WINDOWS
#include "RSP.h"
#include "PluginAPI.h"
#include "Config.h"
#include "wst.h"

void Config::resetToDefaults()
{
	version = CONFIG_VERSION_CURRENT;

#if defined(PANDORA) || defined(VC)
	video.fullscreen = 1;
	video.fullscreenWidth = video.windowedWidth = 800;
#else
#ifdef HAVE_LIBNX
	video.fullscreen = 0;
#else
	video.fullscreen = 1;
#endif // HAVE_LIBNX
	video.fullscreenWidth = video.windowedWidth = 640;
#endif
	video.fullscreenHeight = video.windowedHeight = 480;
	video.fullscreenRefresh = 60;
	video.multisampling = 0;
	video.verticalSync = 0;
	video.cropMode = cmDisable;
	video.cropWidth = video.cropHeight = 0;

	texture.maxAnisotropy = 0;
	texture.bilinearMode = BILINEAR_STANDARD;
#ifdef HAVE_LIBNX
	texture.maxBytes = 1500 * gc_uMegabyte;
#else
	texture.maxBytes = 500 * gc_uMegabyte;
#endif
	texture.screenShotFormat = 0;

	generalEmulation.enableLOD = 1;
	generalEmulation.enableNoise = 1;
	generalEmulation.enableHWLighting = 0;
	generalEmulation.enableCustomSettings = 1;
	generalEmulation.enableShadersStorage = 1;
	generalEmulation.correctTexrectCoords = tcDisable;
	generalEmulation.enableNativeResTexrects = 0;
	generalEmulation.enableLegacyBlending = 0;
	generalEmulation.hacks = 0;
#ifdef GLES2
	generalEmulation.enableFragmentDepthWrite = 0;
#else
	generalEmulation.enableFragmentDepthWrite = 1;
#endif
	generalEmulation.enableBlitScreenWorkaround = 0;
#ifdef ANDROID
	generalEmulation.forcePolygonOffset = 0;
	generalEmulation.polygonOffsetFactor = 0.0f;
	generalEmulation.polygonOffsetUnits = 0.0f;
#endif

#ifdef HAVE_LIBNX
	frameBufferEmulation.enable = 0;
#else
	frameBufferEmulation.enable = 1;
#endif
	frameBufferEmulation.copyDepthToRDRAM = cdSoftwareRender;
	frameBufferEmulation.copyFromRDRAM = 0;
	frameBufferEmulation.copyAuxToRDRAM = 0;
	frameBufferEmulation.copyToRDRAM = ctAsync;
	frameBufferEmulation.N64DepthCompare = 0;
	frameBufferEmulation.aspect = a43;
	frameBufferEmulation.bufferSwapMode = bsOnVerticalInterrupt;
	frameBufferEmulation.nativeResFactor = 0;
	frameBufferEmulation.fbInfoReadColorChunk = 0;
	frameBufferEmulation.fbInfoReadDepthChunk = 1;
#ifndef MUPENPLUSAPI
	frameBufferEmulation.fbInfoDisabled = 0;
#else
	frameBufferEmulation.fbInfoDisabled = 1;
#endif

	textureFilter.txFilterMode = 0;
	textureFilter.txEnhancementMode = 0;
	textureFilter.txDeposterize = 0;
	textureFilter.txFilterIgnoreBG = 0;
	textureFilter.txCacheSize = 100 * gc_uMegabyte;

	textureFilter.txHiresEnable = 0;
	textureFilter.txHiresFullAlphaChannel = 0;
	textureFilter.txHresAltCRC = 0;
	textureFilter.txDump = 0;

	textureFilter.txForce16bpp = 0;
	textureFilter.txCacheCompression = 1;
	textureFilter.txSaveCache = 1;

	api().GetUserDataPath(textureFilter.txPath);
	gln_wcscat(textureFilter.txPath, wst("/hires_texture"));

#ifdef OS_WINDOWS
	font.name.assign("arial.ttf");
#elif defined (ANDROID)
	font.name.assign("DroidSans.ttf");
#elif defined (PANDORA)
	font.name.assign("LiberationMono-Regular.ttf");
#else
	font.name = "FreeSans.ttf";
#endif
	font.size = 18;
	font.color[0] = 0xB5;
	font.color[1] = 0xE6;
	font.color[2] = 0x1D;
	font.color[3] = 0xFF;
	for (int i = 0; i < 4; ++i)
		font.colorf[i] = font.color[i] / 255.0f;

	bloomFilter.enable = 0;
	bloomFilter.thresholdLevel = 4;
	bloomFilter.blendMode = 0;
	bloomFilter.blurAmount = 10;
	bloomFilter.blurStrength = 20;

	gammaCorrection.force = 0;
	gammaCorrection.level = 2.0f;

	onScreenDisplay.vis = 0;
	onScreenDisplay.fps = 0;
	onScreenDisplay.percent = 0;
	onScreenDisplay.pos = posBottomLeft;
}