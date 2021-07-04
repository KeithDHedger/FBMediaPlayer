
AUTOMAKE_OPTIONS = subdir-objects

include ../flagsandlibs
include ../sources

fbmediaplayer_SOURCES = $(COMMONSRC)

man1_MANS = ../resources/man/fbmediaplayer.1

bin_PROGRAMS = fbmediaplayer

install-exec-hook:
	mkdir -vp "$(DESTDIR)${pkgdatadir}"
	cp -r ../resources/pixmaps/* "$(DESTDIR)${pkgdatadir}"






