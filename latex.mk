# Makefile to generate .pdf from .tex sources.
# The "service" mechanism works the same way as in the main makefile;
# append the `pdf` variable with the desired files.

# doc target
doc : $(pdf)

# Directory strip slash
define dirss
$(patsubst %/,%,$(dir $1))
endef

pdfdep := $(pdf:%.pdf=%.dep.mk)

-include $(pdfdep)

$(pdfdep): %.dep.mk:


$(pdf): %.pdf: %.dep.mk
	latexmk -pdf   -M -MF $*.dep.mk -MP   $*.tex   -g \
		-pdflatex="pdflatex --shell-escape %O %S" \
		-outdir=$(call dirss, $*.pdf) -auxdir=$(call dirss $*.pdf)
	touch $*.pdf
