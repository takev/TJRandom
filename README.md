# TJRandom

This package generates random numbers for cryptographic engines.

The design will use Intel's RDRND instruction if compiled and available. If it is not
available it will use rc4random() on Mac OS X, or getrandom() on Linux.

