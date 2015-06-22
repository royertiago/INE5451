# This clears all the implicit rules.
.SUFFIXES:

# Utility defines
define compile_obj
$(CXX) -c $< -o $@ $(ALL_CXXFLAGS)
endef

define link_main
$(CXX) -o $@ $^ $(ALL_CXXFLAGS) $(ALL_LDFLAGS)
endef

define generate_dependency
$(CXX) $*.cpp -MM -MP -MF $*.dep.mk -MT '$*.o $*.dep.mk' $(ALL_CXXFLAGS)
endef


# This makefile handles multiple programs in the same directory
# that include several files.
CXXFLAGS ?= -g
ALL_CXXFLAGS := $(CXXFLAGS) -std=c++1y -iquote./ -isystem Catch/single_include
ALL_LDFLAGS := $(LDFLAGS) -lboost_locale

# List of makefiles that need to be included
submakefiles := $(wildcard */makefile.mk)

# Subdirecories thad need to be ignored by find.
# For instance, we won't scan directories with their own makefile.
findignore := $(dir $(submakefiles))
findignore := .git Catch $(findignore:%/=%)
findignore := $(patsubst %, -path "./%" -prune -o, $(findignore))


# Programs generated by this makefile
prog := $(shell find . $(findignore) -name "*.cpp" -exec grep -l "^int main" {} +)
prog := $(prog:.cpp=)

# cpp files whose compilation will be managed by this makefile.
src := $(shell find . $(findignore) -name "*.cpp" -print)

# .dep.mk files that should be automatically generated from .cpp files.
dep := $(src:.cpp=.dep.mk)

# Object files that contains definitions needed by other programs
obj := $(shell find . $(findignore) -name "*.cpp" -exec grep -L "^int main" {} +)
obj := $(obj:.cpp=.o)

# The makefile will generate rules for treating the files in
# prog, src and dep automatically.
# So, submakefiles may append files to these variables
# to request the specified service.
#
# See submakefiles.md.
include $(submakefiles)

include latex.mk


-include $(dep)


.DEFAULT_GOAL := all

.PHONY: all
all: $(prog)

# Suboptimal dependency management.
$(prog): %: %.o $(obj)
	$(link_main)

$(src:.cpp=.o): %.o : %.cpp
	$(compile_obj)

$(dep): %.dep.mk: %.cpp
	$(generate_dependency)

.PHONY: mostlyclean clean
mostlyclean:
	-find $(findignore) -name "*.o" -exec rm '{}' \;
	-find -name "*.dep.mk" -exec rm '{}' \;

clean: mostlyclean
	-rm -f $(prog)
