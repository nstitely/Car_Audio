sudo rtl_fm -f ${1}M -M fm -s 170k -E deemp -E dc | ffmpeg -f s16le -i pipe: -ar 170k -f wav pipe: | aplay
