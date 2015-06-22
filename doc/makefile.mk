docdir := $(dir $(lastword $(MAKEFILE_LIST)))

pdf += $(docdir)relatorio.pdf

doc : $(docdir)relatorio.pdf
