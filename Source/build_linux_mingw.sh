#!/usr/bin/env bash
set -euo pipefail
cd -- "$(dirname -- "$0")"

: "${CXX:=x86_64-w64-mingw32-g++}"
: "${WINDRES:=x86_64-w64-mingw32-windres}"
: "${OBJDUMP:=x86_64-w64-mingw32-objdump}"
output_dir="${1:-../build}"
mkdir -p -- "$output_dir"
resource="$output_dir/Wizardry7Automap.res.o"
trap 'rm -f -- "$resource"' EXIT

"$WINDRES" Wizardry7Automap.rc -O coff -o "$resource"
"$CXX" -m64 -std=gnu++17 -O2 -DNDEBUG -Wall -Wextra \
    -DUNICODE -D_UNICODE -DWIN32_LEAN_AND_MEAN \
    -finput-charset=UTF-8 -fexec-charset=UTF-8 \
    -ffunction-sections -fdata-sections \
    ExternalAutomapMain.cpp \
    src/wizardry_am/am_wiz7_external.cpp src/wizardry_am/am_wiz7_res.cpp \
    "$resource" -o "$output_dir/Wizardry7Automap.exe" \
    -static -static-libgcc -static-libstdc++ -Wl,--gc-sections \
    -municode -mwindows -lcomdlg32 -luser32 -lgdi32 -lshell32 -ladvapi32 -s
dependencies="$("$OBJDUMP" -p "$output_dir/Wizardry7Automap.exe")"
if rg -i 'DLL Name:.*(SDL2\.dll|libgcc_s_|libstdc\+\+-6\.dll|libwinpthread-1\.dll)' <<< "$dependencies"; then
    echo 'Unexpected external runtime DLL dependency.' >&2
    exit 1
fi
echo "Built $output_dir/Wizardry7Automap.exe"
