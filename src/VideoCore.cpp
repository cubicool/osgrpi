#include "VideoCore.h"

#include <osg/Notify>
#include <bcm_host.h>

namespace VideoCore {

Screen::Screen() {
}

Screen::~Screen() {
	eglMakeCurrent(display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
	eglDestroySurface(display, surface);
	eglDestroyContext(display, context);
	eglTerminate(display);

	bcm_host_deinit();
}

int Screen::init() {
	EGLint num_config;

	static EGL_DISPMANX_WINDOW_T native_window;

	DISPMANX_ELEMENT_HANDLE_T dispman_element;
	DISPMANX_DISPLAY_HANDLE_T dispman_display;
	DISPMANX_UPDATE_HANDLE_T  dispman_update;
	VC_DISPMANX_ALPHA_T       dispman_alpha;

	VC_RECT_T dst_rect;
	VC_RECT_T src_rect;

	static const EGLint attribute_list[] = {
		EGL_RED_SIZE, VIDEOCORE_EGL_RED_SIZE,
		EGL_GREEN_SIZE, VIDEOCORE_EGL_GREEN_SIZE,
		EGL_BLUE_SIZE, VIDEOCORE_EGL_BLUE_SIZE,
		EGL_ALPHA_SIZE, VIDEOCORE_EGL_ALPHA_SIZE,
		EGL_DEPTH_SIZE, VIDEOCORE_EGL_DEPTH_SIZE,
		EGL_STENCIL_SIZE, VIDEOCORE_EGL_STENCIL_SIZE,
		EGL_SAMPLE_BUFFERS, VIDEOCORE_EGL_SAMPLE_BUFFERS,
		EGL_SAMPLES, VIDEOCORE_EGL_SAMPLES,
		EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
		EGL_NONE
	};

	static const EGLint context_attributes[] =  {
		EGL_CONTEXT_CLIENT_VERSION, 2,
		EGL_NONE
	};

	EGLConfig config;

	bcm_host_init();

	display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

	if(display == EGL_NO_DISPLAY) return VIDEOCORE_EGLERR_GET_DISPLAY;

	if(!eglInitialize(display, NULL, NULL)) return VIDEOCORE_EGLERR_INITIALIZE;

	if(!eglChooseConfig(
		display,
		attribute_list,
		&config,
		1,
		&num_config
	)) return VIDEOCORE_EGLERR_CHOOSE_CONFIG;

	if(!eglBindAPI(EGL_OPENGL_ES_API)) return VIDEOCORE_EGLERR_BIND_API;

	context = eglCreateContext(display, config, EGL_NO_CONTEXT, context_attributes);

	if(context == EGL_NO_CONTEXT) return VIDEOCORE_EGLERR_CREATE_CONTEXT;

	if(graphics_get_display_size(0, &width, &height) < 0) {
		OSG_FATAL << "couldn't get display size" << std::endl;

		return -1;
	}

	dst_rect.x      = 0;
	dst_rect.y      = 0;
	dst_rect.width  = width;
	dst_rect.height = height;

	src_rect.x      = 0;
	src_rect.y      = 0;
	src_rect.width  = width << 16;
	src_rect.height = height << 16;        

	dispman_alpha.flags   = DISPMANX_FLAGS_ALPHA_FIXED_ALL_PIXELS;
	dispman_alpha.opacity = 255;
	dispman_alpha.mask    = 0;

	dispman_display = vc_dispmanx_display_open(0);
	dispman_update  = vc_dispmanx_update_start(0);
	dispman_element = vc_dispmanx_element_add (
		dispman_update,
		dispman_display,
		0,
		&dst_rect,
		0,
		&src_rect,
		DISPMANX_PROTECTION_NONE,
		&dispman_alpha,
		0,
		DISPMANX_NO_ROTATE
	);

	native_window.element = dispman_element;
	native_window.width   = width;
	native_window.height  = height;

	vc_dispmanx_update_submit_sync(dispman_update);

	surface = eglCreateWindowSurface(display, config, &native_window, NULL);

	if(surface == EGL_NO_SURFACE) return VIDEOCORE_EGLERR_CREATE_WINDOW_SURFACE;

	if(!eglMakeCurrent(
		display,
		surface,
		surface,
		context
	)) return VIDEOCORE_EGLERR_MAKE_CURRENT;

	return 0;
}

void Screen::swapBuffers() {
	eglSwapBuffers(display, surface);
}

}

