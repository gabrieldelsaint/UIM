/* UOL Fone
 * Copyright (c) 2006 Universo Online S/A
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
 * Universo Online S/A - A/C: UOL Fone 5o. Andar
 * Avenida Brigadeiro Faria Lima, 1.384 - Jardim Paulistano
 * S�o Paulo SP - CEP 01452-002 - BRASIL  */


#pragma once
#include "IUOLFoneClientPhoneLine.h"
#include "IUOLFoneClientPhoneCall.h"
#include "IUOLFoneClientMessageEvent.h"
#include "IUOLFoneClientExtraResponseData.h"
#include "IUOLFoneClientOsipDebugInfo.h"


[
	export
]
enum EnumPhoneCallStreamError
{
	UFC_PHONE_CALL_STREAM_AUDIO_RECEIVE_TIMEOUT,
	UFC_PHONE_CALL_STREAM_VIDEO_RECEIVE_TIMEOUT
};


// IUOLFoneClientCallback
[
	object,
	uuid("6C345696-8407-4d24-BBD0-53CEED2EF8D0"),
	dual,
	helpstring("IUOLFoneClientCallback Interface"),
	pointer_default(unique)
]
__interface IUOLFoneClientCallback : IDispatch
{
	[id(1)] HRESULT PhoneLineStateChanged([in] IUOLFoneClientPhoneLine* pPhoneLine, [in] EnumPhoneLineState phoneLineState, [in] IUOLFoneClientExtraResponseData2* pExtraResponseData);
	[id(2)] HRESULT PhoneCallStateChanged([in] IUOLFoneClientPhoneCall* pPhoneCall, [in] EnumPhoneCallState phoneCallState, [in] IUOLFoneClientExtraResponseData2* pExtraResponseData);
	[id(3)] HRESULT MessageEvent([in] IUOLFoneClientMessageEvent* pMessageEvent, [in] IUOLFoneClientExtraResponseData2* pExtraResponseData);
	[id(4)] HRESULT PhoneCallStreamError([in] IUOLFoneClientPhoneCall* pPhoneCall, [in] EnumPhoneCallStreamError phoneCallStreamError);
	[id(5)] HRESULT PhoneLineConnectionTimeout();
	//[id(6)] HRESULT VideoFrameReceived([in] IUOLFoneClientPhoneCall* pPhoneCall, [in] IUOLFoneClientVideoFrame* pRemoteFrame, [in] IUOLFoneClientVideoFrame* pLocalFrame);
};


// IUOLFoneClientCallback2
[
	object,
	uuid("135D74CC-E412-48a5-B8D4-C91828167094"),
	dual,
	helpstring("IUOLFoneClientCallback2 Interface"),
	pointer_default(unique)
]
__interface IUOLFoneClientCallback2 : IUOLFoneClientCallback
{
	[id(7)] HRESULT OsipDebugEvent([in] IUOLFoneClientOsipDebugInfo* pOsipDebugInfo);
};

