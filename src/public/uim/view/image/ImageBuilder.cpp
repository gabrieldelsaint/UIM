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
#include "ImageBuilder.h"

#include "jpegImage.h"
#include "pngImage.h"

#include "../../controller/uimapplication.h"

namespace UOLMessengerImage
{

CImagePtr CImageBuilder::CreateImage(BYTE* pBuffer, int nLen)
{
	CJpegImagePtr pJpegImage = new CJpegImage();

	if (pJpegImage->Load(pBuffer, nLen))
	{
		return pJpegImage;
	}

	pJpegImage.reset();

	if (CPngImage::IsValidImage(pBuffer, nLen))
	{
		return new CPngImage(pBuffer, nLen);
	}
	
	return CImagePtr();
}

ATL::CImage* CImageBuilder::LoadImage2(const CString& strFilePath, BOOL bThemeRelative)
{
	CString strFullFilePath;

	if (bThemeRelative)
	{
		IUOLMessengerUIManager3Ptr pUIManager3 = ap_dynamic_cast<IUOLMessengerUIManager3Ptr>(CUIMApplication::GetApplication()->GetUIManager());

		if (pUIManager3)
		{
			IUOLMessengerThemePropertiesPtr pThemeProperties = pUIManager3->GetCurrentThemeProperties();

			if (pThemeProperties)
			{
				strFullFilePath = pThemeProperties->GetDirPath() + _T("\\") + strFilePath;
			}
		}

		if (strFullFilePath.IsEmpty())
		{
			strFullFilePath = strFilePath;
		}
	}
	else
	{
		strFullFilePath = strFilePath;
	}

	ATL::CImage *ptrReturn = new ATL::CImage();
	ptrReturn->Load(strFullFilePath);

	return ptrReturn;
}


CImagePtr CImageBuilder::LoadImage(const CString& strFilePath, BOOL bThemeRelative)
{
	CImagePtr pImage;

	CAtlFile file;
	HRESULT hr;

	CString strFullFilePath;

	if (bThemeRelative)
	{
		IUOLMessengerUIManager3Ptr pUIManager3 = ap_dynamic_cast<IUOLMessengerUIManager3Ptr>(CUIMApplication::GetApplication()->GetUIManager());

		if (pUIManager3)
		{
			IUOLMessengerThemePropertiesPtr pThemeProperties = pUIManager3->GetCurrentThemeProperties();

			if (pThemeProperties)
			{
				strFullFilePath = pThemeProperties->GetDirPath() + _T("\\") + strFilePath;
			}
		}

		if (strFullFilePath.IsEmpty())
		{
			strFullFilePath = strFilePath;
		}
	}
	else
	{
		strFullFilePath = strFilePath;
	}

	hr = file.Create(strFullFilePath, GENERIC_READ, FILE_SHARE_READ, OPEN_EXISTING);

	if (SUCCEEDED(hr))
	{
		LPBYTE pBuffer = NULL;
		ULONGLONG nBufferLength;

		hr = file.GetSize(nBufferLength);

		if (SUCCEEDED(hr))
		{
			pBuffer = new BYTE[nBufferLength];

			if (pBuffer != NULL)
			{
				DWORD dwBytesRead;
				hr = file.Read(pBuffer, nBufferLength, dwBytesRead);

				if ((SUCCEEDED(hr)) && (dwBytesRead == nBufferLength))
				{
					pImage = CreateImage(pBuffer, nBufferLength);
				}

				delete pBuffer;
			}
		}

		file.Close();
	}

	if (!pImage)
	{
		CImagePtr pDIBImage = new CImage();
		if (pDIBImage->LoadDIB(strFullFilePath))
		{
			pImage = pDIBImage;
		}		
	}

	return pImage;
}


CImagePtr CImageBuilder::LoadImageFromResource(HMODULE hModule, DWORD dwResourceId)
{
	CImagePtr pDIBImage = new CImage();

	if (pDIBImage->LoadDIB(hModule, MAKEINTRESOURCE(dwResourceId)))
	{
		return pDIBImage;
	}

	return CImagePtr();
}


}
