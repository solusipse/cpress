#include "cpress.c"

int main()
{

    initialize();

    press_key(KEY_A);
    press_key(KEY_B);
    press_key(KEY_B);

    //press_combination(3, KEY_C, KEY_D, KEY_E);

    //press_combination(5, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5);

    press_key(KEY_D);

    press_key(KEY_SPACE);

    //press_combination(3, KEY_LEFTSHIFT, KEY_B, KEY_C);

    press_key(KEY_A);
    press_key(KEY_B);

    press_key(KEY_C);
    press_key(KEY_E);

    //press_combination(3, KEY_X, KEY_Y, KEY_Z);

    press_key(KEY_C);
    press_key(KEY_E);
    press_key(KEY_E);
    press_key(KEY_E);
    press_key(KEY_E);


    finish();


    return 0;
}