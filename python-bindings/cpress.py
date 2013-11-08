'''

Python bindings for cpress.

-------------------------------------------------------------------------------

License: MIT (http://www.opensource.org/licenses/mit-license.php)
Repository: https://github.com/solusipse/cpress

-------------------------------------------------------------------------------

'''

from ctypes import cdll
from keylist import *

import distutils.sysconfig as sysconfig
from os import path

_lpath = path.abspath(path.join(path.dirname(__file__), "..", "_cpress.so"))
_cpress = cdll.LoadLibrary(_lpath)

class Cpress:

    def __init__(self):
        _cpress.initialize()

    def close(self):
        _cpress.finish()

    def press_key(self, key):
        _cpress.press_key(key)

    def hold_key(self, key):
        _cpress.hold_key(key)

    def release_key(self, key):
        _cpress.release_key(key)

    def press_combination(self, keys):
        _cpress.press_combination(len(keys)-1, *keys)
