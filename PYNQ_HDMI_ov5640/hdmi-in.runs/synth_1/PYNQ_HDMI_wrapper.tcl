# 
# Synthesis run script generated by Vivado
# 

proc create_report { reportName command } {
  set status "."
  append status $reportName ".fail"
  if { [file exists $status] } {
    eval file delete [glob $status]
  }
  send_msg_id runtcl-4 info "Executing : $command"
  set retval [eval catch { $command } msg]
  if { $retval != 0 } {
    set fp [open $status w]
    close $fp
    send_msg_id runtcl-5 warning "$msg"
  }
}
create_project -in_memory -part xc7z020clg400-1

set_param project.singleFileAddWarning.threshold 0
set_param project.compositeFile.enableAutoGeneration 0
set_param synth.vivado.isSynthRun true
set_msg_config -source 4 -id {IP_Flow 19-2162} -severity warning -new_severity info
set_property webtalk.parent_dir /home/junhonglin/Xilinx/PYNQ_Car/PYNQ_HDMI_ov5640/hdmi-in.cache/wt [current_project]
set_property parent.project_path /home/junhonglin/Xilinx/PYNQ_Car/PYNQ_HDMI_ov5640/hdmi-in.xpr [current_project]
set_property XPM_LIBRARIES {XPM_CDC XPM_FIFO XPM_MEMORY} [current_project]
set_property default_lib xil_defaultlib [current_project]
set_property target_language VHDL [current_project]
set_property ip_repo_paths /home/junhonglin/Xilinx/PYNQ_Car/PYNQ_HDMI_ov5640/hdmi-in.ip_user_files [current_project]
set_property ip_output_repo /home/junhonglin/Xilinx/Arty/ArtyZ7/repo/cache [current_project]
set_property ip_cache_permissions {read write} [current_project]
read_vhdl -library xil_defaultlib /home/junhonglin/Xilinx/PYNQ_Car/PYNQ_HDMI_ov5640/hdmi-in.srcs/sources_1/bd/PYNQ_HDMI/hdl/PYNQ_HDMI_wrapper.vhd
add_files /home/junhonglin/Xilinx/PYNQ_Car/PYNQ_HDMI_ov5640/hdmi-in.srcs/sources_1/bd/PYNQ_HDMI/PYNQ_HDMI.bd
set_property used_in_implementation false [get_files -all /home/junhonglin/Xilinx/PYNQ_Car/PYNQ_HDMI_ov5640/hdmi-in.srcs/sources_1/bd/PYNQ_HDMI/ip/PYNQ_HDMI_axi_gpio_video_0/PYNQ_HDMI_axi_gpio_video_0_board.xdc]
set_property used_in_implementation false [get_files -all /home/junhonglin/Xilinx/PYNQ_Car/PYNQ_HDMI_ov5640/hdmi-in.srcs/sources_1/bd/PYNQ_HDMI/ip/PYNQ_HDMI_axi_gpio_video_0/PYNQ_HDMI_axi_gpio_video_0_ooc.xdc]
set_property used_in_implementation false [get_files -all /home/junhonglin/Xilinx/PYNQ_Car/PYNQ_HDMI_ov5640/hdmi-in.srcs/sources_1/bd/PYNQ_HDMI/ip/PYNQ_HDMI_axi_gpio_video_0/PYNQ_HDMI_axi_gpio_video_0.xdc]
set_property used_in_implementation false [get_files -all /home/junhonglin/Xilinx/PYNQ_Car/PYNQ_HDMI_ov5640/hdmi-in.srcs/sources_1/bd/PYNQ_HDMI/ip/PYNQ_HDMI_axi_vdma_0_0/PYNQ_HDMI_axi_vdma_0_0.xdc]
set_property used_in_implementation false [get_files -all /home/junhonglin/Xilinx/PYNQ_Car/PYNQ_HDMI_ov5640/hdmi-in.srcs/sources_1/bd/PYNQ_HDMI/ip/PYNQ_HDMI_axi_vdma_0_0/PYNQ_HDMI_axi_vdma_0_0_clocks.xdc]
set_property used_in_implementation false [get_files -all /home/junhonglin/Xilinx/PYNQ_Car/PYNQ_HDMI_ov5640/hdmi-in.srcs/sources_1/bd/PYNQ_HDMI/ip/PYNQ_HDMI_axi_vdma_0_0/PYNQ_HDMI_axi_vdma_0_0_ooc.xdc]
set_property used_in_implementation false [get_files -all /home/junhonglin/Xilinx/PYNQ_Car/PYNQ_HDMI_ov5640/hdmi-in.srcs/sources_1/bd/PYNQ_HDMI/ip/PYNQ_HDMI_processing_system7_0_0/PYNQ_HDMI_processing_system7_0_0.xdc]
set_property used_in_implementation false [get_files -all /home/junhonglin/Xilinx/PYNQ_Car/PYNQ_HDMI_ov5640/hdmi-in.srcs/sources_1/bd/PYNQ_HDMI/ip/PYNQ_HDMI_rgb2dvi_0_0/src/rgb2dvi.xdc]
set_property used_in_implementation false [get_files -all /home/junhonglin/Xilinx/PYNQ_Car/PYNQ_HDMI_ov5640/hdmi-in.srcs/sources_1/bd/PYNQ_HDMI/ip/PYNQ_HDMI_rgb2dvi_0_0/src/rgb2dvi_ooc.xdc]
set_property used_in_implementation false [get_files -all /home/junhonglin/Xilinx/PYNQ_Car/PYNQ_HDMI_ov5640/hdmi-in.srcs/sources_1/bd/PYNQ_HDMI/ip/PYNQ_HDMI_rgb2dvi_0_0/src/rgb2dvi_clocks.xdc]
set_property used_in_implementation false [get_files -all /home/junhonglin/Xilinx/PYNQ_Car/PYNQ_HDMI_ov5640/hdmi-in.srcs/sources_1/bd/PYNQ_HDMI/ip/PYNQ_HDMI_rst_processing_system7_0_100M_0/PYNQ_HDMI_rst_processing_system7_0_100M_0_board.xdc]
set_property used_in_implementation false [get_files -all /home/junhonglin/Xilinx/PYNQ_Car/PYNQ_HDMI_ov5640/hdmi-in.srcs/sources_1/bd/PYNQ_HDMI/ip/PYNQ_HDMI_rst_processing_system7_0_100M_0/PYNQ_HDMI_rst_processing_system7_0_100M_0.xdc]
set_property used_in_implementation false [get_files -all /home/junhonglin/Xilinx/PYNQ_Car/PYNQ_HDMI_ov5640/hdmi-in.srcs/sources_1/bd/PYNQ_HDMI/ip/PYNQ_HDMI_rst_processing_system7_0_100M_0/PYNQ_HDMI_rst_processing_system7_0_100M_0_ooc.xdc]
set_property used_in_implementation false [get_files -all /home/junhonglin/Xilinx/PYNQ_Car/PYNQ_HDMI_ov5640/hdmi-in.srcs/sources_1/bd/PYNQ_HDMI/ip/PYNQ_HDMI_rst_processing_system7_0_150M_0/PYNQ_HDMI_rst_processing_system7_0_150M_0_board.xdc]
set_property used_in_implementation false [get_files -all /home/junhonglin/Xilinx/PYNQ_Car/PYNQ_HDMI_ov5640/hdmi-in.srcs/sources_1/bd/PYNQ_HDMI/ip/PYNQ_HDMI_rst_processing_system7_0_150M_0/PYNQ_HDMI_rst_processing_system7_0_150M_0.xdc]
set_property used_in_implementation false [get_files -all /home/junhonglin/Xilinx/PYNQ_Car/PYNQ_HDMI_ov5640/hdmi-in.srcs/sources_1/bd/PYNQ_HDMI/ip/PYNQ_HDMI_rst_processing_system7_0_150M_0/PYNQ_HDMI_rst_processing_system7_0_150M_0_ooc.xdc]
set_property used_in_implementation false [get_files -all /home/junhonglin/Xilinx/PYNQ_Car/PYNQ_HDMI_ov5640/hdmi-in.srcs/sources_1/bd/PYNQ_HDMI/ip/PYNQ_HDMI_v_axi4s_vid_out_0_0/PYNQ_HDMI_v_axi4s_vid_out_0_0_clocks.xdc]
set_property used_in_implementation false [get_files -all /home/junhonglin/Xilinx/PYNQ_Car/PYNQ_HDMI_ov5640/hdmi-in.srcs/sources_1/bd/PYNQ_HDMI/ip/PYNQ_HDMI_v_axi4s_vid_out_0_0/PYNQ_HDMI_v_axi4s_vid_out_0_0_ooc.xdc]
set_property used_in_implementation false [get_files -all /home/junhonglin/Xilinx/PYNQ_Car/PYNQ_HDMI_ov5640/hdmi-in.srcs/sources_1/bd/PYNQ_HDMI/ip/PYNQ_HDMI_v_tc_0_0/PYNQ_HDMI_v_tc_0_0_clocks.xdc]
set_property used_in_implementation false [get_files -all /home/junhonglin/Xilinx/PYNQ_Car/PYNQ_HDMI_ov5640/hdmi-in.srcs/sources_1/bd/PYNQ_HDMI/ip/PYNQ_HDMI_v_tc_0_0/PYNQ_HDMI_v_tc_0_0_ooc.xdc]
set_property used_in_implementation false [get_files -all /home/junhonglin/Xilinx/PYNQ_Car/PYNQ_HDMI_ov5640/hdmi-in.srcs/sources_1/bd/PYNQ_HDMI/ip/PYNQ_HDMI_xbar_1/PYNQ_HDMI_xbar_1_ooc.xdc]
set_property used_in_implementation false [get_files -all /home/junhonglin/Xilinx/PYNQ_Car/PYNQ_HDMI_ov5640/hdmi-in.srcs/sources_1/bd/PYNQ_HDMI/ip/PYNQ_HDMI_xbar_0/PYNQ_HDMI_xbar_0_ooc.xdc]
set_property used_in_implementation false [get_files -all /home/junhonglin/Xilinx/PYNQ_Car/PYNQ_HDMI_ov5640/hdmi-in.srcs/sources_1/bd/PYNQ_HDMI/ip/PYNQ_HDMI_clk_wiz_0_3/PYNQ_HDMI_clk_wiz_0_3_board.xdc]
set_property used_in_implementation false [get_files -all /home/junhonglin/Xilinx/PYNQ_Car/PYNQ_HDMI_ov5640/hdmi-in.srcs/sources_1/bd/PYNQ_HDMI/ip/PYNQ_HDMI_clk_wiz_0_3/PYNQ_HDMI_clk_wiz_0_3.xdc]
set_property used_in_implementation false [get_files -all /home/junhonglin/Xilinx/PYNQ_Car/PYNQ_HDMI_ov5640/hdmi-in.srcs/sources_1/bd/PYNQ_HDMI/ip/PYNQ_HDMI_clk_wiz_0_3/PYNQ_HDMI_clk_wiz_0_3_ooc.xdc]
set_property used_in_implementation false [get_files -all /home/junhonglin/Xilinx/PYNQ_Car/PYNQ_HDMI_ov5640/hdmi-in.srcs/sources_1/bd/PYNQ_HDMI/ip/PYNQ_HDMI_proc_sys_reset_2_3/PYNQ_HDMI_proc_sys_reset_2_3_board.xdc]
set_property used_in_implementation false [get_files -all /home/junhonglin/Xilinx/PYNQ_Car/PYNQ_HDMI_ov5640/hdmi-in.srcs/sources_1/bd/PYNQ_HDMI/ip/PYNQ_HDMI_proc_sys_reset_2_3/PYNQ_HDMI_proc_sys_reset_2_3.xdc]
set_property used_in_implementation false [get_files -all /home/junhonglin/Xilinx/PYNQ_Car/PYNQ_HDMI_ov5640/hdmi-in.srcs/sources_1/bd/PYNQ_HDMI/ip/PYNQ_HDMI_proc_sys_reset_2_3/PYNQ_HDMI_proc_sys_reset_2_3_ooc.xdc]
set_property used_in_implementation false [get_files -all /home/junhonglin/Xilinx/PYNQ_Car/PYNQ_HDMI_ov5640/hdmi-in.srcs/sources_1/bd/PYNQ_HDMI/ip/PYNQ_HDMI_v_vid_in_axi4s_0_3/PYNQ_HDMI_v_vid_in_axi4s_0_3_clocks.xdc]
set_property used_in_implementation false [get_files -all /home/junhonglin/Xilinx/PYNQ_Car/PYNQ_HDMI_ov5640/hdmi-in.srcs/sources_1/bd/PYNQ_HDMI/ip/PYNQ_HDMI_v_vid_in_axi4s_0_3/PYNQ_HDMI_v_vid_in_axi4s_0_3_ooc.xdc]
set_property used_in_implementation false [get_files -all /home/junhonglin/Xilinx/PYNQ_Car/PYNQ_HDMI_ov5640/hdmi-in.srcs/sources_1/bd/PYNQ_HDMI/ip/PYNQ_HDMI_v_osd_0_0/PYNQ_HDMI_v_osd_0_0_clocks.xdc]
set_property used_in_implementation false [get_files -all /home/junhonglin/Xilinx/PYNQ_Car/PYNQ_HDMI_ov5640/hdmi-in.srcs/sources_1/bd/PYNQ_HDMI/ip/PYNQ_HDMI_v_osd_0_0/PYNQ_HDMI_v_osd_0_0_ooc.xdc]
set_property used_in_synthesis false [get_files -all /home/junhonglin/Xilinx/PYNQ_Car/PYNQ_HDMI_ov5640/hdmi-in.srcs/sources_1/bd/PYNQ_HDMI/ip/PYNQ_HDMI_ila_0_0/ila_v6_2/constraints/ila_impl.xdc]
set_property used_in_implementation false [get_files -all /home/junhonglin/Xilinx/PYNQ_Car/PYNQ_HDMI_ov5640/hdmi-in.srcs/sources_1/bd/PYNQ_HDMI/ip/PYNQ_HDMI_ila_0_0/ila_v6_2/constraints/ila_impl.xdc]
set_property used_in_implementation false [get_files -all /home/junhonglin/Xilinx/PYNQ_Car/PYNQ_HDMI_ov5640/hdmi-in.srcs/sources_1/bd/PYNQ_HDMI/ip/PYNQ_HDMI_ila_0_0/ila_v6_2/constraints/ila.xdc]
set_property used_in_implementation false [get_files -all /home/junhonglin/Xilinx/PYNQ_Car/PYNQ_HDMI_ov5640/hdmi-in.srcs/sources_1/bd/PYNQ_HDMI/ip/PYNQ_HDMI_ila_0_0/PYNQ_HDMI_ila_0_0_ooc.xdc]
set_property used_in_implementation false [get_files -all /home/junhonglin/Xilinx/PYNQ_Car/PYNQ_HDMI_ov5640/hdmi-in.srcs/sources_1/bd/PYNQ_HDMI/ip/PYNQ_HDMI_axi_gpio_0_0/PYNQ_HDMI_axi_gpio_0_0_board.xdc]
set_property used_in_implementation false [get_files -all /home/junhonglin/Xilinx/PYNQ_Car/PYNQ_HDMI_ov5640/hdmi-in.srcs/sources_1/bd/PYNQ_HDMI/ip/PYNQ_HDMI_axi_gpio_0_0/PYNQ_HDMI_axi_gpio_0_0_ooc.xdc]
set_property used_in_implementation false [get_files -all /home/junhonglin/Xilinx/PYNQ_Car/PYNQ_HDMI_ov5640/hdmi-in.srcs/sources_1/bd/PYNQ_HDMI/ip/PYNQ_HDMI_axi_gpio_0_0/PYNQ_HDMI_axi_gpio_0_0.xdc]
set_property used_in_implementation false [get_files -all /home/junhonglin/Xilinx/PYNQ_Car/PYNQ_HDMI_ov5640/hdmi-in.srcs/sources_1/bd/PYNQ_HDMI/ip/PYNQ_HDMI_auto_pc_1/PYNQ_HDMI_auto_pc_1_ooc.xdc]
set_property used_in_implementation false [get_files -all /home/junhonglin/Xilinx/PYNQ_Car/PYNQ_HDMI_ov5640/hdmi-in.srcs/sources_1/bd/PYNQ_HDMI/ip/PYNQ_HDMI_m00_data_fifo_0/PYNQ_HDMI_m00_data_fifo_0_ooc.xdc]
set_property used_in_implementation false [get_files -all /home/junhonglin/Xilinx/PYNQ_Car/PYNQ_HDMI_ov5640/hdmi-in.srcs/sources_1/bd/PYNQ_HDMI/ip/PYNQ_HDMI_m00_regslice_0/PYNQ_HDMI_m00_regslice_0_ooc.xdc]
set_property used_in_implementation false [get_files -all /home/junhonglin/Xilinx/PYNQ_Car/PYNQ_HDMI_ov5640/hdmi-in.srcs/sources_1/bd/PYNQ_HDMI/ip/PYNQ_HDMI_auto_pc_0/PYNQ_HDMI_auto_pc_0_ooc.xdc]
set_property used_in_implementation false [get_files -all /home/junhonglin/Xilinx/PYNQ_Car/PYNQ_HDMI_ov5640/hdmi-in.srcs/sources_1/bd/PYNQ_HDMI/ip/PYNQ_HDMI_s01_regslice_0/PYNQ_HDMI_s01_regslice_0_ooc.xdc]
set_property used_in_synthesis false [get_files -all /home/junhonglin/Xilinx/PYNQ_Car/PYNQ_HDMI_ov5640/hdmi-in.srcs/sources_1/bd/PYNQ_HDMI/ip/PYNQ_HDMI_auto_us_df_0/PYNQ_HDMI_auto_us_df_0_clocks.xdc]
set_property used_in_implementation false [get_files -all /home/junhonglin/Xilinx/PYNQ_Car/PYNQ_HDMI_ov5640/hdmi-in.srcs/sources_1/bd/PYNQ_HDMI/ip/PYNQ_HDMI_auto_us_df_0/PYNQ_HDMI_auto_us_df_0_clocks.xdc]
set_property used_in_implementation false [get_files -all /home/junhonglin/Xilinx/PYNQ_Car/PYNQ_HDMI_ov5640/hdmi-in.srcs/sources_1/bd/PYNQ_HDMI/ip/PYNQ_HDMI_auto_us_df_0/PYNQ_HDMI_auto_us_df_0_ooc.xdc]
set_property used_in_implementation false [get_files -all /home/junhonglin/Xilinx/PYNQ_Car/PYNQ_HDMI_ov5640/hdmi-in.srcs/sources_1/bd/PYNQ_HDMI/ip/PYNQ_HDMI_s00_regslice_0/PYNQ_HDMI_s00_regslice_0_ooc.xdc]
set_property used_in_implementation false [get_files -all /home/junhonglin/Xilinx/PYNQ_Car/PYNQ_HDMI_ov5640/hdmi-in.srcs/sources_1/bd/PYNQ_HDMI/ip/PYNQ_HDMI_s00_data_fifo_0/PYNQ_HDMI_s00_data_fifo_0_ooc.xdc]
set_property used_in_implementation false [get_files -all /home/junhonglin/Xilinx/PYNQ_Car/PYNQ_HDMI_ov5640/hdmi-in.srcs/sources_1/bd/PYNQ_HDMI/PYNQ_HDMI_ooc.xdc]

# Mark all dcp files as not used in implementation to prevent them from being
# stitched into the results of this synthesis run. Any black boxes in the
# design are intentionally left as such for best results. Dcp files will be
# stitched into the design at a later time, either when this synthesis run is
# opened, or when it is stitched into a dependent implementation run.
foreach dcp [get_files -quiet -all -filter file_type=="Design\ Checkpoint"] {
  set_property used_in_implementation false $dcp
}
read_xdc /home/junhonglin/Xilinx/PYNQ_Car/PYNQ_HDMI_ov5640/hdmi-in.srcs/constrs_1/new/PYNQ_HDMI.xdc
set_property used_in_implementation false [get_files /home/junhonglin/Xilinx/PYNQ_Car/PYNQ_HDMI_ov5640/hdmi-in.srcs/constrs_1/new/PYNQ_HDMI.xdc]

read_xdc dont_touch.xdc
set_property used_in_implementation false [get_files dont_touch.xdc]

synth_design -top PYNQ_HDMI_wrapper -part xc7z020clg400-1 -flatten_hierarchy none -directive RuntimeOptimized -fsm_extraction off


# disable binary constraint mode for synth run checkpoints
set_param constraints.enableBinaryConstraints false
write_checkpoint -force -noxdef PYNQ_HDMI_wrapper.dcp
create_report "synth_1_synth_report_utilization_0" "report_utilization -file PYNQ_HDMI_wrapper_utilization_synth.rpt -pb PYNQ_HDMI_wrapper_utilization_synth.pb"
