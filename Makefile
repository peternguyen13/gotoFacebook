#Goto FACEBOOK MAKE FILE
# Written by Peter Nguyen


INSTALLDIR=/usr/bin

CC=gcc

all: gotoFacebook
gotoFacebook: gotoFacebook.c
	$(CC) gotoFacebook.c -o gotoFacebook

clean: gotoFacebook
	-rm gotoFacebook

install: gotoFacebook
	cp -v gotoFacebook $(INSTALLDIR);\
	chmod a+w $(INSTALLDIR)/gotoFacebook;\
	chmod og-w $(INSTALLDIR)/gotoFacebook;\

uninstall: gotoFacebook
	rm -f $(INSTALLDIR)/gotoFacebook;\
