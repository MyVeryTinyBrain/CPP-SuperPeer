#include "pch.h"
#include "RoomTypedef.h"

using namespace std;
using namespace SuperPeer;

SuperPeer::CRoomMembersSet::CRoomMembersSet()
{
    MaxMember = 0;
}

SuperPeer::CRoomMembersSet::CRoomMembersSet(const CRoomMembersSet& X)
{
    *this = X;
}

SuperPeer::CRoomMembersSet::CRoomMembersSet(CRoomMembersSet&& X) noexcept
{
    *this = move(X);
}

CRoomMembersSet& SuperPeer::CRoomMembersSet::operator=(const CRoomMembersSet& X)
{
    MaxMember = X.MaxMember;
    memcpy_s(MembersIDSet, sizeof(MembersIDSet), X.MembersIDSet, sizeof(X.MembersIDSet));

    return *this;
}

CRoomMembersSet& SuperPeer::CRoomMembersSet::operator=(CRoomMembersSet&& X) noexcept
{
    MaxMember = X.MaxMember;
    memcpy_s(MembersIDSet, sizeof(MembersIDSet), X.MembersIDSet, sizeof(X.MembersIDSet));

    X.MaxMember = 0;
    memset(X.MembersIDSet, 0, sizeof(X.MembersIDSet));

    return *this;
}

SuperPeer::CRoomMemberSetInfo::CRoomMemberSetInfo()
{
    NumMembers = 0;
}

SuperPeer::CRoomMemberSetInfo::CRoomMemberSetInfo(const CRoomMembersSet& InMemberSet, int InNumMembers)
{
    MemberSet = InMemberSet;
    NumMembers = InNumMembers;
}

SuperPeer::CRoomMemberChangedData::CRoomMemberChangedData()
{
    MemberChanged = EMemberChanged::None;
    ChangedMemberID = PacketConfig::InvalidID;
}

SuperPeer::CRoomMemberChangedData::CRoomMemberChangedData(EMemberChanged InMemberChanged, int InChangedMemberID, const CRoomMembersSet& InChangedMembersSet, int InNumMembers)
{
    MemberChanged = InMemberChanged;
    ChangedMemberID = InChangedMemberID;
    MemberSetInfo = CRoomMemberSetInfo(InChangedMembersSet, InNumMembers);
}

SuperPeer::CFailedJoinRoomData::CFailedJoinRoomData()
{
    Reason = EReceivedJoinRoomResult::InvalidResult;
}

SuperPeer::CFailedJoinRoomData::CFailedJoinRoomData(EReceivedJoinRoomResult InReason)
{
    Reason = InReason;
}

SuperPeer::CSucceededJoinRoomData::CSucceededJoinRoomData()
{
    ID = DataTypeConfig::InvalidDataType;
    UDPReceivePort = PortConfig::InvalidUDPPort;
}

SuperPeer::CSucceededJoinRoomData::CSucceededJoinRoomData(int InID, unsigned short InUDPReceivePort)
{
    ID = InID;
    UDPReceivePort = InUDPReceivePort;
}

SuperPeer::CRoomConstructorDesc::CRoomConstructorDesc()
{
    OnMemberChangedCallback = nullptr;
}

SuperPeer::CRoomSocketConstructorDesc::CRoomSocketConstructorDesc()
{
    OnMemberChangedCallback = nullptr;
}

