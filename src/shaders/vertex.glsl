#version 100

precision mediump float;

uniform mat4 osg_ModelViewProjectionMatrix;
uniform mat3 osg_NormalMatrix;

attribute vec4 osg_Vertex;
attribute vec3 osg_Normal;

varying vec4 color;

void main() {
	vec3 ecNormal = normalize(osg_NormalMatrix * osg_Normal);
	float diffuse = max(dot(vec3(0.0, 0.5, 1.0), ecNormal), 0.0);
	color         = vec4(1.0, 1.0, 1.0, 1.0) * vec4(vec3(diffuse), 1.0);
	gl_Position   = osg_ModelViewProjectionMatrix * osg_Vertex;
}

