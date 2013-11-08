from distutils.core import setup, Extension
import os

module1 = Extension('_cpress',
        sources = ['src/cpress.c'])

setup (name = 'cpress',
        version = '0.1',
        description = 'Python binding for cpress library',
        package_dir={'cpress': 'src'},
        packages = ['cpress'],
        ext_modules = [module1])