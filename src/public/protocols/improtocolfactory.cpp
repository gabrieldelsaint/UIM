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

#include "improtocolfactory.h"
#include "purpleprotocol.h"
#include "purpleservice.h"
#include "improtocol.h"
#include "LibPurpleToUIMSerializerFactory.h"

#ifdef WIN32
#	include <windows.h>
#	include <tchar.h>
#else
#endif

#include <iostream>

using namespace std;


CIMProtocolFactory::CIMProtocolFactory(void)
{
}


CIMProtocolFactory::~CIMProtocolFactory(void)
{
}


CIMProtocolFactory* CIMProtocolFactory::GetInstance()
{
    static CIMProtocolFactory factoryInstance;

    return &factoryInstance;
}


bool CIMProtocolFactory::Init(char** ppszPluginsSearchPath, 
                              int nPluginsSearchPathCount, 
                              IIMProtocolStack** ppProtocolStack,
                              void** ppProtocolCallbackStack, 
							  char* pszCurrentProfileFullPath, 
							  DWORD dwUIMThreadId)
{
    m_protocolList.clear();

    // Init Purple service...
    CPurpleService* pPurpleService = CPurpleService::GetInstance();

    pPurpleService->SetPluginsSearchPath(nPluginsSearchPathCount, ppszPluginsSearchPath);

    // Init the callback serializer implementation first.
	//
	if (CLibPurpleToUIMSerializerFactory::GetFactoryInstance()->Init())
	{
		if (pPurpleService->Init(pszCurrentProfileFullPath, dwUIMThreadId))
		{
			// Get Purple protocols...
			CIMProtocolList listPurpleProtocols;
			pPurpleService->GetProtocolsList(listPurpleProtocols);

			CIMProtocol* pProtocol = NULL;

			CIMProtocolList::iterator itListPurpleProtocols;		

			for (itListPurpleProtocols = listPurpleProtocols.begin(); 
				itListPurpleProtocols != listPurpleProtocols.end(); 
				++itListPurpleProtocols)
			{
				pProtocol = (*itListPurpleProtocols);			
				m_protocolList.push_back(*itListPurpleProtocols);			
			}

			*ppProtocolStack = pPurpleService;

			return true;
		}
	}

    return false;
}


void CIMProtocolFactory::Finalize()
{
    CPurpleService* pPurpleService = CPurpleService::GetInstance();
    pPurpleService->Finalize();
	
	CLibPurpleToUIMSerializerFactory::GetFactoryInstance()->Finalize();

    m_protocolList.clear();	
}

void CIMProtocolFactory::PreFinalize()
{
    CPurpleService* pPurpleService = CPurpleService::GetInstance();
    pPurpleService->PreFinalize();
}

void CIMProtocolFactory::GetProtocols(CIMProtocolList& protocolList)
{
    protocolList.clear();

    CIMProtocolList::iterator itListProtocols;

    for (itListProtocols = m_protocolList.begin(); 
        itListProtocols != m_protocolList.end(); 
        itListProtocols++)
    {
        protocolList.push_back(*itListProtocols);
    }
}

void CIMProtocolFactory::SetWizardRunnig(BOOL bRunning)
{
    CPurpleService::GetInstance()->SetWizardRunnig(bRunning);
}

BOOL CIMProtocolFactory::IsWizardRunning()
{
    return CPurpleService::GetInstance()->IsWizardRunning();
}

void CIMProtocolFactory::StopProtocolService()
{
	CPurpleService::GetInstance()->SetFinalizeInProgress(TRUE);
}

void CIMProtocolFactory::EnablePurpleDebugLog(BOOL bEnabled)
{
	CPurpleService::GetInstance()->EnablePurpleDebugLog(bEnabled);
}

void CIMProtocolFactory::SetPurpleDebugLogger(IPurpleDebugLogger* pPurpleDebugLogger)
{
	CPurpleService::GetInstance()->SetPurpleDebugLogger(pPurpleDebugLogger);
}
