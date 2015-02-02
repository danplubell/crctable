module CrcTable where

import Data.Bits
import Data.Word

buildTable::[Word16]
buildTable = map (tableEntry.flip shiftL 8 ) [0..255]
  where tableEntry n = foldl calcaccum 0 [0..7]
          where calcaccum accum d = if(((n `shiftL` d) `xor` accum) .&. 0x8000) /= 0
                                    then (accum `shiftL` 1) `xor` 0x1021
                                    else accum `shiftL` 1
