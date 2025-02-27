/* Copyright 2015-2021 Jack Humbert
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

// encoder config
#define ENCODERS_PAD_A { B12 }
#define ENCODERS_PAD_B { B13 }
// Most tactile encoders have detents every 4 stages
#define ENCODER_RESOLUTION 2

// oneshot config
#define ONESHOT_TAP_TOGGLE 3
#define ONESHOT_TIMEOUT 5000

// leader key  config
#define LEADER_PER_KEY_TIMING
#define LEADER_TIMEOUT 300

#define TAPPING_TERM_PER_KEY
#define TAPPING_TERM 150
