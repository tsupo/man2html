/*
 *	readdir.c
 *		directory entry access routine for DOS
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

