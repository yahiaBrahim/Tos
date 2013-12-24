/*
 * summary : 
 * version : 0.1
 * last modification : 24/08/2007
 * authors :Djekidel Mohamed Nadhir
 * emails  : djek_nad [at] yahoo.com
 * -----------------------------------------------------------------------------
 * This file is a part of the TestOs project (TOS), which aims to give students 
 * and researchers a full set of functions and libraries that can help them to 
 * test there own projects.
 * This program is free software; you can redistribute it and/or modify it under 
 * the terms of the GNU General Public License (GPL).
 * -----------------------------------------------------------------------------
 */


/*
File System FAT
*/
/*Les systemes FAT12/16 et FAT32 sont identique dans les 36 premiers Octets puis ils different */
struct BPB
{
	char Bs_jmpBoot[3];			//Instruction du saut vers le code de demarrage
	char Bs_OEMName[8];//OS qui a formaté le disque
	unsigned short BPB_BytsPerSec;//Taille d'un secteur en octets
	unsigned char BPB_SecPerClus;//Taille d'un cluster en seteur
	unsigned short BPB_ResvdSec;//Nombre de secteur resrvé
	unsigned char  BPB_NumFATs;//Nombre de tables FAT.
	unsigned short BPB_RootEntCnt;//Nombre d'entrées dans le repertoire root
	unsigned short BPB_TotSect16;//Doit être à zero si FAT32
	unsigned char  BPB_Media;//0xF0 ou 0xF8 ou 0xFF
	unsigned short BPB_FatSize16;//Taille d'une FAT12/16 doit être à zero si FAT32
	unsigned short BPB_SecPerTrack;//# de secteur par piste
	unsigned int   BPB_HidSec;//# de secteur avant le debut de la partion qui contient la FAT
	unsigned int   BPB_TotSec32;//# de secteur en FAT32 doit être à zero si FAT16
};
/*A partire de la le BPB de la FAT12/16 et la FAT32 different. */
struct BPB_FAT12_16
{
	unsigned char Bs_DrvNum;
	char		   Reserved;
	char		   BS_BootSig;
	unsigned int BS_VolID;
	char		   BS_VolLab[11];
	char		   BS_FileSysType[8];//"FAT12   " ou "FAT16   " ou "FAT32   "
};

struct BPB_FAT32
{
	unsigned int BPB_FATsize32;
	struct BPB_ExtFlg
	{
		unsigned short NumActFat :4 ;//Bits de (0..3) indique le numero de la FAT active
		unsigned short Reserved  :3 ;//Bits de (4..6) "0" FAT reproduite à tous moment sur tous les FATs
		//				  "1" Seul La FAT NumActFat est active
		unsigned short Dup		 :1;//Bit 7
		unsigned short Resrvd	 :8;//Bits de (8..15)
	};

	struct BPB_FSVer //Indique le numero de la versio exple 0.0
	{
		unsigned char NumVerMajor;
		unsigned char NumVerMineur;
	};
	unsigned int   BPB_RootClus;//numero du cluster qui contient le repertoire racine généralement 2
	unsigned short BPB_FsInfo;//Numero du secteur contenant la structure FSinfo. il est generalement 1
	unsigned short BPB_BkBootSec;//Numero du secteur qui contient la copie du secteur boot
	char  BPB_Reserved[12];
	unsigned char BPB_DrvNum;
	char  BS_Reserved1;
	unsigned char BS_BootSig;
	unsigned int  BS_VolID;
	char		  BS_VolLab[11];
	char		  BS_FileSysType[8];//"FAT12   " ou "FAT16   " ou "FAT32   "
};

//Quelques informations utils pour une meilleur exploitation de la FAT
struct InfosUtils
{
	unsigned int   RootDirSize;//Espace occupé par le repertoire racine
	unsigned int   FirstDataSec;//Numero du premier secteur de données
	unsigned short FATType;//Type de la FAT
	unsigned short RootDirEntry;//Entrée du repertoire racine.
};

#define ATTR_READ_ONLY 0x01 
#define ATTR_HIDDEN    0x02
#define ATTR_SYSTEM	   0x04
#define ATTR_VOLUME_ID 0x08
#define ATTR_DIRECTORY 0x10
#define ATTR_ARCHIVE   0x20
#define ATTR_LONG_NAME ( ATTR_READ_ONLY | ATTR_HIDDEN |ATTR_SYSTEM |ATTR_VOLUME_ID )

struct RepEntry
{
	struct DirName
	{
		char Name[8];//Nom du repertoire
		char Extention[3];//Extention du fichier
	};
	char DirAttr;
};
