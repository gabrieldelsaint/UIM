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
 
#include "StdAfx.h"
#include ".\requestSongInfo.h"
#include "util.h"

CRequestSongInfo::CRequestSongInfo(const CString& url,
								   const CString& param,
								   const CString& songRegEx,
								   const CString& artistRegEx,
								   const CString& artistJpgEx,
								   const CString& cdRegEx,
								   const CString& nextSongRegEx
								   ):
	CRequest(url),
	m_strParam(param),
	m_strSongNameRegEx(songRegEx),
	m_strArtistNameRegEx(artistRegEx),
	m_strJpgRegEx(artistJpgEx),
	m_strNextSongRegEx(nextSongRegEx),
	m_strCdRegEx(cdRegEx),
	m_strSongName ("")
{
	m_strUrl.Format(url,param);
}

CRequestSongInfo::~CRequestSongInfo(void)
{
}

BOOL CRequestSongInfo::Process()
{
	//static bool ok = true;
	//ok = !ok;
	//if (ok)
	//{
	//	return CRadioUOLError::HTTP_READ;
	//}

	m_strSongName = GetField(m_strBody, m_strSongNameRegEx);
	m_strSongName.Trim();

	m_strArtistName = GetField(m_strBody, m_strArtistNameRegEx);
	m_strArtistName.Trim();

	m_strJpg = GetField(m_strBody, m_strJpgRegEx);
	m_strJpg.Trim();

	m_strNextSong = GetField(m_strBody, m_strNextSongRegEx);
	m_strNextSong.Trim();

	m_strCd = GetField(m_strBody, m_strCdRegEx);
	m_strCd.Trim();


	ATLTRACE("%s %s %s\n",__FUNCTION__, m_strSongName, m_strArtistName);
	return 0;

//	ATLASSERT(m_strSongName.IsEmpty()==FALSE);
}
