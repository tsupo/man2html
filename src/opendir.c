/*
 *	opendir.c
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
 * $Log: RCS/opendir.cv $
 * Revision 1.1  95/07/14 03:01:56  tsuporone
 * Initial revision
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef  __TURBO_C__
#include <dir.h>
#else   /* _MSC_VER */
#include <io.h>
#endif  /* _MSC_VER */
#include "dirent.h"

#ifndef	lint
static char	*rcs_id =
	"$Header: opendir.cv  1.1  95/07/14 03:01:56  tsuporone  Exp $";
#endif

#ifdef  __TURBO_C__
typedef	struct ffblk	FILEBUF;
#else   /* _MSC_VER */
typedef	struct _finddata_t  FILEBUF;
#define findfirst   _findfirst
#define findnext    _findnext
#define findclose   _findclose
#endif  /* _MSC_VER */

#ifdef  __STDC__
DIR     *opendir( const char *path )
#else
DIR	*
opendir( path )
char	*path;
#endif
{
    FILEBUF         fbuf;
    char            fname[MAXNAMLEN+1], *pp;
    struct dirent   *dp, *p = NULL;
    DIR		    *d;
    int		    cnt = 1;
    static int      id = 0;
#ifndef  __TURBO_C__    /* _MSC_VER */
    long            handle;
#endif

    d = (DIR *)malloc( sizeof (DIR) );
    if ( !d )
	return ( (DIR *)NULL );

    d->dd_fd    = id++;
    d->dd_loc   = 0L;
    d->dd_size  = 0L;
    d->dd_bsize = sizeof (fbuf) / sizeof (FILEBUF);
    d->dd_off   = 0L;

#ifdef  __TURBO_C__
    if ( findfirst( fname, &fbuf, S_ATTRMASK ) != 0 ) {
        free( (char *)d );
        return ( (DIR *)NULL );
    }
#else   /* _MSC_VER */
    if ( (fname[strlen(fname) - 1] == '\\') ||
         (fname[strlen(fname) - 1] == '/')     )
         sprintf( fname, "%s*.*", path );
    else
        sprintf( fname, "%s\\*.*", path );
    if ( (handle = findfirst( fname, &fbuf )) == -1L ) {
        free( (char *)d );
        return ( (DIR *)NULL );
    }
#endif  /* _MSC_VER */

    do {
	dp = (struct dirent *)malloc( sizeof (struct dirent) );
	if ( !dp ) {
	    free( (char *)d );
	    return ( (DIR *)NULL );
	}
        if ( !p ) {
#ifndef __LCC__
	    (struct dirent *)(d->dd_buf) = dp;
#else
            d->dd_buf = (char *)dp;     /* for LCC-Win32 */
#endif
        }
        else {
#ifndef __LCC__
	    (struct dirent *)(p->d_off)  = dp;
#else
	    p->d_off  = (off_t)dp;      /* for LCC-Win32 */
#endif
        }

	dp->d_fileno = cnt++;
	dp->d_reclen = sizeof (struct dirent);
#ifdef  __TURBO_C__
	strcpy( dp->d_name, fbuf.ff_name );
	dp->d_attr  = fbuf.ff_attrib;
	if ( !(dp->d_attr & (S_IHIDDEN|S_ISYSTEM|S_IVOLUME)) ) {
		/* 通常のファイルまたはディレクトリの場合 */
#define	tolower(c)	(((c)>='A') && ((c)<='Z') ? ((c) - 'A' + 'a') : (c))
	    pp = dp->d_name;
	    while ( *pp ) {
		*pp = tolower( *pp );
		pp++;
	    }
#undef	tolower
	}
	else {	/* 不可視ファイル,システムファイル,ボリュームラベルの場合 */
#define	toupper(c)	(((c)>='a') && ((c)<='z') ? ((c) - 'a' + 'A') : (c))
	    p = dp->d_name;
	    while ( *p ) {
		*p = toupper( *p );
		p++;
	    }
#undef	toupper
	}
	dp->d_fdate = fbuf.ff_fdate;
	dp->d_ftime = fbuf.ff_ftime;
	d->dd_size++;
	p = dp;
#else   /* _MSC_VER */
	sprintf( dp->d_name, "%s/%s", path, fbuf.name );
	dp->d_attr  = fbuf.attrib;
	if ( !(dp->d_attr & (S_IHIDDEN|S_ISYSTEM|S_IVOLUME)) ) {
		/* 通常のファイルまたはディレクトリの場合 */
#define	tolower(c)	(((c)>='A') && ((c)<='Z') ? ((c) - 'A' + 'a') : (c))
	    pp = dp->d_name;
	    while ( *pp ) {
		*pp = tolower( *pp );
		pp++;
	    }
#undef	tolower
	}
	else {	/* 不可視ファイル,システムファイル,ボリュームラベルの場合 */
#define	toupper(c)	(((c)>='a') && ((c)<='z') ? ((c) - 'a' + 'A') : (c))
	    pp = dp->d_name;
	    while ( *pp ) {
		*pp = toupper( *pp );
		pp++;
	    }
#undef	toupper
	}
	dp->d_fdate = fbuf.time_write / (24 * 60 * 60);
	dp->d_ftime = fbuf.time_write % (24 * 60 * 60);
	d->dd_size++;
	p = dp;
#endif  /* _MSC_VER */
    } while (
#ifdef  __TURBO_C__
              !findnext( &fbuf )
#else   /* _MSC_VER */
              !findnext( handle, &fbuf )
#endif
                                         );

#ifndef  __TURBO_C__    /* _MSC_VER */
    findclose( handle );
#endif

    if ( p ) {
#ifndef  __LCC__
	(struct dirent *)(p->d_off) = NULL;
#else
        p->d_off = 0;   /* for LCC-Win32 */
#endif
	d->dd_size++;
    }

    return ( (DIR *)d );
}

