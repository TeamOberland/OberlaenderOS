/*
 * mmu.h
 *
 *  Created on: 13.06.2013
 *      Author: Daniel
 */

#ifndef MMU_GENARC_H_
#define MMU_GENARC_H_

#include "../../../lib/types.h"

void __mmu_init(void);
void __mmu_enable(void);
uint8_t __mmu_get_domain_access(uint8_t domain);
void __mmu_load_dabt_data(void);
void __mmu_update_master_table(void);


#endif /* MMU_H_ */
