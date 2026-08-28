/* Generated file. Do not edit. */

#ifndef TMP_SDK_H
#define TMP_SDK_H

#include "TruckersMP/TruckersMP_Base.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define TRUCKERSMP_SDK_VERSION 0x01000100u /* 1.1.0 */

/* TruckersMP_EResult is defined in TruckersMP_Base.h; its values follow. */
enum
{
    TruckersMP_Result_Ok = 0,
    TruckersMP_Result_InternalError = 1,
    TruckersMP_Result_InvalidParameter = 2,
    TruckersMP_Result_WrongThread = 3,
    TruckersMP_Result_NotSupported = 4,
    TruckersMP_Result_NotAuthorized = 5,
    TruckersMP_Result_UnknownEvent = 6,
    TruckersMP_Result_ServiceUnavailable = 7,
    TruckersMP_Result_ChatCommandAlreadyRegistered = 8,
    TruckersMP_Result_ChatCommandNotRegistered = 9,
};

typedef int32_t TruckersMP_LogLevel;
enum
{
    TruckersMP_LogLevel_Info = 0,
    TruckersMP_LogLevel_Warning = 1,
    TruckersMP_LogLevel_Error = 2,
};

typedef int32_t TruckersMP_MouseButton;
enum
{
    TruckersMP_MouseButton_Left = 0,
    TruckersMP_MouseButton_Right = 1,
    TruckersMP_MouseButton_Middle = 2,
};

typedef int32_t TruckersMP_RendererID;
enum
{
    TruckersMP_RendererID_OpenGL = 0,
    TruckersMP_RendererID_DirectX11 = 1,
};

typedef int32_t TruckersMP_NotificationType;
enum
{
    TruckersMP_NotificationType_Normal = 0,
    TruckersMP_NotificationType_Warning = 1,
    TruckersMP_NotificationType_Error = 2,
    TruckersMP_NotificationType_Success = 3,
};

typedef struct TruckersMP_Float3
{
    float x;
    float y;
    float z;
} TruckersMP_Float3;
TRUCKERSMP_ASSERT_SIZE( TruckersMP_Float3, 12 );

typedef struct TruckersMP_Double3
{
    double x;
    double y;
    double z;
} TruckersMP_Double3;
TRUCKERSMP_ASSERT_SIZE( TruckersMP_Double3, 24 );

typedef struct TruckersMP_Quaternion
{
    float w;
    float x;
    float y;
    float z;
} TruckersMP_Quaternion;
TRUCKERSMP_ASSERT_SIZE( TruckersMP_Quaternion, 16 );

typedef struct TruckersMP_Placement
{
    TruckersMP_Double3 position;
    TruckersMP_Quaternion rotation;
} TruckersMP_Placement;
TRUCKERSMP_ASSERT_SIZE( TruckersMP_Placement, 40 );

typedef struct TruckersMP_Color
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
} TruckersMP_Color;
TRUCKERSMP_ASSERT_SIZE( TruckersMP_Color, 4 );

typedef struct TruckersMP_Bounds
{
    TruckersMP_Float3 min;
    TruckersMP_Float3 max;
} TruckersMP_Bounds;
TRUCKERSMP_ASSERT_SIZE( TruckersMP_Bounds, 24 );

typedef struct TruckersMP_PackageInfo
{
    TruckersMP_String name;
} TruckersMP_PackageInfo;
TRUCKERSMP_ASSERT_SIZE( TruckersMP_PackageInfo, 16 );

typedef struct TruckersMP_Player_Handle { uint64_t m_value; } TruckersMP_Player_Handle; /* 0 = invalid */

typedef struct TruckersMP_Trailer_Handle { uint64_t m_value; } TruckersMP_Trailer_Handle; /* 0 = invalid */

typedef struct TruckersMP_Vehicle_Handle { uint64_t m_value; } TruckersMP_Vehicle_Handle; /* 0 = invalid */

#define TRUCKERSMP_API_CORE 0x611c12f8a74565ecull

typedef struct TruckersMP_Core
{
    TruckersMP_EResult( TMP_API *AddListener )( TruckersMP_PluginContext *ctx, uint64_t eventId, TruckersMP_EventFn fn, void *userCtx );
    TruckersMP_EResult( TMP_API *RemoveListener )( TruckersMP_PluginContext *ctx, uint64_t eventId, TruckersMP_EventFn fn, void *userCtx );
    TruckersMP_EResult( TMP_API *UnlockIntent )( TruckersMP_PluginContext *ctx, TruckersMP_String key );
    TruckersMP_EResult( TMP_API *LogMessage )( TruckersMP_PluginContext *ctx, TruckersMP_LogLevel level, TruckersMP_String text );
    bool( TMP_API *GameID )( TruckersMP_PluginContext *ctx, TruckersMP_String *out ); /* free out->m_ptr once via TruckersMP_Host::Free */
    bool( TMP_API *ClientVersion )( TruckersMP_PluginContext *ctx, TruckersMP_String *out ); /* free out->m_ptr once via TruckersMP_Host::Free */
} TruckersMP_Core;

#define TRUCKERSMP_API_ACCOUNTS 0xab1d54b0fe89cb98ull

typedef struct TruckersMP_Accounts
{
    bool( TMP_API *GetAccountID )( TruckersMP_PluginContext *ctx, uint64_t *out );
    bool( TMP_API *IsGameModerator )( TruckersMP_PluginContext *ctx, bool *out );
    bool( TMP_API *IsTeamMember )( TruckersMP_PluginContext *ctx, bool *out );
    bool( TMP_API *IsPatron )( TruckersMP_PluginContext *ctx, bool *out );
    bool( TMP_API *GetCompanyID )( TruckersMP_PluginContext *ctx, uint64_t *out );
} TruckersMP_Accounts;

#define TRUCKERSMP_API_GAMEPLAY 0x9df9e43b7741e28aull

typedef struct TruckersMP_Gameplay
{
    bool( TMP_API *GetMountedPackages )( TruckersMP_PluginContext *ctx, TruckersMP_List *out ); /* free out->m_items once via TruckersMP_Host::Free; element strings live inside that block */
} TruckersMP_Gameplay;

#define TRUCKERSMP_EVT_GAMEPLAY_NO_COLLISION_ZONE 0x32ee69b34aeebab5ull

typedef struct TruckersMP_Evt_GameplayNoCollisionZone
{
    bool m_entered;
} TruckersMP_Evt_GameplayNoCollisionZone;
TRUCKERSMP_ASSERT_SIZE( TruckersMP_Evt_GameplayNoCollisionZone, 1 );
TRUCKERSMP_ASSERT_OFFSET( TruckersMP_Evt_GameplayNoCollisionZone, m_entered, 0 );

#define TRUCKERSMP_API_INPUT 0xd7e26f4231f26fe7ull

typedef struct TruckersMP_Input
{
    bool( TMP_API *IsMouseVisible )( TruckersMP_PluginContext *ctx, bool *out );
    TruckersMP_EResult( TMP_API *IncreaseMouseRef )( TruckersMP_PluginContext *ctx );
    TruckersMP_EResult( TMP_API *DecreaseMouseRef )( TruckersMP_PluginContext *ctx );
    bool( TMP_API *IsGameMouseLocked )( TruckersMP_PluginContext *ctx, bool *out );
    TruckersMP_EResult( TMP_API *SetGameMouseLocked )( TruckersMP_PluginContext *ctx, bool locked );
    bool( TMP_API *IsGameKeyboardLocked )( TruckersMP_PluginContext *ctx, bool *out );
    TruckersMP_EResult( TMP_API *SetGameKeyboardLocked )( TruckersMP_PluginContext *ctx, bool locked );
} TruckersMP_Input;

#define TRUCKERSMP_EVT_INPUT_KEY 0xf56818eb5efbfe1dull

typedef struct TruckersMP_Evt_InputKey
{
    uint8_t m_key;
    uint16_t m_flags;
    bool m_down;
} TruckersMP_Evt_InputKey;
TRUCKERSMP_ASSERT_SIZE( TruckersMP_Evt_InputKey, 6 );
TRUCKERSMP_ASSERT_OFFSET( TruckersMP_Evt_InputKey, m_key, 0 );
TRUCKERSMP_ASSERT_OFFSET( TruckersMP_Evt_InputKey, m_flags, 2 );
TRUCKERSMP_ASSERT_OFFSET( TruckersMP_Evt_InputKey, m_down, 4 );

#define TRUCKERSMP_EVT_INPUT_CHAR 0xdc4d31abbf0feb38ull

typedef struct TruckersMP_Evt_InputChar
{
    uint32_t m_character;
} TruckersMP_Evt_InputChar;
TRUCKERSMP_ASSERT_SIZE( TruckersMP_Evt_InputChar, 4 );
TRUCKERSMP_ASSERT_OFFSET( TruckersMP_Evt_InputChar, m_character, 0 );

#define TRUCKERSMP_EVT_INPUT_MOUSE_MOVE 0xf5c15e1495dc06efull

typedef struct TruckersMP_Evt_InputMouseMove
{
    int32_t m_x;
    int32_t m_y;
} TruckersMP_Evt_InputMouseMove;
TRUCKERSMP_ASSERT_SIZE( TruckersMP_Evt_InputMouseMove, 8 );
TRUCKERSMP_ASSERT_OFFSET( TruckersMP_Evt_InputMouseMove, m_x, 0 );
TRUCKERSMP_ASSERT_OFFSET( TruckersMP_Evt_InputMouseMove, m_y, 4 );

#define TRUCKERSMP_EVT_INPUT_MOUSE_WHEEL 0x7dd742140620cd0dull

typedef struct TruckersMP_Evt_InputMouseWheel
{
    int32_t m_delta;
} TruckersMP_Evt_InputMouseWheel;
TRUCKERSMP_ASSERT_SIZE( TruckersMP_Evt_InputMouseWheel, 4 );
TRUCKERSMP_ASSERT_OFFSET( TruckersMP_Evt_InputMouseWheel, m_delta, 0 );

#define TRUCKERSMP_EVT_INPUT_MOUSE_BUTTON 0xec38ee3601998c78ull

typedef struct TruckersMP_Evt_InputMouseButton
{
    TruckersMP_MouseButton m_button;
    bool m_down;
    bool m_block; /* in-out */
} TruckersMP_Evt_InputMouseButton;
TRUCKERSMP_ASSERT_SIZE( TruckersMP_Evt_InputMouseButton, 8 );
TRUCKERSMP_ASSERT_OFFSET( TruckersMP_Evt_InputMouseButton, m_button, 0 );
TRUCKERSMP_ASSERT_OFFSET( TruckersMP_Evt_InputMouseButton, m_down, 4 );
TRUCKERSMP_ASSERT_OFFSET( TruckersMP_Evt_InputMouseButton, m_block, 5 );

#define TRUCKERSMP_API_NETWORK 0x9c2c7fb50b69537dull

typedef struct TruckersMP_Network
{
    bool( TMP_API *IsConnected )( TruckersMP_PluginContext *ctx, bool *out );
    bool( TMP_API *GetLastPing )( TruckersMP_PluginContext *ctx, uint16_t *out );
    bool( TMP_API *GetGameServerID )( TruckersMP_PluginContext *ctx, uint64_t *out );
} TruckersMP_Network;

#define TRUCKERSMP_EVT_NETWORK_CONNECTED 0x90e5649e2be045d3ull

#define TRUCKERSMP_EVT_NETWORK_DISCONNECTED 0xa9e12170e5ca1702ull

#define TRUCKERSMP_API_PLAYERS 0x91bf40dfad9c41ebull

typedef struct TruckersMP_Players
{
    bool( TMP_API *GetLocalPlayer )( TruckersMP_PluginContext *ctx, TruckersMP_Player_Handle *out );
    bool( TMP_API *GetPlayerByID )( TruckersMP_PluginContext *ctx, int32_t id, TruckersMP_Player_Handle *out );
    bool( TMP_API *GetAllPlayers )( TruckersMP_PluginContext *ctx, TruckersMP_List *out ); /* free out->m_items once via TruckersMP_Host::Free; element strings live inside that block */
} TruckersMP_Players;

#define TRUCKERSMP_API_PLAYER_HANDLE 0x8ee27b0ccfaee795ull

typedef struct TruckersMP_PlayerHandle
{
    bool( TMP_API *GetPlayerID )( TruckersMP_PluginContext *ctx, TruckersMP_Player_Handle self, int32_t *out );
    bool( TMP_API *GetAccountID )( TruckersMP_PluginContext *ctx, TruckersMP_Player_Handle self, uint64_t *out );
    bool( TMP_API *GetSteamID )( TruckersMP_PluginContext *ctx, TruckersMP_Player_Handle self, uint64_t *out );
    bool( TMP_API *GetUsername )( TruckersMP_PluginContext *ctx, TruckersMP_Player_Handle self, TruckersMP_String *out ); /* free out->m_ptr once via TruckersMP_Host::Free */
    bool( TMP_API *GetTagText )( TruckersMP_PluginContext *ctx, TruckersMP_Player_Handle self, TruckersMP_String *out ); /* free out->m_ptr once via TruckersMP_Host::Free */
    bool( TMP_API *GetTagColor )( TruckersMP_PluginContext *ctx, TruckersMP_Player_Handle self, TruckersMP_Color *out );
    bool( TMP_API *IsPatron )( TruckersMP_PluginContext *ctx, TruckersMP_Player_Handle self, bool *out );
    bool( TMP_API *IsGameModerator )( TruckersMP_PluginContext *ctx, TruckersMP_Player_Handle self, bool *out );
    bool( TMP_API *IsTeamMember )( TruckersMP_PluginContext *ctx, TruckersMP_Player_Handle self, bool *out );
    bool( TMP_API *IsManager )( TruckersMP_PluginContext *ctx, TruckersMP_Player_Handle self, bool *out );
    bool( TMP_API *CanStreamFromCamera )( TruckersMP_PluginContext *ctx, TruckersMP_Player_Handle self, bool *out );
    bool( TMP_API *StreamsFromCamera )( TruckersMP_PluginContext *ctx, TruckersMP_Player_Handle self, bool *out );
    bool( TMP_API *GetNetworkLatency )( TruckersMP_PluginContext *ctx, TruckersMP_Player_Handle self, uint16_t *out );
    bool( TMP_API *GetVehicle )( TruckersMP_PluginContext *ctx, TruckersMP_Player_Handle self, TruckersMP_Vehicle_Handle *out );
    bool( TMP_API *GetTrailer )( TruckersMP_PluginContext *ctx, TruckersMP_Player_Handle self, TruckersMP_Trailer_Handle *out );
    bool( TMP_API *GetDistanceFromLocalPlayer )( TruckersMP_PluginContext *ctx, TruckersMP_Player_Handle self, float *out );
    bool( TMP_API *GetDistanceToCamera )( TruckersMP_PluginContext *ctx, TruckersMP_Player_Handle self, float *out );
    bool( TMP_API *CanCollideWith )( TruckersMP_PluginContext *ctx, TruckersMP_Player_Handle self, TruckersMP_Player_Handle player, bool *out );
} TruckersMP_PlayerHandle;

#define TRUCKERSMP_EVT_PLAYER_STREAM_IN 0x095c1192f5da21cdull

typedef struct TruckersMP_Evt_PlayerStreamIn
{
    TruckersMP_Player_Handle m_player;
} TruckersMP_Evt_PlayerStreamIn;
TRUCKERSMP_ASSERT_SIZE( TruckersMP_Evt_PlayerStreamIn, 8 );
TRUCKERSMP_ASSERT_OFFSET( TruckersMP_Evt_PlayerStreamIn, m_player, 0 );

#define TRUCKERSMP_EVT_PLAYER_STREAM_OUT 0x702c3c15a6dff3eeull

typedef struct TruckersMP_Evt_PlayerStreamOut
{
    TruckersMP_Player_Handle m_player;
} TruckersMP_Evt_PlayerStreamOut;
TRUCKERSMP_ASSERT_SIZE( TruckersMP_Evt_PlayerStreamOut, 8 );
TRUCKERSMP_ASSERT_OFFSET( TruckersMP_Evt_PlayerStreamOut, m_player, 0 );

#define TRUCKERSMP_EVT_PLAYER_UPDATE 0x09ebefe5c501cbdbull

typedef struct TruckersMP_Evt_PlayerUpdate
{
    TruckersMP_Player_Handle m_player;
} TruckersMP_Evt_PlayerUpdate;
TRUCKERSMP_ASSERT_SIZE( TruckersMP_Evt_PlayerUpdate, 8 );
TRUCKERSMP_ASSERT_OFFSET( TruckersMP_Evt_PlayerUpdate, m_player, 0 );

#define TRUCKERSMP_API_RENDER 0xe679194985c097e0ull

typedef struct TruckersMP_Render
{
    bool( TMP_API *GetRendererID )( TruckersMP_PluginContext *ctx, TruckersMP_RendererID *out );
    bool( TMP_API *GetDeviceHandle )( TruckersMP_PluginContext *ctx, uint64_t *out );
} TruckersMP_Render;

#define TRUCKERSMP_EVT_RENDER_PRE_RENDER 0x62b8aff307976b31ull

#define TRUCKERSMP_EVT_RENDER_POST_RENDER 0xe4c430a67c63b3beull

#define TRUCKERSMP_API_TRAILER 0x461d88c963294b9dull

typedef struct TruckersMP_Trailer
{
    bool( TMP_API *Exists )( TruckersMP_PluginContext *ctx, TruckersMP_Trailer_Handle self, bool *out );
    bool( TMP_API *GetPlacement )( TruckersMP_PluginContext *ctx, TruckersMP_Trailer_Handle self, TruckersMP_Placement *out );
    bool( TMP_API *GetLinearVelocity )( TruckersMP_PluginContext *ctx, TruckersMP_Trailer_Handle self, TruckersMP_Float3 *out );
    bool( TMP_API *GetAngularVelocity )( TruckersMP_PluginContext *ctx, TruckersMP_Trailer_Handle self, TruckersMP_Float3 *out );
    bool( TMP_API *GetBoundingBox )( TruckersMP_PluginContext *ctx, TruckersMP_Trailer_Handle self, TruckersMP_Bounds *out );
} TruckersMP_Trailer;

#define TRUCKERSMP_EVT_TRAILER_SPAWNED 0xce6ca9d0cc8edb21ull

typedef struct TruckersMP_Evt_TrailerSpawned
{
    TruckersMP_Player_Handle m_player;
    TruckersMP_Trailer_Handle m_trailer;
} TruckersMP_Evt_TrailerSpawned;
TRUCKERSMP_ASSERT_SIZE( TruckersMP_Evt_TrailerSpawned, 16 );
TRUCKERSMP_ASSERT_OFFSET( TruckersMP_Evt_TrailerSpawned, m_player, 0 );
TRUCKERSMP_ASSERT_OFFSET( TruckersMP_Evt_TrailerSpawned, m_trailer, 8 );

#define TRUCKERSMP_EVT_TRAILER_DESPAWNED 0x35dd228cb00e9f5dull

typedef struct TruckersMP_Evt_TrailerDespawned
{
    TruckersMP_Player_Handle m_player;
    TruckersMP_Trailer_Handle m_trailer;
} TruckersMP_Evt_TrailerDespawned;
TRUCKERSMP_ASSERT_SIZE( TruckersMP_Evt_TrailerDespawned, 16 );
TRUCKERSMP_ASSERT_OFFSET( TruckersMP_Evt_TrailerDespawned, m_player, 0 );
TRUCKERSMP_ASSERT_OFFSET( TruckersMP_Evt_TrailerDespawned, m_trailer, 8 );

#define TRUCKERSMP_API_USER_INTERFACE 0xa034f7c6420eb5d2ull

typedef struct TruckersMP_UserInterface
{
    TruckersMP_EResult( TMP_API *ShowNotification )( TruckersMP_PluginContext *ctx, TruckersMP_NotificationType type, TruckersMP_String message );
} TruckersMP_UserInterface;

#define TRUCKERSMP_API_VEHICLE 0x246b095f10333d2full

typedef struct TruckersMP_Vehicle
{
    bool( TMP_API *GetTrailer )( TruckersMP_PluginContext *ctx, TruckersMP_Vehicle_Handle self, TruckersMP_Trailer_Handle *out );
    bool( TMP_API *GetPlacement )( TruckersMP_PluginContext *ctx, TruckersMP_Vehicle_Handle self, TruckersMP_Placement *out );
    bool( TMP_API *GetLinearVelocity )( TruckersMP_PluginContext *ctx, TruckersMP_Vehicle_Handle self, TruckersMP_Float3 *out );
    bool( TMP_API *GetAngularVelocity )( TruckersMP_PluginContext *ctx, TruckersMP_Vehicle_Handle self, TruckersMP_Float3 *out );
    bool( TMP_API *GetBoundingBox )( TruckersMP_PluginContext *ctx, TruckersMP_Vehicle_Handle self, TruckersMP_Bounds *out );
} TruckersMP_Vehicle;

#define TRUCKERSMP_EVT_VEHICLE_SPAWNED 0x2e257d71ce258fe1ull

typedef struct TruckersMP_Evt_VehicleSpawned
{
    TruckersMP_Player_Handle m_player;
    TruckersMP_Vehicle_Handle m_vehicle;
} TruckersMP_Evt_VehicleSpawned;
TRUCKERSMP_ASSERT_SIZE( TruckersMP_Evt_VehicleSpawned, 16 );
TRUCKERSMP_ASSERT_OFFSET( TruckersMP_Evt_VehicleSpawned, m_player, 0 );
TRUCKERSMP_ASSERT_OFFSET( TruckersMP_Evt_VehicleSpawned, m_vehicle, 8 );

#define TRUCKERSMP_EVT_VEHICLE_DESPAWNED 0x2a819837892862cdull

typedef struct TruckersMP_Evt_VehicleDespawned
{
    TruckersMP_Player_Handle m_player;
    TruckersMP_Vehicle_Handle m_vehicle;
} TruckersMP_Evt_VehicleDespawned;
TRUCKERSMP_ASSERT_SIZE( TruckersMP_Evt_VehicleDespawned, 16 );
TRUCKERSMP_ASSERT_OFFSET( TruckersMP_Evt_VehicleDespawned, m_player, 0 );
TRUCKERSMP_ASSERT_OFFSET( TruckersMP_Evt_VehicleDespawned, m_vehicle, 8 );

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* TMP_SDK_H */

/* eof */
