
---

&bullet; [readme.md](https://github.com/Un1Gfn/t500)\
**&#9656; bios.md**

---

## Upgrade

[Windows XP SP3](https://archive.org/details/WinXPProSP3x86)\
&bullet; en_windows_xp_professional_with_service_pack_3_x86_cd_vl_x14-73974.iso\
&bullet; sha256sum fd8c8d42c1581e8767217fe800bfc0d5649c0ad20d754c927d6c763e446d1927

**Restore BIOS settings to default before upgrade!**

```plain
# biosdecode -V
3.2
# biosdecode
?
```

[Hiren's BootCD PE - GRUB - Mini Windows XP](https://www.dell.com/community/Linux-General/HOW-TO-Update-BIOS-on-DELL-Laptops-Desktops-Servers-running/td-p/4166910) `C:\DRIVERS\FLASH\6duj48u6\`

[VC++ all-in-one](https://www.techpowerup.com/download/visual-c-redistributable-runtime-package-all-in-one/) - md5sum DA4846C8825F4005B1A854AE3F14946C

[Support > Driver Detail](https://support.lenovo.com/us/en/downloads/migr-70348)

[BIOS Upgrade Downloads](https://www.thinkwiki.org/wiki/BIOS_Upgrade_Downloads)\
&bullet; [Lenovo EOL Portal](https://download.lenovo.com/eol/index.html)\
&bullet; [6duj48us.txt](https://download.lenovo.com/ibmdl/pub/pc/pccbbs/mobiles/6duj48us.txt)

>While the "To interrupt normal startup, press the blue ThinkVantage button"\
>message is displayed at the lower-left area of the screen, press the F1 key.\
>The BIOS Setup Utility menu will be displayed.

>While the "To interrupt normal startup, press the blue ThinkVantage button"\
>message is displayed at the lower-left area of the screen, press the F12\
>key. Boot Menu will be displayed.

    [For BIOS ID 7Vxxxxxx-based computer]
    (Upper two alphanumeric characters of BIOS ID are 7V)
    -----------------------------------------------------
     
      Package  (ID)     BIOS  (BIOS ID)   ECP   (ECP ID)      Rev.  Issue Date
      ----------------  ----------------  ----------------    ----  ---------------
      3.25  (6FUJ46UC)  3.25  (7VET95WW)  1.06  (7VHT16WW)    01    2012/12/07
      ...
      3.13-1.06         3.13  (7VET83WW)  1.06  (7VHT16WW)    01    2010/03/31

Upgrade w/ [SYSLINUX](https://en.wikipedia.org/wiki/SYSLINUX) memdisk\
&bullet; [ThinkWiki](http://www.thinkwiki.org/wiki/BIOS_Upgrade#Manual_method)\
&bullet; [donarmstrong](https://www.donarmstrong.com/posts/x200_bios_update/)\
&bullet; [result?](http://www.thinkwiki.org/wiki/BIOS_Upgrade_success_failure#GRUB2:_Booting_floppy_Image)\
&bullet; use [MEMDISK](https://wiki.syslinux.org/wiki/index.php?title=MEMDISK) from syslinux 4.x (e.g. [4.07](https://mirrors.edge.kernel.org/pub/linux/utils/boot/syslinux/syslinux-4.07.zip)) instead of 6.x

Trial & error\
&bullet; grub4dos - ?\
&bullet; geteltorito.pl img dd usb - ?\
&bullet; geteltorito.pl img syslinux 4.07 memdisk grub2 usb -

    unzip -j syslinux-4.07.zip memdisk/memdisk
    geteltorito.pl -o 6FUJ46UC.IMG 6fuj46uc.iso

<div></div>

    fdisk /dev/sdX
    # <g>  GUID
    # <n> /dev/sdX1 +4M
    # <t> /dev/sdX1 BIOS boot 21686148-6449-6E6F-744E-656564454649
    # <n>  /dev/sdX2 Linux
    # <p>
    # <w>
    mkfs.ext4 -v /dev/sdX2
    sync
    partprobe
    lsblk -f

<div></div>

    mount -v /dev/sdX2 /mnt
    cp -iv memdisk 6FUJ46UC.IMG /mnt/
    grub-install -v --boot-directory=/mnt --target=i386-pc /dev/sdX
    grub-mkconfig -o /mnt/grub/grub.cfg
    tree -aCL 2 /mnt
    umount -v /mnt
    udisksctl power-off -b /dev/sdX

## Misc1

[SMBIOS](https://en.wikipedia.org/wiki/System_Management_BIOS)

[Serial Peripheral Interface (SPI)](https://en.wikipedia.org/wiki/Serial_Peripheral_Interface)

[25Q32BVSIG](http://www.datasheetcafe.com/25q32bvsig-datasheet-w25q32bvssig-winbond/)

    +----------+
    | winbond  |
    |25Q32BVSIG| (drawn by ./box.c)
    |  1222    |
    +----------+

[r/coreboot](https://www.reddit.com/r/coreboot)\
[r/libreboot](https://www.reddit.com/r/libreboot)\
[r/thinkpad](https://www.reddit.com/r/thinkpad)\
[thinkpads.com forum](https://forum.thinkpads.com/)\
[bios-mods forum](https://www.bios-mods.com/)

[Retrieve video BIOS via Linux kernel](https://www.coreboot.org/VGA_support#Retrieval_via_Linux_kernel) - [01.org](https://01.org/linuxgraphics/documentation/development/how-dump-video-bios)

Battery charging threshold\
&bullet; [ectool](https://www.coreboot.org/Ectool)\
&bullet; [X200](https://www.reddit.com/r/coreboot/comments/cb1tc3/librebootet_x200_battery_charging_threshold_using/)\
&bullet; [X220](https://remireuvekamp.nl/blog/setting-battery-thresholds-on-coreboot-x220.html)\
&bullet; [X230](https://www.reddit.com/r/coreboot/comments/exoida/possible_problem_with_battery_charging_due_skulls/)

## BBGW

YouTube video RPI X200\
&bullet; [GnuLinux Geek](https://youtu.be/CyxgYnOcsTw)\
&bullet; [tripcode!Q/7](https://youtu.be/F5mKul8WUn0)\
&bullet; [Bisqwit](https://youtu.be/PUaDkQFD7FE)

[Libreboot Documentation](https://libreboot.org/docs/)\
&bullet; [ThinkPad X200](https://libreboot.org/docs/hardware/x200.html)\
&bullet; [Hardware Compatibility List](https://libreboot.org/docs/hardware/)\
&bullet; [Installation Instructions](https://libreboot.org/docs/install/)\
&nbsp;   &bullet; [BBB](https://libreboot.org/docs/install/bbb_setup.html) - [BBB X200](https://libreboot.org/docs/install/x200_external.html)\
&nbsp;   &bullet; [RPI X200](https://libreboot.org/docs/install/rpi_setup.html#raspberry-pi-thinkpad-x200)\
&nbsp;   &bullet; [MAC address](https://libreboot.org/docs/hardware/mac_address.html)

[Coreboot](https://coreboot.org/) - [GitHub](https://github.com/coreboot/coreboot) - [Documentation](https://doc.coreboot.org/index.html)\
&bullet; [Lenovo X200 / T400 / T500 / X301 common](https://doc.coreboot.org/mainboard/lenovo/montevina_series.html)

## CH341

<details><summary>details</summary>

---

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

</details>
