/*
 * node.h: automata node header file
 * This file is part of multifast.
 *
    Copyright 2010-2013 Kamiar Kanani <kamiar.kanani@gmail.com>

    multifast is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    multifast is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with multifast.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _NODE_H_
#define _NODE_H_

#include <linux/kmultifast/actypes.h>
#include <linux/kmultifast/ahocorasick.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward Declaration */
struct edge;

/* automata node */
typedef struct AC_NODE
{
    int id; /* Node ID : for debugging purpose */
    short int final; /* 0: no ; 1: yes, it is a final node */
    struct AC_NODE * failure_node; /* The failure node of this node */
    unsigned short depth; /* depth: distance between this node and the root */

    /* Matched patterns */
    //AC_PATTERN_t * matched_patterns; /* Array of matched patterns */
	struct list_head matched_patterns;
	unsigned short matched_patterns_num; /* Number of matched patterns at this node */
    unsigned short matched_patterns_max; /* Max capacity of allocated memory for matched_patterns */

    /* Outgoing Edges */
    struct list_head outgoing; /* Array of outgoing edges */
    unsigned short outgoing_degree; /* Number of outgoing edges */
    unsigned short outgoing_max; /* Max capacity of allocated memory for outgoing */

	struct list_head link; /* attach to AUTOMATA */
} AC_NODE_t;

typedef AC_NODE_t* PAC_NODE_t;

/* The Edge of the Node */
struct edge
{
	struct list_head list;	/*list node*/
    AC_ALPHABET_t alpha; /* Edge alpha */
    AC_NODE_t * next; /* Target of the edge */
};

typedef struct heapframe {
	AC_AUTOMATA_t * Xthiz;
	AC_NODE_t * Xnode;
	AC_ALPHABET_t * Xalphas;
	unsigned int Xi;
	AC_NODE_t * Xnnext;	
	struct heapframe *Xprevframe;
	struct list_head *XL;
	struct edge* XPEDGE;
}heapframe;

AC_STATUS_t node_create(AC_AUTOMATA_t* pac, PAC_NODE_t* pnode);
AC_STATUS_t node_register_matchstr (AC_NODE_t * thiz, AC_PATTERN_t * str);
AC_STATUS_t node_register_outgoing (AC_NODE_t * thiz, AC_NODE_t * next, AC_ALPHABET_t alpha);
AC_NODE_t * node_find_next         (AC_NODE_t * thiz, AC_ALPHABET_t alpha);
AC_NODE_t * node_findbs_next       (AC_NODE_t * thiz, AC_ALPHABET_t alpha);
void        node_release           (AC_NODE_t * thiz);
void        node_sort_edges        (AC_NODE_t * thiz);
AC_STATUS_t node_register_outgoing_nodeptr(AC_AUTOMATA_t * pac, AC_NODE_t * node, AC_NODE_t * next, AC_ALPHABET_t alpha);

#ifdef __cplusplus
}
#endif

#endif
