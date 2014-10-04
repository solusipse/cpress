cpress
======

cpress was made for simulating keyboard input on Linux systems. It interacts with `/dev/uinput` and therefore is very low level and X Window System independend. There are Python and Go bindings provided.

----------------------------

## Installation and usage ##

### Before installation ###

Be aware that by default `/dev/uinput` is writable only for root.
You can start cpress as root or, before doing that, change permissions level:

```bash
chmod +0666 /dev/uinput
```

`cpress` handles this automatically. If permissions level is not sufficient, it asks for root password and sets modes on its own. If you want avoid permissions changes for some reason, start as root.

----------------------------

### C ###

#### Installation ####

See `Makefile` or more informations. To compile examples, type:
```bash
make example
```

#### Usage ####

Before doing anything with `cpress`, you'll have to call `initialize()` function. Then feel free to use these:

```
press_key(KEY_A);
```

```
press_combination(3, KEY_C, KEY_D, KEY_E);
```

```
hold_key(KEY_LEFTSHIFT);
press_key(KEY_E);
press_key(KEY_E);
release_key(KEY_LEFTSHIFT);
```

When you're done with cpress, simply call `finish()`.

For more examples, see self-explanatory file `examples/example.c`.

----------------------------


### Python ###

#### Installation ####

Simply run as root:

```bash
python2 setup.py install
```

#### Usage ####

Import module with:

```python
from cpress import *
```

See self-explanatory file `examples/example.py` for more informations.

----------------------------

### Go ###

#### Installation ####

Just use that command:

```bash
go get github.com/solusipse/cpress/go
```

#### Usage ####

Import package with:

```go
import "github.com/solusipse/cpress/go"
```

See self-explanatory file `examples/example.go` for more informations.


----------------------------

## License ##

See `LICENSE`.
