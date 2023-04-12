#
# Copyright 2022 Xilinx, Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#   http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# Create a project
open_project -reset vitis

# Add design files
add_files include/mergeSort.hpp
add_files mergeSort.cpp
add_files include/medianFilter.hpp
add_files medianFilter.cpp
add_files include/bubbleSort.hpp
add_files bubbleSort.cpp
add_files include/bitonicSort.hpp
add_files bitonicSort.cpp
# Add test bench & files
# add_files -tb loop_perfect_test.cpp
# add_files -tb result.golden.dat

# Set the top-level function
set_top bitonicSort

# ########################################################
# Create a solution
open_solution -reset solution1
# Define technology and clock rate
set_part {xc7a200t-ffv1156-1}
create_clock -period 25

# Set variable to select which steps to execute
set hls_exec 2


# csim_design
# Set any optimization directives
# set_directive_pipeline loop_perfect/LOOP_J
# End of directives

if {$hls_exec == 1} {
    # Run Synthesis and Exit
    csynth_design

    # export_design -format ip_catalog
    export_design
} elseif {$hls_exec == 2} {
    # Run Synthesis, RTL Simulation and Exit
    csynth_design

    cosim_design
} elseif {$hls_exec == 3} { 
    # Run Synthesis, RTL Simulation, RTL implementation and Exit
    csynth_design

    cosim_design
    export_design
} else {
    # Default is to exit after setup
    csynth_design
}

exit
