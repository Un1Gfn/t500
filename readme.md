<!--
&bullet;
-->

## BIOS.GENERAL

[Serial Peripheral Interface (SPI)](https://en.wikipedia.org/wiki/Serial_Peripheral_Interface)

[25Q32BVSIG](http://www.datasheetcafe.com/25q32bvsig-datasheet-w25q32bvssig-winbond/)

    +----------+
    | winbond  |
    |25Q32BVSIG| (drawn by ./box.c)
    |  1222    |
    +----------+

[Latest BIOS Update](https://download.lenovo.com/eol/index.html)\
&bullet; 6duj48us.iso - sha1sum 461fe63039eb3849ff025d4bcb89b86a3607bf95 \
&bullet; [6duj48uc.txt](https://download.lenovo.com/ibmdl/pub/pc/pccbbs/mobiles/6duj48uc.txt) - Read me

[r/coreboot](https://www.reddit.com/r/coreboot)\
[r/libreboot](https://www.reddit.com/r/libreboot)\
[r/thinkpad](https://www.reddit.com/r/thinkpad)\
[thinkpads.com forum](https://forum.thinkpads.com/)\
[bios-mods forum](https://www.bios-mods.com/)

[Retrieve video BIOS via Linux kernel](https://www.coreboot.org/VGA_support#Retrieval_via_Linux_kernel) - [01.org](https://01.org/linuxgraphics/documentation/development/how-dump-video-bios)

## BIOS.FLASHING.BBGW

[Allwinner V5 eMMC Support List](http://files.lindeni.org/lindenis-v5/documents/support_list/Allwinner%C2%A0V5%20eMMC%C2%A0Support%C2%A0List.pdf)\
&bullet; [MTFC8GAKAJCN-1M WT / **Micron MTFC4GACAJCN-1M WT (possibly 6FA27-JY976)**](https://www.micron.com/products/managed-nand/emmc/part-catalog/mtfc8gakajcn-1m-wt)

[Libreboot Documentation](https://libreboot.org/docs/)\
&bullet; [ThinkPad X200](https://libreboot.org/docs/hardware/x200.html)\
&bullet; [Hardware Compatibility List](https://libreboot.org/docs/hardware/)\
&bullet; [Installation Instructions](https://libreboot.org/docs/install/)\
&nbsp;   &bullet; [BBB](https://libreboot.org/docs/install/bbb_setup.html) - [BBB X200](https://libreboot.org/docs/install/x200_external.html)\
&nbsp;   &bullet; [RPI X200](https://libreboot.org/docs/install/rpi_setup.html#raspberry-pi-thinkpad-x200)\
&nbsp;   &bullet; [MAC address](https://libreboot.org/docs/hardware/mac_address.html)

[Coreboot](https://coreboot.org/) - [GitHub](https://github.com/coreboot/coreboot) - [Documentation](https://doc.coreboot.org/index.html)\
&bullet; [Lenovo X200 / T400 / T500 / X301 common](https://doc.coreboot.org/mainboard/lenovo/montevina_series.html)

## BIOS.FLASHING.CH341

[CH341A schematics](https://www.onetransistor.eu/2017/08/ch341a-mini-programmer-schematic.html) -
[XTW100 schematics](https://www.onetransistor.eu/2020/08/xtw100-minprogrammer-schematic-driver.html)

**[Do not use CH341A!](https://libreboot.org/faq.html#do-not-use-ch341a)**\
&bullet; [3V 32M-BIT](https://www.winbond.com/resource-files/w25q32bv_revi_100413_wo_automotive.pdf#page=1)\
&bullet; [Supply Voltage VCC MAX 3.6](https://www.winbond.com/resource-files/w25q32bv_revi_100413_wo_automotive.pdf#page=61)\
&bullet; [V = 2.7V to 3.6V](https://www.winbond.com/resource-files/w25q32bv_revi_100413_wo_automotive.pdf#page=76)

Fix\
&bullet; [YouTube](https://www.youtube.com/watch?v=-ln3VIZKKaE)\
&bullet; [EEVblog](https://www.eevblog.com/forum/repair/ch341a-serial-memory-programmer-power-supply-fix/)

[1a86:5512](https://linux-hardware.org/?id=usb:1a86-5512)\
&bullet; lsmod - ch341\
&bullet; ["ch341" on lcsc](https://lcsc.com/search?q=ch341)\
&bullet; ["ch341" on szlcsc](https://so.szlcsc.com/global.html?k=ch341)\
&bullet; [flashrom](https://flashrom.org/Supported_hardware#USB_Devices) - ch341a_spi Winchiphead (WCH) CH341A\
&bullet; lsusb - QinHeng Electronics CH341 in EPP/MEM/I2C mode, EPP/I2C adapter\
&bullet; modinfo - /lib/modules/"$(uname -r)"/kernel/drivers/usb/serial/ch341.ko.xz


---

X200 specs\
&bullet; [Lenovo](https://support.lenovo.com/jp/en/solutions/migr-73156)\
&bullet; [NotebookReview](http://www.notebookreview.com/notebookreview/lenovo-thinkpad-x200-review/)\
&bullet; [ThinkWiki](https://www.thinkwiki.org/wiki/Category:X200)

[Hardware Devices that Support GNU/Linux](https://www.fsf.org/resources/hw)\
&bullet; [Recommended Complete Systems](https://www.fsf.org/resources/hw/systems)

hardware databases\
&bullet; [h-node](https://h-node.org) \
&bullet; [linux-hardware](https://linux-hardware.org)

[Respects Your Freedom (RYF) Certification](https://ryf.fsf.org/)\
&bullet; [criteria](https://ryf.fsf.org/about/criteria/)\
&bullet; [Technoethical TET-X200](https://ryf.fsf.org/products/TET-X200)

[Battery](https://www.lenovo.com/support/batteries)\
&bullet; [ThinkPad Battery 47/47+/47++](https://support.lenovo.com/jp/en/solutions/migr-70297)\
ThinkPad X200, X200s, X201, X201i, X201s\
43R9255 ThinkPad Battery 47++ (9 cell) X200 Series 9 cell 84.2 Wh

CCFL LCD\
&bullet; LTN121W1-L03 Glossy display vs Matte Display

Fingerprint\
&bullet; [ThinkFinger](https://wiki.archlinux.org/index.php/ThinkFinger)\
&bullet; [Fprint](https://wiki.archlinux.org/index.php/Fprint)

Graphics\
&bullet; GM45 - GMA 4500MHD - Intel Graphics Media Accelerator 4500MHD

[PC3-8500 DRAM](https://www.thinkwiki.org/wiki/PC3-8500) - marketing part number 51J0493 51J0494\
&bullet; [204pin SODIMM DDR3 1.5V DualRank 1333MT/s 4GB Unbuffered](https://www.addonnetworks.com/product/51J0493-AA)\
&bullet; [204pin SODIMM DDR3 1.5V ????Rank 1066MT/s 4GB Unbuffered](https://www.datamemorysystems.com/parts/lenovo/51J0493/)\
&bullet; [204pin SODIMM DDR3 1.5V ????Rank 1066MT/s 4GB Unbuffered](https://www.newegg.com/axiom-4gb-204-pin-ddr3-so-dimm/p/N82E16820611909)

<details><summary>Bash history</summary>

```bash
# https://unix.stackexchange.com/a/178657/246562
sed -n 'line_num p' | bash
"$(sed -n 'line_num p')"
cat -n ???.txt

# Disable history
Kill root logins in workspace 10
su -
set +o history

# Remove duplicate
cat .bash_history | wc -l
awk '!visited[$0]++' .bash_history | wc -l
#
vimdiff <(cat .bash_history) <(awk '!visited[$0]++' .bash_history)
#
cat .bash_history | wc -l
cp .bash_history tmp
awk '!visited[$0]++' .bash_history | sponge .bash_history
cat .bash_history | wc -l

# Remove history record
#
A='pacman'
A='pacman -[A-Za-z]*$'
#
grep -E "$A" .bash_history | less -SRM +%
cat .bash_history | sed -E -n '/'"$A"'/p'
#
cat .bash_history | wc -l
echo
grep -E -e "$A" .bash_history | wc -l
cat .bash_history | sed -E -n '/'"$A"'/p' | wc -l
echo
cat .bash_history | sed -E '/'"$A"'/d' | wc -l
#
cat .bash_history | wc -l
sed -E -i '/'"$A"'/d' .bash_history
cat .bash_history | wc -l
```

</details>

<details><summary>Power</summary>

    tlp-stat
    https://www.2daygeek.com/check-laptop-battery-status-and-charging-state-in-linux-terminal/
    https://wiki.archlinux.org/index.php/Improving_performance

    power off bluetooth/USB/IntegratedSoundJHardware
    https://askubuntu.com/questions/218567/any-way-to-check-the-clock-speed-of-my-processor/218570
    lscpu | grep -i hz
    cpupower frequency-set -u 9999MHz
    cpupower frequency-set -d 0000MHz
    https://wiki.archlinux.org/index.php/Laptop_Mode_Tools
    https://wiki.archlinux.org/index.php/Improving_performance#CPU
    https://wiki.archlinux.org/index.php/CPU_frequency_scaling
    https://wiki.archlinux.org/index.php/Power_management#Power_saving
    https://wiki.archlinux.org/index.php/Laptop#Power_management
    https://developer.toradex.com/knowledge-base/cpu-frequency-(linux)

</details>

<details><summary>PowerTOP</summary>

    https://wiki.gentoo.org/wiki/PowerTOP
    https://wiki.archlinux.org/index.php/Powertop
    https://01.org/powertop/ (videos)
    https://youtu.be/pUUEhK8jpZQ
    https://youtu.be/Ku0491LfhR4
    https://youtu.be/RWyOn1ThEnc

</details>


<details><summary>Trackpoint</summary>

    # i3wm config
    bindsym $mod+Insert exec echo $(($(< /sys/devices/platform/i8042/serio1/sensitivity)+1)) >/sys/devices/platform/i8042/serio1/sensitivity
    bindsym $mod+Delete exec echo $(($(< /sys/devices/platform/i8042/serio1/sensitivity)-1)) >/sys/devices/platform/i8042/serio1/sensitivity
    bindsym $mod+Prior exec echo $(($(< /sys/devices/platform/i8042/serio1/speed)+1)) >/sys/devices/platform/i8042/serio1/speed
    bindsym $mod+Next exec echo $(($(< /sys/devices/platform/i8042/serio1/speed)-1)) >/sys/devices/platform/i8042/serio1/speed

</details>

<details><summary>Misc</summary>

    https://www.thinkwiki.org/wiki/ThinkPad_X200_UltraBase
    https://www.thinkwiki.org/wiki/Installing_Arch_on_an_X200
    https://www.thinkwiki.org/wiki/ThinkPad_History
    https://www.thinkwiki.org/wiki/Category:X200
    https://www.thinkwiki.org/wiki/How_to_configure_the_TrackPoint
    https://www.thinkwiki.org/wiki/TrackPoint
    https://www.thinkwiki.org/wiki/Integrated_Fingerprint_Reader
    https://www.thinkwiki.org/wiki/ThinkLight
    https://www.thinkwiki.org/wiki/Thinkpad-acpi
    https://www.thinkwiki.org/wiki/Ultrabay
    https://www.thinkwiki.org/wiki/Post_Installing_Arch_on_an_X200
    https://www.thinkwiki.org/wiki/Extending_battery_life_on_X200
    https://www.thinkwiki.org/wiki/Installation_instructions_for_the_ThinkPad_X200
    https://www.thinkwiki.org/wiki/Problem_with_unauthorized_MiniPCI_network_card

    i3blocks
    https://wiki.archlinux.org/index.php/I3#i3bar

    https://www.hogarthuk.com/?q=node/8
    #
    nmcli general status
    nmcli general status
    nmcli general hostname
    nmcli general permissions
    nmcli general logging
    #
    nmcli connection show
    nmcli networking connectivity check
    nmcli radio
    nmcli connection delete
    nmcli devices

</details>
