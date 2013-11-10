/*
cpress - go bindings

-------------------------------------------------------------------------------

Installation:

    go get github.com/solusipse/cpress/go

Usage:

Import package with:

    import "github.com/solusipse/cpress/go"

See self-explanatory file `examples/example.go` for more informations.

-------------------------------------------------------------------------------

License: MIT (http://www.opensource.org/licenses/mit-license.php)
Repository: https://github.com/solusipse/cpress

-------------------------------------------------------------------------------
*/

package main

import "github.com/solusipse/cpress/go"

func main() {

    // Use this to initialize cpress
    cpress.Initialize()
    // Some simple examples
    cpress.Press_key(cpress.KEY_A)
    cpress.Press_key(cpress.KEY_B)
    cpress.Press_key(cpress.KEY_C)
    // Hold_key and Release_key makes similar effect to Press_combination
    cpress.Hold_key(cpress.KEY_LEFTSHIFT)
    cpress.Press_key(cpress.KEY_D)
    cpress.Release_key(cpress.KEY_LEFTSHIFT)
    cpress.Press_key(cpress.KEY_E)
    // Press_combination method presses all keys at once
    cpress.Press_combination(cpress.KEY_LEFTSHIFT, cpress.KEY_F)
    cpress.Press_key(cpress.KEY_G)
    // Close() method may be used to star over or just for clean up
    cpress.Close()

}