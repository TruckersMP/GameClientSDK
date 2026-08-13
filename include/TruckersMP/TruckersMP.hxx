/* Generated file. Do not edit. */

#pragma once

#include "TruckersMP/TruckersMP.h"
#include "TruckersMP/TruckersMP_Runtime.hxx"

#include <memory>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace TruckersMP
{

/// @brief Result codes returned by every SDK action.
enum class Result : Int32
{
    /// @brief The operation succeeded.
    Ok = TruckersMP_Result_Ok,

    /// @brief The client failed internally; check the client log.
    InternalError = TruckersMP_Result_InternalError,

    /// @brief A parameter was missing or malformed.
    InvalidParameter = TruckersMP_Result_InvalidParameter,

    /// @brief Called on a wrong thread (usually off the main thread).
    WrongThread = TruckersMP_Result_WrongThread,

    /// @brief The client cannot serve the request; the declared SDK version
    /// is either newer than the client, or the API member was retired.
    NotSupported = TruckersMP_Result_NotSupported,

    /// @brief The plugin does not hold the required intent.
    NotAuthorized = TruckersMP_Result_NotAuthorized,

    /// @brief The event ID is not known to this client.
    UnknownEvent = TruckersMP_Result_UnknownEvent,

    /// @brief No world or service can answer right now (e.g., not in-game).
    ServiceUnavailable = TruckersMP_Result_ServiceUnavailable,

    /// @brief A chat command with this name is already registered.
    ChatCommandAlreadyRegistered = TruckersMP_Result_ChatCommandAlreadyRegistered,

    /// @brief A chat command with this name is not registered.
    ChatCommandNotRegistered = TruckersMP_Result_ChatCommandNotRegistered,
};

/// @brief Severity for LogMessage.
enum class LogLevel : Int32
{
    Info = TruckersMP_LogLevel_Info,
    Warning = TruckersMP_LogLevel_Warning,
    Error = TruckersMP_LogLevel_Error,
};

/// @brief Mouse button identifiers.
enum class MouseButton : Int32
{
    /// @brief Left mouse button.
    Left = TruckersMP_MouseButton_Left,

    /// @brief Right mouse button.
    Right = TruckersMP_MouseButton_Right,

    /// @brief Middle mouse button.
    Middle = TruckersMP_MouseButton_Middle,
};

/// @brief Which graphics backend the client is running on.
enum class RendererID : Int32
{
    /// @brief OpenGL
    OpenGL = TruckersMP_RendererID_OpenGL,

    /// @brief DirectX 11
    DirectX11 = TruckersMP_RendererID_DirectX11,
};

/// @brief Visual style of an in-game notification.
enum class NotificationType : Int32
{
    /// @brief Normal notification.
    Normal = TruckersMP_NotificationType_Normal,

    /// @brief Warning notification.
    Warning = TruckersMP_NotificationType_Warning,

    /// @brief Error notification.
    Error = TruckersMP_NotificationType_Error,

    /// @brief Success notification.
    Success = TruckersMP_NotificationType_Success,
};

/// @brief 3-component vector.
using Float3 = TruckersMP_Float3;

/// @brief 3-component vector.
using Double3 = TruckersMP_Double3;

/// @brief A quaternion representing a 3D rotation.
using Quaternion = TruckersMP_Quaternion;

/// @brief A position and rotation in world space.
using Placement = TruckersMP_Placement;

/// @brief A color with red, green, blue, and alpha channels.
using Color = TruckersMP_Color;

/// @brief One mounted content package.
/// @note An owning value copy of one TruckersMP_PackageInfo list element.
struct PackageInfo
{
    /// @brief The file name of the package (e.g., "accessory_pack.mp").
    std::string name;
};

class Session;

class Player;
class Trailer;
class Vehicle;

/// @brief Opaque reference to a player.
///
/// The handle is valid as long as the player is streaming in.
class Player final
{
public:
    Player() = default;
    Player( Session *owner, TruckersMP_Player_Handle handle ) : m_session( owner ), m_handle( handle ) {}

    Bool IsValid() const { return m_session != nullptr && m_handle.m_value != 0; }
    TruckersMP_Player_Handle RawHandle() const { return m_handle; }

    /// @brief Player's entity ID.
    std::optional< Int32 > GetPlayerID() const;

    /// @brief TruckersMP account ID.
    std::optional< Uint64 > GetAccountID() const;

    /// @brief Steam account ID.
    std::optional< Uint64 > GetSteamID() const;

    /// @brief UTF-8 player's display name, allocated by the client.
    std::optional< std::string > GetUsername() const;

    /// @brief Text of the player's tag that is displayed in front of their name.
    std::optional< std::string > GetTagText() const;

    /// @brief Color of the player's tag that is displayed in front of their name.
    std::optional< Color > GetTagColor() const;

    /// @brief The player has a Patreon tier that qualifies for in-game rewards.
    std::optional< Bool > IsPatron() const;

    /// @brief The player is a game moderator.
    ///
    /// This is true when the user has permission for moderation tools, regardless
    /// of whether the moderator is authorized.
    std::optional< Bool > IsGameModerator() const;

    /// @brief The player is a part of the TruckersMP team.
    std::optional< Bool > IsTeamMember() const;

    /// @brief The player is a part of the TruckersMP management.
    std::optional< Bool > IsManager() const;

    /// @brief The player's camera position can drive streaming.
    ///
    /// Normally players stream in around their vehicle, so moving the camera away
    /// shows an empty world. With this right, the camera itself is the streaming
    /// anchor; teleport it elsewhere and entities will stream in around it.
    std::optional< Bool > CanStreamFromCamera() const;

    /// @brief The player is streaming from their camera position.
    ///
    /// This is true regardless of the user using the developer camera or not.
    std::optional< Bool > StreamsFromCamera() const;

    /// @brief Get the network latency (in ms) between the player and the game server.
    std::optional< Uint16 > GetNetworkLatency() const;

    /// @brief Obtain the vehicle the player is currently driving.
    std::optional< Vehicle > GetVehicle() const;

    /// @brief Obtain the trailer the player is currently towing.
    std::optional< Trailer > GetTrailer() const;

    /// @brief The distance between the player's and local player's vehicle (in meters).
    std::optional< Float > GetDistanceFromLocalPlayer() const;

    /// @brief The distance between the player's vehicle and client's active camera (in meters).
    std::optional< Float > GetDistanceToCamera() const;

    /// @brief Whether the collisions between the given player's and local player's vehicles are enabled.
    std::optional< Bool > CanCollideWith( const Player &player ) const;

private:
    Session *m_session = nullptr;
    TruckersMP_Player_Handle m_handle{};
};

/// @brief Opaque reference to a trailer.
///
/// The handle is valid as long as the trailer is present in the game world.
class Trailer final
{
public:
    Trailer() = default;
    Trailer( Session *owner, TruckersMP_Trailer_Handle handle ) : m_session( owner ), m_handle( handle ) {}

    Bool IsValid() const { return m_session != nullptr && m_handle.m_value != 0; }
    TruckersMP_Trailer_Handle RawHandle() const { return m_handle; }

    /// @brief Whether the trailer is currently present in the game world.
    std::optional< Bool > Exists() const;

    /// @brief Trailer's position and rotation in world space.
    std::optional< Placement > GetPlacement() const;

    /// @brief Obtain trailer's linear velocity in world space, in meters per second.
    std::optional< Float3 > GetLinearVelocity() const;

    /// @brief Obtain trailer's angular velocity in world space, in radians per second.
    std::optional< Float3 > GetAngularVelocity() const;

private:
    Session *m_session = nullptr;
    TruckersMP_Trailer_Handle m_handle{};
};

/// @brief Opaque reference to a vehicle.
///
/// The handle is valid as long as the vehicle is present in the game world.
class Vehicle final
{
public:
    Vehicle() = default;
    Vehicle( Session *owner, TruckersMP_Vehicle_Handle handle ) : m_session( owner ), m_handle( handle ) {}

    Bool IsValid() const { return m_session != nullptr && m_handle.m_value != 0; }
    TruckersMP_Vehicle_Handle RawHandle() const { return m_handle; }

    /// @brief Obtain the trailer that is currently attached to this vehicle, if any.
    std::optional< Trailer > GetTrailer() const;

    /// @brief Vehicle's position and rotation in world space.
    std::optional< Placement > GetPlacement() const;

    /// @brief Obtain vehicle's linear velocity in world space, in meters per second.
    std::optional< Float3 > GetLinearVelocity() const;

    /// @brief Obtain vehicle's angular velocity in world space, in radians per second.
    std::optional< Float3 > GetAngularVelocity() const;

private:
    Session *m_session = nullptr;
    TruckersMP_Vehicle_Handle m_handle{};
};

class GameplayNoCollisionZoneEvent final
{
public:
    GameplayNoCollisionZoneEvent( Session *owner, TruckersMP_Evt_GameplayNoCollisionZone *payload ) : m_session( owner ), m_payload( payload ) {}

    bool GetEntered() const { return m_payload->m_entered; }

private:
    Session *m_session;
    TruckersMP_Evt_GameplayNoCollisionZone *m_payload;
};

class InputKeyEvent final
{
public:
    InputKeyEvent( Session *owner, TruckersMP_Evt_InputKey *payload ) : m_session( owner ), m_payload( payload ) {}

    /// @brief The virtual-key code of the key.
    Uint8 GetKey() const { return m_payload->m_key; }

    /// @brief Message flags coming from the OS.
    Uint16 GetFlags() const { return m_payload->m_flags; }

    /// @brief True if the key was pressed, false if released.
    bool GetDown() const { return m_payload->m_down; }

private:
    Session *m_session;
    TruckersMP_Evt_InputKey *m_payload;
};

class InputCharEvent final
{
public:
    InputCharEvent( Session *owner, TruckersMP_Evt_InputChar *payload ) : m_session( owner ), m_payload( payload ) {}

    /// @brief The UTF-32 codepoint of the character that was typed.
    Uint32 GetCharacter() const { return m_payload->m_character; }

private:
    Session *m_session;
    TruckersMP_Evt_InputChar *m_payload;
};

class InputMouseMoveEvent final
{
public:
    InputMouseMoveEvent( Session *owner, TruckersMP_Evt_InputMouseMove *payload ) : m_session( owner ), m_payload( payload ) {}

    Int32 GetX() const { return m_payload->m_x; }
    Int32 GetY() const { return m_payload->m_y; }

private:
    Session *m_session;
    TruckersMP_Evt_InputMouseMove *m_payload;
};

class InputMouseWheelEvent final
{
public:
    InputMouseWheelEvent( Session *owner, TruckersMP_Evt_InputMouseWheel *payload ) : m_session( owner ), m_payload( payload ) {}

    /// @brief The number of notches scrolled. Positive for forward, negative for backward.
    Int32 GetDelta() const { return m_payload->m_delta; }

private:
    Session *m_session;
    TruckersMP_Evt_InputMouseWheel *m_payload;
};

class InputMouseButtonEvent final
{
public:
    InputMouseButtonEvent( Session *owner, TruckersMP_Evt_InputMouseButton *payload ) : m_session( owner ), m_payload( payload ) {}

    MouseButton GetButton() const { return static_cast< MouseButton >( m_payload->m_button ); }

    bool GetDown() const { return m_payload->m_down; }

    /// @brief Set to true to block the click from reaching the client.
    bool GetBlock() const { return m_payload->m_block; }
    void SetBlock( bool value ) { m_payload->m_block = value; }

private:
    Session *m_session;
    TruckersMP_Evt_InputMouseButton *m_payload;
};

class PlayerStreamInEvent final
{
public:
    PlayerStreamInEvent( Session *owner, TruckersMP_Evt_PlayerStreamIn *payload ) : m_session( owner ), m_payload( payload ) {}

    Player GetPlayer() const { return Player( m_session, m_payload->m_player ); }

private:
    Session *m_session;
    TruckersMP_Evt_PlayerStreamIn *m_payload;
};

class PlayerStreamOutEvent final
{
public:
    PlayerStreamOutEvent( Session *owner, TruckersMP_Evt_PlayerStreamOut *payload ) : m_session( owner ), m_payload( payload ) {}

    Player GetPlayer() const { return Player( m_session, m_payload->m_player ); }

private:
    Session *m_session;
    TruckersMP_Evt_PlayerStreamOut *m_payload;
};

class PlayerUpdateEvent final
{
public:
    PlayerUpdateEvent( Session *owner, TruckersMP_Evt_PlayerUpdate *payload ) : m_session( owner ), m_payload( payload ) {}

    Player GetPlayer() const { return Player( m_session, m_payload->m_player ); }

private:
    Session *m_session;
    TruckersMP_Evt_PlayerUpdate *m_payload;
};

class TrailerSpawnedEvent final
{
public:
    TrailerSpawnedEvent( Session *owner, TruckersMP_Evt_TrailerSpawned *payload ) : m_session( owner ), m_payload( payload ) {}

    Player GetPlayer() const { return Player( m_session, m_payload->m_player ); }
    Trailer GetTrailer() const { return Trailer( m_session, m_payload->m_trailer ); }

private:
    Session *m_session;
    TruckersMP_Evt_TrailerSpawned *m_payload;
};

class TrailerDespawnedEvent final
{
public:
    TrailerDespawnedEvent( Session *owner, TruckersMP_Evt_TrailerDespawned *payload ) : m_session( owner ), m_payload( payload ) {}

    Player GetPlayer() const { return Player( m_session, m_payload->m_player ); }
    Trailer GetTrailer() const { return Trailer( m_session, m_payload->m_trailer ); }

private:
    Session *m_session;
    TruckersMP_Evt_TrailerDespawned *m_payload;
};

class VehicleSpawnedEvent final
{
public:
    VehicleSpawnedEvent( Session *owner, TruckersMP_Evt_VehicleSpawned *payload ) : m_session( owner ), m_payload( payload ) {}

    Player GetPlayer() const { return Player( m_session, m_payload->m_player ); }
    Vehicle GetVehicle() const { return Vehicle( m_session, m_payload->m_vehicle ); }

private:
    Session *m_session;
    TruckersMP_Evt_VehicleSpawned *m_payload;
};

class VehicleDespawnedEvent final
{
public:
    VehicleDespawnedEvent( Session *owner, TruckersMP_Evt_VehicleDespawned *payload ) : m_session( owner ), m_payload( payload ) {}

    Player GetPlayer() const { return Player( m_session, m_payload->m_player ); }
    Vehicle GetVehicle() const { return Vehicle( m_session, m_payload->m_vehicle ); }

private:
    Session *m_session;
    TruckersMP_Evt_VehicleDespawned *m_payload;
};

/// @brief Core services: plugin management, logging, and basic client information.
class CoreModule final
{
public:
    Bool IsAvailable() const { return m_coreTable != nullptr; }

    /// @brief Write a line to the client log, attributed to the calling plugin.
    Result LogMessage( LogLevel level, std::string_view text );

    /// @brief Obtain the Steam ID of the current game.
    std::optional< std::string > GameID() const;

    /// @brief Obtain the current release tag of the game client.
    std::optional< std::string > ClientVersion() const;

private:
    void SessionFree( const void *ptr ) const;

    const TruckersMP_Core *m_coreTable = nullptr;
    TruckersMP_PluginContext *m_ctx = nullptr;
    Session *m_session = nullptr;

private:
    friend class Session;
};

/// @brief Local account service.
///
/// The account data is generally available throughout the session (as plugins are
/// initialized after the login screen) unless the user logs out, for instance, by
/// going back to the title screen and switching servers.
class AccountModule final
{
public:
    Bool IsAvailable() const { return m_accountsTable != nullptr; }

    /// @brief TruckersMP account ID.
    std::optional< Uint64 > GetAccountID() const;

    /// @brief The player is a game moderator.
    std::optional< Bool > IsGameModerator() const;

    /// @brief The player is a part of the TruckersMP team.
    std::optional< Bool > IsTeamMember() const;

    /// @brief The player has a Patreon tier that qualifies for in-game rewards.
    std::optional< Bool > IsPatron() const;

    /// @brief ID of the virtual company the player is a part of.
    std::optional< Uint64 > GetCompanyID() const;

private:
    void SessionFree( const void *ptr ) const;

    const TruckersMP_Accounts *m_accountsTable = nullptr;
    TruckersMP_PluginContext *m_ctx = nullptr;
    Session *m_session = nullptr;

private:
    friend class Session;
};

class GameplayModule final
{
public:
    Bool IsAvailable() const { return m_gameplayTable != nullptr; }

    /// @brief Obtain a list of all packages currently mounted in the game.
    ///
    /// The list is ordered by mount time, with the most recently mounted package
    /// at the end of the list. This list contains only TruckersMP packages.
    std::optional< std::vector< PackageInfo > > GetMountedPackages() const;

public:
    /// @brief The local player entered or left a no-collision zone.
    Event< GameplayNoCollisionZoneEvent & > OnNoCollisionZone;

private:
    void SessionFree( const void *ptr ) const;

    const TruckersMP_Gameplay *m_gameplayTable = nullptr;
    TruckersMP_PluginContext *m_ctx = nullptr;
    Session *m_session = nullptr;

private:
    friend class Session;
};

class InputModule final
{
public:
    Bool IsAvailable() const { return m_inputTable != nullptr; }

    /// @brief Whether the mouse cursor is currently visible on the screen.
    std::optional< Bool > IsMouseVisible() const;

    /// @brief Ask for the mouse cursor.
    ///
    /// Pair every call with DecreaseMouseRef to release the mouse cursor when done.
    /// Otherwise, the cursor stays up for the rest of the session.
    Result IncreaseMouseRef();

    /// @brief Give up one earlier IncreaseMouseRef.
    Result DecreaseMouseRef();

    /// @brief Whether the game mouse input is currently blocked.
    std::optional< Bool > IsGameMouseLocked() const;

    /// @brief Lock the game mouse input.
    Result SetGameMouseLocked( Bool locked );

    /// @brief Whether the game keyboard input is currently blocked.
    std::optional< Bool > IsGameKeyboardLocked() const;

    /// @brief Lock the game keyboard input.
    Result SetGameKeyboardLocked( Bool locked );

public:
    /// @brief A key was pressed or released.
    Event< InputKeyEvent & > OnKey;

    /// @brief A character was typed.
    Event< InputCharEvent & > OnChar;

    /// @brief The mouse moved on the screen. Coordinates are client-relative.
    Event< InputMouseMoveEvent & > OnMouseMove;

    /// @brief The mouse wheel was scrolled.
    Event< InputMouseWheelEvent & > OnMouseWheel;

    /// @brief A mouse button went down or came up.
    Event< InputMouseButtonEvent & > OnMouseButton;

private:
    void SessionFree( const void *ptr ) const;

    const TruckersMP_Input *m_inputTable = nullptr;
    TruckersMP_PluginContext *m_ctx = nullptr;
    Session *m_session = nullptr;

private:
    friend class Session;
};

class NetworkModule final
{
public:
    Bool IsAvailable() const { return m_networkTable != nullptr; }

    /// @brief True if the game client is connected to a server.
    std::optional< Bool > IsConnected() const;

    /// @brief Returns the last ping time between the local client and the game server.
    std::optional< Uint16 > GetLastPing() const;

    /// @brief Obtain the game server's ID.
    std::optional< Uint64 > GetGameServerID() const;

public:
    /// @brief The connection with the server has been successfully established.
    Event<> OnConnected;

    /// @brief The client left the server.
    Event<> OnDisconnected;

private:
    void SessionFree( const void *ptr ) const;

    const TruckersMP_Network *m_networkTable = nullptr;
    TruckersMP_PluginContext *m_ctx = nullptr;
    Session *m_session = nullptr;

private:
    friend class Session;
};

class PlayerModule final
{
public:
    Bool IsAvailable() const { return m_playersTable != nullptr && m_playerHandleTable != nullptr; }

    /// @brief The local player. Absent while the client is not connected to a server.
    std::optional< Player > GetLocalPlayer() const;

    /// @brief The player with the given entity ID. Absent while no such player is streamed in.
    std::optional< Player > GetPlayerByID( Int32 id ) const;

    /// @brief Every player currently streamed in to the client.
    std::optional< std::vector< Player > > GetAllPlayers() const;

public:
    /// @brief The player has entered the client's streaming range.
    ///
    /// This is the first time the client has received a full update for this
    /// player, and the player is now visible in the game world.
    Event< PlayerStreamInEvent & > OnStreamIn;

    /// @brief The player has left the client's streaming range.
    ///
    /// The client will no longer receive updates for this player, and the player
    /// is no longer visible in the game world.
    Event< PlayerStreamOutEvent & > OnStreamOut;

    /// @brief The client has received an update for a player.
    ///
    /// This is raised at network rate, so read it and return; do not call back
    /// into the SDK from here, and avoid executing any heavy logic. Use the data
    /// to update your own state, and act on it in your own update loop.
    Event< PlayerUpdateEvent & > OnUpdate;

private:
    void SessionFree( const void *ptr ) const;

    const TruckersMP_Players *m_playersTable = nullptr;
    const TruckersMP_PlayerHandle *m_playerHandleTable = nullptr;
    TruckersMP_PluginContext *m_ctx = nullptr;
    Session *m_session = nullptr;

private:
    friend class Session;
    friend class Player;
};

/// @brief The client's renderer and its frame boundaries.
class RenderModule final
{
public:
    Bool IsAvailable() const { return m_renderTable != nullptr; }

    std::optional< RendererID > GetRendererID() const;

    /// @brief The backend device as an address. Cast it per the renderer:
    ///
    /// - OpenGL has none and reports 0
    /// - DirectX11 gives an ID3D11Device *
    std::optional< Uint64 > GetDeviceHandle() const;

public:
    /// @brief The client is about to draw a frame.
    Event<> OnPreRender;

    /// @brief The client finished drawing a frame.
    ///
    /// Overlay drawing belongs here, after the game's own output.
    Event<> OnPostRender;

private:
    void SessionFree( const void *ptr ) const;

    const TruckersMP_Render *m_renderTable = nullptr;
    TruckersMP_PluginContext *m_ctx = nullptr;
    Session *m_session = nullptr;

private:
    friend class Session;
};

class TrailerModule final
{
public:
    Bool IsAvailable() const { return m_trailerTable != nullptr; }

public:
    /// @brief A trailer has spawned in the game world.
    Event< TrailerSpawnedEvent & > OnSpawned;

    /// @brief A trailer has despawned from the game world.
    Event< TrailerDespawnedEvent & > OnDespawned;

private:
    void SessionFree( const void *ptr ) const;

    const TruckersMP_Trailer *m_trailerTable = nullptr;
    TruckersMP_PluginContext *m_ctx = nullptr;
    Session *m_session = nullptr;

private:
    friend class Session;
    friend class Trailer;
};

class UserInterfaceModule final
{
public:
    Bool IsAvailable() const { return m_userInterfaceTable != nullptr; }

    /// @brief Show a notification on the screen.
    ///
    /// The notification will be shown for a few seconds and then disappear.
    ///
    /// The maximum length of the message is 200 characters.
    Result ShowNotification( NotificationType type, std::string_view message );

private:
    void SessionFree( const void *ptr ) const;

    const TruckersMP_UserInterface *m_userInterfaceTable = nullptr;
    TruckersMP_PluginContext *m_ctx = nullptr;
    Session *m_session = nullptr;

private:
    friend class Session;
};

class VehicleModule final
{
public:
    Bool IsAvailable() const { return m_vehicleTable != nullptr; }

public:
    /// @brief A vehicle has spawned in the game world.
    Event< VehicleSpawnedEvent & > OnSpawned;

    /// @brief A vehicle has despawned from the game world.
    Event< VehicleDespawnedEvent & > OnDespawned;

private:
    void SessionFree( const void *ptr ) const;

    const TruckersMP_Vehicle *m_vehicleTable = nullptr;
    TruckersMP_PluginContext *m_ctx = nullptr;
    Session *m_session = nullptr;

private:
    friend class Session;
    friend class Vehicle;
};

class Session final
{
public:
    ~Session();
    Session( const Session & ) = delete;
    Session &operator=( const Session & ) = delete;

    /**
     * Establish the SDK connection.
     *
     * @return nullptr when the host is incompatible or the core API is unavailable.
     */
    static std::unique_ptr< Session > Create( const TruckersMP_Host *host );

    CoreModule &Core() { return m_core; }
    AccountModule &Account() { return m_account; }
    GameplayModule &Gameplay() { return m_gameplay; }
    InputModule &Input() { return m_input; }
    NetworkModule &Network() { return m_network; }
    PlayerModule &Player() { return m_player; }
    RenderModule &Render() { return m_render; }
    TrailerModule &Trailer() { return m_trailer; }
    UserInterfaceModule &UserInterface() { return m_user_interface; }
    VehicleModule &Vehicle() { return m_vehicle; }

    /// @brief Extension SPI; used by add-on module wrappers (intent packages).
    const void *GetRawApi( uint64_t apiId ) const;

    Result AddRawListener( uint64_t eventId, TruckersMP_EventFn fn, void *userCtx );
    Result RemoveRawListener( uint64_t eventId, TruckersMP_EventFn fn, void *userCtx );
    Result RawUnlockIntent( std::string_view key );

    /// @brief Extension SPI; an attached add-on module registers a hook the
    /// session invokes on destruction, so modules may outlive the session.
    void AddRawDetachHook( void *owner, void ( *fn )( void * ) );
    void RemoveRawDetachHook( void *owner );

    TruckersMP_PluginContext *RawCtx() const { return m_ctx; }

    void RawFree( const void *ptr ) const;

private:
    Session() = default;

    TruckersMP_PluginContext *m_ctx = nullptr;

    const void *( TMP_API *m_getApi )( TruckersMP_PluginContext *, uint64_t ) = nullptr;
    void( TMP_API *m_free )( TruckersMP_PluginContext *, void * ) = nullptr;

    struct DetachHook
    {
        void *m_owner;
        void ( *m_fn )( void * );
    };
    std::vector< DetachHook > m_detachHooks;

    CoreModule m_core;
    AccountModule m_account;
    GameplayModule m_gameplay;
    InputModule m_input;
    NetworkModule m_network;
    PlayerModule m_player;
    RenderModule m_render;
    TrailerModule m_trailer;
    UserInterfaceModule m_user_interface;
    VehicleModule m_vehicle;
};

inline std::optional< Int32 > Player::GetPlayerID() const
{
    if( !IsValid() ) {
        return std::nullopt;
    }
    const PlayerModule &module = m_session->Player();
    if( module.m_playerHandleTable == nullptr ) {
        return std::nullopt;
    }
    Int32 native;
    if( !module.m_playerHandleTable->GetPlayerID( module.m_ctx, m_handle, &native ) ) {
        return std::nullopt;
    }
    return native;
}

inline std::optional< Uint64 > Player::GetAccountID() const
{
    if( !IsValid() ) {
        return std::nullopt;
    }
    const PlayerModule &module = m_session->Player();
    if( module.m_playerHandleTable == nullptr ) {
        return std::nullopt;
    }
    Uint64 native;
    if( !module.m_playerHandleTable->GetAccountID( module.m_ctx, m_handle, &native ) ) {
        return std::nullopt;
    }
    return native;
}

inline std::optional< Uint64 > Player::GetSteamID() const
{
    if( !IsValid() ) {
        return std::nullopt;
    }
    const PlayerModule &module = m_session->Player();
    if( module.m_playerHandleTable == nullptr ) {
        return std::nullopt;
    }
    Uint64 native;
    if( !module.m_playerHandleTable->GetSteamID( module.m_ctx, m_handle, &native ) ) {
        return std::nullopt;
    }
    return native;
}

inline std::optional< std::string > Player::GetUsername() const
{
    if( !IsValid() ) {
        return std::nullopt;
    }
    const PlayerModule &module = m_session->Player();
    if( module.m_playerHandleTable == nullptr ) {
        return std::nullopt;
    }
    TruckersMP_String native;
    if( !module.m_playerHandleTable->GetUsername( module.m_ctx, m_handle, &native ) ) {
        return std::nullopt;
    }
    std::string value( native.m_ptr, native.m_size );
    m_session->RawFree( native.m_ptr );
    return value;
}

inline std::optional< std::string > Player::GetTagText() const
{
    if( !IsValid() ) {
        return std::nullopt;
    }
    const PlayerModule &module = m_session->Player();
    if( module.m_playerHandleTable == nullptr ) {
        return std::nullopt;
    }
    TruckersMP_String native;
    if( !module.m_playerHandleTable->GetTagText( module.m_ctx, m_handle, &native ) ) {
        return std::nullopt;
    }
    std::string value( native.m_ptr, native.m_size );
    m_session->RawFree( native.m_ptr );
    return value;
}

inline std::optional< Color > Player::GetTagColor() const
{
    if( !IsValid() ) {
        return std::nullopt;
    }
    const PlayerModule &module = m_session->Player();
    if( module.m_playerHandleTable == nullptr ) {
        return std::nullopt;
    }
    Color native;
    if( !module.m_playerHandleTable->GetTagColor( module.m_ctx, m_handle, &native ) ) {
        return std::nullopt;
    }
    return native;
}

inline std::optional< Bool > Player::IsPatron() const
{
    if( !IsValid() ) {
        return std::nullopt;
    }
    const PlayerModule &module = m_session->Player();
    if( module.m_playerHandleTable == nullptr ) {
        return std::nullopt;
    }
    bool native;
    if( !module.m_playerHandleTable->IsPatron( module.m_ctx, m_handle, &native ) ) {
        return std::nullopt;
    }
    return native;
}

inline std::optional< Bool > Player::IsGameModerator() const
{
    if( !IsValid() ) {
        return std::nullopt;
    }
    const PlayerModule &module = m_session->Player();
    if( module.m_playerHandleTable == nullptr ) {
        return std::nullopt;
    }
    bool native;
    if( !module.m_playerHandleTable->IsGameModerator( module.m_ctx, m_handle, &native ) ) {
        return std::nullopt;
    }
    return native;
}

inline std::optional< Bool > Player::IsTeamMember() const
{
    if( !IsValid() ) {
        return std::nullopt;
    }
    const PlayerModule &module = m_session->Player();
    if( module.m_playerHandleTable == nullptr ) {
        return std::nullopt;
    }
    bool native;
    if( !module.m_playerHandleTable->IsTeamMember( module.m_ctx, m_handle, &native ) ) {
        return std::nullopt;
    }
    return native;
}

inline std::optional< Bool > Player::IsManager() const
{
    if( !IsValid() ) {
        return std::nullopt;
    }
    const PlayerModule &module = m_session->Player();
    if( module.m_playerHandleTable == nullptr ) {
        return std::nullopt;
    }
    bool native;
    if( !module.m_playerHandleTable->IsManager( module.m_ctx, m_handle, &native ) ) {
        return std::nullopt;
    }
    return native;
}

inline std::optional< Bool > Player::CanStreamFromCamera() const
{
    if( !IsValid() ) {
        return std::nullopt;
    }
    const PlayerModule &module = m_session->Player();
    if( module.m_playerHandleTable == nullptr ) {
        return std::nullopt;
    }
    bool native;
    if( !module.m_playerHandleTable->CanStreamFromCamera( module.m_ctx, m_handle, &native ) ) {
        return std::nullopt;
    }
    return native;
}

inline std::optional< Bool > Player::StreamsFromCamera() const
{
    if( !IsValid() ) {
        return std::nullopt;
    }
    const PlayerModule &module = m_session->Player();
    if( module.m_playerHandleTable == nullptr ) {
        return std::nullopt;
    }
    bool native;
    if( !module.m_playerHandleTable->StreamsFromCamera( module.m_ctx, m_handle, &native ) ) {
        return std::nullopt;
    }
    return native;
}

inline std::optional< Uint16 > Player::GetNetworkLatency() const
{
    if( !IsValid() ) {
        return std::nullopt;
    }
    const PlayerModule &module = m_session->Player();
    if( module.m_playerHandleTable == nullptr ) {
        return std::nullopt;
    }
    Uint16 native;
    if( !module.m_playerHandleTable->GetNetworkLatency( module.m_ctx, m_handle, &native ) ) {
        return std::nullopt;
    }
    return native;
}

inline std::optional< Vehicle > Player::GetVehicle() const
{
    if( !IsValid() ) {
        return std::nullopt;
    }
    const PlayerModule &module = m_session->Player();
    if( module.m_playerHandleTable == nullptr ) {
        return std::nullopt;
    }
    TruckersMP_Vehicle_Handle native;
    if( !module.m_playerHandleTable->GetVehicle( module.m_ctx, m_handle, &native ) ) {
        return std::nullopt;
    }
    return Vehicle( m_session, native );
}

inline std::optional< Trailer > Player::GetTrailer() const
{
    if( !IsValid() ) {
        return std::nullopt;
    }
    const PlayerModule &module = m_session->Player();
    if( module.m_playerHandleTable == nullptr ) {
        return std::nullopt;
    }
    TruckersMP_Trailer_Handle native;
    if( !module.m_playerHandleTable->GetTrailer( module.m_ctx, m_handle, &native ) ) {
        return std::nullopt;
    }
    return Trailer( m_session, native );
}

inline std::optional< Float > Player::GetDistanceFromLocalPlayer() const
{
    if( !IsValid() ) {
        return std::nullopt;
    }
    const PlayerModule &module = m_session->Player();
    if( module.m_playerHandleTable == nullptr ) {
        return std::nullopt;
    }
    Float native;
    if( !module.m_playerHandleTable->GetDistanceFromLocalPlayer( module.m_ctx, m_handle, &native ) ) {
        return std::nullopt;
    }
    return native;
}

inline std::optional< Float > Player::GetDistanceToCamera() const
{
    if( !IsValid() ) {
        return std::nullopt;
    }
    const PlayerModule &module = m_session->Player();
    if( module.m_playerHandleTable == nullptr ) {
        return std::nullopt;
    }
    Float native;
    if( !module.m_playerHandleTable->GetDistanceToCamera( module.m_ctx, m_handle, &native ) ) {
        return std::nullopt;
    }
    return native;
}

inline std::optional< Bool > Player::CanCollideWith( const Player &player ) const
{
    if( !IsValid() ) {
        return std::nullopt;
    }
    const PlayerModule &module = m_session->Player();
    if( module.m_playerHandleTable == nullptr ) {
        return std::nullopt;
    }
    bool native;
    if( !module.m_playerHandleTable->CanCollideWith( module.m_ctx, m_handle, player.RawHandle(), &native ) ) {
        return std::nullopt;
    }
    return native;
}

inline std::optional< Bool > Trailer::Exists() const
{
    if( !IsValid() ) {
        return std::nullopt;
    }
    const TrailerModule &module = m_session->Trailer();
    if( module.m_trailerTable == nullptr ) {
        return std::nullopt;
    }
    bool native;
    if( !module.m_trailerTable->Exists( module.m_ctx, m_handle, &native ) ) {
        return std::nullopt;
    }
    return native;
}

inline std::optional< Placement > Trailer::GetPlacement() const
{
    if( !IsValid() ) {
        return std::nullopt;
    }
    const TrailerModule &module = m_session->Trailer();
    if( module.m_trailerTable == nullptr ) {
        return std::nullopt;
    }
    Placement native;
    if( !module.m_trailerTable->GetPlacement( module.m_ctx, m_handle, &native ) ) {
        return std::nullopt;
    }
    return native;
}

inline std::optional< Float3 > Trailer::GetLinearVelocity() const
{
    if( !IsValid() ) {
        return std::nullopt;
    }
    const TrailerModule &module = m_session->Trailer();
    if( module.m_trailerTable == nullptr ) {
        return std::nullopt;
    }
    Float3 native;
    if( !module.m_trailerTable->GetLinearVelocity( module.m_ctx, m_handle, &native ) ) {
        return std::nullopt;
    }
    return native;
}

inline std::optional< Float3 > Trailer::GetAngularVelocity() const
{
    if( !IsValid() ) {
        return std::nullopt;
    }
    const TrailerModule &module = m_session->Trailer();
    if( module.m_trailerTable == nullptr ) {
        return std::nullopt;
    }
    Float3 native;
    if( !module.m_trailerTable->GetAngularVelocity( module.m_ctx, m_handle, &native ) ) {
        return std::nullopt;
    }
    return native;
}

inline std::optional< Trailer > Vehicle::GetTrailer() const
{
    if( !IsValid() ) {
        return std::nullopt;
    }
    const VehicleModule &module = m_session->Vehicle();
    if( module.m_vehicleTable == nullptr ) {
        return std::nullopt;
    }
    TruckersMP_Trailer_Handle native;
    if( !module.m_vehicleTable->GetTrailer( module.m_ctx, m_handle, &native ) ) {
        return std::nullopt;
    }
    return Trailer( m_session, native );
}

inline std::optional< Placement > Vehicle::GetPlacement() const
{
    if( !IsValid() ) {
        return std::nullopt;
    }
    const VehicleModule &module = m_session->Vehicle();
    if( module.m_vehicleTable == nullptr ) {
        return std::nullopt;
    }
    Placement native;
    if( !module.m_vehicleTable->GetPlacement( module.m_ctx, m_handle, &native ) ) {
        return std::nullopt;
    }
    return native;
}

inline std::optional< Float3 > Vehicle::GetLinearVelocity() const
{
    if( !IsValid() ) {
        return std::nullopt;
    }
    const VehicleModule &module = m_session->Vehicle();
    if( module.m_vehicleTable == nullptr ) {
        return std::nullopt;
    }
    Float3 native;
    if( !module.m_vehicleTable->GetLinearVelocity( module.m_ctx, m_handle, &native ) ) {
        return std::nullopt;
    }
    return native;
}

inline std::optional< Float3 > Vehicle::GetAngularVelocity() const
{
    if( !IsValid() ) {
        return std::nullopt;
    }
    const VehicleModule &module = m_session->Vehicle();
    if( module.m_vehicleTable == nullptr ) {
        return std::nullopt;
    }
    Float3 native;
    if( !module.m_vehicleTable->GetAngularVelocity( module.m_ctx, m_handle, &native ) ) {
        return std::nullopt;
    }
    return native;
}

inline void CoreModule::SessionFree( const void *ptr ) const
{
    if( m_session != nullptr ) {
        m_session->RawFree( ptr );
    }
}

inline Result CoreModule::LogMessage( LogLevel level, std::string_view text )
{
    if( m_coreTable == nullptr ) {
        return Result::ServiceUnavailable;
    }
    return static_cast< Result >( m_coreTable->LogMessage( m_ctx, static_cast< TruckersMP_LogLevel >( level ), TruckersMP_String{ text.data(), ( Uint32 ) text.size() } ) );
}

inline std::optional< std::string > CoreModule::GameID() const
{
    if( m_coreTable == nullptr ) {
        return std::nullopt;
    }
    TruckersMP_String native;
    if( !m_coreTable->GameID( m_ctx, &native ) ) {
        return std::nullopt;
    }
    std::string value( native.m_ptr, native.m_size );
    SessionFree( native.m_ptr );
    return value;
}

inline std::optional< std::string > CoreModule::ClientVersion() const
{
    if( m_coreTable == nullptr ) {
        return std::nullopt;
    }
    TruckersMP_String native;
    if( !m_coreTable->ClientVersion( m_ctx, &native ) ) {
        return std::nullopt;
    }
    std::string value( native.m_ptr, native.m_size );
    SessionFree( native.m_ptr );
    return value;
}

inline void AccountModule::SessionFree( const void *ptr ) const
{
    if( m_session != nullptr ) {
        m_session->RawFree( ptr );
    }
}

inline std::optional< Uint64 > AccountModule::GetAccountID() const
{
    if( m_accountsTable == nullptr ) {
        return std::nullopt;
    }
    Uint64 native;
    if( !m_accountsTable->GetAccountID( m_ctx, &native ) ) {
        return std::nullopt;
    }
    return native;
}

inline std::optional< Bool > AccountModule::IsGameModerator() const
{
    if( m_accountsTable == nullptr ) {
        return std::nullopt;
    }
    bool native;
    if( !m_accountsTable->IsGameModerator( m_ctx, &native ) ) {
        return std::nullopt;
    }
    return native;
}

inline std::optional< Bool > AccountModule::IsTeamMember() const
{
    if( m_accountsTable == nullptr ) {
        return std::nullopt;
    }
    bool native;
    if( !m_accountsTable->IsTeamMember( m_ctx, &native ) ) {
        return std::nullopt;
    }
    return native;
}

inline std::optional< Bool > AccountModule::IsPatron() const
{
    if( m_accountsTable == nullptr ) {
        return std::nullopt;
    }
    bool native;
    if( !m_accountsTable->IsPatron( m_ctx, &native ) ) {
        return std::nullopt;
    }
    return native;
}

inline std::optional< Uint64 > AccountModule::GetCompanyID() const
{
    if( m_accountsTable == nullptr ) {
        return std::nullopt;
    }
    Uint64 native;
    if( !m_accountsTable->GetCompanyID( m_ctx, &native ) ) {
        return std::nullopt;
    }
    return native;
}

inline void GameplayModule::SessionFree( const void *ptr ) const
{
    if( m_session != nullptr ) {
        m_session->RawFree( ptr );
    }
}

inline std::optional< std::vector< PackageInfo > > GameplayModule::GetMountedPackages() const
{
    if( m_gameplayTable == nullptr ) {
        return std::nullopt;
    }
    TruckersMP_List list;
    if( !m_gameplayTable->GetMountedPackages( m_ctx, &list ) ) {
        return std::nullopt;
    }
    std::vector< PackageInfo > values;
    values.reserve( list.m_count );
    for( Uint32 i = 0; i < list.m_count; ++i )
    {
        const TruckersMP_PackageInfo &native = *( const TruckersMP_PackageInfo * )(
            ( const Uint8 * )list.m_items + ( Uint64 )i * list.m_stride );
        PackageInfo &value = values.emplace_back();
        value.name = std::string( native.name.m_ptr, native.name.m_size );
    }
    SessionFree( list.m_items );
    return values;
}

inline void InputModule::SessionFree( const void *ptr ) const
{
    if( m_session != nullptr ) {
        m_session->RawFree( ptr );
    }
}

inline std::optional< Bool > InputModule::IsMouseVisible() const
{
    if( m_inputTable == nullptr ) {
        return std::nullopt;
    }
    bool native;
    if( !m_inputTable->IsMouseVisible( m_ctx, &native ) ) {
        return std::nullopt;
    }
    return native;
}

inline Result InputModule::IncreaseMouseRef()
{
    if( m_inputTable == nullptr ) {
        return Result::ServiceUnavailable;
    }
    return static_cast< Result >( m_inputTable->IncreaseMouseRef( m_ctx ) );
}

inline Result InputModule::DecreaseMouseRef()
{
    if( m_inputTable == nullptr ) {
        return Result::ServiceUnavailable;
    }
    return static_cast< Result >( m_inputTable->DecreaseMouseRef( m_ctx ) );
}

inline std::optional< Bool > InputModule::IsGameMouseLocked() const
{
    if( m_inputTable == nullptr ) {
        return std::nullopt;
    }
    bool native;
    if( !m_inputTable->IsGameMouseLocked( m_ctx, &native ) ) {
        return std::nullopt;
    }
    return native;
}

inline Result InputModule::SetGameMouseLocked( Bool locked )
{
    if( m_inputTable == nullptr ) {
        return Result::ServiceUnavailable;
    }
    return static_cast< Result >( m_inputTable->SetGameMouseLocked( m_ctx, locked ) );
}

inline std::optional< Bool > InputModule::IsGameKeyboardLocked() const
{
    if( m_inputTable == nullptr ) {
        return std::nullopt;
    }
    bool native;
    if( !m_inputTable->IsGameKeyboardLocked( m_ctx, &native ) ) {
        return std::nullopt;
    }
    return native;
}

inline Result InputModule::SetGameKeyboardLocked( Bool locked )
{
    if( m_inputTable == nullptr ) {
        return Result::ServiceUnavailable;
    }
    return static_cast< Result >( m_inputTable->SetGameKeyboardLocked( m_ctx, locked ) );
}

inline void NetworkModule::SessionFree( const void *ptr ) const
{
    if( m_session != nullptr ) {
        m_session->RawFree( ptr );
    }
}

inline std::optional< Bool > NetworkModule::IsConnected() const
{
    if( m_networkTable == nullptr ) {
        return std::nullopt;
    }
    bool native;
    if( !m_networkTable->IsConnected( m_ctx, &native ) ) {
        return std::nullopt;
    }
    return native;
}

inline std::optional< Uint16 > NetworkModule::GetLastPing() const
{
    if( m_networkTable == nullptr ) {
        return std::nullopt;
    }
    Uint16 native;
    if( !m_networkTable->GetLastPing( m_ctx, &native ) ) {
        return std::nullopt;
    }
    return native;
}

inline std::optional< Uint64 > NetworkModule::GetGameServerID() const
{
    if( m_networkTable == nullptr ) {
        return std::nullopt;
    }
    Uint64 native;
    if( !m_networkTable->GetGameServerID( m_ctx, &native ) ) {
        return std::nullopt;
    }
    return native;
}

inline void PlayerModule::SessionFree( const void *ptr ) const
{
    if( m_session != nullptr ) {
        m_session->RawFree( ptr );
    }
}

inline std::optional< Player > PlayerModule::GetLocalPlayer() const
{
    if( m_playersTable == nullptr ) {
        return std::nullopt;
    }
    TruckersMP_Player_Handle native;
    if( !m_playersTable->GetLocalPlayer( m_ctx, &native ) ) {
        return std::nullopt;
    }
    return Player( m_session, native );
}

inline std::optional< Player > PlayerModule::GetPlayerByID( Int32 id ) const
{
    if( m_playersTable == nullptr ) {
        return std::nullopt;
    }
    TruckersMP_Player_Handle native;
    if( !m_playersTable->GetPlayerByID( m_ctx, id, &native ) ) {
        return std::nullopt;
    }
    return Player( m_session, native );
}

inline std::optional< std::vector< Player > > PlayerModule::GetAllPlayers() const
{
    if( m_playersTable == nullptr ) {
        return std::nullopt;
    }
    TruckersMP_List list;
    if( !m_playersTable->GetAllPlayers( m_ctx, &list ) ) {
        return std::nullopt;
    }
    std::vector< Player > values;
    values.reserve( list.m_count );
    for( Uint32 i = 0; i < list.m_count; ++i )
    {
        const TruckersMP_Player_Handle &native = *( const TruckersMP_Player_Handle * )(
            ( const Uint8 * )list.m_items + ( Uint64 )i * list.m_stride );
        values.emplace_back( Player( m_session, native ) );
    }
    SessionFree( list.m_items );
    return values;
}

inline void RenderModule::SessionFree( const void *ptr ) const
{
    if( m_session != nullptr ) {
        m_session->RawFree( ptr );
    }
}

inline std::optional< RendererID > RenderModule::GetRendererID() const
{
    if( m_renderTable == nullptr ) {
        return std::nullopt;
    }
    TruckersMP_RendererID native;
    if( !m_renderTable->GetRendererID( m_ctx, &native ) ) {
        return std::nullopt;
    }
    return static_cast< RendererID >( native );
}

inline std::optional< Uint64 > RenderModule::GetDeviceHandle() const
{
    if( m_renderTable == nullptr ) {
        return std::nullopt;
    }
    Uint64 native;
    if( !m_renderTable->GetDeviceHandle( m_ctx, &native ) ) {
        return std::nullopt;
    }
    return native;
}

inline void TrailerModule::SessionFree( const void *ptr ) const
{
    if( m_session != nullptr ) {
        m_session->RawFree( ptr );
    }
}

inline void UserInterfaceModule::SessionFree( const void *ptr ) const
{
    if( m_session != nullptr ) {
        m_session->RawFree( ptr );
    }
}

inline Result UserInterfaceModule::ShowNotification( NotificationType type, std::string_view message )
{
    if( m_userInterfaceTable == nullptr ) {
        return Result::ServiceUnavailable;
    }
    return static_cast< Result >( m_userInterfaceTable->ShowNotification( m_ctx, static_cast< TruckersMP_NotificationType >( type ), TruckersMP_String{ message.data(), ( Uint32 ) message.size() } ) );
}

inline void VehicleModule::SessionFree( const void *ptr ) const
{
    if( m_session != nullptr ) {
        m_session->RawFree( ptr );
    }
}

namespace Internal
{

inline void TMP_API Dispatch_GameplayNoCollisionZone( void *userCtx, uint64_t /*eventId*/, void *payload, uint32_t payloadSize )
{
    Session *const owner = static_cast< Session * >( userCtx );
    if( owner == nullptr || payload == nullptr || payloadSize < sizeof( TruckersMP_Evt_GameplayNoCollisionZone ) ) {
        return;
    }
    GameplayNoCollisionZoneEvent args( owner, static_cast< TruckersMP_Evt_GameplayNoCollisionZone * >( payload ) );
    owner->Gameplay().OnNoCollisionZone.Call( args );
}

inline void TMP_API Dispatch_InputKey( void *userCtx, uint64_t /*eventId*/, void *payload, uint32_t payloadSize )
{
    Session *const owner = static_cast< Session * >( userCtx );
    if( owner == nullptr || payload == nullptr || payloadSize < sizeof( TruckersMP_Evt_InputKey ) ) {
        return;
    }
    InputKeyEvent args( owner, static_cast< TruckersMP_Evt_InputKey * >( payload ) );
    owner->Input().OnKey.Call( args );
}

inline void TMP_API Dispatch_InputChar( void *userCtx, uint64_t /*eventId*/, void *payload, uint32_t payloadSize )
{
    Session *const owner = static_cast< Session * >( userCtx );
    if( owner == nullptr || payload == nullptr || payloadSize < sizeof( TruckersMP_Evt_InputChar ) ) {
        return;
    }
    InputCharEvent args( owner, static_cast< TruckersMP_Evt_InputChar * >( payload ) );
    owner->Input().OnChar.Call( args );
}

inline void TMP_API Dispatch_InputMouseMove( void *userCtx, uint64_t /*eventId*/, void *payload, uint32_t payloadSize )
{
    Session *const owner = static_cast< Session * >( userCtx );
    if( owner == nullptr || payload == nullptr || payloadSize < sizeof( TruckersMP_Evt_InputMouseMove ) ) {
        return;
    }
    InputMouseMoveEvent args( owner, static_cast< TruckersMP_Evt_InputMouseMove * >( payload ) );
    owner->Input().OnMouseMove.Call( args );
}

inline void TMP_API Dispatch_InputMouseWheel( void *userCtx, uint64_t /*eventId*/, void *payload, uint32_t payloadSize )
{
    Session *const owner = static_cast< Session * >( userCtx );
    if( owner == nullptr || payload == nullptr || payloadSize < sizeof( TruckersMP_Evt_InputMouseWheel ) ) {
        return;
    }
    InputMouseWheelEvent args( owner, static_cast< TruckersMP_Evt_InputMouseWheel * >( payload ) );
    owner->Input().OnMouseWheel.Call( args );
}

inline void TMP_API Dispatch_InputMouseButton( void *userCtx, uint64_t /*eventId*/, void *payload, uint32_t payloadSize )
{
    Session *const owner = static_cast< Session * >( userCtx );
    if( owner == nullptr || payload == nullptr || payloadSize < sizeof( TruckersMP_Evt_InputMouseButton ) ) {
        return;
    }
    InputMouseButtonEvent args( owner, static_cast< TruckersMP_Evt_InputMouseButton * >( payload ) );
    owner->Input().OnMouseButton.Call( args );
}

inline void TMP_API Dispatch_NetworkConnected( void *userCtx, uint64_t /*eventId*/, void * /*payload*/, uint32_t /*payloadSize*/ )
{
    Session *owner = static_cast< Session * >( userCtx );
    if( owner == nullptr ) {
        return;
    }
    owner->Network().OnConnected.Call();
}

inline void TMP_API Dispatch_NetworkDisconnected( void *userCtx, uint64_t /*eventId*/, void * /*payload*/, uint32_t /*payloadSize*/ )
{
    Session *owner = static_cast< Session * >( userCtx );
    if( owner == nullptr ) {
        return;
    }
    owner->Network().OnDisconnected.Call();
}

inline void TMP_API Dispatch_PlayerStreamIn( void *userCtx, uint64_t /*eventId*/, void *payload, uint32_t payloadSize )
{
    Session *const owner = static_cast< Session * >( userCtx );
    if( owner == nullptr || payload == nullptr || payloadSize < sizeof( TruckersMP_Evt_PlayerStreamIn ) ) {
        return;
    }
    PlayerStreamInEvent args( owner, static_cast< TruckersMP_Evt_PlayerStreamIn * >( payload ) );
    owner->Player().OnStreamIn.Call( args );
}

inline void TMP_API Dispatch_PlayerStreamOut( void *userCtx, uint64_t /*eventId*/, void *payload, uint32_t payloadSize )
{
    Session *const owner = static_cast< Session * >( userCtx );
    if( owner == nullptr || payload == nullptr || payloadSize < sizeof( TruckersMP_Evt_PlayerStreamOut ) ) {
        return;
    }
    PlayerStreamOutEvent args( owner, static_cast< TruckersMP_Evt_PlayerStreamOut * >( payload ) );
    owner->Player().OnStreamOut.Call( args );
}

inline void TMP_API Dispatch_PlayerUpdate( void *userCtx, uint64_t /*eventId*/, void *payload, uint32_t payloadSize )
{
    Session *const owner = static_cast< Session * >( userCtx );
    if( owner == nullptr || payload == nullptr || payloadSize < sizeof( TruckersMP_Evt_PlayerUpdate ) ) {
        return;
    }
    PlayerUpdateEvent args( owner, static_cast< TruckersMP_Evt_PlayerUpdate * >( payload ) );
    owner->Player().OnUpdate.Call( args );
}

inline void TMP_API Dispatch_RenderPreRender( void *userCtx, uint64_t /*eventId*/, void * /*payload*/, uint32_t /*payloadSize*/ )
{
    Session *owner = static_cast< Session * >( userCtx );
    if( owner == nullptr ) {
        return;
    }
    owner->Render().OnPreRender.Call();
}

inline void TMP_API Dispatch_RenderPostRender( void *userCtx, uint64_t /*eventId*/, void * /*payload*/, uint32_t /*payloadSize*/ )
{
    Session *owner = static_cast< Session * >( userCtx );
    if( owner == nullptr ) {
        return;
    }
    owner->Render().OnPostRender.Call();
}

inline void TMP_API Dispatch_TrailerSpawned( void *userCtx, uint64_t /*eventId*/, void *payload, uint32_t payloadSize )
{
    Session *const owner = static_cast< Session * >( userCtx );
    if( owner == nullptr || payload == nullptr || payloadSize < sizeof( TruckersMP_Evt_TrailerSpawned ) ) {
        return;
    }
    TrailerSpawnedEvent args( owner, static_cast< TruckersMP_Evt_TrailerSpawned * >( payload ) );
    owner->Trailer().OnSpawned.Call( args );
}

inline void TMP_API Dispatch_TrailerDespawned( void *userCtx, uint64_t /*eventId*/, void *payload, uint32_t payloadSize )
{
    Session *const owner = static_cast< Session * >( userCtx );
    if( owner == nullptr || payload == nullptr || payloadSize < sizeof( TruckersMP_Evt_TrailerDespawned ) ) {
        return;
    }
    TrailerDespawnedEvent args( owner, static_cast< TruckersMP_Evt_TrailerDespawned * >( payload ) );
    owner->Trailer().OnDespawned.Call( args );
}

inline void TMP_API Dispatch_VehicleSpawned( void *userCtx, uint64_t /*eventId*/, void *payload, uint32_t payloadSize )
{
    Session *const owner = static_cast< Session * >( userCtx );
    if( owner == nullptr || payload == nullptr || payloadSize < sizeof( TruckersMP_Evt_VehicleSpawned ) ) {
        return;
    }
    VehicleSpawnedEvent args( owner, static_cast< TruckersMP_Evt_VehicleSpawned * >( payload ) );
    owner->Vehicle().OnSpawned.Call( args );
}

inline void TMP_API Dispatch_VehicleDespawned( void *userCtx, uint64_t /*eventId*/, void *payload, uint32_t payloadSize )
{
    Session *const owner = static_cast< Session * >( userCtx );
    if( owner == nullptr || payload == nullptr || payloadSize < sizeof( TruckersMP_Evt_VehicleDespawned ) ) {
        return;
    }
    VehicleDespawnedEvent args( owner, static_cast< TruckersMP_Evt_VehicleDespawned * >( payload ) );
    owner->Vehicle().OnDespawned.Call( args );
}

} // namespace Internal

inline void Session::RawFree( const void *ptr ) const
{
    if( m_free != nullptr && ptr != nullptr ) {
        m_free( m_ctx, const_cast< void * >( ptr ) );
    }
}

inline const void *Session::GetRawApi( uint64_t apiId ) const
{
    return m_getApi != nullptr ? m_getApi( m_ctx, apiId ) : nullptr;
}

inline Result Session::AddRawListener( uint64_t eventId, TruckersMP_EventFn fn, void *userCtx )
{
    if( m_core.m_coreTable == nullptr ) {
        return Result::ServiceUnavailable;
    }
    return static_cast< Result >( m_core.m_coreTable->AddListener( m_ctx, eventId, fn, userCtx ) );
}

inline Result Session::RemoveRawListener( uint64_t eventId, TruckersMP_EventFn fn, void *userCtx )
{
    if( m_core.m_coreTable == nullptr ) {
        return Result::ServiceUnavailable;
    }
    return static_cast< Result >( m_core.m_coreTable->RemoveListener( m_ctx, eventId, fn, userCtx ) );
}

inline void Session::AddRawDetachHook( void *owner, void ( *fn )( void * ) )
{
    m_detachHooks.emplace_back( DetachHook{ owner, fn } );
}

inline void Session::RemoveRawDetachHook( void *owner )
{
    for( size_t i = 0; i < m_detachHooks.size(); ++i ) {
        if( m_detachHooks[ i ].m_owner == owner ) {
            m_detachHooks.erase( m_detachHooks.begin() + i );
            return;
        }
    }
}

inline Result Session::RawUnlockIntent( std::string_view key )
{
    if( m_core.m_coreTable == nullptr ) {
        return Result::ServiceUnavailable;
    }
    const TruckersMP_String raw{ key.data(), ( Uint32 ) key.size() };
    return static_cast< Result >( m_core.m_coreTable->UnlockIntent( m_ctx, raw ) );
}

inline std::unique_ptr< Session > Session::Create( const TruckersMP_Host *host )
{
    if( host == nullptr || host->m_size < sizeof( TruckersMP_Host ) || host->GetApi == nullptr ) {
        return nullptr;
    }

    if( host->DeclareVersion( host->m_ctx, TRUCKERSMP_SDK_VERSION ) != TruckersMP_Result_Ok ) {
        return nullptr;
    }

    std::unique_ptr< Session > session( new Session() );
    session->m_ctx = host->m_ctx;
    session->m_getApi = host->GetApi;
    session->m_free = host->Free;

    session->m_core.m_coreTable = static_cast< const TruckersMP_Core * >( session->GetRawApi( TRUCKERSMP_API_CORE ) );
    if( session->m_core.m_coreTable == nullptr ) {
        return nullptr;
    }
    session->m_core.m_ctx = session->m_ctx;
    session->m_core.m_session = session.get();

    session->m_account.m_accountsTable = static_cast< const TruckersMP_Accounts * >( session->GetRawApi( TRUCKERSMP_API_ACCOUNTS ) );
    session->m_account.m_ctx = session->m_ctx;
    session->m_account.m_session = session.get();

    session->m_gameplay.m_gameplayTable = static_cast< const TruckersMP_Gameplay * >( session->GetRawApi( TRUCKERSMP_API_GAMEPLAY ) );
    session->m_gameplay.m_ctx = session->m_ctx;
    session->m_gameplay.m_session = session.get();

    session->m_input.m_inputTable = static_cast< const TruckersMP_Input * >( session->GetRawApi( TRUCKERSMP_API_INPUT ) );
    session->m_input.m_ctx = session->m_ctx;
    session->m_input.m_session = session.get();

    session->m_network.m_networkTable = static_cast< const TruckersMP_Network * >( session->GetRawApi( TRUCKERSMP_API_NETWORK ) );
    session->m_network.m_ctx = session->m_ctx;
    session->m_network.m_session = session.get();

    session->m_player.m_playersTable = static_cast< const TruckersMP_Players * >( session->GetRawApi( TRUCKERSMP_API_PLAYERS ) );
    session->m_player.m_playerHandleTable = static_cast< const TruckersMP_PlayerHandle * >( session->GetRawApi( TRUCKERSMP_API_PLAYER_HANDLE ) );
    session->m_player.m_ctx = session->m_ctx;
    session->m_player.m_session = session.get();

    session->m_render.m_renderTable = static_cast< const TruckersMP_Render * >( session->GetRawApi( TRUCKERSMP_API_RENDER ) );
    session->m_render.m_ctx = session->m_ctx;
    session->m_render.m_session = session.get();

    session->m_trailer.m_trailerTable = static_cast< const TruckersMP_Trailer * >( session->GetRawApi( TRUCKERSMP_API_TRAILER ) );
    session->m_trailer.m_ctx = session->m_ctx;
    session->m_trailer.m_session = session.get();

    session->m_user_interface.m_userInterfaceTable = static_cast< const TruckersMP_UserInterface * >( session->GetRawApi( TRUCKERSMP_API_USER_INTERFACE ) );
    session->m_user_interface.m_ctx = session->m_ctx;
    session->m_user_interface.m_session = session.get();

    session->m_vehicle.m_vehicleTable = static_cast< const TruckersMP_Vehicle * >( session->GetRawApi( TRUCKERSMP_API_VEHICLE ) );
    session->m_vehicle.m_ctx = session->m_ctx;
    session->m_vehicle.m_session = session.get();

    session->Gameplay().OnNoCollisionZone.Internal_SetActivationHook( [ owner = session.get() ]( Bool active )
    {
        if( active ) {
            owner->AddRawListener( TRUCKERSMP_EVT_GAMEPLAY_NO_COLLISION_ZONE, &Internal::Dispatch_GameplayNoCollisionZone, owner );
        } else {
            owner->RemoveRawListener( TRUCKERSMP_EVT_GAMEPLAY_NO_COLLISION_ZONE, &Internal::Dispatch_GameplayNoCollisionZone, owner );
        }
    } );

    session->Input().OnKey.Internal_SetActivationHook( [ owner = session.get() ]( Bool active )
    {
        if( active ) {
            owner->AddRawListener( TRUCKERSMP_EVT_INPUT_KEY, &Internal::Dispatch_InputKey, owner );
        } else {
            owner->RemoveRawListener( TRUCKERSMP_EVT_INPUT_KEY, &Internal::Dispatch_InputKey, owner );
        }
    } );

    session->Input().OnChar.Internal_SetActivationHook( [ owner = session.get() ]( Bool active )
    {
        if( active ) {
            owner->AddRawListener( TRUCKERSMP_EVT_INPUT_CHAR, &Internal::Dispatch_InputChar, owner );
        } else {
            owner->RemoveRawListener( TRUCKERSMP_EVT_INPUT_CHAR, &Internal::Dispatch_InputChar, owner );
        }
    } );

    session->Input().OnMouseMove.Internal_SetActivationHook( [ owner = session.get() ]( Bool active )
    {
        if( active ) {
            owner->AddRawListener( TRUCKERSMP_EVT_INPUT_MOUSE_MOVE, &Internal::Dispatch_InputMouseMove, owner );
        } else {
            owner->RemoveRawListener( TRUCKERSMP_EVT_INPUT_MOUSE_MOVE, &Internal::Dispatch_InputMouseMove, owner );
        }
    } );

    session->Input().OnMouseWheel.Internal_SetActivationHook( [ owner = session.get() ]( Bool active )
    {
        if( active ) {
            owner->AddRawListener( TRUCKERSMP_EVT_INPUT_MOUSE_WHEEL, &Internal::Dispatch_InputMouseWheel, owner );
        } else {
            owner->RemoveRawListener( TRUCKERSMP_EVT_INPUT_MOUSE_WHEEL, &Internal::Dispatch_InputMouseWheel, owner );
        }
    } );

    session->Input().OnMouseButton.Internal_SetActivationHook( [ owner = session.get() ]( Bool active )
    {
        if( active ) {
            owner->AddRawListener( TRUCKERSMP_EVT_INPUT_MOUSE_BUTTON, &Internal::Dispatch_InputMouseButton, owner );
        } else {
            owner->RemoveRawListener( TRUCKERSMP_EVT_INPUT_MOUSE_BUTTON, &Internal::Dispatch_InputMouseButton, owner );
        }
    } );

    session->Network().OnConnected.Internal_SetActivationHook( [ owner = session.get() ]( Bool active )
    {
        if( active ) {
            owner->AddRawListener( TRUCKERSMP_EVT_NETWORK_CONNECTED, &Internal::Dispatch_NetworkConnected, owner );
        } else {
            owner->RemoveRawListener( TRUCKERSMP_EVT_NETWORK_CONNECTED, &Internal::Dispatch_NetworkConnected, owner );
        }
    } );

    session->Network().OnDisconnected.Internal_SetActivationHook( [ owner = session.get() ]( Bool active )
    {
        if( active ) {
            owner->AddRawListener( TRUCKERSMP_EVT_NETWORK_DISCONNECTED, &Internal::Dispatch_NetworkDisconnected, owner );
        } else {
            owner->RemoveRawListener( TRUCKERSMP_EVT_NETWORK_DISCONNECTED, &Internal::Dispatch_NetworkDisconnected, owner );
        }
    } );

    session->Player().OnStreamIn.Internal_SetActivationHook( [ owner = session.get() ]( Bool active )
    {
        if( active ) {
            owner->AddRawListener( TRUCKERSMP_EVT_PLAYER_STREAM_IN, &Internal::Dispatch_PlayerStreamIn, owner );
        } else {
            owner->RemoveRawListener( TRUCKERSMP_EVT_PLAYER_STREAM_IN, &Internal::Dispatch_PlayerStreamIn, owner );
        }
    } );

    session->Player().OnStreamOut.Internal_SetActivationHook( [ owner = session.get() ]( Bool active )
    {
        if( active ) {
            owner->AddRawListener( TRUCKERSMP_EVT_PLAYER_STREAM_OUT, &Internal::Dispatch_PlayerStreamOut, owner );
        } else {
            owner->RemoveRawListener( TRUCKERSMP_EVT_PLAYER_STREAM_OUT, &Internal::Dispatch_PlayerStreamOut, owner );
        }
    } );

    session->Player().OnUpdate.Internal_SetActivationHook( [ owner = session.get() ]( Bool active )
    {
        if( active ) {
            owner->AddRawListener( TRUCKERSMP_EVT_PLAYER_UPDATE, &Internal::Dispatch_PlayerUpdate, owner );
        } else {
            owner->RemoveRawListener( TRUCKERSMP_EVT_PLAYER_UPDATE, &Internal::Dispatch_PlayerUpdate, owner );
        }
    } );

    session->Render().OnPreRender.Internal_SetActivationHook( [ owner = session.get() ]( Bool active )
    {
        if( active ) {
            owner->AddRawListener( TRUCKERSMP_EVT_RENDER_PRE_RENDER, &Internal::Dispatch_RenderPreRender, owner );
        } else {
            owner->RemoveRawListener( TRUCKERSMP_EVT_RENDER_PRE_RENDER, &Internal::Dispatch_RenderPreRender, owner );
        }
    } );

    session->Render().OnPostRender.Internal_SetActivationHook( [ owner = session.get() ]( Bool active )
    {
        if( active ) {
            owner->AddRawListener( TRUCKERSMP_EVT_RENDER_POST_RENDER, &Internal::Dispatch_RenderPostRender, owner );
        } else {
            owner->RemoveRawListener( TRUCKERSMP_EVT_RENDER_POST_RENDER, &Internal::Dispatch_RenderPostRender, owner );
        }
    } );

    session->Trailer().OnSpawned.Internal_SetActivationHook( [ owner = session.get() ]( Bool active )
    {
        if( active ) {
            owner->AddRawListener( TRUCKERSMP_EVT_TRAILER_SPAWNED, &Internal::Dispatch_TrailerSpawned, owner );
        } else {
            owner->RemoveRawListener( TRUCKERSMP_EVT_TRAILER_SPAWNED, &Internal::Dispatch_TrailerSpawned, owner );
        }
    } );

    session->Trailer().OnDespawned.Internal_SetActivationHook( [ owner = session.get() ]( Bool active )
    {
        if( active ) {
            owner->AddRawListener( TRUCKERSMP_EVT_TRAILER_DESPAWNED, &Internal::Dispatch_TrailerDespawned, owner );
        } else {
            owner->RemoveRawListener( TRUCKERSMP_EVT_TRAILER_DESPAWNED, &Internal::Dispatch_TrailerDespawned, owner );
        }
    } );

    session->Vehicle().OnSpawned.Internal_SetActivationHook( [ owner = session.get() ]( Bool active )
    {
        if( active ) {
            owner->AddRawListener( TRUCKERSMP_EVT_VEHICLE_SPAWNED, &Internal::Dispatch_VehicleSpawned, owner );
        } else {
            owner->RemoveRawListener( TRUCKERSMP_EVT_VEHICLE_SPAWNED, &Internal::Dispatch_VehicleSpawned, owner );
        }
    } );

    session->Vehicle().OnDespawned.Internal_SetActivationHook( [ owner = session.get() ]( Bool active )
    {
        if( active ) {
            owner->AddRawListener( TRUCKERSMP_EVT_VEHICLE_DESPAWNED, &Internal::Dispatch_VehicleDespawned, owner );
        } else {
            owner->RemoveRawListener( TRUCKERSMP_EVT_VEHICLE_DESPAWNED, &Internal::Dispatch_VehicleDespawned, owner );
        }
    } );

    return session;
}

inline Session::~Session()
{
    // Attached add-on modules disconnect first.
    const std::vector< DetachHook > detachHooks = std::move( m_detachHooks );
    for( const DetachHook &hook : detachHooks ) {
        hook.m_fn( hook.m_owner );
    }

    m_gameplay.OnNoCollisionZone.UnregisterAll();
    m_input.OnKey.UnregisterAll();
    m_input.OnChar.UnregisterAll();
    m_input.OnMouseMove.UnregisterAll();
    m_input.OnMouseWheel.UnregisterAll();
    m_input.OnMouseButton.UnregisterAll();
    m_network.OnConnected.UnregisterAll();
    m_network.OnDisconnected.UnregisterAll();
    m_player.OnStreamIn.UnregisterAll();
    m_player.OnStreamOut.UnregisterAll();
    m_player.OnUpdate.UnregisterAll();
    m_render.OnPreRender.UnregisterAll();
    m_render.OnPostRender.UnregisterAll();
    m_trailer.OnSpawned.UnregisterAll();
    m_trailer.OnDespawned.UnregisterAll();
    m_vehicle.OnSpawned.UnregisterAll();
    m_vehicle.OnDespawned.UnregisterAll();
}

} // namespace TruckersMP

/* eof */
