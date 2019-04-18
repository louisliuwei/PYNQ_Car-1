--Copyright 1986-2017 Xilinx, Inc. All Rights Reserved.
----------------------------------------------------------------------------------
--Tool Version: Vivado v.2017.4 (lin64) Build 2086221 Fri Dec 15 20:54:30 MST 2017
--Date        : Mon Feb 25 23:12:04 2019
--Host        : ubuntu running 64-bit Ubuntu 16.04.5 LTS
--Command     : generate_target PYNQ_HDMI_wrapper.bd
--Design      : PYNQ_HDMI_wrapper
--Purpose     : IP block netlist
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity PYNQ_HDMI_wrapper is
  port (
    CMOS_DATA : in STD_LOGIC_VECTOR ( 7 downto 0 );
    CMOS_ENA : out STD_LOGIC;
    CMOS_FVAL : in STD_LOGIC;
    CMOS_LVAL : in STD_LOGIC;
    CMOS_PIXCLK : in STD_LOGIC;
    DDR_addr : inout STD_LOGIC_VECTOR ( 14 downto 0 );
    DDR_ba : inout STD_LOGIC_VECTOR ( 2 downto 0 );
    DDR_cas_n : inout STD_LOGIC;
    DDR_ck_n : inout STD_LOGIC;
    DDR_ck_p : inout STD_LOGIC;
    DDR_cke : inout STD_LOGIC;
    DDR_cs_n : inout STD_LOGIC;
    DDR_dm : inout STD_LOGIC_VECTOR ( 3 downto 0 );
    DDR_dq : inout STD_LOGIC_VECTOR ( 31 downto 0 );
    DDR_dqs_n : inout STD_LOGIC_VECTOR ( 3 downto 0 );
    DDR_dqs_p : inout STD_LOGIC_VECTOR ( 3 downto 0 );
    DDR_odt : inout STD_LOGIC;
    DDR_ras_n : inout STD_LOGIC;
    DDR_reset_n : inout STD_LOGIC;
    DDR_we_n : inout STD_LOGIC;
    FIXED_IO_ddr_vrn : inout STD_LOGIC;
    FIXED_IO_ddr_vrp : inout STD_LOGIC;
    FIXED_IO_mio : inout STD_LOGIC_VECTOR ( 53 downto 0 );
    FIXED_IO_ps_clk : inout STD_LOGIC;
    FIXED_IO_ps_porb : inout STD_LOGIC;
    FIXED_IO_ps_srstb : inout STD_LOGIC;
    HDMI_DDC_scl_io : inout STD_LOGIC;
    HDMI_DDC_sda_io : inout STD_LOGIC;
    HDMI_HPD_tri_i : in STD_LOGIC_VECTOR ( 0 to 0 );
    SCL_tri_io : inout STD_LOGIC_VECTOR ( 0 to 0 );
    SDA_tri_io : inout STD_LOGIC_VECTOR ( 0 to 0 );
    TMDS_clk_n : out STD_LOGIC;
    TMDS_clk_p : out STD_LOGIC;
    TMDS_data_n : out STD_LOGIC_VECTOR ( 2 downto 0 );
    TMDS_data_p : out STD_LOGIC_VECTOR ( 2 downto 0 );
    XCLK : out STD_LOGIC
  );
end PYNQ_HDMI_wrapper;

architecture STRUCTURE of PYNQ_HDMI_wrapper is
  component PYNQ_HDMI is
  port (
    HDMI_DDC_sda_i : in STD_LOGIC;
    HDMI_DDC_sda_o : out STD_LOGIC;
    HDMI_DDC_sda_t : out STD_LOGIC;
    HDMI_DDC_scl_i : in STD_LOGIC;
    HDMI_DDC_scl_o : out STD_LOGIC;
    HDMI_DDC_scl_t : out STD_LOGIC;
    DDR_cas_n : inout STD_LOGIC;
    DDR_cke : inout STD_LOGIC;
    DDR_ck_n : inout STD_LOGIC;
    DDR_ck_p : inout STD_LOGIC;
    DDR_cs_n : inout STD_LOGIC;
    DDR_reset_n : inout STD_LOGIC;
    DDR_odt : inout STD_LOGIC;
    DDR_ras_n : inout STD_LOGIC;
    DDR_we_n : inout STD_LOGIC;
    DDR_ba : inout STD_LOGIC_VECTOR ( 2 downto 0 );
    DDR_addr : inout STD_LOGIC_VECTOR ( 14 downto 0 );
    DDR_dm : inout STD_LOGIC_VECTOR ( 3 downto 0 );
    DDR_dq : inout STD_LOGIC_VECTOR ( 31 downto 0 );
    DDR_dqs_n : inout STD_LOGIC_VECTOR ( 3 downto 0 );
    DDR_dqs_p : inout STD_LOGIC_VECTOR ( 3 downto 0 );
    FIXED_IO_mio : inout STD_LOGIC_VECTOR ( 53 downto 0 );
    FIXED_IO_ddr_vrn : inout STD_LOGIC;
    FIXED_IO_ddr_vrp : inout STD_LOGIC;
    FIXED_IO_ps_srstb : inout STD_LOGIC;
    FIXED_IO_ps_clk : inout STD_LOGIC;
    FIXED_IO_ps_porb : inout STD_LOGIC;
    TMDS_clk_p : out STD_LOGIC;
    TMDS_clk_n : out STD_LOGIC;
    TMDS_data_p : out STD_LOGIC_VECTOR ( 2 downto 0 );
    TMDS_data_n : out STD_LOGIC_VECTOR ( 2 downto 0 );
    HDMI_HPD_tri_i : in STD_LOGIC_VECTOR ( 0 to 0 );
    SCL_tri_i : in STD_LOGIC_VECTOR ( 0 to 0 );
    SCL_tri_o : out STD_LOGIC_VECTOR ( 0 to 0 );
    SCL_tri_t : out STD_LOGIC_VECTOR ( 0 to 0 );
    SDA_tri_i : in STD_LOGIC_VECTOR ( 0 to 0 );
    SDA_tri_o : out STD_LOGIC_VECTOR ( 0 to 0 );
    SDA_tri_t : out STD_LOGIC_VECTOR ( 0 to 0 );
    CMOS_FVAL : in STD_LOGIC;
    CMOS_LVAL : in STD_LOGIC;
    XCLK : out STD_LOGIC;
    CMOS_DATA : in STD_LOGIC_VECTOR ( 7 downto 0 );
    CMOS_PIXCLK : in STD_LOGIC;
    CMOS_ENA : out STD_LOGIC
  );
  end component PYNQ_HDMI;
  component IOBUF is
  port (
    I : in STD_LOGIC;
    O : out STD_LOGIC;
    T : in STD_LOGIC;
    IO : inout STD_LOGIC
  );
  end component IOBUF;
  signal HDMI_DDC_scl_i : STD_LOGIC;
  signal HDMI_DDC_scl_o : STD_LOGIC;
  signal HDMI_DDC_scl_t : STD_LOGIC;
  signal HDMI_DDC_sda_i : STD_LOGIC;
  signal HDMI_DDC_sda_o : STD_LOGIC;
  signal HDMI_DDC_sda_t : STD_LOGIC;
  signal SCL_tri_i_0 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal SCL_tri_io_0 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal SCL_tri_o_0 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal SCL_tri_t_0 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal SDA_tri_i_0 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal SDA_tri_io_0 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal SDA_tri_o_0 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal SDA_tri_t_0 : STD_LOGIC_VECTOR ( 0 to 0 );
begin
HDMI_DDC_scl_iobuf: component IOBUF
     port map (
      I => HDMI_DDC_scl_o,
      IO => HDMI_DDC_scl_io,
      O => HDMI_DDC_scl_i,
      T => HDMI_DDC_scl_t
    );
HDMI_DDC_sda_iobuf: component IOBUF
     port map (
      I => HDMI_DDC_sda_o,
      IO => HDMI_DDC_sda_io,
      O => HDMI_DDC_sda_i,
      T => HDMI_DDC_sda_t
    );
PYNQ_HDMI_i: component PYNQ_HDMI
     port map (
      CMOS_DATA(7 downto 0) => CMOS_DATA(7 downto 0),
      CMOS_ENA => CMOS_ENA,
      CMOS_FVAL => CMOS_FVAL,
      CMOS_LVAL => CMOS_LVAL,
      CMOS_PIXCLK => CMOS_PIXCLK,
      DDR_addr(14 downto 0) => DDR_addr(14 downto 0),
      DDR_ba(2 downto 0) => DDR_ba(2 downto 0),
      DDR_cas_n => DDR_cas_n,
      DDR_ck_n => DDR_ck_n,
      DDR_ck_p => DDR_ck_p,
      DDR_cke => DDR_cke,
      DDR_cs_n => DDR_cs_n,
      DDR_dm(3 downto 0) => DDR_dm(3 downto 0),
      DDR_dq(31 downto 0) => DDR_dq(31 downto 0),
      DDR_dqs_n(3 downto 0) => DDR_dqs_n(3 downto 0),
      DDR_dqs_p(3 downto 0) => DDR_dqs_p(3 downto 0),
      DDR_odt => DDR_odt,
      DDR_ras_n => DDR_ras_n,
      DDR_reset_n => DDR_reset_n,
      DDR_we_n => DDR_we_n,
      FIXED_IO_ddr_vrn => FIXED_IO_ddr_vrn,
      FIXED_IO_ddr_vrp => FIXED_IO_ddr_vrp,
      FIXED_IO_mio(53 downto 0) => FIXED_IO_mio(53 downto 0),
      FIXED_IO_ps_clk => FIXED_IO_ps_clk,
      FIXED_IO_ps_porb => FIXED_IO_ps_porb,
      FIXED_IO_ps_srstb => FIXED_IO_ps_srstb,
      HDMI_DDC_scl_i => HDMI_DDC_scl_i,
      HDMI_DDC_scl_o => HDMI_DDC_scl_o,
      HDMI_DDC_scl_t => HDMI_DDC_scl_t,
      HDMI_DDC_sda_i => HDMI_DDC_sda_i,
      HDMI_DDC_sda_o => HDMI_DDC_sda_o,
      HDMI_DDC_sda_t => HDMI_DDC_sda_t,
      HDMI_HPD_tri_i(0) => HDMI_HPD_tri_i(0),
      SCL_tri_i(0) => SCL_tri_i_0(0),
      SCL_tri_o(0) => SCL_tri_o_0(0),
      SCL_tri_t(0) => SCL_tri_t_0(0),
      SDA_tri_i(0) => SDA_tri_i_0(0),
      SDA_tri_o(0) => SDA_tri_o_0(0),
      SDA_tri_t(0) => SDA_tri_t_0(0),
      TMDS_clk_n => TMDS_clk_n,
      TMDS_clk_p => TMDS_clk_p,
      TMDS_data_n(2 downto 0) => TMDS_data_n(2 downto 0),
      TMDS_data_p(2 downto 0) => TMDS_data_p(2 downto 0),
      XCLK => XCLK
    );
SCL_tri_iobuf_0: component IOBUF
     port map (
      I => SCL_tri_o_0(0),
      IO => SCL_tri_io(0),
      O => SCL_tri_i_0(0),
      T => SCL_tri_t_0(0)
    );
SDA_tri_iobuf_0: component IOBUF
     port map (
      I => SDA_tri_o_0(0),
      IO => SDA_tri_io(0),
      O => SDA_tri_i_0(0),
      T => SDA_tri_t_0(0)
    );
end STRUCTURE;
