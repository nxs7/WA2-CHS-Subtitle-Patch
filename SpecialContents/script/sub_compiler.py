import sys
import os
import yaml
from PIL import Image, ImageDraw, ImageFont


# from https://stackoverflow.com/questions/13319067/parsing-yaml-return-with-line-number
class SafeLineLoader(yaml.loader.SafeLoader):

    def construct_mapping(self, node, deep=False):
        mapping = super(SafeLineLoader, self).construct_mapping(node, deep=deep)
        mapping['__line__'] = node.start_mark.line + 1
        return mapping


SUB_FONT_FILENAME = 'font1.ttf'
SONG_FONT_FILENAME = 'font2.ttf'
FONT_SIZE = 28
FONT_STROKE = 2
FONT_OCCUPATION = FONT_SIZE + 2 * FONT_STROKE
FONT_PER_LINE = 30

if len(sys.argv) < 2:
    print('Usage:\npython sub_compiler.py <input_file>')
    exit(1)
if not os.path.isfile(sys.argv[1]):
    print(f"Input file '{sys.argv[1]}' not found.")
    exit(1)

with open(sys.argv[1], encoding='utf-8') as f:
    subdata = yaml.load(f, Loader=SafeLineLoader)

subCharset = set()
songCharset = set()
for key in ['voiceDrama', 'song']:
    if not key in subdata:
        print(f"Key '{key}' expected.")
        exit(1)
for dialogue in subdata['voiceDrama']:
    for key in ['id', 'chapter', 'content']:
        if not key in dialogue:
            print(f"Line {dialogue['__line__']}: voiceDrama/dialogue: Key '{key}' expected.")
            exit(1)
    for subtitle in dialogue['content']:
        for key in ['begin', 'end', 'text']:
            if not key in subtitle:
                print(f"Line {subtitle['__line__']}: voiceDrama/subtitle: Key '{key}' expected.")
                exit(1)
        for char in subtitle['text']:
            subCharset.add(char)
        if 'text2' in subtitle:
            for char in subtitle['text2']:
                subCharset.add(char)
for dialogue in subdata['song']:
    for key in ['id', 'chapter', 'content']:
        if not key in dialogue:
            print(f"Line {dialogue['__line__']}: song/dialogue: Key '{key}' expected.")
            exit(1)
    for subtitle in dialogue['content']:
        for key in ['begin', 'end', 'text']:
            if not key in subtitle:
                print(f"Line {subtitle['__line__']}: song/subtitle: Key '{key}' expected.")
                exit(1)
        for char in subtitle['text']:
            songCharset.add(char)

subCharset = list(subCharset)
subCharset.sort()
songCharset = list(songCharset)
songCharset.sort()
subCharmap = {}
songCharmap = {}
for i in range(len(subCharset)):
    subCharmap[subCharset[i]] = i
for i in range(len(songCharset)):
    songCharmap[songCharset[i]] = i

row_count = -(-len(subCharset) // FONT_PER_LINE)
library = Image.new('RGBA', (FONT_OCCUPATION * FONT_PER_LINE, FONT_OCCUPATION * row_count), (255, 0, 0, 0))
draw = ImageDraw.Draw(library)
font = ImageFont.truetype(SUB_FONT_FILENAME, FONT_SIZE)
for i in range(len(subCharset)):
    draw.text((FONT_STROKE + FONT_OCCUPATION * (i % FONT_PER_LINE), FONT_STROKE + FONT_OCCUPATION * (i // FONT_PER_LINE)), subCharset[i], 'white', font, stroke_width=FONT_STROKE, stroke_fill='black')
library.save('subfont.tga')

row_count = -(-len(songCharset) // FONT_PER_LINE)
library = Image.new('RGBA', (FONT_OCCUPATION * FONT_PER_LINE, FONT_OCCUPATION * row_count), (255, 0, 0, 0))
draw = ImageDraw.Draw(library)
font = ImageFont.truetype(SONG_FONT_FILENAME, FONT_SIZE)
for i in range(len(songCharset)):
    draw.text((FONT_STROKE + FONT_OCCUPATION * (i % FONT_PER_LINE), FONT_STROKE + FONT_OCCUPATION * (i // FONT_PER_LINE)), songCharset[i], 'royalblue', font, stroke_width=FONT_STROKE, stroke_fill='white')
library.save('songfont.tga')

with open('subtext.dat', 'wb') as f:
    # magic number
    f.write(b'xsn7')
    # voice drama count
    f.write(len(subdata['voiceDrama']).to_bytes(4, byteorder='little'))
    # voice dramas
    for dialogue in subdata['voiceDrama']:
        f.write((dialogue['id'] << 16 | dialogue['chapter']).to_bytes(4, byteorder='little'))
        # subtitle count
        f.write(len(dialogue['content']).to_bytes(4, byteorder='little'))
        for subtitle in dialogue['content']:
            f.write(subtitle['begin'].to_bytes(4, byteorder='little'))
            f.write(subtitle['end'].to_bytes(4, byteorder='little'))
            # text length
            f.write(len(subtitle['text']).to_bytes(4, byteorder='little'))
            for char in subtitle['text']:
                f.write(subCharmap[char].to_bytes(2, byteorder='little'))
            # text2 length
            if 'text2' in subtitle:
                f.write(len(subtitle['text2']).to_bytes(4, byteorder='little'))
                for char in subtitle['text2']:
                    f.write(subCharmap[char].to_bytes(2, byteorder='little'))
            else:
                f.write(b'\0\0\0\0')
    # song count
    f.write(len(subdata['song']).to_bytes(4, byteorder='little'))
    # songs
    for dialogue in subdata['song']:
        f.write((dialogue['id'] << 16 | dialogue['chapter']).to_bytes(4, byteorder='little'))
        # subtitle count
        f.write(len(dialogue['content']).to_bytes(4, byteorder='little'))
        for subtitle in dialogue['content']:
            f.write(subtitle['begin'].to_bytes(4, byteorder='little'))
            f.write(subtitle['end'].to_bytes(4, byteorder='little'))
            # text length
            f.write(len(subtitle['text']).to_bytes(4, byteorder='little'))
            for char in subtitle['text']:
                f.write(songCharmap[char].to_bytes(2, byteorder='little'))
