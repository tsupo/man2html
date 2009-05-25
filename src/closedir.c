/*
 *	closedir.c
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
 *  注意: Turbo C に関しては 1997年 に MS-DOS Ver 3.x 上で Turbo C++ Ver 2.x
 *        による コンパイル、動作を確認したのみで、それ以降は作業を行なって
 *        いません(ので、最新の Turbo C もしくは Borland C でコンパイルでき
 *        るかどうかは不明です)。
 *
 * History :
 * $Log: RCS/closedir.cv $
 * Revision 1.1  95/07/14 03:02:34  tsuporone
 * Initial revision
 * 
 */

#include <stdlib.h>
#include "dirent.h"

#ifndef	lint
static char	*rcs_id =
	"$Header: closedir.cv  1.1  95/07/14 03:02:34  tsuporone  Exp $";
#endif

int
closedir( dirp )
DIR	*dirp;
{
    int     ret = -1;

    if ( dirp ) {
	long            l = 0;
	struct dirent   *p, *q;

	p = (struct dirent *)(dirp->dd_buf);
	while ( l < (dirp->dd_size - 1L) ) {
	    q = p;
	    p = (struct dirent *)(p->d_off);
	    free( (char *)q );
	    l++;
	}
	free( (char *)dirp );
	ret = 0;
    }

    return ( ret );
}

