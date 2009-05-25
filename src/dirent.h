/*
 *	dirent.h
 *		for OS independent file access routines
 *		ANEW product
 *
 *          written by H.Tsujimura  1995
 *          updated by H.Tsujimura  1999    for DOS and WIN32
 *
 *      ���̃f�B���N�g���֘A�֐��Q (opendir, closedir, readdir) �� MS-DOS
 *      �p�ɍ쐬�������̂ł��B�֐��̖��O�A�����A�߂�l�� SUN OS 4.x �̂���
 *      �ɍ��킹�܂����B
 *
 *      UNIX �̏ꍇ�AOS(�������̓R���p�C������)�̃��C�u������ opendir ��
 *      �܂܂�Ă���΁A����𗘗p���Ă��������B�܂��AGNU �� fileutil ��
 *      �܂܂�Ă�����̂��g���邩������܂���B
 *
 *      findfirst(), findnext() �𗘗p���Ă��邽�߁AFAT �����ł͂Ȃ��ANTFS
 *      �Ȃǂ̃t�@�C���V�X�e���ł����Ȃ����삵�܂��B
 *      Win32 ���Ɋւ��ẮAWindows 9x, Windows NT 4.0 SP3 ���
 *      Visual C++ 5.0 SP2 ����� LCC-Win32 Ver 3.1 �ɂăR���p�C���A�����
 *      �m�F���s�Ȃ��Ă��܂��B
 *
 *      �Ȃ��AUNIX�{���� opendir, readdir �͋��� OS �y�� �t�@�C���V�X�e����
 *      �ˑ�����������s�Ȃ��Ă��܂����A �{�����ł� opendir �� OS�A�t�@�C
 *      ���V�X�e���̍���S�ċz�����A readdir �� OS �� �t�@�C���V�X�e���Ɉ�
 *      �����Ȃ��悤�ɍl�����Ă��܂��B�{�����𑼂� OS ��t�@�C���V�X�e����
 *      �ڐA����ꍇ�� opendir �݂̂��������邾���ő��v�ł��B
 *
 *  ����: Turbo C �Ɋւ��Ă� 1997�N �� MS-DOS Ver 3.x ��� Turbo C++ Ver 2.x
 *        �ɂ�� �R���p�C���A������m�F�����݂̂ŁA����ȍ~�͍�Ƃ��s�Ȃ���
 *        ���܂���(�̂ŁA�ŐV�� Turbo C �������� Borland C �ŃR���p�C���ł�
 *        �邩�ǂ����͕s���ł�)�B
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
