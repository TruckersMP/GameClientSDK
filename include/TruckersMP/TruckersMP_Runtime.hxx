#pragma once

#include "TruckersMP/TruckersMP_Base.h"

#include <cstring>
#include <functional>
#include <vector>

namespace TruckersMP
{

using Bool = bool;

using Int8 = int8_t;
using Int16 = int16_t;
using Int32 = int32_t;
using Int64 = int64_t;

using Uint8 = uint8_t;
using Uint16 = uint16_t;
using Uint32 = uint32_t;
using Uint64 = uint64_t;

using Float = float;
using Double = double;

using Char = char;

////////////////////////////////////////////////////////////////////////////////

template< typename... Args >
class Event final
{
public:
    using EventID = Int32;
    using Callback = std::function< void( Args... ) >;
    using ActivationHook = std::function< void( Bool ) >;

public:
    EventID Register( Callback handler )
    {
        if( m_slots.empty() )
        {
            Activate( true );
        }

        const EventID id = m_nextId++;
        m_slots.emplace_back( Slot{ id, std::move( handler ) } );
        return id;
    }

    void Unregister( EventID id )
    {
        for( size_t i = 0; i < m_slots.size(); ++i )
        {
            if( m_slots[ i ].m_id == id )
            {
                m_slots.erase( m_slots.begin() + i );

                if( m_slots.empty() )
                {
                    Activate( false );
                }

                return;
            }
        }
    }

    void UnregisterAll()
    {
        if( m_slots.empty() )
        {
            return;
        }

        m_slots.clear();
        Activate( false );
    }

    void Internal_SetActivationHook( ActivationHook hook )
    {
        m_activation = std::move( hook );

        if( !m_slots.empty() )
        {
            Activate( true );
        }
    }

    void Call( Args... args )
    {
        // Snapshot: handlers may mutate the slot list while we dispatch.
        const std::vector< Slot > snapshot = m_slots;
        for( const Slot &slot : snapshot )
        {
            slot.m_callback( args... );
        }
    }

private:
    void Activate( Bool active )
    {
        if( m_activation )
        {
            m_activation( active );
        }
    }

    struct Slot
    {
        EventID m_id;
        Callback m_callback;
    };

    EventID m_nextId = 0;
    std::vector< Slot > m_slots;
    ActivationHook m_activation;
};

////////////////////////////////////////////////////////////////////////////////

struct PluginInfo
{
    const Char *m_name = nullptr;
    const Char *m_author = nullptr;
    const Char *m_version = nullptr;
    const Char *m_description = nullptr;
};

namespace Internal
{

template< Uint64 N >
inline void CopyString( Char( &dest )[ N ], const Char *source )
{
    if( source == nullptr )
    {
        dest[ 0 ] = '\0';
        return;
    }

    Uint64 i = 0;
    for( ; i < N - 1 && source[ i ] != '\0'; ++i )
    {
        dest[ i ] = source[ i ];
    }
    dest[ i ] = '\0';
}

} // namespace Internal

inline void FillPluginDesc( TruckersMP_PluginDesc *desc, const PluginInfo &info )
{
    if( desc == nullptr )
    {
        return;
    }

    Internal::CopyString( desc->m_name, info.m_name );
    Internal::CopyString( desc->m_author, info.m_author );
    Internal::CopyString( desc->m_version, info.m_version );
    Internal::CopyString( desc->m_description, info.m_description );
}

} // namespace TruckersMP

/* eof */
