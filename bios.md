
---

&bullet; [readme.md](https://github.com/Un1Gfn/x200)\
**&#9656; bios.md**

---

## Upgrade

**Restore BIOS settings to default before upgrade!**

```plain
# biosdecode -V
3.2
# biosdecode
?
```

[BIOS Upgrade Downloads](https://www.thinkwiki.org/wiki/BIOS_Upgrade_Downloads)\
&bullet; [Lenovo EOL Portal](https://download.lenovo.com/eol/index.html)\
&bullet; [Support > Driver Detail](https://support.lenovo.com/us/en/downloads/migr-70348)\
&bullet; 6duj48u6.exe - sha1sum 4d65b53a566ca94dde09f0e5d0fed0fe940215d9 -\
&nbsp;   &bullet; [Hiren's BootCD PE - GRUB - Mini Windows XP](https://www.dell.com/community/Linux-General/HOW-TO-Update-BIOS-on-DELL-Laptops-Desktops-Servers-running/td-p/4166910) `C:\DRIVERS\FLASH\6duj48u6\`\
&nbsp;   &bullet; [VC++ all-in-one](https://www.techpowerup.com/download/visual-c-redistributable-runtime-package-all-in-one/) - md5sum DA4846C8825F4005B1A854AE3F14946C\

BIOS Update Utility\
&bullet; 6duj48u6.exe\
&bullet; 6duj48us.exe\
&bullet; [6duj48us.txt](https://download.lenovo.com/ibmdl/pub/pc/pccbbs/mobiles/6duj48us.txt) - Read me -

>The file name ends with "US.EXE" for 32-bit, "U6.EXE" for 64-bit Windows.

BIOS Update CD\
&bullet; 6duj48us.iso - sha1sum 461fe63039eb3849ff025d4bcb89b86a3607bf95\
&bullet; [6duj48uc.txt](https://download.lenovo.com/ibmdl/pub/pc/pccbbs/mobiles/6duj48uc.txt) - Read me -

>While the "To interrupt normal startup, press the blue ThinkVantage button"\
>message is displayed at the lower-left area of the screen, press the F1 key.\
>The BIOS Setup Utility menu will be displayed.

>While the "To interrupt normal startup, press the blue ThinkVantage button"\
>message is displayed at the lower-left area of the screen, press the F12\
>key. Boot Menu will be displayed.

    (Upper two alphanumeric characters of BIOS ID are 6D)
     
    Package  (ID)       BIOS  (BIOS ID)   ECP   (ECP ID)      Rev.  Issue Date
    ------------------- ----------------  ----------------    ----  ---------------
    3.22-1.07(6DUJ48UC) 3.22  (6DET72WW)  1.07  (7XHT25WW)    01    2013/07/03
    3.22     (6DUJ47UC) 3.22  (6DET72WW)  1.06  (7XHT24WW)    01    2012/12/13

<div></div>

    (Upper two alphanumeric characters of BIOS ID are 7X)
     
    Package  (ID)       BIOS  (BIOS ID)   ECP   (ECP ID)      Rev.  Issue Date
    ------------------- ----------------  ----------------    ----  ---------------
    3.22-1.07(6DUJ48UC) 3.22  (7XET72WW)  1.07  (7XHT25WW)    01    2013/07/03
    3.22     (6DUJ47UC) 3.22  (7XET72WW)  1.06  (7XHT24WW)    01    2012/12/13

Upgrade w/ [SYSLINUX](https://en.wikipedia.org/wiki/SYSLINUX) memdisk\
&bullet; [ThinkWiki](http://www.thinkwiki.org/wiki/BIOS_Upgrade#Manual_method)\
&bullet; [donarmstrong](https://www.donarmstrong.com/posts/x200_bios_update/)\
&bullet; [result?](http://www.thinkwiki.org/wiki/BIOS_Upgrade_success_failure#GRUB2:_Booting_floppy_Image)\
&bullet; use [MEMDISK](https://wiki.syslinux.org/wiki/index.php?title=MEMDISK) from syslinux 4.x (e.g. [4.07](https://mirrors.edge.kernel.org/pub/linux/utils/boot/syslinux/syslinux-4.07.zip)) instead of 6.x

Trial & error\
&bullet; grub4dos - ?\
&bullet; <del>geteltorito.pl img dd usb</del> Missing operating system\
&bullet; geteltorito.pl img syslinux 4.07 memdisk grub2 usb -

    unzip -j syslinux-4.07.zip memdisk/memdisk
    geteltorito.pl -o 6DUJ48US.IMG 6duj48us.iso

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
    cp -iv memdisk 6DUJ48US.IMG /mnt/
    grub-install -v --boot-directory=/mnt --target=i386-pc /dev/sdX
    grub-mkconfig -o /mnt/grub/grub.cfg
    tree -aCL 2 /mnt
    umount -v /mnt
    udisksctl power-off -b /dev/sdX

## Misc1

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
