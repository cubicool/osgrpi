######
osgRPi
######

This is a small project for using OpenSceneGraph with the RaspberryPi. It does
not (currently) implement a fully-fledged osgViewer::GraphicsWindow object; it
simply uses the EmbeddedWindow API.

Also included is the script I use to cross-compile OSG applications using CMake
for the RaspberryPi, since building OSG *ON* the Pi would probably take
longer than just **rewriting a new scenegraph yourself**. :)

==================
Future Development
==================

*If you are interested in funding further refinement of OSG support on the
RaspberryPi and Broadcom VideoCore device* please contact us at
`AlphaPixel <http://alphapixel.com>`_. This could be a really interesting,
emerging market for dirt-cheap OpenGL/OSG visualization!
