Buying
https://h-node.org/
https://www.fsf.org/resources/hw
https://www.fsf.org/resources/hw/systems
https://www.fsf.org/resources/hw/endorsement/criteria
https://www.fsf.org/resources/hw/endorsement/respects-your-freedom
https://www.fsf.org/resources/hw/endorsement/technoethical
https://www.fsf.org/resources/hw/endorsement/gluglug

Spec
https://support.lenovo.com/jp/en/solutions/migr-73156
http://www.notebookreview.com/notebookreview/lenovo-thinkpad-x200-review/
Intel Graphics Media Accelerator 4500MHD (GMA 4500MHD), in GM45
1. https://www.thinkwiki.org/wiki/Category:X200
2. https://www.thinkwiki.org/wiki/PC3-8500
3. PC3-8500 51J0493 51J0494 (Marketing Part Number)
4. 204pin SODIMM DDR3 1.5V DualRank 1333MT/s 4GB Unbuffered https://www.addonnetworks.com/product/51J0493-AA
   204pin SODIMM DDR3 1.5V ????Rank 1066MT/s 4GB Unbuffered https://www.datamemorysystems.com/parts/lenovo/51J0493/
   204pin SODIMM DDR3 1.5V ????Rank 1066MT/s 4GB Unbuffered https://www.newegg.com/axiom-4gb-204-pin-ddr3-so-dimm/p/N82E16820611909

Battery
https://www.lenovo.com/support/batteries
https://support.lenovo.com/jp/en/solutions/migr-70297
ThinkPad X200, X200s, X201, X201i, X201s
43R9255 ThinkPad Battery 47++ (9 cell)  X200 Series 9 cell 84.2 Wh

Fingerprint
https://wiki.archlinux.org/index.php/ThinkFinger
https://wiki.archlinux.org/index.php/Fprint

Misc
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

CCFL LCD
LTN121W1-L03 Glossy display vs Matte Display

https://unix.stackexchange.com/a/178657/246562
sed -n 'line_num p' | bash
"$(sed -n 'line_num p')"
cat -n ???.txt

Bash disable history
Kill root logins in workspace 10
su -
set +o history

Remove duplicate history
cat .bash_history | wc -l
awk '!visited[$0]++' .bash_history | wc -l
---
vimdiff <(cat .bash_history) <(awk '!visited[$0]++' .bash_history)
---
cat .bash_history | wc -l
cp .bash_history tmp
awk '!visited[$0]++' .bash_history | sponge .bash_history
cat .bash_history | wc -l

Remove history record
---
A='pacman'
A='pacman -[A-Za-z]*$'
---
grep -E "$A" .bash_history | less -SRM +%
cat .bash_history | sed -E -n '/'"$A"'/p'
---
cat .bash_history | wc -l
echo
grep -E -e "$A" .bash_history | wc -l
cat .bash_history | sed -E -n '/'"$A"'/p' | wc -l
echo
cat .bash_history | sed -E '/'"$A"'/d' | wc -l
---
cat .bash_history | wc -l
sed -E -i '/'"$A"'/d' .bash_history
cat .bash_history | wc -l

Power
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

PowerTOP
https://wiki.gentoo.org/wiki/PowerTOP
https://wiki.archlinux.org/index.php/Powertop
https://01.org/powertop/ (videos)
https://youtu.be/pUUEhK8jpZQ
https://youtu.be/Ku0491LfhR4
https://youtu.be/RWyOn1ThEnc

# Trackpoint
# bindsym $mod+Insert exec echo $(($(< /sys/devices/platform/i8042/serio1/sensitivity)+1)) >/sys/devices/platform/i8042/serio1/sensitivity
# bindsym $mod+Delete exec echo $(($(< /sys/devices/platform/i8042/serio1/sensitivity)-1)) >/sys/devices/platform/i8042/serio1/sensitivity
# bindsym $mod+Prior exec echo $(($(< /sys/devices/platform/i8042/serio1/speed)+1)) >/sys/devices/platform/i8042/serio1/speed
# bindsym $mod+Next exec echo $(($(< /sys/devices/platform/i8042/serio1/speed)-1)) >/sys/devices/platform/i8042/serio1/speed

BIOS晶片
winbond
25Q32BVSIG
1222

ch341a_spi Winchiphead (WCH) CH341A 1a86:5512
https://flashrom.org/Supported_hardware#USB_Devices









