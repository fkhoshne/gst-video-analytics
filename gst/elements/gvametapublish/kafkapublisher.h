/*******************************************************************************
 * Copyright (C) 2018-2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 ******************************************************************************/

#ifndef __KAFKAPUBLISHER_H__
#define __KAFKAPUBLISHER_H__

#include "gva_json_meta.h"
#include <gst/gst.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "statusmessage.h"

#ifdef KAFKA_INC
#include "librdkafka/rdkafka.h"

typedef struct _KafkaPublishConfig KafkaPublishConfig;

struct _KafkaPublishConfig {
    gchar *address;
    gchar *topic;
    gboolean signal_handoffs;
};

void kafka_open_connection(KafkaPublishConfig*, rd_kafka_t*, rd_kafka_topic_t*);
void kafka_close_connection(rd_kafka_t*, rd_kafka_topic_t*);
MetapublishStatusMessage kafka_write_message(rd_kafka_t *producerHandler, rd_kafka_topic_t *rkt, GstBuffer *buffer);
#endif

#endif
