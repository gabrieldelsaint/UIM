/* UOL Messenger
 * Copyright (c) 2005 Universo Online S/A
 *
 * Direitos Autorais Reservados
 * All rights reserved
 *
 * Este programa � software livre; voc� pode redistribu�-lo e/ou modific�-lo
 * sob os termos da Licen�a P�blica Geral GNU conforme publicada pela Free
 * Software Foundation; tanto a vers�o 2 da Licen�a, como (a seu crit�rio)
 * qualquer vers�o posterior.
 * Este programa � distribu�do na expectativa de que seja �til, por�m,
 * SEM NENHUMA GARANTIA; nem mesmo a garantia impl�cita de COMERCIABILIDADE
 * OU ADEQUA��O A UMA FINALIDADE ESPEC�FICA. Consulte a Licen�a P�blica Geral
 * do GNU para mais detalhes. 
 * Voc� deve ter recebido uma c�pia da Licen�a P�blica Geral do GNU junto
 * com este programa; se n�o, escreva para a Free Software Foundation, Inc.,
 * no endere�o 59 Temple Street, Suite 330, Boston, MA 02111-1307 USA. 
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * Universo Online S/A - A/C: UOL Messenger 5o. Andar
 * Avenida Brigadeiro Faria Lima, 1.384 - Jardim Paulistano
 * S�o Paulo SP - CEP 01452-002 - BRASIL  */

#include "stdafx.h"
#include "FileUtils.h"

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <io.h>
#include <stdio.h>


BOOL CFileUtils::CreateDirectory(const CString& strDirPath)
{
	int nFind;
	CString strDir;

	BOOL bPathExists = TRUE;

	nFind = strDirPath.Find('\\');
	while (-1 != nFind)
	{
		strDir = strDirPath.Left(nFind);

		bPathExists = ::PathFileExists(strDir);
		if (!bPathExists)
		{
			bPathExists = ::CreateDirectory(strDir, NULL);
		}
		nFind = strDirPath.Find('\\', nFind+1);
	}

	bPathExists = ::PathFileExists(strDirPath);
	if (!bPathExists)
	{
		bPathExists = ::CreateDirectory(strDirPath, NULL);
	}

	return bPathExists;
}


void CFileUtils::DeleteDirectoryFiles(const CString& strDir, const CString& strFilter)
{
	CAtlList<CString> listFiles;
	GetDirectoryFiles(strDir, strFilter, TRUE, listFiles);

	BOOL bOK = FALSE;

	for (POSITION pos = listFiles.GetHeadPosition(); pos; )
	{
		bOK = DeleteFile(listFiles.GetNext(pos));
		ATLASSERT(bOK);
	}
}


void CFileUtils::GetDirectoryFiles(const CString& strDir, const CString& strFilter, BOOL bAbsoultePath, CAtlList<CString>& listFiles)
{
	CString strBaseDir = strDir;

	if (strBaseDir.Right(1) != '\\')
	{
		strBaseDir += '\\';
	}

	// Build find expression
	CString strFindFilter = strBaseDir + strFilter;

	// Find matching files...
	WIN32_FIND_DATA findFileData = {0};
	HANDLE hFind;

	hFind = ::FindFirstFile(strFindFilter, &findFileData);
	if (INVALID_HANDLE_VALUE == hFind)
	{
		// No matching files
		return;
	}

	CString strFileName;

	do
	{
		if ((0 != CString(".").Compare(findFileData.cFileName)) &&
			(0 != CString("..").Compare(findFileData.cFileName)))
		{
			if (!bAbsoultePath)
			{
				strFileName = findFileData.cFileName;
			}
			else
			{
				strFileName = strBaseDir + findFileData.cFileName;
			}

			listFiles.AddTail(strFileName);
		}
	}
	while (::FindNextFile(hFind, &findFileData));

	::FindClose(hFind);
}


void CFileUtils::DeleteFiles(CAtlList<CString>& listFiles)
{
	BOOL bOK;
	for (POSITION pos = listFiles.GetHeadPosition(); pos; )
	{
		bOK = DeleteFile(listFiles.GetNext(pos));
		ATLASSERT(bOK);
	}
}


BOOL CFileUtils::LoadFile(const CString& strFileName, unsigned char*& pFileData, long& iFileDataLength)
{
	BOOL bLoadedOk = FALSE;
	
	struct __stat64 fileStats;
	int fd = 0;
	int result = 0;
	int bytesRead = 0;
	
	// Initialize first.
	//
	pFileData = NULL;
	iFileDataLength = 0;
	
	if ((fd = _open(strFileName, _O_RDONLY | _O_BINARY)) !=  -1)
	{
		if ((result = _fstat64(fd, &fileStats)) == 0)
		{
			iFileDataLength = fileStats.st_size;
			
			pFileData = (unsigned char*)malloc(iFileDataLength + 1);
			memset(pFileData, 0, iFileDataLength + 1);
			
			bytesRead = _read(fd, pFileData, iFileDataLength);
			
			if (bytesRead == iFileDataLength)
			{
				bLoadedOk = TRUE;
			}
			else
			{
				free(pFileData);
				pFileData = NULL;
				
				iFileDataLength = 0;
			}
		}
		
		_close(fd);
	}
	
	return bLoadedOk;
}


BOOL CFileUtils::StoreOnFile(const CString& strFileName, BOOL bTruncate, unsigned char*& pFileData, long& iFileDataLength)
{
	BOOL bStoredOk = FALSE;
	
	int fd = 0;
	int result = 0;
	int bytesWritten = 0;
	int openFlags = _O_RDWR | _O_CREAT | _O_BINARY;
	
	if (bTruncate == TRUE)
	{
		openFlags |= _O_TRUNC;
	}
	
	if ((fd = _open(strFileName, openFlags, _S_IWRITE )) !=  -1)
	{
		bytesWritten = _write(fd, pFileData, iFileDataLength);
		
		if (bytesWritten == iFileDataLength)
		{
			bStoredOk = TRUE;
		}
		
		_close(fd);
	}
	
	return bStoredOk;
}

