/*
 * semaphore.h
 *
 *  Created on: 27.05.2013
 *      Author: Daniel
 */

#ifndef SEMAPHORE_H_
#define SEMAPHORE_H_

void semaphore_wait(semaphore_t* semaphore);
void semaphore_notify(semaphore_t* semaphore);

#endif /* SEMAPHORE_H_ */
