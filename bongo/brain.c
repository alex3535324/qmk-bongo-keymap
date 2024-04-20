#include "bongo.c"

extern keymap_config_t keymap_config;
extern uint8_t is_master;

// Has Oled?
static uint32_t oled_timer = 0;

int RGB_current_mode;

// Switches off Game layer when idle
void matrix_scan_user(void) {
     return;
}

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
      return; 
}


// Oled Rotations
#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (is_keyboard_master()) {
    return OLED_ROTATION_270;
  }
    else {
    return OLED_ROTATION_180;
  }
}

void render_status_main(void) {
    render_space();
    render_layer_state();
    render_space();
    render_mod_status_gui_alt(get_mods()|get_oneshot_mods());
    render_mod_status_ctrl_shift(get_mods()|get_oneshot_mods());
    render_space();
    render_logo();
    render_space();
}

void render_status_secondary(void) {
  render_anim();
}

// Oled Sleeps
bool oled_task_user(void) {
  if (is_keyboard_master()) {
      render_status_main();
  } else {
      render_status_secondary();
  }
   return true;
}

#endif

// Oled Wakes
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
      oled_timer = timer_read32();
  }

switch (keycode) {
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
    case ADJUST:
        if (record->event.pressed) {
          layer_on(_ADJUST);
        } else {
          layer_off(_ADJUST);
        }
        return false;
  }
  return true;
}
