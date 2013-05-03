#include <osg/Geometry>
#include <osgGA/TrackballManipulator>
#include <osg/ShapeDrawable>
#include <osgViewer/Viewer>

#include "VideoCore.h"

osg::Geode* createScene() {
	osg::Geode*   geode   = new osg::Geode();
	osg::Program* program = new osg::Program();
	osg::Shader*  vert    = osg::Shader::readShaderFile(osg::Shader::VERTEX, "src/shaders/vertex.glsl");
	osg::Shader*  frag    = osg::Shader::readShaderFile(osg::Shader::FRAGMENT, "src/shaders/fragment.glsl");

	program->addShader(vert);
	program->addShader(frag);

	/*
	osg::Geometry*  g = new osg::Geometry();
	osg::Vec3Array* v = new osg::Vec3Array();

	// v->push_back(osg::Vec3(-0.1f, -0.1f, -1.0f));
	// v->push_back(osg::Vec3( 0.1f, -0.1f, -1.0f));
	// v->push_back(osg::Vec3( 0.1f,  0.1f, -1.0f));
	// v->push_back(osg::Vec3(-0.1f,  0.1f, -1.0f));

	v->push_back(osg::Vec3(-0.1f, -1.0f, -0.1f));
	v->push_back(osg::Vec3(-0.1f, -1.0f,  0.1f));
	v->push_back(osg::Vec3( 0.1f, -1.0f, -0.1f));
	v->push_back(osg::Vec3( 0.1f, -1.0f,  0.1f));

	g->setVertexArray(v);
	g->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::TRIANGLE_STRIP, 0, 4));
	*/

	// geode->addDrawable(g);
	geode->addDrawable(new osg::ShapeDrawable(new osg::Sphere(osg::Vec3(), 3.0)));
	geode->getOrCreateStateSet()->setAttribute(program);

	return geode;
}

int main( int argc, char **argv ) {
	VideoCore::Screen screen;

	int r = screen.init();

	if(r) {
		OSG_FATAL << "Couldn't initialize EGL; error code was: " << r << std::endl;

		return r;
	}

	osgViewer::Viewer viewer;
	
	osgViewer::GraphicsWindowEmbedded* gw = viewer.setUpViewerAsEmbeddedInWindow(0, 0, screen.width, screen.height);

	viewer.setSceneData(createScene());
	viewer.setCameraManipulator(new osgGA::TrackballManipulator());
	viewer.realize();
	viewer.getCamera()->setClearColor(osg::Vec4(1.0f, 0.5f, 0.5f, 1.0f));

	// gw->getState()->setUseModelViewAndProjectionUniforms(true);
	// gw->getState()->setUseVertexAttributeAliasing(true);

	while(true) {
		viewer.frame();

		screen.swapBuffers();
	}

	return 0;
}

