#!/usr/bin/env python3

import sys
import os
import os.path
import glob
import re
from pathlib import Path

exported = {}
characters_to_load = []
def char2unicode(ch):
    if ord(ch) > 128:
        formatted = f"{ord(ch)}".zfill(5)
        if not ch in exported:
            print(f"{ch} - {formatted}")
            exported[ch] = exported
            characters_to_load.append(ch)
        return "{"+formatted+"}"
    else:
        return f"{ch}"

if len(sys.argv) > 1:
    path = sys.argv[1]
else:
    path = os.path.abspath('.') + os.sep + "texts-unconverted"+os.sep
if os.path.isdir(path):
    out_path = path.replace("texts-unconverted","texts")
    in_path = os.listdir(path)
    exported_path = path.replace("texts-unconverted","textures" +os.sep+ "unicode/")
    for file in in_path:
        lines = open(os.path.abspath(path +file), 'r', encoding='utf8').readlines()
        out = open(os.path.abspath(out_path +file), 'w')
        for line in lines:
            out.write("".join(map(char2unicode, list(line))))
        out.close()
    out_exported_characters = open(os.path.abspath(exported_path + "unifontCodepoints.hex"),'w')
    characters_to_load.sort()
    for character in characters_to_load:
        out_exported_characters.write(f"{ord(character)}".zfill(5)+"\n")
    out_exported_characters.close()
else:
    print("Use ./tools/unicode-converter.py {Directory}")
