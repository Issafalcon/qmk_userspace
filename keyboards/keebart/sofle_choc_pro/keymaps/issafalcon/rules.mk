ENCODER_MAP_ENABLE = yes
CAPS_WORD_ENABLE = yes
COMBO_ENABLE = yes
SRC += features/chordal_hold.c
SRC += features/encoder.c
SRC += features/custom_rgb.c
SRC += models/layers_enum.c

include $(MAIN_KEYMAP_PATH_1)/qmk-vim/rules.mk

# qmk-vim settings
BETTER_VISUAL_MODE = yes
VIM_I_TEXT_OBJECTS = yes
VIM_A_TEXT_OBJECTS = yes
VIM_G_MOTIONS = yes
VIM_COLON_CMDS = yes
VIM_PASTE_BEFORE = yes
VIM_REPLACE = yes
VIM_DOT_REPEAT = yes
VIM_NUMBERED_JUMPS = yes
