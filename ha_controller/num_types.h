/************************************************************************\
 *  Copyright (C), 2017-2020, Capsheaf Tech. Co., Ltd.
 *
 *  FileName: num_types.h
 *  Author: zhouji
 *  Version: V1.0
 *  Date: 2017/07/06
 *  Description:    通用整数定义
 *
 *  History:
 *      <author>   <time>  <version>  <desc>        
 *       zhouji   17/07/06    1.0     构建这个模块
\************************************************************************/

#ifndef _NUM_TYPES_H_
#define _NUM_TYPES_H_

/* 8位无符号整数 */
#ifdef  __u8
#undef  __u8
#define __u8    unsigned char
#endif

/* 16位无符号整数 */
#ifdef  __u16
#undef  __u16
#define __u16   unsigned short
#endif

/* 32位无符号整数 */
#ifdef  __u32
#undef  __u32
#define __u32   unsigned int
#endif

/* 64位无符号整数 */
#ifdef  __u64
#undef  __u64
#define __u64   unsigned long long
#endif

/* 8位有符号整数 */
#ifdef  __s8
#undef  __s8
#define __s8    char
#endif

/* 16位有符号整数 */
#ifdef  __s16
#undef  __s16
#define __s16   short
#endif

/* 32位有符号整数 */
#ifdef  __s32
#undef  __s32
#define __s32   int
#endif

/* 64位有符号整数 */
#ifdef  __s64
#undef  __s64
#define __s64   long long
#endif

#endif
