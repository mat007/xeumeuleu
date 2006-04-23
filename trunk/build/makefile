#!/usr/bin/make

# configuration
INC_DIR = ../../../include
LIB_DIR = ../../../lib/cygwin
RUN_DIR = ../run

NAME = xeumeuleu
LIBS = xerces-c_2 libboost_unit_test_framework-cygwin-mt-1_32 mockpp

EXPORTS = exception.h xml.h xi*.h xo*.h encoding.h grammar.h start.h end.h content.h attribute.h list.h functor.h caller*.h optional.h

# tools
CXX = g++
AR = ar crsu
MD = mkdir -p
CP = cp -f -u
RM = rm -r -f

# project layout
OUT_DIR = ../out/gcc
SRC_DIR = ../src
DATA_DIR = ../data
DOC_DIR = ../doc
OBJ_DIR = $(OUT_DIR)/obj
DEP_DIR = $(OUT_DIR)/dep
INC_EXPORT_DIR = ../include/$(NAME)
LIB_EXPORT_DIR = ../lib

LIB = $(OUT_DIR)/lib$(NAME).a
TEST = $(OUT_DIR)/$(NAME)_test

LIB_MODULE = libraries/$(NAME)
LIB_SRC = $(wildcard $(SRC_DIR)/$(LIB_MODULE)/*.cpp)
LIB_OBJ = $(LIB_SRC:$(SRC_DIR)/$(LIB_MODULE)/%.cpp=%.o)
LIB_DEP = $(LIB_SRC:$(SRC_DIR)/%.cpp=$(DEP_DIR)/%.d)

TEST_MODULE = tests/$(NAME)_test
TEST_SRC = $(wildcard $(SRC_DIR)/$(TEST_MODULE)/*.cpp)
TEST_OBJ = $(TEST_SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
TEST_DEP = $(TEST_SRC:$(SRC_DIR)/%.cpp=$(DEP_DIR)/%.d)

# flags
CXXFLAGS = -O3 -I$(SRC_DIR)/libraries $(INC_DIR:%=-I%)
LDFLAGS = $(LIB_DIR:%=-L%)

# default rule
all : build test doc export

.PHONY : FORCE all build test doc export clean realclean
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

ifneq ($(MAKECMDGOALS),all)
ifneq ($(MAKECMDGOALS),test)
  -include $(TEST_DEP)
endif
endif

$(TEST) : $(TEST_OBJ) $(LIB)
	$(CXX) $(TEST_OBJ) -o $@ $(LIB) $(LIBS:%=-l%) $(LDFLAGS)

build : $(LIB)

test : $(TEST)
	cd $(RUN_DIR); $(TEST) --log_level=warnings --data_directory=$(DATA_DIR)/$(TEST_MODULE)

doc :

export :
	$(MD) $(INC_EXPORT_DIR)
	$(CP) $(wildcard $(EXPORTS:%=$(SRC_DIR)/libraries/$(NAME)/%)) $(INC_EXPORT_DIR)
	$(CP) $(LIB) $(LIB_EXPORT_DIR)

clean :
	$(RM) $(OBJ_DIR)
	$(RM) $(DEP_DIR)

realclean :
	$(RM) $(OUT_DIR)
