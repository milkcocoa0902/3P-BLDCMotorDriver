/*
 * @brief FLASH Memory Controller (FMC) registers and control functions
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2013
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licensor disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights.  NXP Semiconductors assumes no responsibility
 * or liability for the use of the software, conveys no license or rights under any
 * patent, copyright, mask work right, or any other intellectual property rights in
 * or to any products. NXP Semiconductors reserves the right to make changes
 * in the software without notification. NXP Semiconductors also makes no
 * representation or warranty that such application will be suitable for the
 * specified use without further testing or modification.
 *
 * @par
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */

#ifndef __FMC_15XX_H_
#define __FMC_15XX_H_

/** @defgroup FMC_15XX CHIP: LPC15xx FLASH Memory Controller driver
 * @ingroup CHIP_15XX_Drivers
 * @{
 */

/**
 * @brief FLASH Memory Controller Unit register block structure
 */
typedef struct {		/*!< FMC Structure */
	__I  uint32_t  RESERVED1[7];
	__IO uint32_t  FMSSTART;
	__IO uint32_t  FMSSTOP;
	__I  uint32_t  RESERVED2;
	__I  uint32_t  FMSW[1];
} LPC_FMC_T;

/* Flash signature start and busy status bit */
#define FMC_FLASHSIG_BUSY   (1UL << 17)

/**
 * @brief	Start computation of a signature for a FLASH memory range
 * @param	start	: Starting FLASH address for computation, must be aligned on 16 byte boundary
 * @param	stop	: Ending FLASH address for computation, must be aligned on 16 byte boundary
 * @return	Nothing
 * @note	Only bits 20..4 are used for the FLASH signature computation.
 *			Use the Chip_FMC_IsSignatureBusy() function to determine when the
 *			signature computation operation is complete and use the
 *			Chip_FMC_GetSignature() function to get the computed signature.
 */
STATIC INLINE void Chip_FMC_ComputeSignature(uint32_t start, uint32_t stop)
{
	LPC_FMC->FMSSTART = (start >> 4);
	LPC_FMC->FMSSTOP = (stop >> 4) | FMC_FLASHSIG_BUSY;
}

/**
 * @brief	Start computation of a signature for a FLASH memory address and block count
 * @param	start	: Starting FLASH address for computation, must be aligned on 16 byte boundary
 * @param	blocks	: Number of 16 byte blocks used for computation
 * @return	Nothing
 * @note	Only bits 20..4 are used for the FLASH signature computation.
 *			Use the Chip_FMC_IsSignatureBusy() function to determine when the
 *			signature computation operation is complete and the
 *			Chip_FMC_GetSignature() function to get the computed signature.
 */
STATIC INLINE void Chip_FMC_ComputeSignatureBlocks(uint32_t start, uint32_t blocks)
{
	Chip_FMC_ComputeSignature(start, (start + (blocks * 16)));
}

/**
 * @brief	Check for signature geenration completion
 * @return	true if the signature computation is running, false if finished
 */
STATIC INLINE bool Chip_FMC_IsSignatureBusy(void)
{
	return (bool) ((LPC_FMC->FMSSTOP & FMC_FLASHSIG_BUSY) != 0);
}

/**
 * @brief	Returns the generated FLASH signature value
 * @param	index	: Not used, must be 0
 * @return	the generated FLASH signature value
 */
STATIC INLINE uint32_t Chip_FMC_GetSignature(int index)
{
	return LPC_FMC->FMSW[index];
}

/**
 * @}
 */



#endif /* __FMC_15XX_H_ */
