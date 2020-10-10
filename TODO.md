The following are upcoming changes I plan to make in future releases of this software...

- Add a test driver interface so that people can more easily alpha-test the library.
- Add `dfloatN_printf()`, `dfloatN_fprintf()`, `dfloatN_sprintf()`, and `dfloatN_snprintf()` functions analogous to the functions defined in the C Standard Libary. I think this would be a good idea because `dfloatN_ftoa()` requires the user to explicitly free the returned string when done using it, which can be awkward, and which they can easily forget to do, resulting in lost objects accumulating.
- Add arithmetic functions that combine `dfloat` types with `int` types so that the `int` types do not have to be explicitly converted to strings and then converted into `dfloat`s in order for these operations to be performed on the `dfloat`s, which again is awkward for the programmer and can result in accumulated lost objects.

Got any suggestions for other possible improvements? Don't hesitate to message me or submit your own code for review. If I use your code I'll be sure to credit you as a contributer to this project.
