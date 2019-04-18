-- Copyright 1986-2018 Xilinx, Inc. All Rights Reserved.
-- --------------------------------------------------------------------------------
-- Tool Version: Vivado v.2018.2 (lin64) Build 2258646 Thu Jun 14 20:02:38 MDT 2018
-- Date        : Mon Mar 18 13:20:52 2019
-- Host        : ubuntu running 64-bit Ubuntu 16.04.5 LTS
-- Command     : write_vhdl -force -mode synth_stub
--               /home/junhonglin/Xilinx/PYNQ_Car/Robot/Robot.srcs/sources_1/bd/system/ip/system_trace_cntrl_64_0_0/system_trace_cntrl_64_0_0_stub.vhdl
-- Design      : system_trace_cntrl_64_0_0
-- Purpose     : Stub declaration of top-level module interface
-- Device      : xc7z020clg400-1
-- --------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity system_trace_cntrl_64_0_0 is
  Port ( 
    s_axi_trace_cntrl_AWADDR : in STD_LOGIC_VECTOR ( 5 downto 0 );
    s_axi_trace_cntrl_AWVALID : in STD_LOGIC;
    s_axi_trace_cntrl_AWREADY : out STD_LOGIC;
    s_axi_trace_cntrl_WDATA : in STD_LOGIC_VECTOR ( 31 downto 0 );
    s_axi_trace_cntrl_WSTRB : in STD_LOGIC_VECTOR ( 3 downto 0 );
    s_axi_trace_cntrl_WVALID : in STD_LOGIC;
    s_axi_trace_cntrl_WREADY : out STD_LOGIC;
    s_axi_trace_cntrl_BRESP : out STD_LOGIC_VECTOR ( 1 downto 0 );
    s_axi_trace_cntrl_BVALID : out STD_LOGIC;
    s_axi_trace_cntrl_BREADY : in STD_LOGIC;
    s_axi_trace_cntrl_ARADDR : in STD_LOGIC_VECTOR ( 5 downto 0 );
    s_axi_trace_cntrl_ARVALID : in STD_LOGIC;
    s_axi_trace_cntrl_ARREADY : out STD_LOGIC;
    s_axi_trace_cntrl_RDATA : out STD_LOGIC_VECTOR ( 31 downto 0 );
    s_axi_trace_cntrl_RRESP : out STD_LOGIC_VECTOR ( 1 downto 0 );
    s_axi_trace_cntrl_RVALID : out STD_LOGIC;
    s_axi_trace_cntrl_RREADY : in STD_LOGIC;
    ap_clk : in STD_LOGIC;
    ap_rst_n : in STD_LOGIC;
    interrupt : out STD_LOGIC;
    trace_64_TVALID : in STD_LOGIC;
    trace_64_TREADY : out STD_LOGIC;
    trace_64_TDATA : in STD_LOGIC_VECTOR ( 63 downto 0 );
    trace_64_TDEST : in STD_LOGIC_VECTOR ( 0 to 0 );
    trace_64_TKEEP : in STD_LOGIC_VECTOR ( 7 downto 0 );
    trace_64_TSTRB : in STD_LOGIC_VECTOR ( 7 downto 0 );
    trace_64_TUSER : in STD_LOGIC_VECTOR ( 0 to 0 );
    trace_64_TLAST : in STD_LOGIC_VECTOR ( 0 to 0 );
    trace_64_TID : in STD_LOGIC_VECTOR ( 0 to 0 );
    capture_64_TVALID : out STD_LOGIC;
    capture_64_TREADY : in STD_LOGIC;
    capture_64_TDATA : out STD_LOGIC_VECTOR ( 63 downto 0 );
    capture_64_TDEST : out STD_LOGIC_VECTOR ( 0 to 0 );
    capture_64_TKEEP : out STD_LOGIC_VECTOR ( 7 downto 0 );
    capture_64_TSTRB : out STD_LOGIC_VECTOR ( 7 downto 0 );
    capture_64_TUSER : out STD_LOGIC_VECTOR ( 0 to 0 );
    capture_64_TLAST : out STD_LOGIC_VECTOR ( 0 to 0 );
    capture_64_TID : out STD_LOGIC_VECTOR ( 0 to 0 )
  );

end system_trace_cntrl_64_0_0;

architecture stub of system_trace_cntrl_64_0_0 is
attribute syn_black_box : boolean;
attribute black_box_pad_pin : string;
attribute syn_black_box of stub : architecture is true;
attribute black_box_pad_pin of stub : architecture is "s_axi_trace_cntrl_AWADDR[5:0],s_axi_trace_cntrl_AWVALID,s_axi_trace_cntrl_AWREADY,s_axi_trace_cntrl_WDATA[31:0],s_axi_trace_cntrl_WSTRB[3:0],s_axi_trace_cntrl_WVALID,s_axi_trace_cntrl_WREADY,s_axi_trace_cntrl_BRESP[1:0],s_axi_trace_cntrl_BVALID,s_axi_trace_cntrl_BREADY,s_axi_trace_cntrl_ARADDR[5:0],s_axi_trace_cntrl_ARVALID,s_axi_trace_cntrl_ARREADY,s_axi_trace_cntrl_RDATA[31:0],s_axi_trace_cntrl_RRESP[1:0],s_axi_trace_cntrl_RVALID,s_axi_trace_cntrl_RREADY,ap_clk,ap_rst_n,interrupt,trace_64_TVALID,trace_64_TREADY,trace_64_TDATA[63:0],trace_64_TDEST[0:0],trace_64_TKEEP[7:0],trace_64_TSTRB[7:0],trace_64_TUSER[0:0],trace_64_TLAST[0:0],trace_64_TID[0:0],capture_64_TVALID,capture_64_TREADY,capture_64_TDATA[63:0],capture_64_TDEST[0:0],capture_64_TKEEP[7:0],capture_64_TSTRB[7:0],capture_64_TUSER[0:0],capture_64_TLAST[0:0],capture_64_TID[0:0]";
attribute X_CORE_INFO : string;
attribute X_CORE_INFO of stub : architecture is "trace_cntrl_64,Vivado 2018.2";
begin
end;