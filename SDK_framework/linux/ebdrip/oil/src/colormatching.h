/*
 *      colormatching.h :  hedaer for Color Matching Module 
 *	ICC file I/O header.
 *
 *      $Author$
 *      $Date$
 *      $Revision$
 *
 *      COPYRIGHT (C) 2001 RICOH COMPANY LTD.
 *      All rights reserved.
 */

typedef char    	BYTE;
typedef long     	DWORD;
typedef int **  	HANDLE2;
typedef char *  	PBYTE;
typedef unsigned char  	UBYTE;

/*	fixed number.		*/
typedef	struct FIX_16NUMBER {
	unsigned short	intp;		/* Integer number.	        */
	unsigned short	fractp;		/* fract number.		*/
} fix16_t;

/* ICC profile header tag.	*/
typedef	struct ICC_FILE_HEADER {
	DWORD	filesz;		/* pro file size.			*/
	char	cmmid[4];	/* cmm id.				*/
	DWORD	ver;		/* version of profile.			*/
	DWORD	kind;		/* kind of profile.			*/
	DWORD	cspace;		/* color space.				*/
	DWORD	stdcspace;	/* standard color space.		*/
	char	cdate[12];	/* create date.				*/
	DWORD	acsp;		/* 'acsp'				*/
	DWORD	target;		/* computer name of target.		*/
	DWORD	option;		/* color matching option.		*/
	DWORD	maker;		/* the maker name of of this profile.	*/
	DWORD	model;		/* device model name.			*/
	char	media[8];	/* media type.				*/
	DWORD	xlate;		/* color trans mode.			*/
	fix16_t	D50XYZ[3];	/* standard white of X.			*/
	char	reserve[48];	/* reserved area.			*/
} icchdr_t;


/* tag header data.	*/
typedef	struct ICC_TAG_HEADER {
	DWORD	signature;	/* signature of this tag.		*/
	DWORD	offset;		/* offset of this tag body.		*/
	DWORD	size;		/* size of this tag.			*/
} taghdr_t;


/* Lab->CMY table tag.	*/
typedef	struct LabCMY_Tag {
	BYTE	descripter[4];	/* type descripter '0x6d667431'		*/
	DWORD	reserved1;	/* reserved area(filled by '0')		*/
	BYTE	Ichannel;	/* Input channel.			*/
	BYTE	Ochannel;	/* Output channel.			*/
	BYTE	clut_cnt;	/* color look up table count.		*/
	BYTE	reserved2;	/* reserved byte(filled by '0').	*/
	fix16_t	el[3][3];	/* element of matrics(3X3).		*/
} labtag_t;

#define FALSE               0
#define TRUE                1
#define CMM_OK              0
#define CMM_MEMORYERROR     -3
#define CMM_FILEOPENERROR   -2
#define CMM_ERROR           -1
#define FILEBASE      0
#define MEMORYBASE    1

typedef struct _COLORCACHE {
        unsigned long   nocm_rgb; /* not color matching RGB */
        unsigned long   cm_rgb;   /*     color matching RGB */
} COLORCACHE, *PCOLORCACHE;

PCOLORCACHE   init_colcache();

#ifdef CACHEDEBUG
int           hit = 0;
#endif /* CACHEDEBUG */

/* �i�q�_�� */
#define	NUM_GRID	17 /*64*/

/* 4�F */
#define	NUM_OUTPUT	4  /* KCMY�v���t�@�C���p�Ɋg���ARGB�Ȃ�3��OK */
typedef	unsigned char	rcm_clut[NUM_GRID][NUM_GRID][NUM_GRID][NUM_OUTPUT];

/* �v���t�@�C���� */
#define NUM_PROF        32          /* �e�[�u���̍ő吔�B�ی��Ȃ����������m�ۂ��ăn�b�V���ɓo�^���邽�� */

#define	NUM_OBJTYPE	4 /* number of drawing type.	*/

#define CMM_HASHSZ    16            /* �n�b�V���L�[,�e�[�u���̍ő吔�ł͂Ȃ�                */
#define GETCMMID(id)  ((id) & 0x0f) /* �n�b�V���L�[��16�Ƃ����̂ŁA��]�Z�̓}�X�N��OK�ƂȂ� */
#define GETCMMID_OLD(id)  ((id) % CMM_HASHSZ)

/* CMM HASHTABLE tag.    */
/* CMMLib�ł͓o�^����v���t�@�C������MAX��256�iPROFNUM�̍ő�l�j�����A
   GPS��key��unsigned long�œn����Ă��邽�ߕϊ��e�[�u����p�ӂ���K�v������*/
typedef struct CmmHashTable {
        struct CmmHashTable  *next;  /* next cmm hashtable tag.  */
        unsigned long        gpsid;  /* GPS profile key          */
        unsigned char        cmmid;  /* �ϊ����CMMLib id�Agpsid�ƑΉ����Ă��� */
} cmmhash_t;

/*
 * color matching handle tags.
 */
typedef	struct Color_Matching_Tag {
	rcm_clut  *clutdata[NUM_PROF];  /* RGB->R'B'G' point data. �_���� rcm_clut�^�̃|�C���^�z�� */
	cmmhash_t *hash[CMM_HASHSZ];    /* ID�ϊ��p�̃n�b�V���e�[�u���T�C�Y */
	long    (*allocfunc)();		/* allocate function */
	void    (*freefunc)();		/* free function */
	unsigned long cachesize;        /* size of cache-table */
	void     *handle;               /* handle for allocate&free function */
	PCOLORCACHE cache;      	/* address of cache-table */
#ifdef USE_ACCENTPHOTO
	rcm_clut *backup;          	/* �f�W�J���␳�p�i�q�_�f�[�^�̃o�b�N�A�b�v�̈� */ 
#endif
	unsigned char clutnum[NUM_PROF];	/* �e�v���t�@�C���̊i�q�_�� */
	unsigned char pretype;  	/* �O��g�p�����v���t�@�C���̎�ށi�L���b�V���e�[�u���N���A�p�j */
	unsigned char internal_id;  	/* GPS��key��ϊ����������p��CMMID */   
#ifdef USE_SANDATA
	PBYTE	CLUTSanData[NUM_PROF][3];/* RGB->R'B'G' point data. �ʏ��� */
#endif
} cmm_t;

/* �f�W�J���␳ */
#ifdef USE_ACCENTPHOTO
#define HOKAN_DELTA         16
#define CHROM_CHANGE_SCALE  6
#define A11   0.2989
#define A12   0.5866
#define A13   0.1145
#define GET_Y(r, g, b) (A11*r + A12*g + A13*b)
#endif 

/*
 * �������֐��֘A
 */
#ifdef _WINDOWS
#define CMM_USE_MEMSET		/* Windows �ɂ� bzero() ���Ȃ� */
#endif

#ifdef CMM_USE_MEMSET		/* bzero() �̑���� memset() ���g�� */
#define bzero(ptr, len)		memset(ptr, 0, len)
#endif

/*
 *
 *      COPYRIGHT (C) 2001 RICOH COMPANY LTD.
 *      All rights reserved.
 *
 */

