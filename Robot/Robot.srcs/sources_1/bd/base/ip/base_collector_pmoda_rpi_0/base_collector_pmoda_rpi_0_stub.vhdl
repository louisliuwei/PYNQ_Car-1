-- Copyright 1986-2018 Xilinx, Inc. All Rights Reserved.
-- --------------------------------------------------------------------------------
-- Tool Version: Vivado v.2018.2 (lin64) Build 2258646 Thu Jun 14 20:02:38 MDT 2018
-- Date        : Wed Mar 20 13:50:56 2019
-- Host        : ubuntu running 64-bit Ubuntu 18.04.2 LTS
-- Command     : write_vhdl -force -mode synth_stub
--               /home/junhonglin/Xilinx/PYNQ_Car/Robot/Robot.srcs/sources_1/bd/base/ip/base_collector_pmoda_rpi_0/base_collector_pmoda_rpi_0_stub.vhdl
-- Design      : base_collector_pmoda_rpi_0
-- Purpose     : Stub declaration of top-level module interface
-- Device      : xc7z020clg400-1
-- --------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity base_collector_pmoda_rpi_0 is
  Port ( 
    wire_i_i : out STD_LOGIC_VECTOR ( 7 downto 0 );
    wire_i_o : in STD_LOGIC_VECTOR ( 7 downto 0 );
    wire_i_t : in STD_LOGIC_VECTOR ( 7 downto 0 );
    gpio_o_i : in STD_LOGIC_VECTOR ( 7 downto 0 );
    gpio_o_o : out STD_LOGIC_VECTOR ( 7 downto 0 );
    gpio_o_t : out STD_LOGIC_VECTOR ( 7 downto 0 )
  );

end base_collector_pmoda_rpi_0;

architecture stub of base_collector_pmoda_rpi_0 is
attribute syn_black_box : boolean;
attribute black_box_pad_pin : string;
attribute syn_black_box of stub : architecture is true;
attribute black_box_pad_pin of stub : architecture is "wire_i_i[7:0],wire_i_o[7:0],wire_i_t[7:0],gpio_o_i[7:0],gpio_o_o[7:0],gpio_o_t[7:0]";
attribute X_CORE_INFO : string;
attribute X_CORE_INFO of stub : architecture is "wire_distributor,Vivado 2018.2";
begin
end;
