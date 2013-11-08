#include "cpress.c"

int main()
{

    press_key(KEY_A);
    press_key(KEY_B);

    press_combination(3, KEY_A, KEY_B, KEY_C);

    press_combination(3, KEY_LEFTSHIFT, KEY_B, KEY_C);

    press_key(KEY_A);
    press_key(KEY_B);

    press_key(KEY_C);
    press_key(KEY_E);

    press_combination(3, KEY_X, KEY_Y, KEY_Z);

    press_combination(2, KEY_LEFTSHIFT, KEY_Y);

    press_key(KEY_C);
    press_key(KEY_E);

    return 0;
}