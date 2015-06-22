# Makefile to generate .pdf from .tex sources.
# The "service" mechanism works the same way as in the main makefile;
# append the `pdf` variable with the desired files.
pdf += $(shell find . $(findignore) -name '*.tex' -print)

# doc target
doc : $(pdf)

# Directory strip slash
define dirss
$(patsubst %/,%,$(dir $1))
endef

pdfdep := $(pdf:%.pdf=%.dep.mk)

$(pdfdep): %.dep.mk:

-include $(pdfdep)

$(pdf): %.pdf: %.dep.mk
	latexmk -pdf   -M -MF $*.dep.mk -MP   $*.tex   -g\
		-outdir=$(call dirss, $*.pdf) -auxdir=$(call dirss $*.pdf)
	touch $*.pdf
