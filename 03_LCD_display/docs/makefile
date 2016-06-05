PLUGINS := markdown+superscript+subscript+raw_tex
ARGS := --parse-raw --smart --latex-engine=pdflatex --variable papersize:a4
DOCUMENT_OPTIONS := -V documentclass:article -V fontsize:12pt

pdf:
	find . -maxdepth 1 -name "*.md" | while read ITEM; do \
		OUT=`printf $$ITEM | sed 's/.md/.pdf/'`; \
	   	pandoc -t latex -o $$OUT -f $(PLUGINS) $(ARGS) \
			$(DOCUMENT_OPTIONS) $$ITEM; \
	done
