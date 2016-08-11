########################## Created by Aszdrick Graf ###########################
############################ <aszdrick@gmail.com> #############################
###############################################################################

################################## VARIABLES ##################################
# Directories
SRCDIR    :=src
HDRDIR    :=include
BUILDIR   :=build
BINDIR    :=bin
TESTDIR   :=tests
DEPDIR    :=.deps
# Compiler & linker flags
LDLIBS    :=-lm -lgtest -pthread
LDFLAGS   :=
CXXFLAGS  :=-std=c++14 -Wall -O3
INCLUDE   :=-I$(HDRDIR)
# Files
SRC       :=$(shell find $(SRCDIR) -name '*.cpp')
DEP       :=$(patsubst %.cpp,$(DEPDIR)/%.d,$(SRC))
OBJ       :=$(patsubst %.cpp,$(BUILDIR)/%.o,$(SRC))
MAIN      :=main
EXEC      :=$(BINDIR)/executable
PUREOBJ   :=$(filter-out $(BUILDIR)/$(SRCDIR)/$(MAIN).o,$(OBJ))
TSTFILE   :=$(shell find $(TESTDIR) -name '*.cpp')
TSTDEP    :=$(patsubst %.cpp,$(DEPDIR)/%.d,$(TSTFILE))
TSTOBJ    :=$(patsubst %.cpp,$(BUILDIR)/%.o,$(TSTFILE))
TSTEXEC   :=$(patsubst $(TESTDIR)/%.cpp,$(BINDIR)/%,$(TSTFILE))
# Utilities
GETDEPCOM :='$(CXX) -MM $(INCLUDE) $(CXXFLAGS)'

.PHONY: all makedir clean clean_deps clean_all tests

################################# MAIN MODULE #################################
all: makedir $(EXEC)

$(EXEC): $(OBJ)
	@echo "[linking] $@"
	@$(CXX) $(OBJ) -o $@ $(LDLIBS) $(LDFLAGS)

$(BUILDIR)/%.o: %.cpp
	@echo "[  $(CXX)  ] $< -> .o"
	@mkdir -p $(BUILDIR)/$(*D)
	@$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

# For each .cpp file, creates a .d file with all dependencies of .cpp,
# including .d as target (to ensure up-to-date dependencies, in case of
# new includes being added. Wouldn't be necessary if dependencies 
# tracking were made in the same call of compiler with this:
# -MMD -MT "$@" -MF "$(DEPDIR)/$*.d")
$(DEPDIR)/%.d: %.cpp
	@echo "[makedep] $< -> .d"
	@mkdir -p $(DEPDIR)/$(*D)
	@$(CXX) -MM -MP -MT "$(BUILDIR)/$*.o $@" -MF "$@" $< $(INCLUDE) $(CXXFLAGS)
	

makedir: | $(BINDIR) $(BUILDIR)

$(BINDIR) $(BUILDIR) $(DEPDIR):
	@echo "[ mkdir ] Creating directory '$@'"
	@mkdir -p $@

################################ TESTS MODULE #################################
tests: makedir $(TSTEXEC)

$(TSTEXEC): $(PUREOBJ) $(TSTOBJ)
	@echo "[linking] $@"
	@$(CXX) $(PUREOBJ) $(BUILDIR)/$(TESTDIR)/$(@F).o -o $@ $(LDLIBS) $(LDFLAGS)

################################ CLEAN MODULE #################################
# Only remove object files
clean:
	@$(RM) -r $(BUILDIR)

# Only remove dependency files
clean_deps:
	@$(RM) -r $(DEPDIR)

# Remove object, binary and dependency files
clean_all: clean clean_deps
	@$(RM) -r $(BINDIR)

################################## INCLUDES ###################################
# Do not include list of dependencies if make was called with target clean_all
# or clean_deps
ifneq ($(MAKECMDGOALS), clean_all)
ifneq ($(MAKECMDGOALS), clean_deps)
-include $(DEP)
-include $(TSTDEP)
endif
endif
