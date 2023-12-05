USER = stefanom
KEYBOARDS = iris badwings
PATH_KEYBOARD_iris = keebio/iris/rev6
PATH_KEYMAPS_iris = keebio/iris
PATH_KEYBOARD_badwings = hazel/bad_wings
PATH_KEYMAPS_badwings = hazel/bad_wings

all: $(KEYBOARDS)

.PHONY: $(KEYBOARDS)
$(KEYBOARDS):

	# cleanup old symlinks
	for f in $@; do \
		rm -rf qmk_firmware/keyboards/$(PATH_KEYMAPS_$@)/keymaps/$(USER); \
	done

	# add new symlinks
	ln -s $(shell pwd)/$@ qmk_firmware/keyboards/${PATH_KEYMAPS_$@}/keymaps/$(USER)

	# run lint check
	# cd qmk_firmware; qmk lint -km $(USER) -kb ${PATH_KEYBOARD_$@} --strict

	# run build
	cd qmk_firmware; qmk compile -c -kb ${PATH_KEYBOARD_$@} -km $(USER) -e AVR_CFLAGS="-Wno-array-bounds"

	# cleanup symlinks
	for f in $@; do \
		rm -rf qmk_firmware/keyboards/${PATH_$@}/keymaps/$(USER); \
	done

clean:
	rm -rf obj_*
	rm -f *.elf
	rm -f *.map
	rm -f *.hex

update: 
	# init submodule
	git submodule update --init --recursive
