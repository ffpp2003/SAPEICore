DOXYFILE = Doxyfile

LATEX_DIR = latex

LATEX_MAIN = $(LATEX_DIR)/refman.tex

OUTPUT_PDF = $(LATEX_DIR)/refman.pdf

PDFLATEX = pdflatex

GREEN=\033[0;32m
NC=\033[0m

all: pdf

doxygen:
	@echo "$(GREEN)Generando documentación con Doxygen...$(NC)"
	doxygen $(DOXYFILE)

pdf: doxygen
	@echo "$(GREEN)Compilando LaTeX a PDF...$(NC)"
	cd $(LATEX_DIR) && $(PDFLATEX) refman.tex
	cd $(LATEX_DIR) && $(PDFLATEX) refman.tex
	cd $(LATEX_DIR) && $(PDFLATEX) refman.tex

clean:
	@echo "$(GREEN)Limpiando archivos temporales y PDF...$(NC)"
	rm -f $(LATEX_DIR)/*.aux $(LATEX_DIR)/*.toc $(LATEX_DIR)/*.idx $(LATEX_DIR)/*.ind $(LATEX_DIR)/*.ilg
	$(LATEX_DIR)/*.log $(LATEX_DIR)/*.out $(LATEX_DIR)/*.brf $(LATEX_DIR)/*.blg $(LATEX_DIR)/*.bbl 
	$(LATEX_DIR)/*.pdf

distclean: clean
	@echo "$(GREEN)Eliminando documentación generada por Doxygen...$(NC)"
	rm -rf $(LATEX_DIR)
	rm -rf html

.PHONY: all doxygen pdf clean distclean

