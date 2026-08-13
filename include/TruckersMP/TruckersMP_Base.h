#ifndef TRUCKERSMP_BASE_H
#define TRUCKERSMP_BASE_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

#if defined( _WIN32 )
    #if defined( _WIN64 )
        #define TRUCKERSMP_ARCHITECTURE_X64
    #endif
#elif defined( __GNUG__ )
    #if defined( __x86_64__ )
        #define TRUCKERSMP_ARCHITECTURE_X64
    #endif
#else
    #error "Unknown compiler!"
#endif

#if !defined( TRUCKERSMP_ARCHITECTURE_X64 )
    #error "TruckersMP SDK does not support the current architecture."
#endif

#define TMP_API

#if defined( _WIN32 )
    #define TMP_EXPORT __declspec( dllexport )
#else
    #define TMP_EXPORT __attribute__( ( visibility( "default" ) ) )
#endif

// C++ and C23 spell it static_assert; _Static_assert is the legacy form.
#if defined( __cplusplus ) || ( defined( __STDC_VERSION__ ) && __STDC_VERSION__ >= 202311L )
    #define TRUCKERSMP_ASSERT( cond, msg ) static_assert( cond, msg )
#else
    #define TRUCKERSMP_ASSERT( cond, msg ) _Static_assert( cond, msg )
#endif

#define TRUCKERSMP_ASSERT_SIZE( type, size ) TRUCKERSMP_ASSERT( sizeof( type ) == size, "Incorrect size for " #type )
#define TRUCKERSMP_ASSERT_OFFSET( type, member, offset ) TRUCKERSMP_ASSERT( offsetof( type, member ) == offset, "Incorrect offset for " #type "." #member )

typedef int32_t TruckersMP_EResult;

/*
 * A string buffer returned by a getter. The memory is allocated by the client;
 * the receiver must free the memory. Not NUL-terminated.
 *
 * Ownership depends on where the instance comes from:
 *
 * - a string getter's result is one client allocation: the receiver frees
 *   `m_ptr` exactly once through TruckersMP_Host::Free;
 * - a string passed into a call, or carried by an event payload, is borrowed
 *   and valid only for the duration of that call or callback; no need to free;
 * - a string inside a list element is part of the list's storage and follows
 *   the list's rules; the string is never freed on its own.
 */
typedef struct TruckersMP_String
{
    const char *m_ptr;
    uint32_t m_size;
} TruckersMP_String;

/*
 * A list view: `m_count` elements of `m_stride` bytes each.
 *
 * Ownership follows the same rule as strings:
 *
 * - carried by an event payload, the view is borrowed, valid only for the
 *   duration of that callback, and never freed by the receiver;
 * - a list getter's result is one client allocation holding the elements and
 *   every string byte they reference. The receiver frees `m_items` exactly once
 *   through TruckersMP_Host::Free, and nothing else: the element strings live
 *   inside that same allocation.
 */
typedef struct TruckersMP_List
{
    const void *m_items;
    uint32_t m_count;
    uint32_t m_stride;
} TruckersMP_List;

typedef struct TruckersMP_PluginContext TruckersMP_PluginContext;

typedef void( TMP_API *TruckersMP_EventFn )(
    void *userCtx,
    uint64_t eventId,
    void *payload,
    uint32_t payloadSize );

/*
 * The host interface handed to the plugin at entry.
 */
typedef struct TruckersMP_Host
{
    uint32_t m_size;
    TruckersMP_PluginContext *m_ctx;

    TruckersMP_EResult( TMP_API *DeclareVersion )( TruckersMP_PluginContext *ctx, uint32_t sdkVersion );
    const void *( TMP_API *GetApi )( TruckersMP_PluginContext *ctx, uint64_t id );
    void( TMP_API *Free )( TruckersMP_PluginContext *ctx, void *ptr );
} TruckersMP_Host;

/*
 * Plugin descriptor, filled by the plugin during the init call.
 */
typedef struct TruckersMP_PluginDesc
{
    uint32_t m_size;

    char m_name[ 64 ];
    char m_author[ 64 ];
    char m_version[ 32 ];
    char m_description[ 512 ];
} TruckersMP_PluginDesc;

/*
 * The two exports a plugin must provide.
 *
 * truckersmp_init returns true to finish loading. Returning false refuses the
 * load: the plugin must have cleaned up already, and the client unloads it
 * without calling truckersmp_shutdown.
 */
TMP_EXPORT bool TMP_API truckersmp_init( const TruckersMP_Host *host, TruckersMP_PluginDesc *desc );
TMP_EXPORT void TMP_API truckersmp_shutdown( void );

typedef bool( TMP_API *TruckersMP_PluginEntryFn )( const TruckersMP_Host *host, TruckersMP_PluginDesc *desc );
typedef void( TMP_API *TruckersMP_PluginShutdownFn )( void );

TRUCKERSMP_ASSERT_SIZE( TruckersMP_String, 16 );
TRUCKERSMP_ASSERT_SIZE( TruckersMP_List, 16 );
TRUCKERSMP_ASSERT_SIZE( TruckersMP_Host, 40 );
TRUCKERSMP_ASSERT_SIZE( TruckersMP_PluginDesc, 676 );

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* TRUCKERSMP_BASE_H */

/* eof */
