//==============================================================================
// Copyright (c) 2015-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief THIS CODE WAS AUTOGENERATED BY PASSTHROUGHGENERATOR ON 07/11/16
//==============================================================================

#include <iostream>
#include <cstring>
#include <stdlib.h>

#include "Logger.h"

#include "../HSAPMCInterceptionHelpers.h"

#include "HSAPMCInterception.h"

#ifdef FUTURE_ROCR_VERSION
CoreApiTable*      g_pRealCoreFunctions         = nullptr;
FinalizerExtTable* g_pRealFinalizerExtFunctions = nullptr;
ImageExtTable*     g_pRealImageExtFunctions     = nullptr;
AmdExtTable*       g_pRealAmdExtFunctions       = nullptr;
#else
ApiTable* g_pRealCoreFunctions         = nullptr;
ExtTable* g_pRealFinalizerExtFunctions = nullptr;
ExtTable* g_pRealImageExtFunctions     = nullptr;
#endif

hsa_status_t HSA_PMC_hsa_agent_get_info(hsa_agent_t agent, hsa_agent_info_t attribute, void* value)
{
    hsa_status_t retVal = g_pRealCoreFunctions->hsa_agent_get_info_fn(agent, attribute, value);
    HSA_PMC_hsa_agent_get_info_PostCallHelper(retVal, agent, attribute, value);

    return retVal;
}

hsa_status_t HSA_PMC_hsa_queue_create(hsa_agent_t agent, uint32_t size, hsa_queue_type_t type, void (*callback)(hsa_status_t status, hsa_queue_t* source, void* data), void* data, uint32_t private_segment_size, uint32_t group_segment_size, hsa_queue_t** queue)
{
    // SoftCP mode requires a queue to be able to handle at least 128 packets
    if (MIN_QUEUE_SIZE_FOR_SOFTCP > size)
    {
        std::cout << "The CodeXL GPU Profiler is overriding the queue size passed to hsa_queue_create.\nQueues must have a size of at least " << MIN_QUEUE_SIZE_FOR_SOFTCP << " in order to support profiling." << std::endl;
        size = MIN_QUEUE_SIZE_FOR_SOFTCP;
    }

    hsa_status_t retVal = g_pRealCoreFunctions->hsa_queue_create_fn(agent, size, type, callback, data, private_segment_size, group_segment_size, queue);
    HSA_PMC_hsa_queue_create_PostCallHelper(retVal, agent, size, type, callback, data, private_segment_size, group_segment_size, queue);

    return retVal;
}

hsa_status_t HSA_PMC_hsa_queue_destroy(hsa_queue_t* queue)
{
    HSA_PMC_hsa_queue_destroy_PreCallHelper(queue);
    hsa_status_t retVal = g_pRealCoreFunctions->hsa_queue_destroy_fn(queue);

    return retVal;
}

hsa_status_t HSA_PMC_hsa_executable_get_symbol(hsa_executable_t executable, const char* module_name, const char* symbol_name, hsa_agent_t agent, int32_t call_convention, hsa_executable_symbol_t* symbol)
{
    hsa_status_t retVal = g_pRealCoreFunctions->hsa_executable_get_symbol_fn(executable, module_name, symbol_name, agent, call_convention, symbol);
    HSA_PMC_hsa_executable_get_symbol_PostCallHelper(retVal, executable, module_name, symbol_name, agent, call_convention, symbol);

    return retVal;
}

#ifdef FUTURE_ROCR_VERSION
void InitHSAAPIInterceptPMC(HsaApiTable* pTable)
{
    g_pRealCoreFunctions = (CoreApiTable*)malloc(sizeof(CoreApiTable));
    memcpy(g_pRealCoreFunctions, pTable->core_, sizeof(CoreApiTable));

    g_pRealFinalizerExtFunctions = (FinalizerExtTable*)malloc(sizeof(FinalizerExtTable));
    memcpy(g_pRealFinalizerExtFunctions, pTable->finalizer_ext_, sizeof(FinalizerExtTable));

    g_pRealImageExtFunctions = (ImageExtTable*)malloc(sizeof(ImageExtTable));
    memcpy(g_pRealImageExtFunctions, pTable->image_ext_, sizeof(ImageExtTable));

    g_pRealAmdExtFunctions = (AmdExtTable*)malloc(sizeof(AmdExtTable));
    memcpy(g_pRealAmdExtFunctions, pTable->amd_ext_, sizeof(AmdExtTable));

    pTable->core_->hsa_agent_get_info_fn = HSA_PMC_hsa_agent_get_info;
    pTable->core_->hsa_queue_create_fn = HSA_PMC_hsa_queue_create;
    pTable->core_->hsa_queue_destroy_fn = HSA_PMC_hsa_queue_destroy;
    pTable->core_->hsa_executable_get_symbol_fn = HSA_PMC_hsa_executable_get_symbol;
}
#endif

void DoneHSAAPIInterceptPMC()
{
    free(g_pRealCoreFunctions);
    free(g_pRealFinalizerExtFunctions);
#ifdef FUTURE_ROCR_VERSION	
    free(g_pRealImageExtFunctions);
    free(g_pRealAmdExtFunctions);
#endif
}


