/*
 * nullfix.h
 *
 *  Created on: 17.06.2013
 *      Author: Daniel
 */

#ifndef NULLFIX_H_
#define NULLFIX_H_

// very weird bug in this project: some c-files cannot
// find NULL even if it's defined in the types.h
#define NULL 0


#endif /* NULLFIX_H_ */
