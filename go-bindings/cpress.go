package cpress

// #include "../src/cpress.c"
import "C"

func initialize() {
    C.initialize()
}

func press_key(key C.int) {
    C.press_key(key)
}

func hold_key(key C.int) {
    C.hold_key(key)
}

func release_key(key C.int) {
    C.release_key(key)
}

/* TODO: C.press_combination() */