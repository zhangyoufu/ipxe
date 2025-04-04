#ifndef CONFIG_DEFAULTS_PCBIOS_H
#define CONFIG_DEFAULTS_PCBIOS_H

/** @file
 *
 * Configuration defaults for PCBIOS
 *
 */

FILE_LICENCE ( GPL2_OR_LATER_OR_UBDL );

#define UACCESS_LIBRM
#define IOAPI_X86
#define PCIAPI_PCBIOS
#define DMAAPI_FLAT
#define TIMER_PCBIOS
#define CONSOLE_PCBIOS
#define NAP_PCBIOS
#define UMALLOC_MEMTOP
#define SMBIOS_PCBIOS
#define SANBOOT_NULL
#define ENTROPY_RTC
#define ENTROPY_RDRAND
#define TIME_RTC
#define REBOOT_PCBIOS
#define ACPI_RSDP
#define MPAPI_PCBIOS

#ifdef __x86_64__
#define IOMAP_PAGES
#else
#define IOMAP_VIRT
#endif

#define	IMAGE_ELF		/* ELF image support */
#define	IMAGE_MULTIBOOT		/* MultiBoot image support */
#define	IMAGE_PXE		/* PXE image support */
#define IMAGE_SCRIPT		/* iPXE script image support */
#define IMAGE_BZIMAGE		/* Linux bzImage image support */

#define PXE_STACK		/* PXE stack in iPXE - required for PXELINUX */
#define PXE_MENU		/* PXE menu booting */

#define	REBOOT_CMD		/* Reboot command */
#define	CPUID_CMD		/* x86 CPU feature detection command */

#endif /* CONFIG_DEFAULTS_PCBIOS_H */
