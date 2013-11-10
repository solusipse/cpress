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

from distutils.core import setup, Extension
import os

module1 = Extension('_cpress',
        sources = ['src/cpress.c'])

setup (name = 'cpress',
        version = '0.1',
        description = 'Python binding for cpress library',
        package_dir={'cpress': 'python'},
        packages = ['cpress'],
        ext_modules = [module1])