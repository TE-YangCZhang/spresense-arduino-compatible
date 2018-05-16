.phony: all windows linux macosx base extract clean_base clean

COMPILER_PATH=packages/SPRESENSE/tools/gcc-arm-none-eabi/5.4.1
ARCHIVE_PREFIX=spresense-arduino-
ZIP_SETTINGS=-q9r
TMPDIR=/tmp/
OS=windows linux macosx

packages: $(OS) clean_base

$(OS): base
	cp $(TMPDIR)$(ARCHIVE_PREFIX).zip $(ARCHIVE_PREFIX)$@-$(RELEASE_NAME).zip
	(cd Arduino15/; zip $(ZIP_SETTINGS) ../$(ARCHIVE_PREFIX)$@-$(RELEASE_NAME).zip  $(COMPILER_PATH)/$@/*)

base:
	(cd Arduino15/; zip $(ZIP_SETTINGS) $(TMPDIR)$(ARCHIVE_PREFIX) . -x$(COMPILER_PATH)/*)

extract: $(addsuffix _extract, $(OS))

%_extract:
	mkdir -p extract/$*
	unzip -q $(ARCHIVE_PREFIX)$*.zip -d extract/$*

clean_base:
	-rm -v $(TMPDIR)$(ARCHIVE_PREFIX).zip

clean:
	-rm -rf extract
	-rm  $(TMPDIR)$(ARCHIVE_PREFIX).zip
	-rm  $(ARCHIVE_PREFIX)*.zip
