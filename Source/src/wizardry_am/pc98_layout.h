#pragma once

#include <cstddef>

// All offsets are relative to the resident DOS filename ("a:ds.exe").
struct W7PC98Layout {
    const char* name;
    std::size_t level, quadrant, qX, qY, absX, absY, direction;
    std::size_t visited;
    std::size_t fixedMap;
    std::size_t mapPointer; // zero for a layout with a fixed map address
    std::size_t filenameInDS;
};

inline constexpr W7PC98Layout W7_PC9801_LAYOUT = {
    "pc9801", 0x84EE, 0x84E4, 0x84E8, 0x84E6, 0x84EC, 0x84EA, 0x785A,
    0x80A4, 0xA708, 0, 0
};

// Verified against the supplied DS.EXE and three runtime captures:
// N -> E in place, then one step backwards (X=92 -> 91, qX=4 -> 3).
// DS:0EE4 holds the map pointer; the filename is at DS:0BEA.
// +7842 is an eight-frame compass animation; +7840 is the actual facing.
inline constexpr W7PC98Layout W7_PC9821_LAYOUT = {
    "pc9821", 0x849E, 0x8494, 0x8498, 0x8496, 0x849C, 0x849A, 0x7840,
    0x805A, 0, 0x02FA, 0x0BEA
};

inline constexpr std::size_t W7_PC98_MAP_SIZE = 0xA30;
inline constexpr std::size_t W7_PC98_SNAPSHOT_SIZE = 0x10000;
