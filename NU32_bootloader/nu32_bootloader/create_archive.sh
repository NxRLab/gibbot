#!/bin/bash
git archive master --prefix=nu32_bootloader/ | bzip2 >nu32_bootloader-$(git rev-parse HEAD | cut -c -8).tar.bz2
