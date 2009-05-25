/*
 *	closedir.c
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
 *  ����: Turbo C �Ɋւ��Ă� 1997�N �� MS-DOS Ver 3.x ��� Turbo C++ Ver 2.x
 *        �ɂ�� �R���p�C���A������m�F�����݂̂ŁA����ȍ~�͍�Ƃ��s�Ȃ���
 *        ���܂���(�̂ŁA�ŐV�� Turbo C �������� Borland C �ŃR���p�C���ł�
 *        �邩�ǂ����͕s���ł�)�B
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

