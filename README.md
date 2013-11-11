cpress
======

cpress is C library for simulating keyboard actions. It interacts with `/dev/uinput` so it's low level and 
xserver independent. There are Python and Go bindings.

----------------------------

## Installation and usage ##

### Before installation ###

Be aware that defaultly `/dev/uinput` is writable only for root.
You can use cpress as root or change permissions level:

```bash
chmod +0666 /dev/uinput
```

Cpress asks for root password if is not be able to operate on uinput file. Then
it will chmod uinput file. If you want to avoid that for some reasons, always run
as root.

----------------------------

### C ###

#### Installation ####

See `Makefile` or more informations. Compile example with:
```bash
make example
```

#### Usage ####

See self-explanatory file `examples/example.c` for more informations.

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

cpress is MIT licensed.
