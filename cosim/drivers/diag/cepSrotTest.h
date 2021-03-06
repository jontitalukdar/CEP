//************************************************************************
// Copyright (C) 2020 Massachusetts Institute of Technology
// SPDX License Identifier: MIT
//
// File Name:      
// Program:        Common Evaluation Platform (CEP)
// Description:    
// Notes:          
//
//************************************************************************

#ifndef cepSrotTest_H
#define cepSrotTest_H

#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>

  // ----------------------------------------------------------------------------
  // LLKI related constants, structures, and function prototypes  
  // ----------------------------------------------------------------------------

  // LLKI Message ID constants
  const uint8_t   LLKI_MID_C2LOADKEYREQ             = 0x00;
  const uint8_t   LLKI_MID_C2CLEARKEYREQ            = 0x01;
  const uint8_t   LLKI_MID_C2KEYSTATUSREQ           = 0x02;
  const uint8_t   LLKI_MID_C2LOADKEYACK             = 0x03;
  const uint8_t   LLKI_MID_C2CLEARKEYACK            = 0x04;
  const uint8_t   LLKI_MID_C2KEYSTATUSRESP          = 0x05;
  const uint8_t   LLKI_MID_C2ERRORRESP              = 0x06;

  // LLKI Status Constants
  const uint8_t   LLKI_STATUS_GOOD                  = 0x00;
  const uint8_t   LLKI_STATUS_KEY_PRESENT           = 0x01;
  const uint8_t   LLKI_STATUS_KEY_NOT_PRESENT       = 0x02;

  const uint8_t   LLKI_STATUS_BAD_MSG_ID            = 0x20;
  const uint8_t   LLKI_STATUS_BAD_MSG_LEN           = 0x21;
  const uint8_t   LLKI_STATUS_KEY_INDEX_EXCEED      = 0x22; // Specified key index exceeds size
                                                            // of key index ram
  const uint8_t   LLKI_STATUS_KEY_INDEX_INVALID     = 0x23;
  const uint8_t   LLKI_STATUS_BAD_POINTER_PAIR      = 0x24;
  const uint8_t   LLKI_STATUS_BAD_CORE_INDEX        = 0x25;
  const uint8_t   LLKI_STATUS_KL_REQ_BAD_MSG_ID     = 0x26;
  const uint8_t   LLKI_STATUS_KL_REQ_BAD_MSG_LEN    = 0x27;
  const uint8_t   LLKI_STATUS_KL_RESP_BAD_MSG_ID    = 0x28;
  const uint8_t   LLKI_STATUS_KL_TILELINK_ERROR     = 0x29;
  const uint8_t   LLKI_STATUS_KL_LOSS_OF_SYNC       = 0x30;

  const uint8_t   LLKI_STATUS_UNKNOWN_ERROR         = 0xFF;

  // LLKI Core Index Constants
  const uint8_t   LLKI_AES_CORE_INDEX               = 0x00;
  const uint8_t   LLKI_INVALID_CORE_INDEX           = 0xFF;

  const uint8_t   LLKI_KEYINDEX_VALID               = 0x80;

  // Packing macro for creating an LLKIC2 message to send to the SRoT 
  #define llkic2_pack(msg_id, status, msg_len, key_index, rsvd1) { \
    (((uint64_t)msg_id << 0)            & 0x00000000000000FF) | \
    (((uint64_t)status << 8)            & 0x000000000000FF00) | \
    (((uint64_t)msg_len << 16)          & 0x0000000000FF0000) | \
    (((uint64_t)key_index << 24)        & 0x00000000FF000000) | \
    (((uint64_t)rsvd1 << 32)            & 0xFFFFFFFF00000000) \
  }

  // Packing macro for creating a Key Index entry
  #define key_index_pack(low_pointer, high_pointer, core_index, valid) { \
    (((uint64_t)low_pointer << 0)       & 0x000000000000FFFF) | \
    (((uint64_t)high_pointer << 16)     & 0x00000000FFFF0000) | \
    (((uint64_t)core_index << 32)       & 0x000000FF00000000) | \
    (((uint64_t)valid << 63)            & 0x8000000000000000) \
  }

  // Helper macros for response message processing
  #define llkic2_extract_status(message) { \
    (uint8_t)(((uint64_t)message >> 8)  & 0x00000000000000FF) \
  }

  // LLKI helper functions
  uint8_t send_srot_message(int verbose, uint64_t message);
  int parse_message_status(uint8_t message_status, int verbose);

  // Mock TSS Keys
  const uint64_t  AES_MOCK_TSS_KEY_0      = 0x0123456789ABCDEF;
  const uint64_t  AES_MOCK_TSS_KEY_1      = 0xFEDCBA9876543210;

  //
  // The test itself
  //
  int cepSrotTest_runTest(int cpuId, int seed, int verbose);

#endif
