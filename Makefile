# You'll need to set this directory to where your OSG include files
# and binary objects are. If you're using my prebuilt stuff the 
# googlecode site:
#
# 	https://osgrpi.googlecode.com/files/OpenSceneGraph-3.1.4.tar.bz2
#
# ...then extract that tarball in the current directory and do:
#
# 	make
# 	make run
#
# Enjoy!
OSG_DIR = OpenSceneGraph-3.1.4

export LD_LIBRARY_PATH = $(OSG_DIR)/lib

CFLAGS = \
	-I$(OSG_DIR)/include \
	-L$(OSG_DIR)/lib \
	-I/opt/vc/include \
	-I/opt/vc/include/interface/vcos/pthreads \
	-I/opt/vc/include/interface/vmcs_host/linux/ \
	-losg -losgViewer -losgDB -losgGA \
	-W -Wall -Wno-unused

OBJS = src/.VideoCore.o src/.osgrpi.o

src/.%.o: src/%.cpp
	@echo Compiling: $(<)
	@g++ -c $(<) -o $(@) $(CFLAGS)

osgrpi: src/VideoCore.h $(OBJS)
	@g++ -o $(@) $(OBJS) $(CFLAGS)

clean:
	@rm -f src/.*.o osgrpi

run:
	@./osgrpi

