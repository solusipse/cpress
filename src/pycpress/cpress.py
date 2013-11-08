from ctypes import cdll
from keylist import *

cpresslib = cdll.LoadLibrary('../cpress.so')

class Cpress:

    def __init__(self):
        cpresslib.initialize()

    def close(self):
        cpresslib.finish()

    def press_key(self, key):
        cpresslib.press_key(key)

    def hold_key(self, key):
        cpresslib.hold_key(key)

    def release_key(self, key):
        cpresslib.release_key(key)

    def press_combination(self, keys):
        cpresslib.press_combination(len(keys)-1, *keys)