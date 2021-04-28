<!--
&bullet;
-->

---

**&#9656; readme.md**\
&bullet; [bios.md](https://github.com/Un1Gfn/x200/blob/master/bios.md)

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

Wi-Fi

* PDF page 91 - Intel WiFi Link 5300

|Color|Function|Socket|
|-|-|-|
|gray|MAIN|TR1|
|white||TR3|
|black|AUX|TR2|

* PDF page 133 - antenna

|Color|Function|
|-|-|
|blue|<del>WWAN</del> AUX|
|black|WLAN AUX|
|gray|WLAN MAIN|
|red|<del>WWAN</del> MAIN|

[Battery](https://www.lenovo.com/support/batteries)\
&bullet; [ThinkPad Battery 47/47+/47++](https://support.lenovo.com/jp/en/solutions/migr-70297)\
ThinkPad X200, X200s, X201, X201i, X201s\
43R9255 ThinkPad Battery 47++ (9 cell) X200 Series 9 cell 84.2 Wh

CCFL LCD\
&bullet; LEN4010\
&bullet; LTN121W1-L03 Glossy display vs Matte Display

    $ grep -i "manufacturer" .local/share/xorg/Xorg.0.log
    [   238.099] (II) intel(0): Manufacturer: LEN  Model: 4010  Serial#: 0
    [   238.099] (II) intel(0): Manufacturer's mask: 0

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
