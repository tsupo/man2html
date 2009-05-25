/*
 *	dirent.h
 *		for OS independent file access routines
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
 * $Log: RCS/dirent.hv $
 * Revision 1.1  95/07/14 02:49:28  tsuporone
 * Initial revision
 * 
 */

#ifndef	__DIRENT_H

#define	__DIRENT_H

#ifdef	MAXDIR
#undef	MAXDIR
#endif

typedef	long	    off_t;
#define	MAXNAMLEN   128

typedef	struct dirdesc	{
    long    dd_fd;	/* file descriptor */
    long    dd_loc;	/* buf offset of entry from last readdir() */
    long    dd_size;	/* amount of valid data in buffer */
    long    dd_bsize;	/* amount of entries read at a time */
    long    dd_off;	/* current offset in dir (for telldir) */
    char    *dd_buf;	/* directory data buffer */
}   DIR;

struct dirent	{
    off_t           d_off;	/* offset of disk directory entry */
    unsigned long   d_fileno;	/* file number of entry */
    unsigned short  d_reclen;	/* length of this record */
#ifdef	MSDOS
    unsigned char   d_attr;	/* file attribute */
    unsigned short  d_fdate;	/* date of file's timestamp */
    unsigned short  d_ftime;	/* time of file's timestamp */
#endif
    char            d_name[MAXNAMLEN+1];  /* name of file */
};

#define	d_ino	d_fileno

#ifdef	MSDOS
#define	S_IHIDDEN	0x02
#define	S_ISYSTEM	0x04
#define	S_IVOLUME	0x08
#define	S_IARCHIVE	0x20
#define	S_ATTRMASK	0x3F
#endif

#ifndef	__
#ifdef	__STDC__
#define	__( args )	args
#else
#define	__( args )	()
#endif
#endif

DIR		*opendir __(( const char * ));
struct dirent	*readdir __(( DIR* ));
long		telldir __(( DIR * ));
void		seekdir __(( DIR *, long ));
int		closedir __(( DIR * ));

#define	rewinddir( dirp )	seekdir( (dirp), 0L )

#endif	/* __DIRENT_H */
