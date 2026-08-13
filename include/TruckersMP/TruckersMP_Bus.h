/* Generated file. Do not edit. */

#ifndef TMP_SDK_BUS_H
#define TMP_SDK_BUS_H

#include "TruckersMP/TruckersMP.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define TRUCKERSMP_INTENT_KEY_BUS "736c612c4dd271e0b7f36960937f63db"

typedef int32_t TruckersMP_BusJobCancellationReason;
enum
{
    TruckersMP_BusJobCancellationReason_ExistingJob = 0,
    TruckersMP_BusJobCancellationReason_Abandon = 1,
    TruckersMP_BusJobCancellationReason_Incompatible = 2,
    TruckersMP_BusJobCancellationReason_ExternalSource = 3,
};

typedef struct TruckersMP_BusJob_Handle { uint64_t m_value; } TruckersMP_BusJob_Handle; /* 0 = invalid */

typedef struct TruckersMP_BusStop_Handle { uint64_t m_value; } TruckersMP_BusStop_Handle; /* 0 = invalid */

#define TRUCKERSMP_API_BUS 0x557d40fa8a53c90full

typedef struct TruckersMP_Bus
{
    bool( TMP_API *GetJob )( TruckersMP_PluginContext *ctx, TruckersMP_BusJob_Handle *out );
} TruckersMP_Bus;

#define TRUCKERSMP_API_BUS_JOB 0x2aae708e9504c09dull

typedef struct TruckersMP_BusJob
{
    bool( TMP_API *GetStops )( TruckersMP_PluginContext *ctx, TruckersMP_BusJob_Handle self, TruckersMP_List *out ); /* free out->m_items once via TruckersMP_Host::Free; element strings live inside that block */
    bool( TMP_API *GetStartTime )( TruckersMP_PluginContext *ctx, TruckersMP_BusJob_Handle self, uint32_t *out );
    bool( TMP_API *GetPassengerCount )( TruckersMP_PluginContext *ctx, TruckersMP_BusJob_Handle self, uint32_t *out );
} TruckersMP_BusJob;

#define TRUCKERSMP_API_BUS_STOP 0x8aaa2ad91e702e41ull

typedef struct TruckersMP_BusStop
{
    bool( TMP_API *GetName )( TruckersMP_PluginContext *ctx, TruckersMP_BusStop_Handle self, TruckersMP_String *out ); /* free out->m_ptr once via TruckersMP_Host::Free */
    bool( TMP_API *GetCityIdentifier )( TruckersMP_PluginContext *ctx, TruckersMP_BusStop_Handle self, TruckersMP_String *out ); /* free out->m_ptr once via TruckersMP_Host::Free */
    bool( TMP_API *GetScheduledTime )( TruckersMP_PluginContext *ctx, TruckersMP_BusStop_Handle self, uint32_t *out );
    bool( TMP_API *GetPlannedDistance )( TruckersMP_PluginContext *ctx, TruckersMP_BusStop_Handle self, float *out );
    bool( TMP_API *GetBoardingPassengers )( TruckersMP_PluginContext *ctx, TruckersMP_BusStop_Handle self, uint8_t *out );
    bool( TMP_API *GetLeavingPassengers )( TruckersMP_PluginContext *ctx, TruckersMP_BusStop_Handle self, uint8_t *out );
} TruckersMP_BusStop;

#define TRUCKERSMP_EVT_BUS_JOB_STARTED 0x06f3c4dde622f80full

typedef struct TruckersMP_Evt_BusJobStarted
{
    TruckersMP_BusJob_Handle m_job;
    int64_t m_estimatedPayout;
} TruckersMP_Evt_BusJobStarted;
TRUCKERSMP_ASSERT_SIZE( TruckersMP_Evt_BusJobStarted, 16 );
TRUCKERSMP_ASSERT_OFFSET( TruckersMP_Evt_BusJobStarted, m_job, 0 );
TRUCKERSMP_ASSERT_OFFSET( TruckersMP_Evt_BusJobStarted, m_estimatedPayout, 8 );

#define TRUCKERSMP_EVT_BUS_JOB_DATA_READY 0x659ce81c83522d9full

typedef struct TruckersMP_Evt_BusJobDataReady
{
    TruckersMP_BusJob_Handle m_job;
    TruckersMP_List m_stops;
} TruckersMP_Evt_BusJobDataReady;
TRUCKERSMP_ASSERT_SIZE( TruckersMP_Evt_BusJobDataReady, 24 );
TRUCKERSMP_ASSERT_OFFSET( TruckersMP_Evt_BusJobDataReady, m_job, 0 );
TRUCKERSMP_ASSERT_OFFSET( TruckersMP_Evt_BusJobDataReady, m_stops, 8 );

#define TRUCKERSMP_EVT_BUS_JOB_CANCELED 0xae7618764b23ae16ull

typedef struct TruckersMP_Evt_BusJobCanceled
{
    TruckersMP_BusJob_Handle m_job;
    TruckersMP_BusJobCancellationReason m_reason;
} TruckersMP_Evt_BusJobCanceled;
TRUCKERSMP_ASSERT_SIZE( TruckersMP_Evt_BusJobCanceled, 16 );
TRUCKERSMP_ASSERT_OFFSET( TruckersMP_Evt_BusJobCanceled, m_job, 0 );
TRUCKERSMP_ASSERT_OFFSET( TruckersMP_Evt_BusJobCanceled, m_reason, 8 );

#define TRUCKERSMP_EVT_BUS_JOB_FINISHED 0x8e3301ac89383040ull

typedef struct TruckersMP_Evt_BusJobFinished
{
    TruckersMP_BusJob_Handle m_job;
    int64_t m_payout;
} TruckersMP_Evt_BusJobFinished;
TRUCKERSMP_ASSERT_SIZE( TruckersMP_Evt_BusJobFinished, 16 );
TRUCKERSMP_ASSERT_OFFSET( TruckersMP_Evt_BusJobFinished, m_job, 0 );
TRUCKERSMP_ASSERT_OFFSET( TruckersMP_Evt_BusJobFinished, m_payout, 8 );

#define TRUCKERSMP_EVT_BUS_NEXT_STOP 0x7dba4f6419fb16dcull

typedef struct TruckersMP_Evt_BusNextStop
{
    TruckersMP_BusJob_Handle m_job;
    TruckersMP_BusStop_Handle m_stop;
} TruckersMP_Evt_BusNextStop;
TRUCKERSMP_ASSERT_SIZE( TruckersMP_Evt_BusNextStop, 16 );
TRUCKERSMP_ASSERT_OFFSET( TruckersMP_Evt_BusNextStop, m_job, 0 );
TRUCKERSMP_ASSERT_OFFSET( TruckersMP_Evt_BusNextStop, m_stop, 8 );

#define TRUCKERSMP_EVT_BUS_STOP_ACTIVATED 0x25f81257723ec8cfull

typedef struct TruckersMP_Evt_BusStopActivated
{
    TruckersMP_BusJob_Handle m_job;
    TruckersMP_BusStop_Handle m_stop;
} TruckersMP_Evt_BusStopActivated;
TRUCKERSMP_ASSERT_SIZE( TruckersMP_Evt_BusStopActivated, 16 );
TRUCKERSMP_ASSERT_OFFSET( TruckersMP_Evt_BusStopActivated, m_job, 0 );
TRUCKERSMP_ASSERT_OFFSET( TruckersMP_Evt_BusStopActivated, m_stop, 8 );

#define TRUCKERSMP_EVT_BUS_STOP_COMPLETED 0x8c1f5cf9220f124bull

typedef struct TruckersMP_Evt_BusStopCompleted
{
    TruckersMP_BusJob_Handle m_job;
    TruckersMP_BusStop_Handle m_stop;
    float m_drivenDistance;
} TruckersMP_Evt_BusStopCompleted;
TRUCKERSMP_ASSERT_SIZE( TruckersMP_Evt_BusStopCompleted, 24 );
TRUCKERSMP_ASSERT_OFFSET( TruckersMP_Evt_BusStopCompleted, m_job, 0 );
TRUCKERSMP_ASSERT_OFFSET( TruckersMP_Evt_BusStopCompleted, m_stop, 8 );
TRUCKERSMP_ASSERT_OFFSET( TruckersMP_Evt_BusStopCompleted, m_drivenDistance, 16 );

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* TMP_SDK_BUS_H */

/* eof */
