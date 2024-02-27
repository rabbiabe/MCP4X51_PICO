# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/Users/abefriedman/Code/pico-sdk/tools/elf2uf2"
  "/Users/abefriedman/Code/mylib/MCP4X51_PICO/build/elf2uf2"
  "/Users/abefriedman/Code/mylib/MCP4X51_PICO/build/elf2uf2"
  "/Users/abefriedman/Code/mylib/MCP4X51_PICO/build/elf2uf2/tmp"
  "/Users/abefriedman/Code/mylib/MCP4X51_PICO/build/elf2uf2/src/ELF2UF2Build-stamp"
  "/Users/abefriedman/Code/mylib/MCP4X51_PICO/build/elf2uf2/src"
  "/Users/abefriedman/Code/mylib/MCP4X51_PICO/build/elf2uf2/src/ELF2UF2Build-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/abefriedman/Code/mylib/MCP4X51_PICO/build/elf2uf2/src/ELF2UF2Build-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Users/abefriedman/Code/mylib/MCP4X51_PICO/build/elf2uf2/src/ELF2UF2Build-stamp${cfgdir}") # cfgdir has leading slash
endif()
