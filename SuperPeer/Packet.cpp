#include "pch.h"
#include "Packet.h"
#include "Util.h"

using namespace std;

SuperPeer::CPacketHeader::CPacketHeader()
{
	SenderID = PacketConfig::InvalidID;
	DataType = PacketConfig::InvalidDataType;
	DataSize = 0;
	Flags = 0;

	SingleTargetReceiverID = PacketConfig::InvalidSingleTargetReceiverID;

	UserDataType = 0;
	UserFlags = 0;
}

void SuperPeer::CPacketHeader::SetFlag(unsigned int InFlag, bool bInActive)
{
	if (bInActive)
	{
		Flags |= InFlag;
	}
	else
	{
		Flags &= (~InFlag);
	}
}

void SuperPeer::CPacketHeader::SetUserFlag(unsigned int InUserFlag, bool bInActive)
{
	if (bInActive)
	{
		UserFlags |= InUserFlag;
	}
	else
	{
		UserFlags &= (~InUserFlag);
	}
}

bool SuperPeer::CPacketHeader::IsValid() const
{
	return
		(SenderID != PacketConfig::InvalidID) &&
		(DataType != PacketConfig::InvalidDataType) &&
		(DataSize > 0);
}

SuperPeer::CPacket::CPacket()
{
	Data = nullptr;
}

SuperPeer::CPacket::CPacket(const CPacketHeader& InHeader, const void* InData)
{
	Data = nullptr;
	Header = InHeader;
	SetData(InHeader.DataType, InHeader.DataSize, InData);
}

SuperPeer::CPacket::CPacket(const CPacket& X)
{
	*this = X;
}

SuperPeer::CPacket::CPacket(CPacket&& X) noexcept
{
	*this = move(X);
}

SuperPeer::CPacket::~CPacket()
{
	Util::SafeDeleteArray(Data);
}

SuperPeer::CPacket& SuperPeer::CPacket::operator=(const CPacket& X)
{
	Header = X.Header;
	Data = new Byte[X.Header.DataSize]{};
	memcpy_s(Data, X.Header.DataSize, X.Data, X.Header.DataSize);

	return* this;
}

SuperPeer::CPacket& SuperPeer::CPacket::operator=(CPacket&& X) noexcept
{
	Header = X.Header;
	Data = X.Data;

	X.Header = CPacketHeader();
	X.Data = nullptr;

	return*this;
}

bool SuperPeer::CPacket::SetData(int InDataType, int InDataSize, const void* InData)
{
	if ((InDataType == PacketConfig::InvalidDataType) || 
		(InDataSize <= 0) || 
		(InData == nullptr))
	{
		return false;
	}

	Header.DataType = InDataType;
	Header.DataSize = InDataSize;

	Util::SafeDeleteArray(Data);
	Data = new Byte[InDataSize]{};
	memcpy_s(Data, InDataSize, InData, InDataSize);

	return true;
}

bool SuperPeer::CPacket::IsValid() const
{
	return
		(Header.IsValid()) &&
		(Data != nullptr) &&
		(Header.DataSize <= PacketConfig::MaxPacketSize);
}
