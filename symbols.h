/******************************************************************************
* File:    symbols.h
* Author:  Brandon Milton
* Website: http://brandonsoft.com
* GitHub:  http://github.com/brandonio21
* May 19, 2014
*
* This file contains all data pertaining to the symbols that can be found
* within the zim and markdown syntax so they can be easily changed and found
* from within the files themselves. 
******************************************************************************/
#ifndef ZIMDOWN_SYMBOLS
#define ZIMDOWN_SYMBOLS

/* headers */
#define ZIM_HEADER '='          /* === header === */
#define MARKDOWN_HEADER '#'     /* ### header */
#define ZIM_MD_HEADER_DIFF 8    /* difference in h1 vs h6 definitions */

/* italics */
#define ZIM_ITALICS '/'         /* //italics// */
#define MARKDOWN_ITALICS '*'    /* *italics* */

/* bold */
#define ZIM_BOLD '*'            /* **bold** */
#define MARKDOWN_BOLD '*'       /* **bold** */

/* image */
#define ZIM_IMAGE_OPEN '{'      /* {{image}} */
#define ZIM_IMAGE_CLOSE '}'     /* {{image}} */
#define MARKDOWN_IMAGE_OPEN '(' 
#define MARKDOWN_IMAGE_CLOSE ')'


#endif
