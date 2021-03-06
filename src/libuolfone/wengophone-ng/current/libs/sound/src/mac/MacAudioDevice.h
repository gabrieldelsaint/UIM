/*
 * WengoPhone, a voice over Internet phone
 * Copyright (C) 2004-2006  Wengo
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef OWMACAUDIODEVICE_H
#define OWMACAUDIODEVICE_H

#include <sound/AudioDevice.h>

#include <CoreAudio/CoreAudio.h>

/**
 * MacOS X implementation of AudioDevice.
 *
 * _data[0]: AudioDeviceID => audio device id
 * _data[1]: UInt32 => data source id
 * _data[2]: Boolean => is input?
 *
 * @author Philippe Bernery
 */
class MacAudioDevice : public AudioDevice {
public:

	/**
	 * @see AudioDevice::AudioDevice
	 */
	MacAudioDevice(const StringList & data);

	MacAudioDevice(AudioDeviceID audioDeviceID, UInt32 dataSourceID, bool isInput);

	MacAudioDevice(AudioDeviceID audioDeviceID, bool isInput);

	~MacAudioDevice();

	std::string getName() const;

	StringList getData() const;
};

#endif	//OWMACAUDIODEVICE_H
