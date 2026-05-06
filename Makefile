.PHONY: ci lab-01 lab-02 lab-03 lab-04 lab-05 lab-06 analyze clean

LAB01=labs/01-secure-string-handling
LAB02=labs/02-stack-buffer-overflow
LAB03=labs/03-heap-buffer-overflow
LAB04=labs/04-use-after-free
LAB05=labs/05-integer-overflow
LAB06=labs/06-format-string

ci: clean
	$(MAKE) -C $(LAB01) run
	$(MAKE) -C $(LAB01) sanitize
	$(MAKE) -C $(LAB01) analyze
	$(MAKE) -C $(LAB02) fixed
	$(MAKE) -C $(LAB02) analyze-safe
	$(MAKE) -C $(LAB03) fixed
	$(MAKE) -C $(LAB03) analyze-safe
	$(MAKE) -C $(LAB04) fixed
	$(MAKE) -C $(LAB04) analyze-safe
	$(MAKE) -C $(LAB05) fixed
	$(MAKE) -C $(LAB05) analyze-safe
	$(MAKE) -C $(LAB06) fixed
	$(MAKE) -C $(LAB06) analyze-safe

lab-01:
	$(MAKE) -C $(LAB01) run

lab-02:
	$(MAKE) -C $(LAB02) fixed

lab-03:
	$(MAKE) -C $(LAB03) fixed

lab-04:
	$(MAKE) -C $(LAB04) fixed

lab-05:
	$(MAKE) -C $(LAB05) fixed

lab-06:
	$(MAKE) -C $(LAB06) fixed

analyze:
	$(MAKE) -C $(LAB01) analyze
	$(MAKE) -C $(LAB02) analyze-safe
	$(MAKE) -C $(LAB03) analyze-safe
	$(MAKE) -C $(LAB04) analyze-safe
	$(MAKE) -C $(LAB05) analyze-safe
	$(MAKE) -C $(LAB06) analyze-safe

clean:
	$(MAKE) -C $(LAB01) clean
	$(MAKE) -C $(LAB02) clean
	$(MAKE) -C $(LAB03) clean
	$(MAKE) -C $(LAB04) clean
	$(MAKE) -C $(LAB05) clean
	$(MAKE) -C $(LAB06) clean
	rm -rf build *.dSYM
