report : src/tex/homework4.tex src/tex/ref.bib
	cp src/tex/homework4.tex ./
	cp src/tex/ref.bib ./
	cp -r src/tex/pic ./
	xelatex homework4.tex
	bibtex homework4.aux
	xelatex homework4.tex
	xelatex homework4.tex
	rm homework4.tex
	rm ref.bib
	rm -R pic
	rm homework4.aux homework4.log homework4.out homework4.blg
	rm homework4.brf homework4.bbl

clean :
	rm homework4.pdf
