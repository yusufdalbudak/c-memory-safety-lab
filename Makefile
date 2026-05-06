.PHONY: ci lab-01 lab-02 lab-03 lab-04 lab-05 lab-06 lab-07 lab-08 lab-09 lab-10 \
	lab-11 lab-12 lab-13 lab-14 lab-15 analyze clean

LAB01=labs/01-secure-string-handling
LAB02=labs/02-stack-buffer-overflow
LAB03=labs/03-heap-buffer-overflow
LAB04=labs/04-use-after-free
LAB05=labs/05-integer-overflow
LAB06=labs/06-format-string
LAB07=labs/07-secure-file-parsing
LAB08=labs/08-binary-inspector
LAB09=labs/09-tlv-parser
LAB10=labs/10-fuzzing-harness
LAB11=labs/11-pcap-offline-analysis
LAB12=labs/12-dns-response-parser
LAB13=labs/13-tcp-metadata-checker
LAB14=labs/14-hashing-integrity-checker
LAB15=labs/15-secure-mini-toolkit

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
	$(MAKE) -C $(LAB07) fixed
	$(MAKE) -C $(LAB07) analyze-safe
	$(MAKE) -C $(LAB08) fixed
	$(MAKE) -C $(LAB08) analyze-safe
	$(MAKE) -C $(LAB09) fixed
	$(MAKE) -C $(LAB09) analyze-safe
	$(MAKE) -C $(LAB10) run
	$(MAKE) -C $(LAB10) stress
	$(MAKE) -C $(LAB10) analyze
	$(MAKE) -C $(LAB11) fixed
	$(MAKE) -C $(LAB11) analyze-safe
	$(MAKE) -C $(LAB12) fixed
	$(MAKE) -C $(LAB12) analyze-safe
	$(MAKE) -C $(LAB13) fixed
	$(MAKE) -C $(LAB13) analyze-safe
	$(MAKE) -C $(LAB14) run
	$(MAKE) -C $(LAB14) analyze
	$(MAKE) -C $(LAB15) run
	$(MAKE) -C $(LAB15) analyze

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

lab-07:
	$(MAKE) -C $(LAB07) fixed

lab-08:
	$(MAKE) -C $(LAB08) fixed

lab-09:
	$(MAKE) -C $(LAB09) fixed

lab-10:
	$(MAKE) -C $(LAB10) run

lab-11:
	$(MAKE) -C $(LAB11) fixed

lab-12:
	$(MAKE) -C $(LAB12) fixed

lab-13:
	$(MAKE) -C $(LAB13) fixed

lab-14:
	$(MAKE) -C $(LAB14) run

lab-15:
	$(MAKE) -C $(LAB15) run

analyze:
	$(MAKE) -C $(LAB01) analyze
	$(MAKE) -C $(LAB02) analyze-safe
	$(MAKE) -C $(LAB03) analyze-safe
	$(MAKE) -C $(LAB04) analyze-safe
	$(MAKE) -C $(LAB05) analyze-safe
	$(MAKE) -C $(LAB06) analyze-safe
	$(MAKE) -C $(LAB07) analyze-safe
	$(MAKE) -C $(LAB08) analyze-safe
	$(MAKE) -C $(LAB09) analyze-safe
	$(MAKE) -C $(LAB10) analyze
	$(MAKE) -C $(LAB11) analyze-safe
	$(MAKE) -C $(LAB12) analyze-safe
	$(MAKE) -C $(LAB13) analyze-safe
	$(MAKE) -C $(LAB14) analyze
	$(MAKE) -C $(LAB15) analyze

clean:
	$(MAKE) -C $(LAB01) clean
	$(MAKE) -C $(LAB02) clean
	$(MAKE) -C $(LAB03) clean
	$(MAKE) -C $(LAB04) clean
	$(MAKE) -C $(LAB05) clean
	$(MAKE) -C $(LAB06) clean
	$(MAKE) -C $(LAB07) clean
	$(MAKE) -C $(LAB08) clean
	$(MAKE) -C $(LAB09) clean
	$(MAKE) -C $(LAB10) clean
	$(MAKE) -C $(LAB11) clean
	$(MAKE) -C $(LAB12) clean
	$(MAKE) -C $(LAB13) clean
	$(MAKE) -C $(LAB14) clean
	$(MAKE) -C $(LAB15) clean
	rm -rf build *.dSYM
