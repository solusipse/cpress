#include "cpress.c"

int main()
{
    initialize();

    press_key(KEY_A);
    press_key(KEY_B);

    //press_combination(3, KEY_A, KEY_B, KEY_C);

    //press_combination(3, KEY_LEFTSHIFT, KEY_B, KEY_C);

    press_key(KEY_A);
    press_key(KEY_B);

    press_key(KEY_C);
    press_key(KEY_E);

    press_combination(3, KEY_X, KEY_Y, KEY_Z);

    press_key(KEY_C);
    press_key(KEY_E);

    finish();

    return 0;
}