# Literate Programming makefile support.
# This makefile assumes noweb format.

literatesrc = $(shell find . -name "*.nw")

literatetex = $(literatesrc:%.nw=%.tex)
literatepdf = $(literatesrc:%.nw=%.pdf)
pdf += $(literatepdf)

$(literatepdf): %.pdf: %.tex

$(literatetex): %.tex: %.nw
	noweave -latex -delay $< > $@
