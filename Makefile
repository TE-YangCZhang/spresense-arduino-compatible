.phony: packages windows linux macosx base extract clean_base clean

BUILDCHAIN_PATH=packages/SPRESENSE/tools/gcc-arm-none-eabi/5.4.1
ARCHIVE_PREFIX=manual-install-spresense-arduino-
PREBUILT_PGK=spresense-prebuilt-sdk-SPRESENSE_ADN_1.0.0_SDK_1.0.001.zip
SHASUM=shasum.txt
ZIP_SETTINGS=-q9r
TMPDIR=/tmp/
PWD=$(shell pwd)
OS=windows linux macosx

ifdef RELEASE_NAME
R_NAME=-$(RELEASE_NAME)
endif

packages: $(SHASUM) $(OS) clean_base

$(SHASUM): spresense-tools$(R_NAME).zip spresense-sdk$(R_NAME).zip spresense$(R_NAME).zip
	sha256sum $^ > $@

spresense$(R_NAME).zip: $(BUILDCHAIN_PATH)
	(cd Arduino15/packages/SPRESENSE/hardware/spresense; zip $(ZIP_SETTINGS) $(PWD)/$@ *)

spresense-sdk$(R_NAME).zip: $(BUILDCHAIN_PATH)
	(cd Arduino15/packages/SPRESENSE/tools/spresense-sdk; zip $(ZIP_SETTINGS) $(PWD)/$@ * )

spresense-tools$(R_NAME).zip: $(BUILDCHAIN_PATH)
	(cd Arduino15/packages/SPRESENSE/tools/spresense-tools; zip $(ZIP_SETTINGS) $(PWD)/$@ * )

$(OS): base
	cp $(TMPDIR)$(ARCHIVE_PREFIX).zip $(ARCHIVE_PREFIX)$@$(R_NAME).zip
	(cd Arduino15/; zip $(ZIP_SETTINGS) ../$(ARCHIVE_PREFIX)$@$(R_NAME).zip  $(BUILDCHAIN_PATH)/$@/*)

base: $(BUILDCHAIN_PATH)
	(cd Arduino15/; zip $(ZIP_SETTINGS) $(TMPDIR)$(ARCHIVE_PREFIX) . -x$(BUILDCHAIN_PATH)/*)

$(BUILDCHAIN_PATH):
	./tools/prepare_arduino.sh -H Windows -s $(PREBUILT_PGK) -g gcc-arm-none-eabi-5.4.1-windows.zip
	./tools/prepare_arduino.sh -H Linux64 -s $(PREBUILT_PGK) -g gcc-arm-none-eabi-5.4.1-linux.zip
	./tools/prepare_arduino.sh -H Mac -s $(PREBUILT_PGK) -g gcc-arm-none-eabi-5.4.1-macosx.zip

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
	-rm $(BUILDCHAIN_PATH)
	-rm spresense-v* spresense.zip spresense-sdk* spresense-tools* $(ARCHIVE_PREFIX)*

