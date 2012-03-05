# set the include path for X, qt and KDE
INCLUDES = $(all_includes)

# these are the headers for your project


# let automoc handle all of the meta source files (moc)
METASOURCES = AUTO

messages: rc.cpp
	$(XGETTEXT) *.cpp -o $(podir)/fftexplorer.pot

KDE_ICON = fftexplorer

#########################################################################
# APPLICATION SECTION
#########################################################################
# this is the program that gets installed.  it's name is used for all
# of the other Makefile.am variables
bin_PROGRAMS = fftexplorer

# the application source, library search path, and link libraries
fftexplorer_SOURCES = main.cpp fftexplorergui.ui fftexplorer.cpp \
	dataprocessor.cpp mulawconverter.cpp quickfft.cpp workthread.cpp deltatimemeasure.cpp \
	ScopePaneGUI.ui scopepane.cpp helpwidget.cpp HelpWidgetGUI.ui initfilehandler.cpp
fftexplorer_LDFLAGS = $(KDE_RPATH) $(all_libraries)
fftexplorer_LDADD = $(LIB_KDEUI)

# this is where the desktop file will go 
shelldesktopdir   = $(kde_appsdir)/Utilities


# this is where the shell's XML-GUI resource file goes
shellrcdir   = $(kde_datadir)/fftexplorer
shellrc_DATA = fftexplorerui.rc



noinst_HEADERS = scopepane.h HelpText.h helpwidget.h initfilehandler.h
