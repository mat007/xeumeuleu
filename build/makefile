#!/usr/bin/make

# configuration
INC_DIRS = ../../../include
LIB_DIRS = ../../../lib/cygwin
RUN_DIR = ../run/cygwin

NAME = xeumeuleu
LIBS = xerces-c_2 libboost_unit_test_framework-cygwin-mt-1_32 mockpp

EXPORTS = xml.h exception.h xi*.h xo*.h encoding.h grammar.h start.h end.h \
          content.h attribute.h list.h name_list.h visitor.h caller*.h \
          name_caller*.h optional.h

# tools
CXX = g++
AR = ar crsu
MD = mkdir -p
CP = cp -f -u
RM = rm -r -f

# helpers
location = $(shell mkdir -p $(1); cd $(1); pwd)

# project layout
OUT_DIR = ../out/gcc
SRC_DIR = ../src
DATA_DIR = $(call location,../data)
OBJ_DIR = $(OUT_DIR)/obj
DEP_DIR = $(OUT_DIR)/dep
INC_EXPORT_DIR = ../include/$(NAME)
LIB_EXPORT_DIR = ../lib

LIB = $(OUT_DIR)/lib$(NAME).a
TEST = $(call location,$(OUT_DIR))/$(NAME)_test

LIB_MODULE = libraries/$(NAME)
LIB_SRC = $(wildcard $(SRC_DIR)/$(LIB_MODULE)/*.cpp)
LIB_OBJ = $(LIB_SRC:$(SRC_DIR)/$(LIB_MODULE)/%.cpp=%.o)
LIB_DEP = $(LIB_SRC:$(SRC_DIR)/%.cpp=$(DEP_DIR)/%.d)

TEST_MODULE = tests/$(NAME)_test
TEST_SRC = $(wildcard $(SRC_DIR)/$(TEST_MODULE)/*.cpp)
TEST_OBJ = $(TEST_SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
TEST_DEP = $(TEST_SRC:$(SRC_DIR)/%.cpp=$(DEP_DIR)/%.d)

# flags
CXXFLAGS = -O3 -I$(SRC_DIR)/libraries $(INC_DIRS:%=-I%)
LDFLAGS = $(LIB_DIRS:%=-L%)

# rules
default : export

.PHONY : FORCE all build test install export clean realclean
FORCE : ;
.DELETE_ON_ERROR :

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	@$(MD) $(shell dirname $@)
	$(CXX) -c $(CXXFLAGS) -o $@ $<

# WARNING this trick is to prevent 'ar' to be run in parallel (-j option)
$(LIB) : $(LIB)($(LIB_OBJ))
$(LIB) : $(LIB_OBJ:%=$(OBJ_DIR)/$(LIB_MODULE)/%)
	$(AR) $(LIB) $(LIB_OBJ:%=$(OBJ_DIR)/$(LIB_MODULE)/%)
$(LIB)(%.o) : $(OBJ_DIR)/$(LIB_MODULE)/%.o ;

$(DEP_DIR)/%.d : $(SRC_DIR)/%.cpp
	@$(MD) $(shell dirname $@)
	$(CXX) -E -MM -MG $(CXXFLAGS) $< | sed -e "s@^\(.*\).o:@\$@ \$$(OBJ_DIR)/$*.o:@" > $@

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(MAKECMDGOALS),realclean)
  -include $(LIB_DEP)
endif
endif

ifeq ($(MAKECMDGOALS),test)
  -include $(TEST_DEP)
endif

$(TEST) : $(TEST_OBJ) $(LIB)
	$(CXX) $(TEST_OBJ) -o $@ $(LIB) $(LIBS:%=-l%) $(LDFLAGS)

build : $(LIB)

test : build $(TEST)
	@$(MD) $(RUN_DIR)
	@cd $(RUN_DIR); $(TEST) --log_level=warnings --data_directory=$(DATA_DIR)/$(TEST_MODULE)

install export : build
	$(MD) $(INC_EXPORT_DIR)
	$(CP) $(wildcard $(EXPORTS:%=$(SRC_DIR)/libraries/$(NAME)/%)) $(INC_EXPORT_DIR)
	$(MD) $(LIB_EXPORT_DIR)
	$(CP) $(LIB) $(LIB_EXPORT_DIR)

clean :
	$(RM) $(OBJ_DIR) $(DEP_DIR)

realclean :
	$(RM) $(OUT_DIR)
