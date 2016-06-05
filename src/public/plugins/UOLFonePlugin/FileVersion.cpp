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
 
// FileVersion.cpp: implementation of the CFileVersion class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FileVersion.h"



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFileVersion::CFileVersion(const CString& strFileName)
{	
	// Trabalhar apenas com o nome curto do arquivo

	TCHAR szShortPath[MAX_PATH];
	TCHAR szLongPath[MAX_PATH];
	LPTSTR szLongFile;

	if (::GetFullPathName(strFileName, MAX_PATH, szLongPath, &szLongFile))
	{
		if (::GetShortPathName(szLongPath, szShortPath, MAX_PATH))
		{
			m_strFilePath = szShortPath;		 		

			// o Nome curto n�o pode ser maior que 126

			if (m_strFilePath.GetLength() > 126)
			{
				m_strFilePath.Empty();
			}
		}
	}
}

CFileVersion::~CFileVersion()
{

}

ULONGLONG CFileVersion::GetVersion() const
{
	DWORD dwHandle;
	DWORD dwSize;
	ULONGLONG nRet = 0;

	if (0 == m_strFilePath.GetLength())
	{
		return 0L;
	}

	dwSize = ::GetFileVersionInfoSize(m_strFilePath, &dwHandle);

	if (0 == dwSize)
	{
		return 0;
	}

	LPVOID lpData = new BYTE[dwSize];	

	__try
	{	
		if (FALSE == ::GetFileVersionInfo(m_strFilePath, NULL, dwSize, lpData))
		{
			return 0;
		}

		VS_FIXEDFILEINFO*	pFileInfo;
		UINT				nSize;

		if (FALSE == ::VerQueryValue(lpData, _T("\\"), reinterpret_cast<LPVOID*>(&pFileInfo), &nSize))
		{
			return 0;
		}

		if (0 != ::IsBadReadPtr(reinterpret_cast<LPVOID*>(&pFileInfo), nSize))
		{
			return 0;
		}

		nRet = pFileInfo->dwFileVersionMS;
		nRet <<= 32;
		nRet |= pFileInfo->dwFileVersionLS;
	}
	__finally
	{
		if (lpData)
		{
			delete[] lpData;
		}
	}

	return nRet;
}

