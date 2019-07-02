/*******************************************************************************
 * Copyright (C) <2018-2019> Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 ******************************************************************************/

#ifndef __FILEPUBLISHER_H__
#define __FILEPUBLISHER_H__

#include "gva_json_meta.h"
#include <gst/gst.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "statusmessage.h"

// File specific constants
typedef enum _tagPublishOutputFormat { E_OF_STREAM = 0, E_OF_BATCH = 1 } PublishOutputFormat;

typedef struct _FilePublishConfig FilePublishConfig;

struct _FilePublishConfig {
    gchar *file_path;
    PublishOutputFormat e_output_format;
    gboolean signal_handoffs;
};

#define OF_BATCH "batch"
#define OF_STREAM "stream"
#define MAX_RESPONSE_MESSAGE 1024
#define MIN_FILE_LEN 4

MetapublishStatusMessage file_open(FILE *pFile, FilePublishConfig *config);
MetapublishStatusMessage file_close(FILE *pFile, FilePublishConfig *config);
MetapublishStatusMessage file_write(FILE *pFile, FilePublishConfig *config, GstBuffer *buffer);

enum _publish_error {
    E_PUBLISH_SUCCESS = 0,
    E_PUBLISH_ERROR = -1,
    E_PUBLISH_ERROR_WRITING_FILE = -2,
    E_PUBLISH_ERROR_NO_INFERENCE = -3,
    E_PUBLISH_ERROR_FILE_EXISTS = -4,
    E_PUBLISH_ERROR_FILE_CREATE = -5,
    E_PUBLISH_ERROR_INVALID_FILEPATH = -6
};

#endif