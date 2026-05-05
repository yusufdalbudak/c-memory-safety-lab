.PHONY: ci lab-01 lab-02 analyze clean

LAB01=labs/01-secure-string-handling
LAB02=labs/02-stack-buffer-overflow

ci: clean
	$(MAKE) -C $(LAB01) run
	$(MAKE) -C $(LAB01) sanitize
	$(MAKE) -C $(LAB01) analyze
	$(MAKE) -C $(LAB02) fixed
	$(MAKE) -C $(LAB02) analyze-safe

lab-01:
	$(MAKE) -C $(LAB01) run

lab-02:
	$(MAKE) -C $(LAB02) fixed

analyze:
	$(MAKE) -C $(LAB01) analyze
	$(MAKE) -C $(LAB02) analyze-safe

clean:
	$(MAKE) -C $(LAB01) clean
	$(MAKE) -C $(LAB02) clean
	rm -rf build *.dSYM
