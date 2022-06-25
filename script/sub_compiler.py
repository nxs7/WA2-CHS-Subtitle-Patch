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


FONT_FILENAME = 'font.ttf'
FONT_SIZE = 28
FONT_STROKE = 2
FONT_OCCUPATION = FONT_SIZE + 2 * FONT_STROKE
FONT_PER_LINE = 20

if len(sys.argv) < 2:
    print('Usage:\npython sub_compiler.py <input_file>')
    exit(1)
if not os.path.isfile(sys.argv[1]):
    print(f"Input file '{sys.argv[1]}' not found.")
    exit(1)

with open(sys.argv[1], encoding='utf-8') as f:
    subdata = yaml.load(f, Loader=SafeLineLoader)

charset = set()
for key in ['soundEffect', 'voice']:
    if not key in subdata:
        print(f"Key '{key}' expected.")
        exit(1)
for dialogue in subdata['soundEffect']:
    for key in ['id', 'content']:
        if not key in dialogue:
            print(f"Line {dialogue['__line__']}: soundEffect/dialogue: Key '{key}' expected.")
            exit(1)
    for subtitle in dialogue['content']:
        for key in ['begin', 'end', 'text']:
            if not key in subtitle:
                print(f"Line {subtitle['__line__']}: soundEffect/subtitle: Key '{key}' expected.")
                exit(1)
            for char in subtitle['text']:
                charset.add(char)
for dialogue in subdata['voice']:
    for key in ['scene', 'id', 'content']:
        if not key in dialogue:
            print(f"Line {dialogue['__line__']}: voice/dialogue: Key '{key}' expected.")
            exit(1)
    for subtitle in dialogue['content']:
        for key in ['begin', 'end', 'text']:
            if not key in subtitle:
                print(f"Line {subtitle['__line__']}: voice/subtitle: Key '{key}' expected.")
                exit(1)
            for char in subtitle['text']:
                charset.add(char)

charset = list(charset)
charset.sort()
charmap = {}
for i in range(0, len(charset)):
    charmap[charset[i]] = i

row_count = -(-len(charset) // FONT_PER_LINE)
library = Image.new('RGBA', (FONT_OCCUPATION * FONT_PER_LINE, FONT_OCCUPATION * row_count), (255, 0, 0, 0))
draw = ImageDraw.Draw(library)
font = ImageFont.truetype(FONT_FILENAME, FONT_SIZE)
for i in range(0, len(charset)):
    draw.text((FONT_STROKE + FONT_OCCUPATION * (i % FONT_PER_LINE), FONT_STROKE + FONT_OCCUPATION * (i // FONT_PER_LINE)), charset[i], 'white', font, stroke_width=FONT_STROKE, stroke_fill='black')
library.save('subfont.tga')

with open('subtext.dat', 'wb') as f:
    # magic number
    f.write(b'nxs7')
    # dialogue count
    # sound effect and voice are combined
    f.write((len(subdata['soundEffect']) + len(subdata['voice'])).to_bytes(4, byteorder='little'))
    # sound effect dialogues
    for dialogue in subdata['soundEffect']:
        f.write(dialogue['id'].to_bytes(4, byteorder='little'))
        # subtitle count
        f.write(len(dialogue['content']).to_bytes(4, byteorder='little'))
        for subtitle in dialogue['content']:
            f.write(subtitle['begin'].to_bytes(4, byteorder='little'))
            f.write(subtitle['end'].to_bytes(4, byteorder='little'))
            # string length
            f.write(len(subtitle['text']).to_bytes(4, byteorder='little'))
            for char in subtitle['text']:
                f.write(charmap[char].to_bytes(2, byteorder='little'))
    # voice dialogues
    for dialogue in subdata['voice']:
        # combine scene id and voice id as new id
        f.write((dialogue['scene'] << 16 | dialogue['id']).to_bytes(4, byteorder='little'))
        # subtitle count
        f.write(len(dialogue['content']).to_bytes(4, byteorder='little'))
        for subtitle in dialogue['content']:
            f.write(subtitle['begin'].to_bytes(4, byteorder='little'))
            f.write(subtitle['end'].to_bytes(4, byteorder='little'))
            # string length
            f.write(len(subtitle['text']).to_bytes(4, byteorder='little'))
            for char in subtitle['text']:
                f.write(charmap[char].to_bytes(2, byteorder='little'))
