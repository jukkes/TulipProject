TARGET = sip.so
OFILES = siplib.o apiversions.o descriptors.o qtlib.o threads.o objmap.o voidptr.o array.o bool.o
HFILES = sip.h sipint.h array.h 

CC = gcc
CXX = g++
LINK = g++
CPPFLAGS = -DNDEBUG -I. -I/usr/include/python2.7
CFLAGS = -pipe -fPIC -O2 -w
CXXFLAGS = -pipe -fPIC -O2 -w
LFLAGS = -shared -Wl,--version-script=sip.exp
LIBS = 
.SUFFIXES: .c .o .cpp .cc .cxx .C


.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) -o $@ $<

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) -o $@ $<

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) -o $@ $<

.C.o:
	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) -o $@ $<

.c.o:
	$(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $<

all: $(TARGET)

$(OFILES): $(HFILES)

$(TARGET): $(OFILES)
	@echo '{ global: initsip; local: *; };' > sip.exp
	$(LINK) $(LFLAGS) -o $(TARGET) $(OFILES) $(LIBS)

install: $(TARGET)
	@test -d $(DESTDIR)/home/jules/SAMOGWAS/Tulip4.6/build-debug/thirdparty/sip-4.15.5/siplib || mkdir -p $(DESTDIR)/home/jules/SAMOGWAS/Tulip4.6/build-debug/thirdparty/sip-4.15.5/siplib
	cp -f $(TARGET) $(DESTDIR)/home/jules/SAMOGWAS/Tulip4.6/build-debug/thirdparty/sip-4.15.5/siplib/$(TARGET)
	strip $(DESTDIR)/home/jules/SAMOGWAS/Tulip4.6/build-debug/thirdparty/sip-4.15.5/siplib/$(TARGET)
	@test -d $(DESTDIR)/home/jules/SAMOGWAS/Tulip4.6/tulip-src/thirdparty/sip-4.15.5/siplib || mkdir -p $(DESTDIR)/home/jules/SAMOGWAS/Tulip4.6/tulip-src/thirdparty/sip-4.15.5/siplib
	cp -f /home/jules/SAMOGWAS/Tulip4.6/tulip-src/thirdparty/sip-4.15.5/siplib/sip.h $(DESTDIR)/home/jules/SAMOGWAS/Tulip4.6/tulip-src/thirdparty/sip-4.15.5/siplib/sip.h

clean:
	-rm -f $(TARGET)
	-rm -f siplib.o
	-rm -f apiversions.o
	-rm -f descriptors.o
	-rm -f qtlib.o
	-rm -f threads.o
	-rm -f objmap.o
	-rm -f voidptr.o
	-rm -f array.o
	-rm -f bool.o
	-rm -f sip.exp
