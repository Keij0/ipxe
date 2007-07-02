/** @file
 *
 * PXE UNDI API
 *
 */

/*
 * Copyright (C) 2004 Michael Brown <mbrown@fensystems.co.uk>.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <stdint.h>
#include <string.h>
#include <byteswap.h>
#include <gpxe/netdevice.h>
#include <gpxe/device.h>
#include <gpxe/pci.h>
#include <gpxe/if_ether.h>
#include <gpxe/shutdown.h>
#include "pxe.h"

/* PXENV_UNDI_STARTUP
 *
 * Status: working
 */
PXENV_EXIT_t pxenv_undi_startup ( struct s_PXENV_UNDI_STARTUP *undi_startup ) {
	DBG ( "PXENV_UNDI_STARTUP" );

	undi_startup->Status = PXENV_STATUS_SUCCESS;
	return PXENV_EXIT_SUCCESS;
}

/* PXENV_UNDI_CLEANUP
 *
 * Status: working
 */
PXENV_EXIT_t pxenv_undi_cleanup ( struct s_PXENV_UNDI_CLEANUP *undi_cleanup ) {
	DBG ( "PXENV_UNDI_CLEANUP" );

	undi_cleanup->Status = PXENV_STATUS_SUCCESS;
	return PXENV_EXIT_SUCCESS;
}

/* PXENV_UNDI_INITIALIZE
 *
 * Status: working
 */
PXENV_EXIT_t pxenv_undi_initialize ( struct s_PXENV_UNDI_INITIALIZE
				     *undi_initialize ) {
	DBG ( "PXENV_UNDI_INITIALIZE" );

	undi_initialize->Status = PXENV_STATUS_SUCCESS;
	return PXENV_EXIT_SUCCESS;
}

/* PXENV_UNDI_RESET_ADAPTER
 *
 * Status: working
 */
PXENV_EXIT_t pxenv_undi_reset_adapter ( struct s_PXENV_UNDI_RESET
					*undi_reset_adapter ) {
	DBG ( "PXENV_UNDI_RESET_ADAPTER" );

	undi_reset_adapter->Status = PXENV_STATUS_SUCCESS;
	return PXENV_EXIT_SUCCESS;
}

/* PXENV_UNDI_SHUTDOWN
 *
 * Status: working
 */
PXENV_EXIT_t pxenv_undi_shutdown ( struct s_PXENV_UNDI_SHUTDOWN
				   *undi_shutdown ) {
	DBG ( "PXENV_UNDI_SHUTDOWN" );

	shutdown();

	undi_shutdown->Status = PXENV_STATUS_SUCCESS;
	return PXENV_EXIT_SUCCESS;
}

/* PXENV_UNDI_OPEN
 *
 * Status: working
 */
PXENV_EXIT_t pxenv_undi_open ( struct s_PXENV_UNDI_OPEN *undi_open ) {
	DBG ( "PXENV_UNDI_OPEN" );

#if 0
	/* PXESPEC: This is where we choose to enable interrupts.
	 * Can't actually find where we're meant to in the PXE spec,
	 * but this should work.
	 */
	eth_irq ( ENABLE );
#endif

	undi_open->Status = PXENV_STATUS_SUCCESS;
	return PXENV_EXIT_SUCCESS;
}

/* PXENV_UNDI_CLOSE
 *
 * Status: working
 */
PXENV_EXIT_t pxenv_undi_close ( struct s_PXENV_UNDI_CLOSE *undi_close ) {
	DBG ( "PXENV_UNDI_CLOSE" );

	undi_close->Status = PXENV_STATUS_SUCCESS;
	return PXENV_EXIT_SUCCESS;
}

/* PXENV_UNDI_TRANSMIT
 *
 * Status: working
 */
PXENV_EXIT_t pxenv_undi_transmit ( struct s_PXENV_UNDI_TRANSMIT
				   *undi_transmit ) {
	struct s_PXENV_UNDI_TBD *tbd;
	const char *dest;
	unsigned int type;
	unsigned int length;
	const char *data;

	DBG ( "PXENV_UNDI_TRANSMIT" );

#if 0
	/* We support only the "immediate" portion of the TBD.  Who
	 * knows what Intel's "engineers" were smoking when they came
	 * up with the array of transmit data blocks...
	 */
	tbd = SEGOFF16_TO_PTR ( undi_transmit->TBD );
	if ( tbd->DataBlkCount > 0 ) {
		undi_transmit->Status = PXENV_STATUS_UNDI_INVALID_PARAMETER;
		return PXENV_EXIT_FAILURE;
	}
	data = SEGOFF16_TO_PTR ( tbd->Xmit );
	length = tbd->ImmedLength;

	/* If destination is broadcast, we need to supply the MAC address */
	if ( undi_transmit->XmitFlag == XMT_BROADCAST ) {
		dest = broadcast_mac;
	} else {
		dest = SEGOFF16_TO_PTR ( undi_transmit->DestAddr );
	}

	/* We can't properly support P_UNKNOWN without rewriting all
	 * the driver transmit() methods, so we cheat: if P_UNKNOWN is
	 * specified we rip the destination address and type out of
	 * the pre-assembled packet, then skip over the header.
	 */
	switch ( undi_transmit->Protocol ) {
	case P_IP:	type = ETH_P_IP;	break;
	case P_ARP:	type = ETH_P_ARP;	break;
	case P_RARP:	type = ETH_P_RARP;	break;
	case P_UNKNOWN:
		media_header = (media_header_t*)data;
		dest = media_header->dest;
		type = ntohs ( media_header->nstype );
		data += ETH_HLEN;
		length -= ETH_HLEN;
		break;
	default:
		undi_transmit->Status = PXENV_STATUS_UNDI_INVALID_PARAMETER;
		return PXENV_EXIT_FAILURE;
	}

	/* Send the packet */
	eth_transmit ( dest, type, length, data );
#endif
	
	undi_transmit->Status = PXENV_STATUS_SUCCESS;
	return PXENV_EXIT_SUCCESS;
}

/* PXENV_UNDI_SET_MCAST_ADDRESS
 *
 * Status: stub (no PXE multicast support)
 */
PXENV_EXIT_t
pxenv_undi_set_mcast_address ( struct s_PXENV_UNDI_SET_MCAST_ADDRESS
			       *undi_set_mcast_address ) {
	DBG ( "PXENV_UNDI_SET_MCAST_ADDRESS" );

	undi_set_mcast_address->Status = PXENV_STATUS_UNSUPPORTED;
	return PXENV_EXIT_FAILURE;
}

/* PXENV_UNDI_SET_STATION_ADDRESS
 *
 * Status: working
 */
PXENV_EXIT_t 
pxenv_undi_set_station_address ( struct s_PXENV_UNDI_SET_STATION_ADDRESS
				 *undi_set_station_address ) {

	DBG ( "PXENV_UNDI_SET_STATION_ADDRESS" );

	/* If adapter is open, the change will have no effect; return
	 * an error
	 */
	if ( pxe_netdev->state & NETDEV_OPEN ) {
		undi_set_station_address->Status =
			PXENV_STATUS_UNDI_INVALID_STATE;
		return PXENV_EXIT_FAILURE;
	}

	/* Update MAC address */
	memcpy ( pxe_netdev->ll_addr,
		 &undi_set_station_address->StationAddress,
		 pxe_netdev->ll_protocol->ll_addr_len );

	undi_set_station_address = PXENV_STATUS_SUCCESS;
	return PXENV_EXIT_SUCCESS;
}

/* PXENV_UNDI_SET_PACKET_FILTER
 *
 * Status: won't implement (would require driver API changes for no
 * real benefit)
 */
PXENV_EXIT_t
pxenv_undi_set_packet_filter ( struct s_PXENV_UNDI_SET_PACKET_FILTER
			       *undi_set_packet_filter ) {
	DBG ( "PXENV_UNDI_SET_PACKET_FILTER" );

	undi_set_packet_filter->Status = PXENV_STATUS_UNSUPPORTED;
	return PXENV_EXIT_FAILURE;
}

/* PXENV_UNDI_GET_INFORMATION
 *
 * Status: working
 */
PXENV_EXIT_t pxenv_undi_get_information ( struct s_PXENV_UNDI_GET_INFORMATION
					  *undi_get_information ) {
	struct device *dev = pxe_netdev->dev;
	struct ll_protocol *ll_protocol = pxe_netdev->ll_protocol;

	DBG ( "PXENV_UNDI_GET_INFORMATION" );

	undi_get_information->BaseIo = dev->desc.ioaddr;
	undi_get_information->IntNumber = dev->desc.irq;
	/* Cheat: assume all cards can cope with this */
	undi_get_information->MaxTranUnit = ETH_MAX_MTU;
	undi_get_information->HwType = ntohs ( ll_protocol->ll_proto );
	undi_get_information->HwAddrLen = ll_protocol->ll_addr_len;
	/* Cheat: assume card is always configured with its permanent
	 * node address.  This is a valid assumption within Etherboot
	 * at the time of writing.
	 */
	memcpy ( &undi_get_information->CurrentNodeAddress,
		 pxe_netdev->ll_addr,
		 sizeof ( undi_get_information->CurrentNodeAddress ) );
	memcpy ( &undi_get_information->PermNodeAddress,
		 pxe_netdev->ll_addr,
		 sizeof ( undi_get_information->PermNodeAddress ) );
	undi_get_information->ROMAddress = 0;
		/* nic.rom_info->rom_segment; */
	/* We only provide the ability to receive or transmit a single
	 * packet at a time.  This is a bootloader, not an OS.
	 */
	undi_get_information->RxBufCt = 1;
	undi_get_information->TxBufCt = 1;

	undi_get_information->Status = PXENV_STATUS_SUCCESS;
	return PXENV_EXIT_SUCCESS;
}

/* PXENV_UNDI_GET_STATISTICS
 *
 * Status: won't implement (would require driver API changes for no
 * real benefit)
 */
PXENV_EXIT_t pxenv_undi_get_statistics ( struct s_PXENV_UNDI_GET_STATISTICS
					 *undi_get_statistics ) {
	DBG ( "PXENV_UNDI_GET_STATISTICS" );

	undi_get_statistics->Status = PXENV_STATUS_UNSUPPORTED;
	return PXENV_EXIT_FAILURE;
}

/* PXENV_UNDI_CLEAR_STATISTICS
 *
 * Status: won't implement (would require driver API changes for no
 * real benefit)
 */
PXENV_EXIT_t pxenv_undi_clear_statistics ( struct s_PXENV_UNDI_CLEAR_STATISTICS
					   *undi_clear_statistics ) {
	DBG ( "PXENV_UNDI_CLEAR_STATISTICS" );

	undi_clear_statistics->Status = PXENV_STATUS_UNSUPPORTED;
	return PXENV_EXIT_FAILURE;
}

/* PXENV_UNDI_INITIATE_DIAGS
 *
 * Status: won't implement (would require driver API changes for no
 * real benefit)
 */
PXENV_EXIT_t pxenv_undi_initiate_diags ( struct s_PXENV_UNDI_INITIATE_DIAGS
					 *undi_initiate_diags ) {
	DBG ( "PXENV_UNDI_INITIATE_DIAGS" );

	undi_initiate_diags->Status = PXENV_STATUS_UNSUPPORTED;
	return PXENV_EXIT_FAILURE;
}

/* PXENV_UNDI_FORCE_INTERRUPT
 *
 * Status: working
 */
PXENV_EXIT_t pxenv_undi_force_interrupt ( struct s_PXENV_UNDI_FORCE_INTERRUPT
					  *undi_force_interrupt ) {
	DBG ( "PXENV_UNDI_FORCE_INTERRUPT" );

#if 0
	eth_irq ( FORCE );
#endif

	undi_force_interrupt->Status = PXENV_STATUS_SUCCESS;
	return PXENV_EXIT_SUCCESS;
}

/* PXENV_UNDI_GET_MCAST_ADDRESS
 *
 * Status: stub (no PXE multicast support)
 */
PXENV_EXIT_t
pxenv_undi_get_mcast_address ( struct s_PXENV_UNDI_GET_MCAST_ADDRESS
			       *undi_get_mcast_address ) {
	DBG ( "PXENV_UNDI_GET_MCAST_ADDRESS" );

	undi_get_mcast_address->Status = PXENV_STATUS_UNSUPPORTED;
	return PXENV_EXIT_FAILURE;
}

/* PXENV_UNDI_GET_NIC_TYPE
 *
 * Status: working
 */
PXENV_EXIT_t pxenv_undi_get_nic_type ( struct s_PXENV_UNDI_GET_NIC_TYPE
				       *undi_get_nic_type ) {
	struct device *dev = pxe_netdev->dev;

	DBG ( "PXENV_UNDI_GET_NIC_TYPE" );

	memset ( &undi_get_nic_type->info, 0,
		 sizeof ( undi_get_nic_type->info ) );

	switch ( dev->desc.bus_type ) {
	case BUS_TYPE_PCI: {
		struct pci_nic_info *info = &undi_get_nic_type->info.pci;

		undi_get_nic_type->NicType = PCI_NIC;
		info->Vendor_ID = dev->desc.vendor;
		info->Dev_ID = dev->desc.device;
		info->Base_Class = PCI_BASE_CLASS ( dev->desc.class );
		info->Sub_Class = PCI_SUB_CLASS ( dev->desc.class );
		info->Prog_Intf = PCI_PROG_INTF ( dev->desc.class );
		info->BusDevFunc = dev->desc.location;
		/* Cheat: remaining fields are probably unnecessary,
		 * and would require adding extra code to pci.c.
		 */
		undi_get_nic_type->info.pci.SubVendor_ID = 0xffff;
		undi_get_nic_type->info.pci.SubDevice_ID = 0xffff;
		break; }
	case BUS_TYPE_ISAPNP: {
		struct pnp_nic_info *info = &undi_get_nic_type->info.pnp;

		undi_get_nic_type->NicType = PnP_NIC;
		info->EISA_Dev_ID = ( ( dev->desc.vendor << 16 ) |
				      dev->desc.device );
		info->CardSelNum = dev->desc.location;
		/* Cheat: remaining fields are probably unnecessary,
		 * and would require adding extra code to isapnp.c.
		 */
		break; }
	default:
		undi_get_nic_type->Status = PXENV_STATUS_FAILURE;
		return PXENV_EXIT_FAILURE;
	}

	undi_get_nic_type->Status = PXENV_STATUS_SUCCESS;
	return PXENV_EXIT_SUCCESS;
}

/* PXENV_UNDI_GET_IFACE_INFO
 *
 * Status: working
 */
PXENV_EXIT_t pxenv_undi_get_iface_info ( struct s_PXENV_UNDI_GET_IFACE_INFO
					 *undi_get_iface_info ) {
	DBG ( "PXENV_UNDI_GET_IFACE_INFO" );

#if 0
	/* Just hand back some info, doesn't really matter what it is.
	 * Most PXE stacks seem to take this approach.
	 */
	sprintf ( undi_get_iface_info->IfaceType, "Etherboot" );
	undi_get_iface_info->LinkSpeed = 10000000; /* 10 Mbps */
	undi_get_iface_info->ServiceFlags = 0;
	memset ( undi_get_iface_info->Reserved, 0,
		 sizeof(undi_get_iface_info->Reserved) );
#endif

	undi_get_iface_info->Status = PXENV_STATUS_SUCCESS;
	return PXENV_EXIT_SUCCESS;
}

/* PXENV_UNDI_GET_STATE
 *
 * Status: impossible
 */
PXENV_EXIT_t pxenv_undi_get_state ( struct s_PXENV_UNDI_GET_STATE
				    *undi_get_state ) {
	DBG ( "PXENV_UNDI_GET_STATE" );

	undi_get_state->Status = PXENV_STATUS_UNSUPPORTED;
	return PXENV_EXIT_FAILURE;
};

/* PXENV_UNDI_ISR
 *
 * Status: working
 */
PXENV_EXIT_t pxenv_undi_isr ( struct s_PXENV_UNDI_ISR *undi_isr ) {
	DBG ( "PXENV_UNDI_ISR" );

#if 0
	/* We can't call ENSURE_READY, because this could be being
	 * called as part of an interrupt service routine.  Instead,
	 * we should simply die if we're not READY.
	 */
	if ( ( pxe_stack == NULL ) || ( pxe_stack->state < READY ) ) {
		undi_isr->Status = PXENV_STATUS_UNDI_INVALID_STATE;
		return PXENV_EXIT_FAILURE;
	}
	
	/* Just in case some idiot actually looks at these fields when
	 * we weren't meant to fill them in...
	 */
	undi_isr->BufferLength = 0;
	undi_isr->FrameLength = 0;
	undi_isr->FrameHeaderLength = 0;
	undi_isr->ProtType = 0;
	undi_isr->PktType = 0;

	switch ( undi_isr->FuncFlag ) {
	case PXENV_UNDI_ISR_IN_START :
		/* Is there a packet waiting?  If so, disable
		 * interrupts on the NIC and return "it's ours".  Do
		 * *not* necessarily acknowledge the interrupt; this
		 * can happen later when eth_poll(1) is called.  As
		 * long as the interrupt is masked off so that it
		 * doesn't immediately retrigger the 8259A then all
		 * should be well.
		 */
		DBG ( " START" );
		if ( eth_poll ( 0 ) ) {
			DBG ( " OURS" );
			eth_irq ( DISABLE );
			undi_isr->FuncFlag = PXENV_UNDI_ISR_OUT_OURS;
		} else {
			DBG ( " NOT_OURS" );
			undi_isr->FuncFlag = PXENV_UNDI_ISR_OUT_NOT_OURS;
		}
		break;
	case PXENV_UNDI_ISR_IN_PROCESS :
		/* Call poll(), return packet.  If no packet, return "done".
		 */
		DBG ( " PROCESS" );
		if ( eth_poll ( 1 ) ) {
			DBG ( " RECEIVE %d", nic.packetlen );
			if ( nic.packetlen > sizeof(pxe_stack->packet) ) {
				/* Should never happen */
				undi_isr->FuncFlag = PXENV_UNDI_ISR_OUT_DONE;
				undi_isr->Status =
					PXENV_STATUS_OUT_OF_RESOURCES;
				return PXENV_EXIT_FAILURE;
			}
			undi_isr->FuncFlag = PXENV_UNDI_ISR_OUT_RECEIVE;
			undi_isr->BufferLength = nic.packetlen;
			undi_isr->FrameLength = nic.packetlen;
			undi_isr->FrameHeaderLength = ETH_HLEN;
			memcpy ( pxe_stack->packet, nic.packet, nic.packetlen);
			PTR_TO_SEGOFF16 ( pxe_stack->packet, undi_isr->Frame );
			switch ( ntohs(media_header->nstype) ) {
			case ETH_P_IP:	undi_isr->ProtType = P_IP;	break;
			case ETH_P_ARP:	undi_isr->ProtType = P_ARP;	break;
			case ETH_P_RARP: undi_isr->ProtType = P_RARP;	break;
			default :	undi_isr->ProtType = P_UNKNOWN;
			}
			if ( memcmp ( media_header->dest, broadcast_mac,
				      sizeof(broadcast_mac) ) ) {
				undi_isr->PktType = XMT_BROADCAST;
			} else {
				undi_isr->PktType = XMT_DESTADDR;
			}
			break;
		} else {
			/* No break - fall through to IN_GET_NEXT */
		}
	case PXENV_UNDI_ISR_IN_GET_NEXT :
		/* We only ever return one frame at a time */
		DBG ( " GET_NEXT DONE" );
		/* Re-enable interrupts */
		eth_irq ( ENABLE );
		/* Force an interrupt if there's a packet still
		 * waiting, since we only handle one packet per
		 * interrupt.
		 */
		if ( eth_poll ( 0 ) ) {
			DBG ( " (RETRIGGER)" );
			eth_irq ( FORCE );
		}
		undi_isr->FuncFlag = PXENV_UNDI_ISR_OUT_DONE;
		break;
	default :
		/* Should never happen */
		undi_isr->FuncFlag = PXENV_UNDI_ISR_OUT_DONE;
		undi_isr->Status = PXENV_STATUS_UNDI_INVALID_PARAMETER;
		return PXENV_EXIT_FAILURE;
	}
#endif

	undi_isr->Status = PXENV_STATUS_SUCCESS;
	return PXENV_EXIT_SUCCESS;
}
