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

#include <util/Thread.h>
#include <util/IRunnable.h>
#include <interfaces/IUOLMessengerHistoryRecord.h>
#include <interfaces/IUOLMessengerAccount.h>
#include "HistoryRecord.h"


///////////////////////////////////////////////////////////////////////////////
// CHistoryRecordVoip
///////////////////////////////////////////////////////////////////////////////
class CHistoryRecordVoip : public CHistoryRecord
{
public:
	// this constructor must be used when writing to xml
	CHistoryRecordVoip(IUOLMessengerAccountPtr pAccount,
		const CString& strEventFrom, const CString& strEventTo,
		const CString& strStatus, const CString& strType, const CString& strText);
	
	// this constructor must be used when reading from xml
	CHistoryRecordVoip(IUOLMessengerAccountPtr pAccount, const CString& strTypeFilter);

	virtual ~CHistoryRecordVoip();

	// IUOLMessengerHistoryRecord interface
	virtual BOOL CanLog() const;	
	virtual BOOL ConvertFrom(IUOLMessengerHistoryRecordPtr pHistoryRecord);
	virtual CString GetHistoryText();
	virtual CString GetRecentHistoryText();
	void GetRecentEvents(CAtlList<IUOLMessengerHistoryEventPtr>& listEvents);

	IUOLMessengerAccountPtr GetAccount();
	CString GetTypeFilter();

protected:
	CString FindAlias(const CString& strName);
	CString GetEventFromByType(IUOLMessengerHistoryEventPtr pHistoryEvent);

private:
	IUOLMessengerAccountPtr	m_pAccount;
	CComAutoCriticalSection	m_csList;
	
	CTime		m_timeHistory;
	CTime		m_StartTime;
	CString		m_strContactName;
	CString		m_strTypeFilter;
	CString		m_strHistoryText;
};
MAKEAUTOPTR(CHistoryRecordVoip);


///////////////////////////////////////////////////////////////////////////////
// CHistoryRecordVoipList Class
///////////////////////////////////////////////////////////////////////////////
class CHistoryRecordVoipList : 
	public IRunnable,
	public CHistoryRecordList
{
public:
	CHistoryRecordVoipList(CHistoryRecordVoipPtr pHistoryRecordVoip);
	virtual ~CHistoryRecordVoipList();

	virtual CString GetHistoryText(CTime eventTime);
	virtual IUOLMessengerHistoryRecordPtr GetHistoryRecord(CTime eventTime);
	virtual IUOLMessengerHistoryRecordPtr GetHistoryRecordByIndex(int nIndex);
	virtual int GetCount();
	virtual void GetHistoryEvents(CAtlList<CTime>& listHistoryEvents);
	virtual void DeleteHistory(CTime eventTime);
	virtual void DeleteAllHistory();
	virtual void RemoveAll();
	virtual CString GetProtocolId();
	virtual BOOL StartLoad();
	virtual BOOL StopLoad();
	
protected:
	void GetEventRecord(CHistoryRecordVoipPtr pHistoryRecordVoip);
	void Run();

private:
	CAtlList<CHistoryRecordVoipPtr>	m_listHistoryRecordVoip;
	CHistoryRecordVoipPtr			m_pHistoryRecordVoip;
	CComAutoCriticalSection			m_csList;

	CThread		m_thread;
	BOOL		m_bStopFlag;
};
MAKEAUTOPTR(CHistoryRecordVoipList);