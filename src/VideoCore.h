#ifndef VIDEOCORE_H
#define VIDEOCORE_H

#include <GLES2/gl2.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>

#define VIDEOCORE_EGL_RED_SIZE       8
#define VIDEOCORE_EGL_GREEN_SIZE     8
#define VIDEOCORE_EGL_BLUE_SIZE      8
#define VIDEOCORE_EGL_ALPHA_SIZE     0
#define VIDEOCORE_EGL_DEPTH_SIZE     24
#define VIDEOCORE_EGL_STENCIL_SIZE   0
#define VIDEOCORE_EGL_SAMPLE_BUFFERS 0
#define VIDEOCORE_EGL_SAMPLES        0

#define VIDEOCORE_EGLERR_GET_DISPLAY           101
#define VIDEOCORE_EGLERR_INITIALIZE            102
#define VIDEOCORE_EGLERR_CHOOSE_CONFIG         103
#define VIDEOCORE_EGLERR_BIND_API              104
#define VIDEOCORE_EGLERR_CREATE_CONTEXT        105
#define VIDEOCORE_EGLERR_CREATE_WINDOW_SURFACE 106
#define VIDEOCORE_EGLERR_MAKE_CURRENT          107

namespace VideoCore {

struct Screen {
	Screen();
	~Screen();

	// Returns 0 if sucessful, or something else if it fails.
	int init();

	// A wrapper around eglSwapBuffers().
	void swapBuffers();

	uint32_t width;
	uint32_t height;

	EGLDisplay display;
	EGLSurface surface;
	EGLContext context;
};

}

#endif 

