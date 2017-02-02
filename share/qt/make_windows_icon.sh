#!/bin/bash
# create multiresolution windows icon
ICON_DST=../../src/qt/res/icons/stepcoin.ico

convert ../../src/qt/res/icons/ico/stepcoin_16.png ../../src/qt/res/icons/ico/stepcoin_64.png ../../src/qt/res/icons/ico/stepcoin_128.png ../../src/qt/res/icons/ico/stepcoin_256.png ${ICON_DST}
