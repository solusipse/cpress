cpress
======

cpress is C library for simulating keyboard actions. It interacts with ```/dev/uinput``` so it's low level and 
xserver independent. There are Python and Golang (TODO) bindings.

### Installation ###

#### C ####

See '''Makefile''' for more informations. Compile example with:
'''
make example
'''

#### Python ####

Simply run as root:

'''
python2 setup.py install
'''

### Usage ###

See '''src/examples/''' for more informations.

### License ###

cpress is MIT licensed.
