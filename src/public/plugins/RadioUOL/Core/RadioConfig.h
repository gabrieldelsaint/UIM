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
 
#pragma once


#include "xmlNodeWrapper.h"


class CRadioConfig
{
public:
	BOOL LoadConfig();
	
	
	
	void Trace();
	//Site
	CString	GetSiteSearchURL()		const { return m_strSiteSearchURL; }
	CString	GetSiteChannelURL()		const { return m_strSiteChannelURL; }
	CString	GetSiteSearchRegEx()	const { return m_strSiteSearchRegEx; }
	CString	GetSiteChannelRegEx()	const { return m_strSiteChannelRegEx; }


	//XMLConfig
	CString GetXMLConfigURL()		const { return m_strXMLConfigURL;}


	CString GetTicketURL()			const { return m_strTicketURL;   } 
	CString GetTicketRegex()		const { return m_strTicketRegex; } 
	CString GetWMPURL()				const { return m_strWMPURL;		 }
	CString GetWMPURLRegEx()		const { return m_strWMPURLRegex; }
	CString GetChannelsURL()		const { return m_strChannelURL;  }  
	CString GetSongInfoURL()		const { return m_strSongInfoURL; }
	CString GetFerrugemURL()		const { return m_strFerrugemURL;  }  
	CString GetFerrugemURLRegEx()	const { return m_strFerrugemURLRegEx; }
	CString GetSongInfoSongRegEx()	const { return m_strSongInfoSongRegExURL; }
	CString GetSongInfoArtistRegEx()const { return m_strSongInfoArtistRegExURL; }
	CString GetSongInfoJpegRegEx()	const { return m_strSongInfoJpegRegExURL; }
	CString GetSongInfoCdRegEx()	const { return m_strSongInfoCdRegExURL; }
	CString GetSongInfoNextSongRegEx()	const { return m_strSongInfoNextSongRegExURL; }


protected:
	int LoadConfigFile(const CString& filePath);
	//BOOL UpdateConfigFile(	const CString& filePath, 
	//						const CString& fromUrl,
	//						BOOL bForce=FALSE);

	CString GetConfigFilePath() const;
	BOOL HasNewConfig(const CString & filepath );

	CString m_strSiteSearchURL;
	CString m_strSiteChannelURL;
	CString m_strSiteSearchRegEx;
	CString m_strSiteChannelRegEx;

	CString m_strXMLConfigURL;

	CString m_strTicketURL;
	CString m_strTicketRegex;
	CString m_strWMPURL;
	CString m_strWMPURLRegex;
	CString m_strChannelURL;
	
	CString m_strFerrugemURL;
	CString m_strFerrugemURLRegEx;

    CString m_strSongInfoCdRegExURL;
	CString m_strSongInfoNextSongRegExURL;
	CString m_strSongInfoURL;
	CString m_strSongInfoSongRegExURL;
	CString m_strSongInfoArtistRegExURL;
	CString m_strSongInfoJpegRegExURL;
};
