# Project Name
TARGET = Tap-O-Matic

USE_DAISYSP_LGPL=1
#DEBUG=1

# Sources
CPP_SOURCES = time_machine_hardware.cpp TimeMachine.cpp

# Library Locations
LIBDAISY_DIR = /Users/jonask/Music/Daisy/libDaisy
DAISYSP_DIR = /Users/jonask/Music/Daisy/DaisySP

# Core location, and generic Makefile.
SYSTEM_FILES_DIR = $(LIBDAISY_DIR)/core
include $(SYSTEM_FILES_DIR)/Makefile
