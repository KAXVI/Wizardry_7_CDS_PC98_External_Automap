#pragma once

#include <cstddef>
#include <cstdint>

// DS.EXE changes the drive letter in this resident filename at runtime.
// Match the whole ASCIIZ filename, accepting any DOS drive and ASCII case.
// The caller must also verify the nearby resident-data signatures.
inline bool W7_IsDsExeAnchor(const void* bytes, std::size_t size)
{
    constexpr char suffix[] = ":ds.exe";
    if (!bytes || size < 9) return false;
    const auto* data = static_cast<const uint8_t*>(bytes);
    const auto lower = [](uint8_t c) {
        return static_cast<uint8_t>(c >= 'A' && c <= 'Z' ? c + ('a' - 'A') : c);
    };
    const uint8_t drive = lower(data[0]);
    if (drive < 'a' || drive > 'z') return false;
    for (std::size_t i = 0; i < sizeof(suffix); ++i) {
        if (lower(data[i + 1]) != static_cast<uint8_t>(suffix[i])) return false;
    }
    return true;
}
