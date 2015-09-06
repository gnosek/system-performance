#!/bin/bash

blkparse -i "$@" -F 'Q,IO_BEGIN %M:%m %S %n %T.%t\n' -F 'C,IO_END %M:%m %S %n %T.%t\n' | grep ^IO_
