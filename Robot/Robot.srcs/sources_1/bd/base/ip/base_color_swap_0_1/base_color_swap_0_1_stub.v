// Copyright 1986-2018 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2018.2 (lin64) Build 2258646 Thu Jun 14 20:02:38 MDT 2018
// Date        : Wed Mar 20 13:22:19 2019
// Host        : ubuntu running 64-bit Ubuntu 18.04.2 LTS
// Command     : write_verilog -force -mode synth_stub
//               /home/junhonglin/Xilinx/PYNQ_Car/Robot/Robot.srcs/sources_1/bd/base/ip/base_color_swap_0_1/base_color_swap_0_1_stub.v
// Design      : base_color_swap_0_1
// Purpose     : Stub declaration of top-level module interface
// Device      : xc7z020clg400-1
// --------------------------------------------------------------------------------

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// The synthesis directives are for Synopsys Synplify support to prevent IO buffer insertion.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
(* X_CORE_INFO = "color_swap,Vivado 2018.2" *)
module base_color_swap_0_1(hsync_in, hsync_out, pixel_in, pixel_out, vde_in, 
  vde_out, vsync_in, vsync_out)
/* synthesis syn_black_box black_box_pad_pin="hsync_in,hsync_out,pixel_in[23:0],pixel_out[23:0],vde_in,vde_out,vsync_in,vsync_out" */;
  input hsync_in;
  output hsync_out;
  input [23:0]pixel_in;
  output [23:0]pixel_out;
  input vde_in;
  output vde_out;
  input vsync_in;
  output vsync_out;
endmodule
