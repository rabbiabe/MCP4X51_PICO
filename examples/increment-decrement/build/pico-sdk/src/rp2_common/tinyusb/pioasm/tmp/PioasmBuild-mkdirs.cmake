# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/Users/abefriedman/Code/pico-sdk/tools/pioasm"
  "/Users/abefriedman/Code/mylib/MCP4X51_PICO/examples/increment-decrement/build/pioasm"
  "/Users/abefriedman/Code/mylib/MCP4X51_PICO/examples/increment-decrement/build/pico-sdk/src/rp2_common/tinyusb/pioasm"
  "/Users/abefriedman/Code/mylib/MCP4X51_PICO/examples/increment-decrement/build/pico-sdk/src/rp2_common/tinyusb/pioasm/tmp"
  "/Users/abefriedman/Code/mylib/MCP4X51_PICO/examples/increment-decrement/build/pico-sdk/src/rp2_common/tinyusb/pioasm/src/PioasmBuild-stamp"
  "/Users/abefriedman/Code/mylib/MCP4X51_PICO/examples/increment-decrement/build/pico-sdk/src/rp2_common/tinyusb/pioasm/src"
  "/Users/abefriedman/Code/mylib/MCP4X51_PICO/examples/increment-decrement/build/pico-sdk/src/rp2_common/tinyusb/pioasm/src/PioasmBuild-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/abefriedman/Code/mylib/MCP4X51_PICO/examples/increment-decrement/build/pico-sdk/src/rp2_common/tinyusb/pioasm/src/PioasmBuild-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Users/abefriedman/Code/mylib/MCP4X51_PICO/examples/increment-decrement/build/pico-sdk/src/rp2_common/tinyusb/pioasm/src/PioasmBuild-stamp${cfgdir}") # cfgdir has leading slash
endif()
