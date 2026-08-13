/* Generated file. Do not edit. */

#pragma once

#include "TruckersMP/TruckersMP.hxx"
#include "TruckersMP/TruckersMP_Bus.h"

namespace TruckersMP
{

/// @brief The reason why a bus job has been canceled.
enum class BusJobCancellationReason : Int32
{
    /// @brief A new job is being created while there is already an active one.
    ExistingJob = TruckersMP_BusJobCancellationReason_ExistingJob,

    /// @brief The local player abandoned the job on their own.
    Abandon = TruckersMP_BusJobCancellationReason_Abandon,

    /// @brief A save was loaded and did not meet the requirements of continuing the job.
    Incompatible = TruckersMP_BusJobCancellationReason_Incompatible,

    /// @brief The exact cause is unknown; the job was cancelled from the outer scope.
    ExternalSource = TruckersMP_BusJobCancellationReason_ExternalSource,
};

class BusModule;
class BusJob;
class BusStop;
class BusJobStartedEvent;
class BusJobDataReadyEvent;
class BusJobCanceledEvent;
class BusJobFinishedEvent;
class BusNextStopEvent;
class BusStopActivatedEvent;
class BusStopCompletedEvent;

/// @brief Opaque reference to a bus job.
///
/// The handle is valid as long as the bus job is active.
class BusJob final
{
public:
    BusJob() = default;
    BusJob( BusModule *owner, TruckersMP_BusJob_Handle handle ) : m_module( owner ), m_handle( handle ) {}

    Bool IsValid() const { return m_module != nullptr && m_handle.m_value != 0; }
    TruckersMP_BusJob_Handle RawHandle() const { return m_handle; }

    /// @brief Get the list of all stops that are a part of the job.
    std::optional< std::vector< BusStop > > GetStops() const;

    /// @brief The economy time of when the job was started.
    std::optional< Uint32 > GetStartTime() const;

    /// @brief Get the number of passengers that are currently on board.
    std::optional< Uint32 > GetPassengerCount() const;

private:
    BusModule *m_module = nullptr;
    TruckersMP_BusJob_Handle m_handle{};
};

/// @brief Opaque reference to a bus stop.
///
/// The handle is active only as long as the bus stop is in scope.
class BusStop final
{
public:
    BusStop() = default;
    BusStop( BusModule *owner, TruckersMP_BusStop_Handle handle ) : m_module( owner ), m_handle( handle ) {}

    Bool IsValid() const { return m_module != nullptr && m_handle.m_value != 0; }
    TruckersMP_BusStop_Handle RawHandle() const { return m_handle; }

    /// @brief Get the display name of the bus stop.
    ///
    /// At this moment, this is the localized name of the city.
    std::optional< std::string > GetName() const;

    /// @brief Obtain the unit name of the city that the bus stop is located in.
    std::optional< std::string > GetCityIdentifier() const;

    /// @brief How many economy minutes it is supposed to take to drive to this stop.
    ///
    /// This may return 0 if the system is still calculating the data.
    std::optional< Uint32 > GetScheduledTime() const;

    /// @brief Planned distance based on navigation data (in km).
    ///
    /// This may return 0 if the system is still calculating the data.
    std::optional< Float > GetPlannedDistance() const;

    /// @brief Get the number of passengers that will board at this stop.
    std::optional< Uint8 > GetBoardingPassengers() const;

    /// @brief Get the number of passengers that will get off at this stop.
    std::optional< Uint8 > GetLeavingPassengers() const;

private:
    BusModule *m_module = nullptr;
    TruckersMP_BusStop_Handle m_handle{};
};

/// @brief The bus gameplay module.
class BusModule final
{
public:
    ~BusModule();
    BusModule( const BusModule & ) = delete;
    BusModule &operator=( const BusModule & ) = delete;

    static std::unique_ptr< BusModule > Attach( Session &session );

    /// @brief Obtain the handle of the currently active bus job.
    std::optional< BusJob > GetJob() const;

public:
    /// @brief A valid bus job has been created.
    Event< BusJobStartedEvent & > OnJobStarted;

    /// @brief The navigation data for bus stops of the current bus job has been calculated.
    Event< BusJobDataReadyEvent & > OnJobDataReady;

    /// @brief The bus job has been canceled.
    Event< BusJobCanceledEvent & > OnJobCanceled;

    /// @brief The bus job has been successfully finished.
    Event< BusJobFinishedEvent & > OnJobFinished;

    /// @brief The system started routing the player to the next bus stop.
    Event< BusNextStopEvent & > OnNextStop;

    /// @brief The vehicle has successfully stopped in a bus stop and is boarding passengers.
    Event< BusStopActivatedEvent & > OnStopActivated;

    /// @brief Boarding passengers has finished.
    Event< BusStopCompletedEvent & > OnStopCompleted;

private:
    BusModule() = default;

    static void RawDetach( void *module );
    void Teardown();

    Session *m_session = nullptr;
    const TruckersMP_Bus *m_busTable = nullptr;
    const TruckersMP_BusJob *m_busJobTable = nullptr;
    const TruckersMP_BusStop *m_busStopTable = nullptr;
    TruckersMP_PluginContext *m_ctx = nullptr;

private:
    friend class BusJob;
    friend class BusStop;
};

class BusJobStartedEvent final
{
public:
    BusJobStartedEvent( BusModule *owner, TruckersMP_Evt_BusJobStarted *payload ) : m_owner( owner ), m_payload( payload ) {}

    BusJob GetJob() const { return BusJob( m_owner, m_payload->m_job ); }
    Int64 GetEstimatedPayout() const { return m_payload->m_estimatedPayout; }

private:
    BusModule *m_owner;
    TruckersMP_Evt_BusJobStarted *m_payload;
};

class BusJobDataReadyEvent final
{
public:
    BusJobDataReadyEvent( BusModule *owner, TruckersMP_Evt_BusJobDataReady *payload ) : m_owner( owner ), m_payload( payload ) {}

    BusJob GetJob() const { return BusJob( m_owner, m_payload->m_job ); }
    std::vector< BusStop > GetStops() const;

private:
    BusModule *m_owner;
    TruckersMP_Evt_BusJobDataReady *m_payload;
};

class BusJobCanceledEvent final
{
public:
    BusJobCanceledEvent( BusModule *owner, TruckersMP_Evt_BusJobCanceled *payload ) : m_owner( owner ), m_payload( payload ) {}

    BusJob GetJob() const { return BusJob( m_owner, m_payload->m_job ); }
    BusJobCancellationReason GetReason() const { return static_cast< BusJobCancellationReason >( m_payload->m_reason ); }

private:
    BusModule *m_owner;
    TruckersMP_Evt_BusJobCanceled *m_payload;
};

class BusJobFinishedEvent final
{
public:
    BusJobFinishedEvent( BusModule *owner, TruckersMP_Evt_BusJobFinished *payload ) : m_owner( owner ), m_payload( payload ) {}

    BusJob GetJob() const { return BusJob( m_owner, m_payload->m_job ); }
    Int64 GetPayout() const { return m_payload->m_payout; }

private:
    BusModule *m_owner;
    TruckersMP_Evt_BusJobFinished *m_payload;
};

class BusNextStopEvent final
{
public:
    BusNextStopEvent( BusModule *owner, TruckersMP_Evt_BusNextStop *payload ) : m_owner( owner ), m_payload( payload ) {}

    BusJob GetJob() const { return BusJob( m_owner, m_payload->m_job ); }
    BusStop GetStop() const { return BusStop( m_owner, m_payload->m_stop ); }

private:
    BusModule *m_owner;
    TruckersMP_Evt_BusNextStop *m_payload;
};

class BusStopActivatedEvent final
{
public:
    BusStopActivatedEvent( BusModule *owner, TruckersMP_Evt_BusStopActivated *payload ) : m_owner( owner ), m_payload( payload ) {}

    BusJob GetJob() const { return BusJob( m_owner, m_payload->m_job ); }
    BusStop GetStop() const { return BusStop( m_owner, m_payload->m_stop ); }

private:
    BusModule *m_owner;
    TruckersMP_Evt_BusStopActivated *m_payload;
};

class BusStopCompletedEvent final
{
public:
    BusStopCompletedEvent( BusModule *owner, TruckersMP_Evt_BusStopCompleted *payload ) : m_owner( owner ), m_payload( payload ) {}

    BusJob GetJob() const { return BusJob( m_owner, m_payload->m_job ); }

    BusStop GetStop() const { return BusStop( m_owner, m_payload->m_stop ); }

    /// @brief Recorded driven distance for the bus stop only (in km).
    Float GetDrivenDistance() const { return m_payload->m_drivenDistance; }

private:
    BusModule *m_owner;
    TruckersMP_Evt_BusStopCompleted *m_payload;
};

inline std::vector< BusStop > BusJobDataReadyEvent::GetStops() const
{
    std::vector< BusStop > values;
    values.reserve( m_payload->m_stops.m_count );
    for( Uint32 i = 0; i < m_payload->m_stops.m_count; ++i )
    {
        const TruckersMP_BusStop_Handle &native = *( const TruckersMP_BusStop_Handle * )(
            ( const Uint8 * )m_payload->m_stops.m_items + ( Uint64 )i * m_payload->m_stops.m_stride );
        values.emplace_back( BusStop( m_owner, native ) );
    }
    return values;
}

inline std::optional< std::vector< BusStop > > BusJob::GetStops() const
{
    if( !IsValid() ) {
        return std::nullopt;
    }
    const BusModule &module = *m_module;
    if( module.m_busJobTable == nullptr ) {
        return std::nullopt;
    }
    TruckersMP_List list;
    if( !module.m_busJobTable->GetStops( module.m_ctx, m_handle, &list ) ) {
        return std::nullopt;
    }
    std::vector< BusStop > values;
    values.reserve( list.m_count );
    for( Uint32 i = 0; i < list.m_count; ++i )
    {
        const TruckersMP_BusStop_Handle &native = *( const TruckersMP_BusStop_Handle * )(
            ( const Uint8 * )list.m_items + ( Uint64 )i * list.m_stride );
        values.emplace_back( BusStop( m_module, native ) );
    }
    m_module->m_session->RawFree( list.m_items );
    return values;
}

inline std::optional< Uint32 > BusJob::GetStartTime() const
{
    if( !IsValid() ) {
        return std::nullopt;
    }
    const BusModule &module = *m_module;
    if( module.m_busJobTable == nullptr ) {
        return std::nullopt;
    }
    Uint32 native;
    if( !module.m_busJobTable->GetStartTime( module.m_ctx, m_handle, &native ) ) {
        return std::nullopt;
    }
    return native;
}

inline std::optional< Uint32 > BusJob::GetPassengerCount() const
{
    if( !IsValid() ) {
        return std::nullopt;
    }
    const BusModule &module = *m_module;
    if( module.m_busJobTable == nullptr ) {
        return std::nullopt;
    }
    Uint32 native;
    if( !module.m_busJobTable->GetPassengerCount( module.m_ctx, m_handle, &native ) ) {
        return std::nullopt;
    }
    return native;
}

inline std::optional< std::string > BusStop::GetName() const
{
    if( !IsValid() ) {
        return std::nullopt;
    }
    const BusModule &module = *m_module;
    if( module.m_busStopTable == nullptr ) {
        return std::nullopt;
    }
    TruckersMP_String native;
    if( !module.m_busStopTable->GetName( module.m_ctx, m_handle, &native ) ) {
        return std::nullopt;
    }
    std::string value( native.m_ptr, native.m_size );
    m_module->m_session->RawFree( native.m_ptr );
    return value;
}

inline std::optional< std::string > BusStop::GetCityIdentifier() const
{
    if( !IsValid() ) {
        return std::nullopt;
    }
    const BusModule &module = *m_module;
    if( module.m_busStopTable == nullptr ) {
        return std::nullopt;
    }
    TruckersMP_String native;
    if( !module.m_busStopTable->GetCityIdentifier( module.m_ctx, m_handle, &native ) ) {
        return std::nullopt;
    }
    std::string value( native.m_ptr, native.m_size );
    m_module->m_session->RawFree( native.m_ptr );
    return value;
}

inline std::optional< Uint32 > BusStop::GetScheduledTime() const
{
    if( !IsValid() ) {
        return std::nullopt;
    }
    const BusModule &module = *m_module;
    if( module.m_busStopTable == nullptr ) {
        return std::nullopt;
    }
    Uint32 native;
    if( !module.m_busStopTable->GetScheduledTime( module.m_ctx, m_handle, &native ) ) {
        return std::nullopt;
    }
    return native;
}

inline std::optional< Float > BusStop::GetPlannedDistance() const
{
    if( !IsValid() ) {
        return std::nullopt;
    }
    const BusModule &module = *m_module;
    if( module.m_busStopTable == nullptr ) {
        return std::nullopt;
    }
    Float native;
    if( !module.m_busStopTable->GetPlannedDistance( module.m_ctx, m_handle, &native ) ) {
        return std::nullopt;
    }
    return native;
}

inline std::optional< Uint8 > BusStop::GetBoardingPassengers() const
{
    if( !IsValid() ) {
        return std::nullopt;
    }
    const BusModule &module = *m_module;
    if( module.m_busStopTable == nullptr ) {
        return std::nullopt;
    }
    Uint8 native;
    if( !module.m_busStopTable->GetBoardingPassengers( module.m_ctx, m_handle, &native ) ) {
        return std::nullopt;
    }
    return native;
}

inline std::optional< Uint8 > BusStop::GetLeavingPassengers() const
{
    if( !IsValid() ) {
        return std::nullopt;
    }
    const BusModule &module = *m_module;
    if( module.m_busStopTable == nullptr ) {
        return std::nullopt;
    }
    Uint8 native;
    if( !module.m_busStopTable->GetLeavingPassengers( module.m_ctx, m_handle, &native ) ) {
        return std::nullopt;
    }
    return native;
}

inline std::optional< BusJob > BusModule::GetJob() const
{
    if( m_busTable == nullptr ) {
        return std::nullopt;
    }
    TruckersMP_BusJob_Handle native;
    if( !m_busTable->GetJob( m_ctx, &native ) ) {
        return std::nullopt;
    }
    return BusJob( const_cast< BusModule * >( this ), native );
}

inline void TMP_API Bus_Dispatch_BusJobStarted( void *userCtx, uint64_t /*eventId*/, void *payload, uint32_t payloadSize )
{
    BusModule *const owner = static_cast< BusModule * >( userCtx );
    if( owner == nullptr || payload == nullptr || payloadSize < sizeof( TruckersMP_Evt_BusJobStarted ) ) {
        return;
    }
    BusJobStartedEvent args( owner, static_cast< TruckersMP_Evt_BusJobStarted * >( payload ) );
    owner->OnJobStarted.Call( args );
}

inline void TMP_API Bus_Dispatch_BusJobDataReady( void *userCtx, uint64_t /*eventId*/, void *payload, uint32_t payloadSize )
{
    BusModule *const owner = static_cast< BusModule * >( userCtx );
    if( owner == nullptr || payload == nullptr || payloadSize < sizeof( TruckersMP_Evt_BusJobDataReady ) ) {
        return;
    }
    BusJobDataReadyEvent args( owner, static_cast< TruckersMP_Evt_BusJobDataReady * >( payload ) );
    owner->OnJobDataReady.Call( args );
}

inline void TMP_API Bus_Dispatch_BusJobCanceled( void *userCtx, uint64_t /*eventId*/, void *payload, uint32_t payloadSize )
{
    BusModule *const owner = static_cast< BusModule * >( userCtx );
    if( owner == nullptr || payload == nullptr || payloadSize < sizeof( TruckersMP_Evt_BusJobCanceled ) ) {
        return;
    }
    BusJobCanceledEvent args( owner, static_cast< TruckersMP_Evt_BusJobCanceled * >( payload ) );
    owner->OnJobCanceled.Call( args );
}

inline void TMP_API Bus_Dispatch_BusJobFinished( void *userCtx, uint64_t /*eventId*/, void *payload, uint32_t payloadSize )
{
    BusModule *const owner = static_cast< BusModule * >( userCtx );
    if( owner == nullptr || payload == nullptr || payloadSize < sizeof( TruckersMP_Evt_BusJobFinished ) ) {
        return;
    }
    BusJobFinishedEvent args( owner, static_cast< TruckersMP_Evt_BusJobFinished * >( payload ) );
    owner->OnJobFinished.Call( args );
}

inline void TMP_API Bus_Dispatch_BusNextStop( void *userCtx, uint64_t /*eventId*/, void *payload, uint32_t payloadSize )
{
    BusModule *const owner = static_cast< BusModule * >( userCtx );
    if( owner == nullptr || payload == nullptr || payloadSize < sizeof( TruckersMP_Evt_BusNextStop ) ) {
        return;
    }
    BusNextStopEvent args( owner, static_cast< TruckersMP_Evt_BusNextStop * >( payload ) );
    owner->OnNextStop.Call( args );
}

inline void TMP_API Bus_Dispatch_BusStopActivated( void *userCtx, uint64_t /*eventId*/, void *payload, uint32_t payloadSize )
{
    BusModule *const owner = static_cast< BusModule * >( userCtx );
    if( owner == nullptr || payload == nullptr || payloadSize < sizeof( TruckersMP_Evt_BusStopActivated ) ) {
        return;
    }
    BusStopActivatedEvent args( owner, static_cast< TruckersMP_Evt_BusStopActivated * >( payload ) );
    owner->OnStopActivated.Call( args );
}

inline void TMP_API Bus_Dispatch_BusStopCompleted( void *userCtx, uint64_t /*eventId*/, void *payload, uint32_t payloadSize )
{
    BusModule *const owner = static_cast< BusModule * >( userCtx );
    if( owner == nullptr || payload == nullptr || payloadSize < sizeof( TruckersMP_Evt_BusStopCompleted ) ) {
        return;
    }
    BusStopCompletedEvent args( owner, static_cast< TruckersMP_Evt_BusStopCompleted * >( payload ) );
    owner->OnStopCompleted.Call( args );
}

inline std::unique_ptr< BusModule > BusModule::Attach( Session &session )
{
    session.RawUnlockIntent( TRUCKERSMP_INTENT_KEY_BUS );

    const void *table = session.GetRawApi( TRUCKERSMP_API_BUS );
    if( table == nullptr ) return nullptr;
    std::unique_ptr< BusModule > module( new BusModule() );
    module->m_session = &session;
    module->m_busTable = static_cast< const TruckersMP_Bus * >( table );
    module->m_busJobTable = static_cast< const TruckersMP_BusJob * >( session.GetRawApi( TRUCKERSMP_API_BUS_JOB ) );
    module->m_busStopTable = static_cast< const TruckersMP_BusStop * >( session.GetRawApi( TRUCKERSMP_API_BUS_STOP ) );
    module->m_ctx = session.RawCtx();

    module->OnJobStarted.Internal_SetActivationHook( [ owner = module.get() ]( Bool active )
    {
        if( active ) {
            owner->m_session->AddRawListener( TRUCKERSMP_EVT_BUS_JOB_STARTED, &Bus_Dispatch_BusJobStarted, owner );
        } else {
            owner->m_session->RemoveRawListener( TRUCKERSMP_EVT_BUS_JOB_STARTED, &Bus_Dispatch_BusJobStarted, owner );
        }
    } );

    module->OnJobDataReady.Internal_SetActivationHook( [ owner = module.get() ]( Bool active )
    {
        if( active ) {
            owner->m_session->AddRawListener( TRUCKERSMP_EVT_BUS_JOB_DATA_READY, &Bus_Dispatch_BusJobDataReady, owner );
        } else {
            owner->m_session->RemoveRawListener( TRUCKERSMP_EVT_BUS_JOB_DATA_READY, &Bus_Dispatch_BusJobDataReady, owner );
        }
    } );

    module->OnJobCanceled.Internal_SetActivationHook( [ owner = module.get() ]( Bool active )
    {
        if( active ) {
            owner->m_session->AddRawListener( TRUCKERSMP_EVT_BUS_JOB_CANCELED, &Bus_Dispatch_BusJobCanceled, owner );
        } else {
            owner->m_session->RemoveRawListener( TRUCKERSMP_EVT_BUS_JOB_CANCELED, &Bus_Dispatch_BusJobCanceled, owner );
        }
    } );

    module->OnJobFinished.Internal_SetActivationHook( [ owner = module.get() ]( Bool active )
    {
        if( active ) {
            owner->m_session->AddRawListener( TRUCKERSMP_EVT_BUS_JOB_FINISHED, &Bus_Dispatch_BusJobFinished, owner );
        } else {
            owner->m_session->RemoveRawListener( TRUCKERSMP_EVT_BUS_JOB_FINISHED, &Bus_Dispatch_BusJobFinished, owner );
        }
    } );

    module->OnNextStop.Internal_SetActivationHook( [ owner = module.get() ]( Bool active )
    {
        if( active ) {
            owner->m_session->AddRawListener( TRUCKERSMP_EVT_BUS_NEXT_STOP, &Bus_Dispatch_BusNextStop, owner );
        } else {
            owner->m_session->RemoveRawListener( TRUCKERSMP_EVT_BUS_NEXT_STOP, &Bus_Dispatch_BusNextStop, owner );
        }
    } );

    module->OnStopActivated.Internal_SetActivationHook( [ owner = module.get() ]( Bool active )
    {
        if( active ) {
            owner->m_session->AddRawListener( TRUCKERSMP_EVT_BUS_STOP_ACTIVATED, &Bus_Dispatch_BusStopActivated, owner );
        } else {
            owner->m_session->RemoveRawListener( TRUCKERSMP_EVT_BUS_STOP_ACTIVATED, &Bus_Dispatch_BusStopActivated, owner );
        }
    } );

    module->OnStopCompleted.Internal_SetActivationHook( [ owner = module.get() ]( Bool active )
    {
        if( active ) {
            owner->m_session->AddRawListener( TRUCKERSMP_EVT_BUS_STOP_COMPLETED, &Bus_Dispatch_BusStopCompleted, owner );
        } else {
            owner->m_session->RemoveRawListener( TRUCKERSMP_EVT_BUS_STOP_COMPLETED, &Bus_Dispatch_BusStopCompleted, owner );
        }
    } );

    session.AddRawDetachHook( module.get(), &BusModule::RawDetach );

    return module;
}

inline BusModule::~BusModule()
{
    if( m_session != nullptr ) {
        m_session->RemoveRawDetachHook( this );
    }
    Teardown();
}

inline void BusModule::RawDetach( void *module )
{
    static_cast< BusModule * >( module )->Teardown();
}

inline void BusModule::Teardown()
{
    if( m_session == nullptr ) {
        return;
    }

    OnJobStarted.UnregisterAll();
    OnJobDataReady.UnregisterAll();
    OnJobCanceled.UnregisterAll();
    OnJobFinished.UnregisterAll();
    OnNextStop.UnregisterAll();
    OnStopActivated.UnregisterAll();
    OnStopCompleted.UnregisterAll();

    OnJobStarted.Internal_SetActivationHook( {} );
    OnJobDataReady.Internal_SetActivationHook( {} );
    OnJobCanceled.Internal_SetActivationHook( {} );
    OnJobFinished.Internal_SetActivationHook( {} );
    OnNextStop.Internal_SetActivationHook( {} );
    OnStopActivated.Internal_SetActivationHook( {} );
    OnStopCompleted.Internal_SetActivationHook( {} );

    m_busTable = nullptr;
    m_busJobTable = nullptr;
    m_busStopTable = nullptr;
    m_session = nullptr;
}

} // namespace TruckersMP

/* eof */
