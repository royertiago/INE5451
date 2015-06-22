# Literate Programming makefile support.
# This makefile assumes noweb format.

literatesrc = $(shell find . -name "*.nw")

literatetex = $(literatesrc:%.nw=%.tex)
literatepdf = $(literatesrc:%.nw=%.pdf)
pdf += $(literatepdf)

$(literatepdf): %.pdf: %.tex

$(literatetex): %.tex: %.nw
	noweave -latex -delay $< > $@

define make-noweb-rule

$(warning command is noroots $1 | sed 's/^<<\(.*\)>>$$/\1/')
$(eval roots := $(shell noroots $1 | sed 's/^<<\(.*\)>>$$/\1/'))
$(warning roots is $(roots))
$(eval roots := $(patsubst %,$(dir $1)%,$(roots))))

noweb : $(roots)

$(warning roots is $(roots))
$(warning 1 is $1)

$(foreach file,$(roots),$(eval $(file) : $1
	notangle -R$(notdir $@) $1 > $@))

$(warning done.)
endef

noweb:

$(foreach file, $(literatesrc),$(eval$(call make-noweb-rule,$(file))))
