'''
cpress - python bindings

-------------------------------------------------------------------------------

Installation:

    python2 setup.py install

Usage:

Import module with:

    from cpress import *

See self-explanatory file `examples/example.py` for more informations.

-------------------------------------------------------------------------------

License: MIT (http://www.opensource.org/licenses/mit-license.php)
Repository: https://github.com/solusipse/cpress

-------------------------------------------------------------------------------
'''

from cpress import *

keyboard = Cpress()

keyboard.press_key(keylist.KEY_A)
keyboard.press_key(keylist.KEY_B)
keyboard.press_key(keylist.KEY_C)
keyboard.hold_key(keylist.KEY_LEFTSHIFT)
keyboard.press_key(keylist.KEY_D)
keyboard.release_key(keylist.KEY_LEFTSHIFT)
keyboard.press_combination({keylist.KEY_E, keylist.KEY_F})

keyboard.close()