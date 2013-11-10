package main

import "C"
import "github.com/solusipse/cpress/go"


func main() {

    cpress.Initialize()
    cpress.Press_key(cpress.KEY_A)
    cpress.Press_key(cpress.KEY_B)
    cpress.Press_key(cpress.KEY_C)
    cpress.Hold_key(cpress.KEY_LEFTSHIFT)
    cpress.Press_key(cpress.KEY_D)
    cpress.Release_key(cpress.KEY_LEFTSHIFT)
    cpress.Press_key(cpress.KEY_E)
    cpress.Press_combination(cpress.KEY_LEFTSHIFT, cpress.KEY_F)
    cpress.Press_key(cpress.KEY_G)

}