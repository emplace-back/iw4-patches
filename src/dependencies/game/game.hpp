#pragma once
#include "utils/string.hpp"
#include "structs.hpp"
#include "offsets.hpp"
#include "core/command/command.hpp"

namespace game
{
	namespace oob
	{
		bool send(const netadr_t & target, const std::string & data);
	}
	
	const static auto MSG_ReadBigString = reinterpret_cast<const char*(*)(msg_t*)>(0x005703D0); 
	const static auto SV_SetConfigstring = reinterpret_cast<void(*)(int, const char*)>(0x00589C20);
	const static auto SV_Loaded = reinterpret_cast<bool(*)()>(0x00589460);
	const static auto Steam_GetInviteHostAddr = reinterpret_cast<XNADDR*(*)()>(0x00627760);
	const static auto SV_IsBestOfRoundsDone = reinterpret_cast<bool(*)()>(0x0058BBF0);
	const static auto DB_FindXAssetHeader = reinterpret_cast<XAssetHeader(*)(XAssetType type, const char* name)>(0x004F4800);
	const static auto CL_SendBandwidthTestPacketMsg = reinterpret_cast<bool(*)(LocalClientNum_t, size_t, const char*, size_t)>(0x004C8A00); 
	const static auto PartyMigrate_BandwidthTest_SendTestPacketMsg = reinterpret_cast<bool(*)(PartyData_s*, size_t, const char*, size_t)>(0x004DD134);
	const static auto SV_GetGuid = reinterpret_cast<const char*(*)(size_t client_num)>(0x00588BB0);
	const static auto Xenon_RegisterRemoteXenon = reinterpret_cast<bool(*)(XSESSION_INFO const*, std::uint32_t*, unsigned short *)>(0x005CA500);
	const static auto Live_GetMapIndex = reinterpret_cast<int(*)(const char *map)>(0x005B8AB0);
	const static auto Live_GetMapCount = reinterpret_cast<int(*)()>(0x005B8A90);
	const static auto Cmd_TokenizeString = reinterpret_cast<void(*)(const char*)>(0x00564350);
	const static auto SV_Cmd_TokenizeString = reinterpret_cast<void(*)(const char *text_in)>(0x005643B0);
	const static auto SV_Cmd_EndTokenizedString = reinterpret_cast<void(*)()>(0x005643E0);
	const static auto Cmd_EndTokenizedString = reinterpret_cast<void(*)()>(0x00564380);
	const static auto ClientCommand = reinterpret_cast<void(*)(int)>(0x00526280);
	const static auto UI_GetMapDisplayName = reinterpret_cast<const char*(*)(const char*)>(0x0059E440);
	const static auto UI_GetGameTypeDisplayName = reinterpret_cast<const char*(*)(const char*)>(0x0059E550);
	const static auto CG_TranslateHudElemMessage = reinterpret_cast<void(*)(LocalClientNum_t localClientNum, const char *message, const char *messageType, char *hudElemString, size_t)>(0x00492A30);
	const static auto SEH_LocalizeTextMessage = reinterpret_cast<char*(*)(const char *pszInputBuffer, const char *pszMessageType, std::uint32_t errType)>(0x00591CF0);
	const static auto BG_WeaponBulletFire_ShouldSpread = reinterpret_cast<bool(*)(std::uint32_t*, const WeaponDef*)>(0x0047A7A0);
	const static auto BG_WeaponBulletFire_ShouldPenetrate = reinterpret_cast<bool(*)(std::uint32_t*, const WeaponDef*)>(0x0047A7F0);
	const static auto device = reinterpret_cast<IDirect3DDevice9**>(0x006664C60);
	const static auto CL_Netchan_Transmit = reinterpret_cast<bool(*)(netchan_t *chan, char *data, int length)>(0x004C94C0);
	const static auto Netchan_Transmit = reinterpret_cast<bool(*)(netchan_t *chan, int, char*)>(0x00573940);
	const static auto SV_Netchan_Transmit = reinterpret_cast<bool(*)(client_t *, char *data, int length)>(0x0058D1C0);
	const static auto MSG_WriteBitsCompress = reinterpret_cast<bool(*)(bool trainHuffman, const char *from, char *to, int fromSizeBytes)>(0x0056FD20);
	const static auto CL_AddReliableCommand = reinterpret_cast<void(*)(LocalClientNum_t, const char*)>(0x004C2E40);
	const static auto Sys_GetValue = reinterpret_cast<int(*)(int valueIndex)>(0x00576760);
	const static auto Com_Error = reinterpret_cast<void(*)(errorParm_t errorType, const char* text)>(0x0056A0C0);
	const static auto SV_GameDropClient = reinterpret_cast<void(*)(ClientNum_t clientNum, const char*)>(0x005884D0);
	const static auto SV_DropClient = reinterpret_cast<void(*)(client_t *, const char *, bool)>(0x00585E30);
	const static auto SV_GameSendServerCommand = reinterpret_cast<void(*)(ClientNum_t clientNum, std::uint32_t type, const char *text)>(0x00588480);
	const static auto Cbuf_AddText = reinterpret_cast<void(*)(LocalClientNum_t localClientNum, const char *text)>(0x00563D10);
	const static auto Cbuf_ExecuteBuffer = reinterpret_cast<void(*)(LocalClientNum_t localClientNum, int a2, const char *text)>(0x00564A30);
	const static auto G_Say = reinterpret_cast<void(*)(gentity_s*, gentity_s*, int, const char*)>(0x005260E0);
	const static auto CG_GameMessage = reinterpret_cast<void(*)(LocalClientNum_t localClientNum, const char* message)>(0x00497600);
	const static auto CG_BoldGameMessage = reinterpret_cast<void(*)(LocalClientNum_t localClientNum, const char* message)>(0x00497630);
	const static auto Sys_Milliseconds = reinterpret_cast<std::uint32_t(*)()>(0x005CA750);
	const static auto NET_OutOfBandPrint = reinterpret_cast<bool(*)(netsrc_t sock, netadr_t adr, const char* format)>(0x00573400);
	const static auto NET_OutOfBandData = reinterpret_cast<bool(*)(netsrc_t sock, netadr_t adr, const char* format, size_t length)>(0x005734C0);
	const static auto NET_OutOfBandVoiceData = reinterpret_cast<bool(*)(netsrc_t sock, netadr_t adr, const char* format, size_t length)>(0x00573570);
	const static auto CL_SendPeerVoiceData = reinterpret_cast<bool(*)(void*, int, netsrc_t, int, msg_t*, bool)>(0x004CBC80);
	const static auto Sys_SendPacket = reinterpret_cast<bool(*)(netsrc_t sock, size_t len, const char* format, netadr_t netadr)>(0x005C9930);
	const static auto NET_SendPacket = reinterpret_cast<bool(*)(netsrc_t sock, int length, const void *data, netadr_t to)>(0x005733A0);
	const static auto RMsg_AddMessage = reinterpret_cast<bool(*)(const netadr_t* adr, msg_t* msg)>(0x005C3020);
	const static auto RMsg_AddPrint = reinterpret_cast<bool(*)(netadr_t* adr, const char* message)>(0x005C3050);
	const static auto Info_ValueForKey = reinterpret_cast<char*(*)(const char *s, const char *key)>(0x005C2040);
	const static auto Info_SetValueForKey = reinterpret_cast<char*(*)(char *s, const char *key, const char *value)>(0x005C2460);
	const static auto CL_GetConfigString = reinterpret_cast<const char*(*)(int)>(0x004BBFC0);
	const static auto Cmd_Argv = reinterpret_cast<char*(*)(int index)>(0x00426A20);
	const static auto Live_GetXuid = reinterpret_cast<std::uint64_t(*)(ControllerIndex_t controllerIndex)>(0x005C7190);
	const static auto Steam_GetUid = reinterpret_cast<std::uint64_t(*)()>(0x00627730);
	const static auto MSG_Init = reinterpret_cast<void(*)(msg_t * buf, char* data, int length)>(0x0056FA70);
	const static auto MSG_WriteData = reinterpret_cast<void(*)(msg_t *buf, const void *data, int length)>(0x0056FE30);
	const static auto MSG_WriteString = reinterpret_cast<void(*)(msg_t * msg, const char* s)>(0x0056FF60);
	const static auto MSG_WriteBigString = reinterpret_cast<void(*)(msg_t * msg, const char* s)>(0x005700D0);
	const static auto MSG_WriteByte = reinterpret_cast<void(*)(msg_t * msg, int c)>(0x0056FDE0);
	const static auto MSG_WriteShort = reinterpret_cast<void(*)(msg_t * msg, int c)>(0x0056FE70);
	const static auto MSG_WriteInt64 = reinterpret_cast<void(*)(msg_t * msg, std::uint64_t c)>(0x0056FF10);
	const static auto MSG_WriteLong = reinterpret_cast<void(*)(msg_t *msg, int c)>(0x0056FEC0);
	const static auto MSG_WriteBits = reinterpret_cast<void(*)(msg_t *msg, int value, int bits)>(0x0056FCA0);
	const static auto MSG_WriteBit0 = reinterpret_cast<void(*)(msg_t *msg)>(0x0056FC10);
	const static auto MSG_WriteBit1 = reinterpret_cast<void(*)(msg_t *msg)>(0x0056FC50);
	const static auto MSG_Discard = reinterpret_cast<int(*)(msg_t *msg)>(0x0056FB70);
	const static auto MSG_ClearLastReferencedEntity = reinterpret_cast<void(*)(msg_t *msg)>(0x005713F0);
	const static auto Scr_GetScrambleBuf = reinterpret_cast<int(*)(std::uint32_t)>(0x0057A010);
	const static auto CL_CanWeConnectToClient = reinterpret_cast<int(*)(const void *sessionData, ClientNum_t ourClientNum, ClientNum_t theirClientNum)>(0x004CB520);
	const static auto Live_GetCurrentSession = reinterpret_cast<void*(*)()>(0x005C7160);
	const static auto NET_StringToAdr = reinterpret_cast<bool(*)(const char* s, netadr_t* a)>(0x00573600);
	const static auto BigShort = reinterpret_cast<std::uint16_t(*)(std::uint16_t)>(0x005C18A0);
	const static auto CL_IsLocalClientInGame = reinterpret_cast<bool(*)()>(0x004C4EA0);
	const static auto Steam_SendIntroducerMSG = reinterpret_cast<void(*)(std::uint64_t)>(0x006298E0);
	const static auto Com_Quit_f = reinterpret_cast<void(*)()>(0x0056A2D0);
	const static auto Party_FindMember = reinterpret_cast<int(*)(PartyData_s * party, netadr_t playerAddr)>(0x004D2CC0);
	const static auto NET_CompareAdr = reinterpret_cast<bool(*)(netadr_t a, netadr_t b)>(0x00572FD0);
	const static auto StringToXNAddr = reinterpret_cast<bool(*)(const char*, XNADDR*)>(0x005737F0);
	const static auto NET_CompareBaseAdr = reinterpret_cast<bool(*)(netadr_t a, netadr_t b)>(0x00572E30);
	const static auto DB_GetXAssetName = reinterpret_cast<const char*(*)(const XAsset*)>(0x004DFDE0);
	const static auto DB_EnumXAssets_Internal = reinterpret_cast<void(*)(XAssetType type, void(*)(XAssetHeader, void*), const void* inData, bool includeOverride)>(0x004F15B0);
	const static auto Steam_GetSteamLobbyID = reinterpret_cast<std::uint64_t(*)()>(0x00627770);
	const static auto Steam_JoinLobby = reinterpret_cast<bool(*)(std::uint64_t xuid, bool b)>(0x00629170);
	const static auto Party_AskToJoinParty = reinterpret_cast<bool(*)(PartyData_s*, int b, int c)>(0x004D4ED0);
	const static auto Live_StartAcceptingInvitation = reinterpret_cast<int(*)(std::uint64_t, bool b)>(0x005C8050);
	const static auto Cmd_AddCommandInternal = reinterpret_cast<std::uint32_t(*)(const char *cmdName, void(__cdecl *function)(), cmd_function_s *allocedCmd)>(0x00564460);
	const static auto MSG_ReadByte = reinterpret_cast<std::uint8_t(*)(msg_t* msg)>(0x005701E0);
	const static auto MSG_ReadStringLine = reinterpret_cast<char*(*)(msg_t *msg, char *string, unsigned int maxChars)>(0x00570430);
	const static auto Scr_IsValidGameType = reinterpret_cast<bool(*)(const char*)>(0x00547C00);
	const static auto MSG_ReadString = reinterpret_cast<char*(*)(msg_t *msg, char *string, unsigned int maxChars)>(0x00570380);
	const static auto MSG_ReadData = reinterpret_cast<void*(*)(msg_t* msg, const void* data, size_t)>(0x005704C0);
	const static auto MSG_ReadLong = reinterpret_cast<std::uint32_t(*)(msg_t* msg)>(0x005702C0);
	const static auto MSG_ReadShort = reinterpret_cast<std::uint16_t(*)(msg_t* msg)>(0x00570260);
	const static auto CL_GetClientName = reinterpret_cast<char*(*)(LocalClientNum_t, int, char*, int)>(0x004CB370);
	const static auto IsServerRunning = reinterpret_cast<bool(*)()>(0x005C7530);
	const static auto LiveStorage_GetPersistentDataBuffer = reinterpret_cast<void*(*)(LocalClientNum_t)>(0x00566D10);
	const static auto LiveStorage_StatsWriteNeeded = reinterpret_cast<void*(*)(LocalClientNum_t)>(0x00566D30);
	const static auto Steam_GetClientPersonaName = reinterpret_cast<char*(*)()>(0x00627500);
	const static auto Dvar_FindVar = reinterpret_cast<dvar_t*(*)(const char*)>(0x005BCF30);
	const static auto XUIDToString = reinterpret_cast<void(*)(const unsigned __int64 *a1, char *a2)>(0x00573760);
	const static auto I_CleanStr = reinterpret_cast<char*(*)(const char *a1)>(0x005C1EF0);
	const static auto I_strncat = reinterpret_cast<void(*)(char *dest, int size, const char *src)>(0x005C1E90);
	const static auto Com_BlockChecksumKey32 = reinterpret_cast<std::uint32_t(*)(const void *, unsigned int, unsigned int)>(0x0060D160);
	const static auto GScr_AllocString = reinterpret_cast<std::uint32_t(*)(const char* s)>(0x00539B50);
	const static auto CG_GetPlayerViewOrigin = reinterpret_cast<std::uint32_t(*)(LocalClientNum_t, const playerState_s*, Vec3*)>(0x004B4480);
	const static auto Com_GetClientDObj = reinterpret_cast<char*(*)(int handle)>(0x0056B8E0);
	const static auto CG_DObjGetWorldTagPos = reinterpret_cast<std::uint32_t(*)(const centity_t * entity, void* obj, std::uint32_t tagName, Vec3* pos)>(0x0048E720);
	const static auto vectoangles = reinterpret_cast<void(*)(const Vec3* vec, Vec3* angles)>(0x005B41F0);
	const static auto BG_GetViewmodelWeaponIndex = reinterpret_cast<int(*)(const playerState_s*)>(0x004795C0);
	const static auto Trace_GetEntityHitId = reinterpret_cast<std::uint16_t(*)(const trace_t* results)>(0x0055D550);
	const static auto CG_ClientHasPerk = reinterpret_cast<bool(*)(std::uint32_t* perk, std::uint32_t b)>(0x0045FAE0);
	const static auto BG_GetSurfacePenetrationDepth = reinterpret_cast<float(*)(WeaponDef* weapon, int surfaceType)>(0x00479430);
	const static auto BG_AdvanceTrace = reinterpret_cast<bool(*)(BulletFireParams* bp, BulletTraceResults* br, float distance)>(0x00479A80);
	const static auto BG_GetSpreadForWeapon = reinterpret_cast<void(*)(playerState_s const*, WeaponDef*, float*, float*)>(0x0047A1A0);
	const static auto AngleVectors = reinterpret_cast<void(*)(const Vec3 * angles, Vec3 * forward, Vec3 * right, Vec3 * up)>(0x005B74E0);
	const static auto ClampChar = reinterpret_cast<char(*)(int)>(0x005B38F0);
	const static auto BG_srand = reinterpret_cast<std::uint32_t*(*)(std::uint32_t* serverTime)>(0x00472230);
	const static auto BG_random = reinterpret_cast<float(*)(std::uint32_t* serverTime)>(0x004709E0);
	const static auto CG_IsPlayerReloading = reinterpret_cast<bool(*)()>(0x004B2710);
	const static auto Dvar_SetStringByName = reinterpret_cast<void(*)(const char*, const char*)>(0x005BE860);
	const static auto Cbuf_AddCall = reinterpret_cast<void(*)(LocalClientNum_t, void(*)(LocalClientNum_t))>(0x00563DC0);
	const static auto UI_Map = reinterpret_cast<void(*)(LocalClientNum_t)>(0x0059BE70);
	const static auto SV_FastRestart = reinterpret_cast<void(*)(LocalClientNum_t)>(0x005853E0);
	const static auto Live_GetPlayerAddr = reinterpret_cast<netadr_t*(*)(netadr_t* netadr, void* session, size_t index)>(0x00621C90);
	const static auto Live_UpdatePlayerAddr = reinterpret_cast<void(*)(void*, size_t, netadr_t*)>(0x00621BE0);
	const static auto Live_UpdatePlayerInAddr = reinterpret_cast<void(*)(void*, size_t, std::uint32_t, std::uint16_t)>(0x006221B0);
	const static auto DB_GetMaterialIndex = reinterpret_cast<std::uint32_t(*)(void*)>(0x004F29F0);
	const static auto CG_MapRestart = reinterpret_cast<void(*)(LocalClientNum_t, bool)>(0x004A7690);
	const static auto Session_IsHost = reinterpret_cast<bool(*)(void*, size_t)>(0x00621CF0);
	const static auto CG_LocationalTrace = reinterpret_cast<bool(*)(trace_t *, const Vec3*, const Vec3*, int, int)>(0x004BB120);
	const static auto CG_SetAds = reinterpret_cast<void(*)(LocalClientNum_t, bool)>(0x004BCB40);
	const static auto ScrPlace_GetActivePlacement = reinterpret_cast<ScreenPlacement*(*)(LocalClientNum_t)>(0x004DF860);
	const static auto PartyHost_TellClientToRejoin = reinterpret_cast<void(*)(PartyData_s*, netadr_t)>(0x004D7CC0);
	const static auto Party_SendNewLobbyToAddr = reinterpret_cast<void(*)(PartyData_s*, netadr_t)>(0x004D4370);
	const static auto SV_EndClientSnapshot = reinterpret_cast<void(*)(client_t *, msg_t *, char*)>(0x0058F720);
	const static auto SL_ConvertToString = reinterpret_cast<const char*(*)(unsigned int stringValue)>(0x00579AF0);
	const static auto BG_GetNumWeapons = reinterpret_cast<std::uint32_t(*)()>(0x00479600);
	const static auto Material_RegisterHandle = reinterpret_cast<Material*(*)(const char*)>(0x0040FD60);
	const static auto SV_AddTestClient = reinterpret_cast<gentity_s*(*)()>(0x00588280);
	const static auto Xenon_GetXNAddr = reinterpret_cast<XNADDR*(*)()>(0x005C72F0);
	const static auto Dvar_ValueToString = reinterpret_cast<const char*(*)(dvar_t*, DvarValue)>(0x005BBFB0);
	const static auto Dvar_IsValidName = reinterpret_cast<bool(*)(const char*)>(0x005BBCA0);
	const static auto SendToHost = reinterpret_cast<void(*)(const char *cmd, int len)>(0x004C88C0);
	const static auto GetHostRating = reinterpret_cast<int(*)()>(0x004C8C10);
	const static auto PartyMigrate_GetClientConnectivity = reinterpret_cast<int(*)(void*, LocalClientNum_t)>(0x004DC350);
	const static auto SV_BeginClientSnapshot = reinterpret_cast<void(*)(client_t*, msg_t*, char*)>(0x0058F6C0);
	const static auto SV_WriteSnapshotToClient = reinterpret_cast<void(*)(client_t*, msg_t*, bool, bool)>(0x0058EF80);
	const static auto SV_SendMessageToClient = reinterpret_cast<void(*)(msg_t*, client_t*)>(0x0058F4D0);
	const static auto Session_IsUserRegistered = reinterpret_cast<bool(*)(void*, size_t)>(0x00621340);
	const static auto SV_Cmd_Argv = reinterpret_cast<char*(*)(int argIndex)>(0x00563C60);
	const static auto& bg_lastParsedWeaponIndex = *reinterpret_cast<std::uint32_t*>(0x00873D84);
	const static auto& map_handler = reinterpret_cast<MapnameRichPresenceInfo*>(0x006AC1D8); 
	const static auto& g_partyData = reinterpret_cast<PartyData_s*>(0x010F5A98);
	const static auto& g_lobbyData = reinterpret_cast<PartyData_s*>(0x010F9268); 
	const static auto& match_data = reinterpret_cast<void*>(offsets::match_data);
	const static auto& s_sortedDvars = reinterpret_cast<dvar_t**>(0x0637C470);
	const static auto& g_dvarCount = *reinterpret_cast<std::uint32_t*>(0x0637C448);
	const static auto& cmd_functions = reinterpret_cast<cmd_function_s*>(0x01B741D0);
	const static auto& ucmds = reinterpret_cast<ucmd_t*>(0x0085AF58);
	const static auto& g_ourXnaddr = reinterpret_cast<XNADDR*>(0x006466898);
	const static auto& cmd_argc = reinterpret_cast<std::uint32_t*>(0x01B7418C);
	const static auto& cmd_id = reinterpret_cast<std::uint32_t*>(0x01B74148);
	const static auto& sv_cmd_argc = reinterpret_cast<std::uint32_t*>(0x01B87254);
	const static auto& sv_cmd_id = reinterpret_cast<std::uint32_t*>(0x01B87210);
	const static auto& end_address = reinterpret_cast<void*>(offsets::end_address);
	const static auto& net_field_checksum = *reinterpret_cast<std::uint8_t*>(0x006428E9C);
	const static auto& playlist_version_number = *reinterpret_cast<std::uint32_t*>(0x0062EC848);
	const static auto& g_assetNames = reinterpret_cast<const char**>(0x006F7B98);
	const static auto& g_statsBackup = reinterpret_cast<void*>(0x00AAD508);
	const static auto& stats = reinterpret_cast<stats_t*>(0x01B8B7E8);
	const static auto& g_steamInitialized = *reinterpret_cast<bool*>(0x066547A8);
	const static auto& atTime = *reinterpret_cast<int*>(0x06260D04);
	const static auto& g_inLobby = *reinterpret_cast<bool*>(offsets::g_inLobby);
	const static auto& g_IWLobbyJoinInProgress = *reinterpret_cast<bool*>(offsets::g_IWLobbyJoinInProgress);
	const static auto& inviteState = *reinterpret_cast<std::uint32_t*>(offsets::inviteState);
	const static auto& sv_serverId_value = *reinterpret_cast<int*>(0x02022928);
	const static auto& svs_numclients = *reinterpret_cast<int*>(0x03172088);
	const static auto& hwnd = *reinterpret_cast<HWND*>(offsets::window);

	extern client_t* svs_clients;

	void initialize();
	size_t get_client_num(const PartyMember * member);
	size_t get_client_num(const client_t * client);
	char* I_strncpyz(char* place, const std::string& string, const size_t length);
	bool is_authed_client(const game::client_t & client);
	bool is_authed_client(const size_t client_num);
	bool is_authed_client(const netadr_t & target);
	void for_each_authed_client(const size_t count, const std::function<void(size_t)>& callback);
	void send_server_command(const int client_num, const std::string & command);
	connstate_t & CL_GetLocalClientConnectionState();
	bool is_real_address(const XNADDR& xnaddr, const netadr_t& netadr);

	inline clientConnection_t* clc() {
		return reinterpret_cast<clientConnection_t*>(0x00AB5E58);
	}
	
	inline PartyData_s* party_data()
	{
		static PartyData_s* party = nullptr;
		if (g_lobbyData->in_party() || (party = g_partyData, !g_partyData->in_party()))
			party = g_lobbyData;

		return party;
	}
}