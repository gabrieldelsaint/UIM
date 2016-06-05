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
#include "NotifyPopUpManager.h"

#include "UIMApplication.h"
#include "UIManager.h"

#include "../resource.h"
#include "../view/NotifyPopUp/NotifyPopUpBuilder.h"
#include "../view/NotifyPopUp/NotifyPopUpHandler.h"


CNotifyPopUpManager::CNotifyPopUpManager():   
m_nIDTimer(1),
m_nTimerInterval(300),
m_dwTimeout(5000),
m_bIsDirty(TRUE),
m_bFirstTimer(TRUE),
m_bStopTimer(FALSE),
m_dwTickCount(0)
{
	ATLTRACE(_T("%s\n"), __FUNCTION__);
}


CNotifyPopUpManager::~CNotifyPopUpManager()
{
	ATLTRACE(_T("%s\n"), __FUNCTION__);
}


CNotifyPopUpPtr CNotifyPopUpManager::CreateNotifyPopUp()
{
	static_cast<CUIMApplication*>(CUIMApplication::GetApplication())->
			GetLogger()->LogStartMethod(__FUNCTION__);
	
	CUIManager* pUIManager = dynamic_cast<CUIManager*>(CUIMApplication::GetApplication()->GetUIManager().get());
	ATLASSERT(pUIManager);

	static_cast<CUIMApplication*>(CUIMApplication::GetApplication())->
			GetLogger()->LogDebug(__FUNCTION__, "pUIManager = [%x].", pUIManager);
	
	CNotifyPopUpBuilderPtr pNotifyPopUpBuilder = ap_dynamic_cast<CNotifyPopUpBuilderPtr>(const_cast<CUOLWindowManager*>(pUIManager->GetWindowManager())->GetElement("__NotifyPopUpBuilderInstance"));
	ATLASSERT(pNotifyPopUpBuilder.get());

	static_cast<CUIMApplication*>(CUIMApplication::GetApplication())->
			GetLogger()->LogDebug(__FUNCTION__, "pNotifyPopUpBuilder = [%x].", pNotifyPopUpBuilder.get());
	
	CNotifyPopUpPtr pNotifyPopUp = ap_dynamic_cast<CNotifyPopUpPtr>(pNotifyPopUpBuilder->CreateElement());
	ATLASSERT(pNotifyPopUp.get());
	
	static_cast<CUIMApplication*>(CUIMApplication::GetApplication())->
			GetLogger()->LogDebug(__FUNCTION__, "pNotifyPopUp = [%x].", pNotifyPopUp.get());
	
	static_cast<CUIMApplication*>(CUIMApplication::GetApplication())->
			GetLogger()->LogEndMethod(__FUNCTION__);

	return pNotifyPopUp;
}


void CNotifyPopUpManager::Add(CNotifyPopUpPtr pNotifyPopUp)
{
	static_cast<CUIMApplication*>(CUIMApplication::GetApplication())->
			GetLogger()->LogStartMethod(__FUNCTION__);
	
	//ATLTRACE(_T("%s\n"), __FUNCTION__);

	pNotifyPopUp->Create(m_hWnd);
	pNotifyPopUp->AddNotifyPopUpObserver(this);

	m_listPopUps.AddTail(pNotifyPopUp);

	//A LISTA DE JANELAS EST� "SUJA", A UI DEVE SER ATUALIZA EM MOMENTO OPORTUNO
	m_bIsDirty = TRUE;
	
	static_cast<CUIMApplication*>(CUIMApplication::GetApplication())->
			GetLogger()->LogEndMethod(__FUNCTION__);
}


BOOL CNotifyPopUpManager::CloseChild(CNotifyPopUp* pNotifyPopUp)
{
	BOOL bRet = FALSE;
	
	static_cast<CUIMApplication*>(CUIMApplication::GetApplication())->
			GetLogger()->LogStartMethod(__FUNCTION__);
	
	//ATLTRACE(_T("%s\n"), __FUNCTION__);

	ATLASSERT(pNotifyPopUp != NULL);

	CComCritSecLock<CComAutoCriticalSection> comCritSecLock(m_criticalSection);

	for (POSITION pos = m_listPopUps.GetHeadPosition(); pos; m_listPopUps.GetNext(pos))
	{
		CNotifyPopUpPtr pPopUp = m_listPopUps.GetAt(pos);

		if (pPopUp.get() && (pPopUp.get() == pNotifyPopUp))
		{
			if (pPopUp->IsWindow())
			{
				pPopUp->RemoveNotifyPopUpObserver(this);
				pPopUp->DestroyWindow();
//				m_listPopUps.RemoveAt(pos);
	
				bRet = TRUE;

				break;
			}
		}
	}
	
	static_cast<CUIMApplication*>(CUIMApplication::GetApplication())->
			GetLogger()->LogDebug(__FUNCTION__, "bRet = [%d].", bRet);
	
	static_cast<CUIMApplication*>(CUIMApplication::GetApplication())->
			GetLogger()->LogEndMethod(__FUNCTION__);

	return bRet;
}


BOOL CNotifyPopUpManager::ProtectChild(CNotifyPopUpPtr pNotifyPopUp)
{
	BOOL bRet = FALSE;
	
	static_cast<CUIMApplication*>(CUIMApplication::GetApplication())->
			GetLogger()->LogStartMethod(__FUNCTION__);
	
	//ATLTRACE(_T("%s\n"), __FUNCTION__);

	CComCritSecLock<CComAutoCriticalSection> comCritSecLock(m_criticalSection);

	POSITION pos = m_listPopUps.Find(pNotifyPopUp);

	if (pos)
	{
		CNotifyPopUpPtr pPopUp = m_listPopUps.GetAt(pos);

		static_cast<CUIMApplication*>(CUIMApplication::GetApplication())->
				GetLogger()->LogDebug(__FUNCTION__, "pPopUp = [%x].", pPopUp.get());
		
		if (pPopUp)
		{
			if (pPopUp->IsWindow())
			{
				pPopUp->SetProtected(TRUE);
			}
		}	

		bRet = TRUE;
	}
	
	static_cast<CUIMApplication*>(CUIMApplication::GetApplication())->
			GetLogger()->LogDebug(__FUNCTION__, "bRet = [%d].", bRet);
	
	static_cast<CUIMApplication*>(CUIMApplication::GetApplication())->
			GetLogger()->LogEndMethod(__FUNCTION__);

	return bRet;
}


void CNotifyPopUpManager::OnDestroy()
{
	static_cast<CUIMApplication*>(CUIMApplication::GetApplication())->
			GetLogger()->LogStartMethod(__FUNCTION__);
	
	//ATLTRACE(_T("%s\n"), __FUNCTION__);

	CComCritSecLock<CComAutoCriticalSection> comCritSecLock(m_criticalSection);

	KillTimer(m_nIDTimer);

	for (POSITION pos = m_listPopUps.GetHeadPosition(); pos; )
	{
		CNotifyPopUpPtr pNotifyPopUp = m_listPopUps.GetNext(pos);

		if(pNotifyPopUp.get())
		{
			if(pNotifyPopUp->IsWindow())
			{
				pNotifyPopUp->DestroyWindow();
			}

			pNotifyPopUp->m_hWnd = NULL;
		}
	}

	m_listPopUps.RemoveAll();
	
	static_cast<CUIMApplication*>(CUIMApplication::GetApplication())->
			GetLogger()->LogEndMethod(__FUNCTION__);
}


LRESULT CNotifyPopUpManager::OnCreate(LPCREATESTRUCT /*lpcs*/)
{
	static_cast<CUIMApplication*>(CUIMApplication::GetApplication())->
			GetLogger()->LogStartMethod(__FUNCTION__);
	
	//ATLTRACE(_T("%s\n"), __FUNCTION__);

	SetTimer(m_nIDTimer, 2000);
	
	static_cast<CUIMApplication*>(CUIMApplication::GetApplication())->
			GetLogger()->LogEndMethod(__FUNCTION__);
	
	return 1;
}


void CNotifyPopUpManager::OnTimer(UINT , TIMERPROC )
{
	static_cast<CUIMApplication*>(CUIMApplication::GetApplication())->
			GetLogger()->LogStartMethod(__FUNCTION__);
	
	//ATLTRACE(_T("%s\n"), __FUNCTION__);

	POINT pt = {0};
	RECT rect = {0};
	HWND wndHover=NULL;

	m_bStopTimer = false;

	GetCursorPos(&pt);

	wndHover = WindowFromPoint(pt);

	{
		CComCritSecLock<CComAutoCriticalSection> comCritSecLock(m_criticalSection);

		for (POSITION pos = m_listPopUps.GetHeadPosition(); pos; )
		{
			CNotifyPopUpPtr pNotifyPopUp = m_listPopUps.GetNext(pos);

			if(pNotifyPopUp.get())
			{
				if(pNotifyPopUp->IsWindow())
				{
					pNotifyPopUp->GetWindowRect(&rect);

					if (::PtInRect(&rect, pt) 
						&& (wndHover == pNotifyPopUp->m_hWnd || pNotifyPopUp->IsChild(wndHover)))
					{
						m_bStopTimer = true;
						break;
					}
				}
			}
		}

		DeleteOldChildren();
		ShowChildren();
	}

	if(!m_bStopTimer)
	{
		m_dwTickCount += m_nTimerInterval; 
	}

	if(m_bFirstTimer)
	{
		SetTimer(m_nIDTimer, m_nTimerInterval);
		m_bFirstTimer = FALSE;
	}
	
	static_cast<CUIMApplication*>(CUIMApplication::GetApplication())->
			GetLogger()->LogEndMethod(__FUNCTION__);
}


void CNotifyPopUpManager::ShowChildren()
{
	static_cast<CUIMApplication*>(CUIMApplication::GetApplication())->
			GetLogger()->LogStartMethod(__FUNCTION__);
	
	//ATLTRACE(_T("%s\n"), __FUNCTION__);

	CRect rCurrent;
	CRect rWorkArea;
	CRect rNextPos;

	int totalHeight=0;

	if(!m_bIsDirty)
	{
		return;
	}

	//OBTEM O TAMANHO DO DESKTOP
	if(!SystemParametersInfo(SPI_GETWORKAREA, 0,(LPRECT)rWorkArea , 0))
	{
		CWindow	pDesk = ::GetDesktopWindow();
		pDesk.GetWindowRect(rWorkArea);
	}

	rNextPos = rWorkArea;

	for (POSITION pos = m_listPopUps.GetHeadPosition(); pos; )
	{
		CNotifyPopUpPtr pNotifyPopUp = m_listPopUps.GetNext(pos);

		if(pNotifyPopUp.get() && pNotifyPopUp->IsWindow())
		{	
			//OBTEM AS DIMENSOES DA JANELA A SER POSICIONADA
			pNotifyPopUp->GetWindowRect(rCurrent); 
			//O TOPO DA NOVA POSIC�O SER� A PARTE MAIS BAIXA DA POSICAO ANTERIOR MENOS A ALTURA DESTA JANELA (MAIS 1 PIXEL PARA N�O FICAR COLADO)
			rNextPos.top = rNextPos.bottom - (rCurrent.Height()+1);
			//A ESQUERDA DA NOVA POSIC�O SER� A POSI~��O MAIS A DIREITA DA POSI��O ANTERIOR MENOS A LARGURA DESTA JANELA(MAIS 1 PIXEL PARA N�O FICAR COLADO)
			rNextPos.left = rNextPos.right - (rCurrent.Width()+1); 
			
			//SE � A PRIMEIRA VEZ DESSA JANELA NO PROCESSAMENTO
			if(pNotifyPopUp->IsFirstTime())
			{
				//PRIMERIO VERIFICAMOS SE ATINGIMOS O LIMITE DE OCUPA��O DO DESKTOP
				if((totalHeight + rCurrent.Height()) < (rWorkArea.Height()/2)) 
				{
					//CONFIGURA A POSI��O INICIAL (EM CIMA DA POSI��O ANTERIOR E COM ALTURA ZERO)
					pNotifyPopUp->SetWindowPos(NULL, rNextPos.left, rNextPos.bottom, rCurrent.Width(), 0, SWP_NOACTIVATE | SWP_NOZORDER);

					//EXIBE A JANELA
					pNotifyPopUp->ShowWindow(SW_SHOWNOACTIVATE);

					//FAZ A ANIMA��O, ALTERANDO O TOPO DA POSI��O E A LARGURA DESTA JANELA
					for(int i=rNextPos.bottom; i >= rNextPos.top; i-=10)
					{
						pNotifyPopUp->SetWindowPos(NULL, rNextPos.left, i, rCurrent.Width(), rNextPos.bottom - i, SWP_NOACTIVATE | SWP_NOZORDER);

						//ATUALIZA TODAS AS JANELAS DA LISTA
						UpdateChildren();

						Sleep(15);
					}	

					//CONFIGURA A POSI��O FINAL (A QUAL O LA�O ANTERIOR PODE N�O TER ATINGIDO POR CAUSA DA RAZ�O DO INCREMENTO DE i)
					pNotifyPopUp->SetWindowPos(NULL, rNextPos.left, rNextPos.top, rCurrent.Width(), rCurrent.Height(), SWP_NOACTIVATE | SWP_NOZORDER);

					//ATUALIZA O TEMPO NO QUAL A JANELA FOI EXIBIDA
					pNotifyPopUp->SetShowTime(m_dwTickCount);
					pNotifyPopUp->SetFirstTime(FALSE);

					//ATUALIZA O TOTALIZADOR DE ALTURA DAS JANELAS
					totalHeight += rCurrent.Height();
				}
			}
			else
			{
				//POSICIONA A JANELA NA NOVA POSI��O
				pNotifyPopUp->SetWindowPos(NULL, rNextPos.left, rNextPos.top, rCurrent.Width(), rCurrent.Height(), SWP_NOACTIVATE | SWP_NOZORDER);

				//ATUALIZA O TOTALIZADOR DE ALTURA DAS JANELAS
				totalHeight += rCurrent.Height();
			}

			//ATUALIZA A POSI��O PARA A NOVA ITERA��O DO LA�O
			//A PARTE MAIS BAIXA DA PR�XIMA POSI��O SERA A PARTE MAIS ALTA DA POSI��O ATUAL
			rNextPos.bottom = rNextPos.top;
		}
	}

	m_bIsDirty = FALSE;
	
	static_cast<CUIMApplication*>(CUIMApplication::GetApplication())->
			GetLogger()->LogEndMethod(__FUNCTION__);
}


void CNotifyPopUpManager::UpdateChildren()
{
	static_cast<CUIMApplication*>(CUIMApplication::GetApplication())->
			GetLogger()->LogStartMethod(__FUNCTION__);
	
	//ATLTRACE(_T("%s\n"), __FUNCTION__);

	for (POSITION pos = m_listPopUps.GetHeadPosition(); pos; )
	{
		CNotifyPopUpPtr pNotifyPopUp = m_listPopUps.GetNext(pos);

		if(pNotifyPopUp.get() && pNotifyPopUp->IsWindow())
		{
			if(!pNotifyPopUp->IsFirstTime())
			{
				pNotifyPopUp->UpdateWindow();
			}
		}
	}
	
	static_cast<CUIMApplication*>(CUIMApplication::GetApplication())->
			GetLogger()->LogEndMethod(__FUNCTION__);
}


void CNotifyPopUpManager::DeleteOldChildren()
{
	static_cast<CUIMApplication*>(CUIMApplication::GetApplication())->
			GetLogger()->LogStartMethod(__FUNCTION__);
	
	//ATLTRACE(_T("%s\n"), __FUNCTION__);

	for (POSITION pos = m_listPopUps.GetHeadPosition(); pos; m_listPopUps.GetNext(pos))
	{
		CNotifyPopUpPtr pNotifyPopUp = m_listPopUps.GetAt(pos);

		if(pNotifyPopUp.get())
		{
			if(!pNotifyPopUp->IsFirstTime())
			{
				if(!pNotifyPopUp->IsProtected())
				{
					DWORD dwShowTimeout = pNotifyPopUp->GetTimeout();

					if (((SHOW_TIMEOUT_INFINITE != dwShowTimeout) && 
						 (m_dwTickCount - pNotifyPopUp->GetShowTime()) > dwShowTimeout) ||
					    (pNotifyPopUp->IsExpired()))
					{
						pNotifyPopUp->RemoveNotifyPopUpObserver(this);
						if (pNotifyPopUp->IsWindow())
						{
							pNotifyPopUp->DestroyWindow();
						}
						pNotifyPopUp->m_hWnd = NULL;
						m_listPopUps.RemoveAt(pos);
						m_bIsDirty = TRUE;

						return;
					}
				}
			}
		}
	}
	
	static_cast<CUIMApplication*>(CUIMApplication::GetApplication())->
			GetLogger()->LogEndMethod(__FUNCTION__);
}


LRESULT CNotifyPopUpManager::OnChildClicked(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	//ATLTRACE(_T("%s\n"), __FUNCTION__);

//	ProtectChild((HWND) wParam);
	
	return 0;
}


LRESULT CNotifyPopUpManager::OnPopUpMouseEnter(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	static_cast<CUIMApplication*>(CUIMApplication::GetApplication())->
			GetLogger()->LogStartMethod(__FUNCTION__);
	
	//ATLTRACE(_T("%s\n"), __FUNCTION__);

	m_bStopTimer = TRUE;
	
	static_cast<CUIMApplication*>(CUIMApplication::GetApplication())->
			GetLogger()->LogEndMethod(__FUNCTION__);
	
	return 0;
}


LRESULT CNotifyPopUpManager::OnPopUpMouseLeave(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	static_cast<CUIMApplication*>(CUIMApplication::GetApplication())->
			GetLogger()->LogStartMethod(__FUNCTION__);
	
	//ATLTRACE(_T("%s\n"), __FUNCTION__);

	m_bStopTimer = FALSE;
	
	static_cast<CUIMApplication*>(CUIMApplication::GetApplication())->
			GetLogger()->LogEndMethod(__FUNCTION__);
	
	return 0;
}


BOOL CNotifyPopUpManager::Init()
{
	static_cast<CUIMApplication*>(CUIMApplication::GetApplication())->
			GetLogger()->LogStartMethod(__FUNCTION__);
	
	//ATLTRACE(_T("%s\n"), __FUNCTION__);
	
	DWORD dwStyle = WS_POPUP;
	HWND hWnd =	__super::Create(NULL, NULL, "NotifyPopUpWndController", dwStyle);
	
	static_cast<CUIMApplication*>(CUIMApplication::GetApplication())->
			GetLogger()->LogDebug(__FUNCTION__, "hWnd = [%x]", hWnd);
	
	static_cast<CUIMApplication*>(CUIMApplication::GetApplication())->
			GetLogger()->LogEndMethod(__FUNCTION__);

	return (hWnd != NULL);
}


void CNotifyPopUpManager::Finalize()
{
	static_cast<CUIMApplication*>(CUIMApplication::GetApplication())->
			GetLogger()->LogStartMethod(__FUNCTION__);
	
	//ATLTRACE(_T("%s\n"), __FUNCTION__);

	CComCritSecLock<CComAutoCriticalSection> comCritSecLock(m_criticalSection);

	static_cast<CUIMApplication*>(CUIMApplication::GetApplication())->
			GetLogger()->LogDebug(__FUNCTION__, 
			"IsWindow() = [%d]", IsWindow());
	
	if(IsWindow())
	{
		DestroyWindow();
	}

	m_hWnd = NULL;

	for (POSITION pos = m_listPopUps.GetHeadPosition(); pos;)
	{
		CNotifyPopUpPtr pNotifyPopUp = m_listPopUps.GetNext(pos);

		if(pNotifyPopUp.get())
		{
			if(pNotifyPopUp->IsWindow())
			{
				pNotifyPopUp->DestroyWindow();
			}

			pNotifyPopUp->m_hWnd = NULL;
		}
	}

	m_listPopUps.RemoveAll();
	
	static_cast<CUIMApplication*>(CUIMApplication::GetApplication())->
			GetLogger()->LogEndMethod(__FUNCTION__);
}


void CNotifyPopUpManager::ShowAlertWindow(const CString& strTitle, 
										  CAtlList<CString>& listTextLines, IUOLMessengerImagePtr pMessageIcon,  
										  IUOLMessengerNotifyPopUpHyperLinkHandlerPtr pTextLinkHandler,
										  IUOLMessengerNotifyPopUpHyperLinkHandlerPtr pOptionsLinkHandler,
										  IUOLMessengerImagePtr pWindowIcon,
										  DWORD dwShowTimeout)
{
	static_cast<CUIMApplication*>(CUIMApplication::GetApplication())->
			GetLogger()->LogStartMethod(__FUNCTION__);
	
	//ATLTRACE(_T("%s\n"), __FUNCTION__);

	CNotifyPopUpHandlerPtr pNotifyPopUpHandler = new CNotifyPopUpHandler();

	if (pNotifyPopUpHandler != NULL)
	{
		pNotifyPopUpHandler->SetTitle(strTitle);
		pNotifyPopUpHandler->SetTextLines(listTextLines);
		pNotifyPopUpHandler->SetMessageIcon(pMessageIcon);
		pNotifyPopUpHandler->SetOptionsHyperLinkHandler(pOptionsLinkHandler);
		pNotifyPopUpHandler->SetTextHyperLinkHandler(pTextLinkHandler);
		
		if (!pWindowIcon)
		{
			IUOLMessengerNotifyPopUpResourcePtr pNotifyPopUpResource = CUIMApplication::GetApplication()->GetUIManager()->GetNotifyPopUpResource();
			pNotifyPopUpHandler->SetWindowIcon(pNotifyPopUpResource->GetImage(IUOLMessengerNotifyPopUpResource::NPR_DEFAULT));
		}
		else
		{
			pNotifyPopUpHandler->SetWindowIcon(pWindowIcon);
		}
		
		ShowAlertWindow(pNotifyPopUpHandler, dwShowTimeout);
	}
	else
	{
		static_cast<CUIMApplication*>(CUIMApplication::GetApplication())->
				GetLogger()->LogError(__FUNCTION__, "pNotifyPopUpHandler == NULL.");
	}
	
	static_cast<CUIMApplication*>(CUIMApplication::GetApplication())->
			GetLogger()->LogEndMethod(__FUNCTION__);
}


void CNotifyPopUpManager::ShowAlertWindow(IUOLMessengerNotifyPopUpHandlerPtr pNotifyPopUpHandler, DWORD dwShowTimeout)
{
	static_cast<CUIMApplication*>(CUIMApplication::GetApplication())->
			GetLogger()->LogStartMethod(__FUNCTION__);
	
	if (pNotifyPopUpHandler)
	{
		CNotifyPopUpPtr pNotifyPopUp = CreateNotifyPopUp();

		pNotifyPopUp->SetNotifyPopUpHandler(pNotifyPopUpHandler);

		if (dwShowTimeout == SHOW_TIMEOUT_DEFAULT)
		{
			pNotifyPopUp->SetTimeout(m_dwTimeout);
		}
		else
		{
			pNotifyPopUp->SetTimeout(dwShowTimeout);
		}

		{
			CComCritSecLock<CComAutoCriticalSection> comCritSecLock(m_criticalSection);

			Add(pNotifyPopUp);
		}
	}
	
	static_cast<CUIMApplication*>(CUIMApplication::GetApplication())->
			GetLogger()->LogEndMethod(__FUNCTION__);
}


void CNotifyPopUpManager::OnClose(CNotifyPopUp* pNotifyPopUp)
{
	static_cast<CUIMApplication*>(CUIMApplication::GetApplication())->
			GetLogger()->LogStartMethod(__FUNCTION__);
	
	//ATLTRACE(_T("%s\n"), __FUNCTION__);

	CloseChild(pNotifyPopUp);

	m_bIsDirty = TRUE;
	
	static_cast<CUIMApplication*>(CUIMApplication::GetApplication())->
			GetLogger()->LogEndMethod(__FUNCTION__);
}


void CNotifyPopUpManager::OnOptions(CNotifyPopUp* pNotifyPopUp)
{
	static_cast<CUIMApplication*>(CUIMApplication::GetApplication())->
			GetLogger()->LogStartMethod(__FUNCTION__);
	
	//ATLTRACE(_T("%s\n"), __FUNCTION__);

	// Hide pop-up window
	pNotifyPopUp->SetExpired(TRUE);
	
	static_cast<CUIMApplication*>(CUIMApplication::GetApplication())->
			GetLogger()->LogEndMethod(__FUNCTION__);
}


void CNotifyPopUpManager::OnClick(CNotifyPopUp* pNotifyPopUp)
{
	static_cast<CUIMApplication*>(CUIMApplication::GetApplication())->
			GetLogger()->LogStartMethod(__FUNCTION__);
	
	//ATLTRACE(_T("%s\n"), __FUNCTION__);

	// Hide pop-up window
	pNotifyPopUp->SetExpired(TRUE);
	
	static_cast<CUIMApplication*>(CUIMApplication::GetApplication())->
			GetLogger()->LogEndMethod(__FUNCTION__);
}