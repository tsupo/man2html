/*
 *	readdir.c
 *		directory entry access routine for DOS
 *		ANEW product
 *
 *          written by H.Tsujimura  1995
 *          updated by H.Tsujimura  1999    for DOS and WIN32
 *
 *      このディレクトリ関連関数群 (opendir, closedir, readdir) は MS-DOS
 *      用に作成したものです。関数の名前、引数、戻り値は SUN OS 4.x のもの
 *      に合わせました。
 *
 *      UNIX の場合、OS(もしくはコンパイラ附属)のライブラリに opendir が
 *      含まれていれば、それを利用してください。また、GNU の fileutil に
 *      含まれているものが使えるかもしれません。
 *
 *      findfirst(), findnext() を利用しているため、FAT だけではなく、NTFS
 *      などのファイルシステムでも問題なく動作します。
 *      Win32 環境に関しては、Windows 9x, Windows NT 4.0 SP3 上で
 *      Visual C++ 5.0 SP2 および LCC-Win32 Ver 3.1 にてコンパイル、動作の
 *      確認を行なっています。
 *
 *      なお、UNIX本来の opendir, readdir は共に OS 及び ファイルシステムに
 *      依存する実装が行なわれていますが、 本実装では opendir で OS、ファイ
 *      ルシステムの差を全て吸収し、 readdir は OS や ファイルシステムに依
 *      存しないように考慮しています。本実装を他の OS やファイルシステムに
 *      移植する場合は opendir のみを改造するだけで大丈夫です。
 *
 *  注意: Turbo C に関しては 1997年 に MS-DOS Ver 3.x 上で Turbo C++ Ver 2.x
 *        による コンパイル、動作を確認したのみで、それ以降は作業を行なって
 *        いません(ので、最新の Turbo C もしくは Borland C でコンパイルでき
 *        るかどうかは不明です)。
 *
 * History :
 * $Log: RCS/readdir.cv $
 * Revision 1.1  95/07/14 03:02:08  tsuporone
 * Initial revision
 * 
 */

#include <stdlib.h>
#include "dirent.h"

#ifndef	lint
static char	*rcs_id =
	"$Header: readdir.cv  1.1  95/07/14 03:02:08  tsuporone  Exp $";
#endif

struct dirent	*
readdir( dirp )
DIR	*dirp;
{
    long            l = 0L;
    struct dirent   *p;

    if ( dirp->dd_loc + 1L >= dirp->dd_size )
	return ( (struct dirent *)0L );

    p = (struct dirent *)(dirp->dd_buf);
    while ( l < dirp->dd_loc ) {
	p = (struct dirent *)(p->d_off);
	l++;
    }
    dirp->dd_off = ++(dirp->dd_loc);

    return ( p );
}

