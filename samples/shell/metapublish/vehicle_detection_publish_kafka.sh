#!/bin/bash
# ==============================================================================
# Copyright (C) 2018-2019 Intel Corporation
#
# SPDX-License-Identifier: MIT
# ==============================================================================

set -e

BASEDIR=$(dirname "$0")/../../..
if [ -n ${GST_SAMPLES_DIR} ]
then
    source $BASEDIR/scripts/setup_env.sh
fi

#import GET_MODEL_PATH
source $BASEDIR/scripts/path_extractor.sh

FILE=${1:-$VIDEO_EXAMPLES_DIR/Pexels_Videos_4786_960x540.mp4}

MODEL=vehicle-license-plate-detection-barrier-0106

DEVICE=CPU

DETECT_MODEL_PATH=$(GET_MODEL_PATH $MODEL )

if ldconfig -p | grep -q librdkafka
then
        echo "Rdkafka library found";
else
        echo "No Rdkafka library found, please run the install_dependencies.sh script in the scripts folder";
        exit 1
fi


# Note that two pipelines create instances of singleton element 'inf0', so we can specify parameters only in first instance
gst-launch-1.0 --gst-plugin-path ${GST_PLUGIN_PATH} \
                filesrc location=$FILE ! decodebin ! video/x-raw ! videoconvert ! \
                gvadetect inference-id=inf0 model=$DETECT_MODEL_PATH device=$DEVICE every-nth-frame=1 batch-size=1 ! queue ! \
                gvawatermark ! videoconvert ! fakesink \
                filesrc location=${FILE} ! decodebin ! video/x-raw ! videoconvert ! gvadetect inference-id=inf0 ! \
                gvametaconvert converter=json method=all ! \
		gvametapublish method=kafka address=kafka:9092 topic=test ! \
                queue ! gvawatermark ! videoconvert ! fakesink
