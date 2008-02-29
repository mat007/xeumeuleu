#!/usr/bin/make

# configuration
PLATFORM = cygwin
INC_DIRS = ../../include
LIB_DIRS = ../../lib/$(PLATFORM)
RUN_DIR = ../../run/$(PLATFORM)

# tools
MAKE = make PLATFORM=$(PLATFORM) INC_DIRS=$(INC_DIRS) LIB_DIRS=$(LIB_DIRS) RUN_DIR=$(RUN_DIR) -f

# rules
default : xeumeuleu xeuseuleu

.PHONY : FORCE default xeumeuleu xeuseuleu test
FORCE : ;
.DELETE_ON_ERROR :

xeumeuleu :
	$(MAKE) xeumeuleu

xeuseuleu : xeumeuleu
	$(MAKE) xeuseuleu

test :
	$(MAKE) xeumeuleu test
	$(MAKE) xeuseuleu test
