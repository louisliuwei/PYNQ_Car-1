// Copyright 1986-2018 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2018.2 (lin64) Build 2258646 Thu Jun 14 20:02:38 MDT 2018
// Date        : Wed Mar 20 12:40:33 2019
// Host        : ubuntu running 64-bit Ubuntu 18.04.2 LTS
// Command     : write_verilog -force -mode synth_stub -rename_top decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix -prefix
//               decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_ base_slice_pmodb_gpio_0_stub.v
// Design      : base_slice_pmodb_gpio_0
// Purpose     : Stub declaration of top-level module interface
// Device      : xc7z020clg400-1
// --------------------------------------------------------------------------------

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// The synthesis directives are for Synopsys Synplify support to prevent IO buffer insertion.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
(* X_CORE_INFO = "interface_slice,Vivado 2018.2" *)
module decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix(gpio_w_i, gpio_w_o, gpio_w_t, gpio_i, gpio_o, 
  gpio_t)
/* synthesis syn_black_box black_box_pad_pin="gpio_w_i[7:0],gpio_w_o[7:0],gpio_w_t[7:0],gpio_i[7:0],gpio_o[7:0],gpio_t[7:0]" */;
  input [7:0]gpio_w_i;
  input [7:0]gpio_w_o;
  input [7:0]gpio_w_t;
  output [7:0]gpio_i;
  output [7:0]gpio_o;
  output [7:0]gpio_t;
endmodule
