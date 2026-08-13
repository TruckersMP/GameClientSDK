#include <TruckersMP/TruckersMP.hxx>
#include <TruckersMP/Bus.hxx>

#include <cstdio>
#include <memory>

static std::unique_ptr< TruckersMP::Session > g_session;
static std::unique_ptr< TruckersMP::BusModule > g_bus;

template< typename ...Args >
static void Log( const char *format, const Args &...args )
{
    char line[ 2048 ];
    snprintf( line, sizeof( line ), format, args... );
    g_session->Core().LogMessage( TruckersMP::LogLevel::Info, line );
}

TMP_EXPORT bool TMP_API truckersmp_init( const TruckersMP_Host *host, TruckersMP_PluginDesc *desc )
{
    using namespace TruckersMP;

    // Identity only; shown in the client's plugin list and logs.
    PluginInfo info;
    info.m_name = "Demo Plugin";
    info.m_author = "TruckersMP";
    info.m_version = "1.0.0";
    info.m_description = "A minimal reference plugin.";
    FillPluginDesc( desc, info );

    g_session = Session::Create( host );
    if( g_session == nullptr )
    {
        return false;
    }
    Session &session = *g_session;

    ////////////////////////////////////////////////////////////////////////////
    // Getters. Every getter returns std::optional. Read current state here at
    // init instead of waiting for events, so a load in the middle of a server
    // session sees the current world.
    ////////////////////////////////////////////////////////////////////////////

    {
        std::string version = session.Core().ClientVersion().value_or( "unknown" );
        std::string gameID = session.Core().GameID().value_or( "unknown" );
        Log( "Initialized on client %s, game %s", version.c_str(), gameID.c_str() );
    }

    if( session.Network().IsConnected().value_or( false ) )
    {
        Uint16 ping = session.Network().GetLastPing().value_or( 0 );
        Log( "Already connected, ping %u ms", ping );
    }

    ////////////////////////////////////////////////////////////////////////////
    // Events. Handlers stay registered until unregistered or the session is
    // destroyed. Payloads are views, valid only during the callback.
    ////////////////////////////////////////////////////////////////////////////

    // An event without a payload.
    session.Network().OnConnected.Register( []
    {
        Log( "Connected to a server" );
    } );

    // An event with a payload carrying a plain field.
    session.Gameplay().OnNoCollisionZone.Register( []( GameplayNoCollisionZoneEvent &event )
    {
        std::string_view message = event.GetEntered()
            ? "Entered a no-collision zone."
            : "Left a no-collision zone.";

        g_session->UserInterface().ShowNotification( NotificationType::Success, message );
    } );

    // An event with a payload carrying an entity handle. The handle is valid
    // during the callback; pull data through its getters and let it go.
    session.Player().OnStreamIn.Register( []( PlayerStreamInEvent &event )
    {
        const Player player = event.GetPlayer();

        Int32 id = player.GetPlayerID().value_or( -1 );
        std::string name = player.GetUsername().value_or( "unknown" );
        Float distance = player.GetDistanceFromLocalPlayer().value_or( 0.0f );

        Log( "Spotted %s (%d, %.0f m away)", name.c_str(), id, distance );
    } );

    ////////////////////////////////////////////////////////////////////////////
    // Intent module: probe & attach. Returns nullptr when the module is absent
    // or this plugin is not authorized by the client. The attached module
    // carries its own getters and events, same patterns as above.
    ////////////////////////////////////////////////////////////////////////////

    if( g_bus = BusModule::Attach( session ); g_bus != nullptr )
    {
        session.Core().LogMessage( LogLevel::Info, "Bus module attached" );

        // Module-level getter: state that may already exist at load time.
        if( const std::optional< BusJob > job = g_bus->GetJob() )
        {
            Uint32 passengers = job->GetPassengerCount().value_or( 0 );
            Log( "A bus job is already active (%u passengers)", passengers );
        }

        // Module event; the payload hands out module-owned handles.
        g_bus->OnJobStarted.Register( []( BusJobStartedEvent &event )
        {
            const size_t stops = event.GetJob().GetStops().value_or( {} ).size();
            Log( "A bus job started: %llu stops on the route", stops );
        } );

        g_bus->OnJobFinished.Register( []( BusJobFinishedEvent &event )
        {
            Log( "A bus job finished, payout %lld", event.GetPayout() );
        } );
    }
    else
    {
        session.Core().LogMessage( LogLevel::Warning, "Bus module unavailable" );
    }

    return true;
}

TMP_EXPORT void TMP_API truckersmp_shutdown( void )
{
    // Any order works: a session destroyed first disconnects its modules.
    g_bus.reset();
    g_session.reset();
}

/* eof */
