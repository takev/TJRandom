// TJRandom - A Swift package for generating random numbers.
// Copyright (C) 2017  Tjienta Vara
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef TJRANDOM_H
#define TJRANDOM_H

#include <stdint.h>
#include <stdlib.h>

/** Fill and array of 64 bit integers with random data.
 *
 * - parameter values:      The array of 64 bit integers.
 * - parameter nrValues:    Number of alaments in the array to fill with random data.
 */
void TJRandom_getUInt64Array(uint64_t *values, size_t nrValues);

#endif /* integer_intrinsics_h */
