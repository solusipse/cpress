from distutils.core import setup, Extension

module1 = Extension('cpress', sources = ['cpress.c'])

setup (name = 'cpress',
       version = '0.1',
       description = 'Python binding for cpress library',
       packages = ['pycpress'],
       ext_modules = [module1])