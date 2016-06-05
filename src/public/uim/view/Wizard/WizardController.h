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

#include "UOLPropPageImpl.h"

#include <interfaces/IUOLMessengerProfileManager.h>

#include "../../Controller/UIMApplication.h"
#include "../../Controller/UIManager.h"


#define		ID_PROFILE_WIZARD_PAGE				1
#define		ID_MSN_PROTOCOL_WIZARD_PAGE			2
#define		ID_UOL_PROTOCOL_WIZARD_PAGE			3
#define		ID_ICQ_PROTOCOL_WIZARD_PAGE			4
#define		ID_YAHOO_PROTOCOL_WIZARD_PAGE		5
#define		ID_JABBER_PROTOCOL_WIZARD_PAGE		6
#define		ID_PREFERENCES_WIZARD_PAGE			7


class CWizardController
{
public:
	
	virtual ~CWizardController();
	
	static CWizardController* GetInstance();
	
	void SetProtocolsToConfig(BOOL bConfigMSN, BOOL bConfigUOL, BOOL bConfigICQ, 
			BOOL bConfigYahoo, BOOL bConfigJabber);
	
	BOOL HaveProtocolsToConfig();
	
	/*
	 * bIsUserUOLValid metters only when the page is MSN, so we can decide 
	 * whether the next to be called is the UOL, or ICQ one.
	 */
	CUOLPropPagePtr GetNextValidPage(int iWizardId);
	
protected:
	
	CWizardController();
	
	int GetNextWizardPageID(int iCurrentWizardID);
	
private:
	
	BOOL		m_bConfigMSN;
	BOOL		m_bConfigUOL;
	BOOL		m_bConfigICQ;
	BOOL		m_bConfigYahoo;
	BOOL		m_bConfigJabber;
	
	UOLLib::ISettings*	m_pWizardSettings;
	
	AccountsListPtr m_pAccountsList;
};

