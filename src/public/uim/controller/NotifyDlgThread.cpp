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

#include "NotifyDlgThread.h"


CNotifyDlgThread::CNotifyDlgThread(IShutdownFlag& shutdownFlag) : 
	m_shutdownFlag(shutdownFlag), 
	m_dlg(shutdownFlag), 
	m_thread(this)
{
	m_dlg.SetTime(200);
}


CNotifyDlgThread::~CNotifyDlgThread()
{
}


BOOL CNotifyDlgThread::Init()
{
	static_cast<CUIMApplication*>(CUIMApplication::GetApplication())->
			GetLogger()->LogStartMethod(__FUNCTION__);
	
	BOOL bRet = m_thread.Start();
	
	static_cast<CUIMApplication*>(CUIMApplication::GetApplication())->
			GetLogger()->LogDebug(__FUNCTION__, "bRet = [%d].", bRet);
	
	static_cast<CUIMApplication*>(CUIMApplication::GetApplication())->
			GetLogger()->LogEndMethod(__FUNCTION__);
	
	return bRet;
}


BOOL CNotifyDlgThread::Shutdown()
{
	static_cast<CUIMApplication*>(CUIMApplication::GetApplication())->
			GetLogger()->LogStartMethod(__FUNCTION__);
	
	m_thread.Wait();
	
	static_cast<CUIMApplication*>(CUIMApplication::GetApplication())->
			GetLogger()->LogEndMethod(__FUNCTION__);

	return TRUE;
}


void CNotifyDlgThread::SetMessage(const CString& strMessage)
{
	m_dlg.SetText(strMessage);
}


void CNotifyDlgThread::SetURL(const CString& strURL)
{
	m_dlg.SetTextLink(strURL);
}

void CNotifyDlgThread::SetCommand(IUOLMessengerCommandPtr pCommand)
{
	m_dlg.SetCommand(pCommand);
}

void CNotifyDlgThread::Run()
{
	static_cast<CUIMApplication*>(CUIMApplication::GetApplication())->
			GetLogger()->LogStartMethod(__FUNCTION__);
	
	CThread::SetThreadName("NotifyDlgThread");	

	m_dlg.DoModal();

	delete this;	
	
	static_cast<CUIMApplication*>(CUIMApplication::GetApplication())->
			GetLogger()->LogEndMethod(__FUNCTION__);
}